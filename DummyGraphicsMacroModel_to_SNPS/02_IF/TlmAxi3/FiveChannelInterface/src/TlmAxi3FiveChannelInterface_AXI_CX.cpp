/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 201
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
#include "TlmAxi3FiveChannelInterface_AXI_CX.h"

namespace fj {

TlmAxi3FiveChannelInterface_AXI_CX::TlmAxi3FiveChannelInterface_AXI_CX(const sc_module_name name,
                                                                       const fj::uint32 id_width,
                                                                       const fj::uint32 bus_width,
                                                                       const bool no_receive_b,
                                                                       const bool no_receive_r,
                                                                       const fj::uint32 write_outstanding_limit,
                                                                       const fj::uint32 read_outstanding_limit):
  sc_module(name),
  m_id_width(id_width),
  m_bus_width(bus_width),
  m_no_receive_b(no_receive_b),
  m_no_receive_r(no_receive_r),
  m_write_outstanding_limit(write_outstanding_limit),
  m_read_outstanding_limit(read_outstanding_limit),
  m_id_mask(0),
  m_aw_outstanding_number(0),
  m_w_outstanding_number(0),
  m_ar_outstanding_number(0) {
  
  SC_THREAD(AwSender);
  SC_THREAD(WSender);
  SC_THREAD(ArSender);
  
  /* AXI ID マスク値の生成 */
  m_id_mask = 1;
  for (fj::uint32 i = 1; i < id_width; ++i) {
    m_id_mask = (m_id_mask << 1) + 1;
  }
  
  m_bus_width_byte = (m_bus_width + 7) / 8;
  
  /* TLMソケットの初期化 */
  m_primitive.initializeAw(this);
  m_primitive.initializeW(this);
  m_primitive.initializeB(this);
  m_primitive.initializeAr(this);
  m_primitive.initializeR(this);
  
  /* TLMソケットへ各AXIチャネル送信完了通知イベント登録 */
  m_primitive.registerReceiveAwResponseEvent(&e_aw_response_receive);
  m_primitive.registerReceiveWResponseEvent(&e_w_response_receive);
  m_primitive.registerReceiveArResponseEvent(&e_ar_response_receive);
}

int
TlmAxi3FiveChannelInterface_AXI_CX::sendAw(const unsigned int AWID,
                                           const unsigned int AWADDR,
                                           const unsigned int AWLEN,
                                           const unsigned int AWSIZE,
                                           const unsigned int AWBURST,
                                           const unsigned int AWLOCK,
                                           const unsigned int AWCACHE,
                                           const unsigned int AWPROT,
                                           const unsigned int AWUSER) {
  int result = 0;

  result = sendAwWithNoWait(AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);

  while (!m_aw_queue.empty()) {
    wait(e_aw_queue_pop);
  }

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::sendAwWithNoWait(const unsigned int AWID,
                                                     const unsigned int AWADDR,
                                                     const unsigned int AWLEN,
                                                     const unsigned int AWSIZE,
                                                     const unsigned int AWBURST,
                                                     const unsigned int AWLOCK,
                                                     const unsigned int AWCACHE,
                                                     const unsigned int AWPROT,
                                                     const unsigned int AWUSER) {
  int result = 0;

  /* AWIDチェック */
  if ((AWID & ~m_id_mask) != 0) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported AWID. (AWID="<< AWID << ", id_width="<< m_id_width << ")" << std::endl;
    result = -200;
  }

  /* AWLENチェック */
  if (32 <= AWLEN) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported AWLEN. (AWLEN="<< AWLEN << ")" << std::endl;
    result = -201;
  }

  /* AWSIZEチェック */
  if (8 <= AWSIZE) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported AWSIZE. (AWSIZE="<< AWSIZE << ")" << std::endl;
    result = -202;
  }

  /* AWBURSTチェック */
  if (4 <= AWBURST) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported AWBURST. (AWBURST="<< AWBURST << ")" << std::endl;
    result = -203;
  }

  /* AWLOCKチェック */
  if (4 <= AWLOCK) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported AWLOCK. (AWLOCK="<< AWLOCK << ")" << std::endl;
    result = -204;
  }

  /* AWCACHEチェック */
  if (16 <= AWCACHE) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported AWCACHE. (AWCACHE="<< AWCACHE << ")" << std::endl;
    result = -205;
  }

  /* AWPROTチェック */
  if (8 <= AWPROT) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported AWPROT. (AWPROT="<< AWPROT << ")" << std::endl;
    result = -206;
  }

  /* チェック結果がNGの場合にAssertion発生 */
  assert(0 <= result);

  /* AWペイロード生成 */
  AxiPayloadPtr aw_payload(new TlmAxi3Payload(m_bus_width_byte));
  aw_payload->setAWID(AWID);
  aw_payload->setAWADDR(AWADDR);
  aw_payload->setAWLEN(AWLEN);
  aw_payload->setAWSIZE(AWSIZE);
  aw_payload->setAWBURST(AWBURST);
  aw_payload->setAWLOCK(AWLOCK);
  aw_payload->setAWCACHE(AWCACHE);
  aw_payload->setAWPROT(AWPROT);
  aw_payload->setAWUSER(AWUSER);

  m_aw_queue.push(aw_payload);  
  
  /* AWペイロード送信スレッドの起動 */
  e_aw_sender.notify();

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::sendW(const unsigned int WID,
                                          const unsigned int WLAST,
                                          const unsigned char *wdata,
                                          const unsigned char *wstrb) {
  int result = 0;

  result = sendWWithNoWait(WID, WLAST, wdata, wstrb);
  
  while (!m_w_queue.empty()) {
    wait(e_w_queue_pop);
  }

  return result;
}


int
TlmAxi3FiveChannelInterface_AXI_CX::sendWWithNoWait(const unsigned int WID,
                                                    const unsigned int WLAST,
                                                    const unsigned char *wdata,
                                                    const unsigned char *wstrb) {
  int result = 0;
  
  /* WIDチェック */
  if ((WID & ~m_id_mask) != 0) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported WID. (WID="<< WID << ", id_width="<< m_id_width << ")" << std::endl;
    result = -200;
  }

  /* ライトデータのポインタチェック */
  if (!wdata) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: invalid write data pointer. (wdata="<< wdata << ")" << std::endl;
    result = -207;
  }

  /* ライトストローブのポインタチェック */
  if (!wstrb) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: invalid write strobe pointer. (wstrb="<< wstrb << ")" << std::endl;
    result = -208;
  }

  /* チェック結果がNGの場合にAssertion発生 */
  assert(0 <= result);

  /* Wペイロード生成 */
  AxiPayloadPtr w_payload(new TlmAxi3Payload(m_bus_width_byte));
  w_payload->setWID(WID);
  w_payload->setWLAST(WLAST);
  w_payload->setWDATA(wdata);
  w_payload->setWSTRB(wstrb);

  m_w_queue.push(w_payload);  
  
  /* Wペイロード送信スレッドの起動 */
  e_w_sender.notify();

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveB(unsigned int *BID,
                                             unsigned int *BRESP) {
  int result = 0;

  if (m_no_receive_b) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get B check constructor's parameter." << std::endl;
    result = -1;
  } else {
    int is_get_b = receiveBWithNoWait(BID, BRESP);

    while (!is_get_b) {
      wait(e_b_queue_push);
      is_get_b = receiveBWithNoWait(BID, BRESP);
    }
  }

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveBWithNoWait(unsigned int *BID,
                                                       unsigned int *BRESP) {
  int result = 0;

  /* レスポンス破棄モード時に本APIがコールされた場合はWarning出力 */
  if (m_no_receive_b) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get B check constructor's parameter." << std::endl;
    result = -1;
  } else {
    /* Bペイロードキューが空か確認 */
    if (m_b_queue.empty()) {
      result = -1;
    } else {
      /* Bペイロートの取得 */
      AxiPayloadPtr b_payload = m_b_queue.front();
      m_b_queue.pop_front();
      
      *BID = b_payload->getBID();
      *BRESP = b_payload->getBRESP();
    }
  }
  
  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveBById(const unsigned int BID,
                                                 unsigned int *BRESP) {
  int result = 0;

  if (m_no_receive_b) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get B check constructor's parameter." << std::endl;
    result = -1;
  } else {
    int is_get_b = receiveBByIdWithNoWait(BID, BRESP);;

    while (!is_get_b) {
      wait(e_b_queue_push);
      is_get_b = receiveBByIdWithNoWait(BID, BRESP);
    }
  }

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveBByIdWithNoWait(const unsigned int BID,
                                                           unsigned int *BRESP) {
  int result = 0;

  /* レスポンス破棄モード時に本APIがコールされた場合はWarning出力 */
  if (m_no_receive_b) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get B check constructor's parameter." << std::endl;
    result = -1;
  } else {
    /* Bペイロードキューが空か確認 */
    if (m_b_queue.empty()) {
      result = -1;
    } else {
      std::list<AxiPayloadPtr>::iterator itr = m_b_queue.begin();

      while (itr != m_b_queue.end()) {
        if ((*itr)->getBID() == BID) {
          break;
        } else {
          ++itr;
        }
      }

      if (itr != m_b_queue.end()) {
        *BRESP = (*itr)->getBRESP();
        m_b_queue.erase(itr);
      } else {
        result = -1;
      }
    }
  }
  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::sendAr(const unsigned int ARID,
                                           const unsigned int ARADDR,
                                           const unsigned int ARLEN,
                                           const unsigned int ARSIZE,
                                           const unsigned int ARBURST,
                                           const unsigned int ARLOCK,
                                           const unsigned int ARCACHE,
                                           const unsigned int ARPROT,
                                           const unsigned int ARUSER) {
  int result = 0;

  result = sendArWithNoWait(ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);

  while (!m_ar_queue.empty()) {
    wait(e_ar_queue_pop);
  }

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::sendArWithNoWait(const unsigned int ARID,
                                                     const unsigned int ARADDR,
                                                     const unsigned int ARLEN,
                                                     const unsigned int ARSIZE,
                                                     const unsigned int ARBURST,
                                                     const unsigned int ARLOCK,
                                                     const unsigned int ARCACHE,
                                                     const unsigned int ARPROT,
                                                     const unsigned int ARUSER) {
  int result = 0;

  /* ARIDチェック */
  if ((ARID & ~m_id_mask) != 0) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported ARID. (ARID="<< ARID << ", id_width="<< m_id_width << ")" << std::endl;
    result = -200;
  }

  /* ARLENチェック */
  if (32 <= ARLEN) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported ARLEN. (ARLEN="<< ARLEN << ")" << std::endl;
    result = -201;
  }

  /* ARSIZEチェック */
  if (8 <= ARSIZE) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported ARSIZE. (ARSIZE="<< ARSIZE << ")" << std::endl;
    result = -202;
  }

  /* ARBURSTチェック */
  if (4 <= ARBURST) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported ARBURST. (ARBURST="<< ARBURST << ")" << std::endl;
    result = -203;
  }

  /* ARLOCKチェック */
  if (4 <= ARLOCK) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported ARLOCK. (ARLOCK="<< ARLOCK << ")" << std::endl;
    result = -204;
  }

  /* ARCACHEチェック */
  if (16 <= ARCACHE) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported ARCACHE. (ARCACHE="<< ARCACHE << ")" << std::endl;
    result = -205;
  }

  /* ARPROTチェック */
  if (8 <= ARPROT) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Error: Not supported ARPROT. (ARPROT="<< ARPROT << ")" << std::endl;
    result = -206;
  }

  /* チェック結果がNGの場合にAssertion発生 */
  assert(0 <= result);

  /* ARペイロード生成 */
  AxiPayloadPtr ar_payload(new TlmAxi3Payload(m_bus_width_byte));
  ar_payload->setARID(ARID);
  ar_payload->setARADDR(ARADDR);
  ar_payload->setARLEN(ARLEN);
  ar_payload->setARSIZE(ARSIZE);
  ar_payload->setARBURST(ARBURST);
  ar_payload->setARLOCK(ARLOCK);
  ar_payload->setARCACHE(ARCACHE);
  ar_payload->setARPROT(ARPROT);
  ar_payload->setARUSER(ARUSER);

  m_ar_queue.push(ar_payload);  
  
  /* ARペイロード送信スレッドの起動 */
  e_ar_sender.notify();

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveR(unsigned int *RID,
                                             unsigned int *RLAST,
                                             unsigned int *RRESP,
                                             unsigned char *rdata) {
  int result = 0;

  if (m_no_receive_r) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get R check constructor's parameter." << std::endl;
    result = -1;
  } else {
    int is_get_r = receiveRWithNoWait(RID, RLAST, RRESP, rdata);

    while (is_get_r != 0) {
      wait(e_r_queue_push);
      is_get_r = receiveRWithNoWait(RID, RLAST, RRESP, rdata);
    }
  }

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveRWithNoWait(unsigned int *RID,
                                                       unsigned int *RLAST,
                                                       unsigned int *RRESP,
                                                       unsigned char *rdata) {
  int result = 0;

  /* レスポンス破棄モード時に本APIがコールされた場合はWarning出力 */
  if (m_no_receive_r) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get R check constructor's parameter." << std::endl;
    result = -1;
  } else {
    /* Rペイロードキューが空か確認 */
    if (m_r_queue.empty()) {
      result = -1;
    } else {
      /* Rペイロートの取得 */
      AxiPayloadPtr r_payload = m_r_queue.front();
      m_r_queue.pop_front();

      *RID = r_payload->getRID();
      *RLAST = r_payload->getRLAST();
      *RRESP = r_payload->getRRESP();
      
      unsigned char *tmp_rdata = r_payload->getRDATA();
      for (unsigned int i = 0; i < m_bus_width_byte; ++i) {
        rdata[i] = tmp_rdata[i];
      }
    }
  }

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveRById(const unsigned int RID,
                                                 unsigned int *RLAST,
                                                 unsigned int *RRESP,
                                                 unsigned char *rdata) {
  int result = 0;

  if (m_no_receive_r) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get R check constructor's parameter." << std::endl;
    result = -1;
  } else {
    int is_get_r = receiveRByIdWithNoWait(RID, RLAST, RRESP, rdata);

    while (is_get_r != 0) {
      wait(e_r_queue_push);
      is_get_r = receiveRByIdWithNoWait(RID, RLAST, RRESP, rdata);
    }
  }

  return result;
}

int
TlmAxi3FiveChannelInterface_AXI_CX::receiveRByIdWithNoWait(const unsigned int RID,
                                                           unsigned int *RLAST,
                                                           unsigned int *RRESP,
                                                           unsigned char *rdata) {
  int result = 0;

  /* レスポンス破棄モード時に本APIがコールされた場合はWarning出力 */
  if (m_no_receive_r) {
    std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: cannot get R check constructor's parameter." << std::endl;
    result = -1;
  } else {
    /* Rペイロードキューが空か確認 */
    if (m_r_queue.empty()) {
      result = -1;
    } else {
      std::list<AxiPayloadPtr>::iterator itr = m_r_queue.begin();

      while (itr != m_r_queue.end()) {
        if ((*itr)->getRID() == RID) {
          break;
        } else {
          ++itr;
        }
      }

      if (itr != m_r_queue.end()) {
        *RLAST = (*itr)->getRLAST();
        *RRESP = (*itr)->getRRESP();

        unsigned char *tmp_rdata = (*itr)->getRDATA();
        for (unsigned int i = 0; i < m_bus_width_byte; i++) {
          rdata[i] = tmp_rdata[i];
        }

        m_r_queue.erase(itr);
      } else {
        result = -1;
      }
    }
  }

  return result;
}

void
TlmAxi3FiveChannelInterface_AXI_CX::AwSender(void)
{
  while(1) {
    wait(e_aw_sender);

    /* AWペイロードキューが空になるまで動作継続 */
    while (!m_aw_queue.empty()) {
      /* ライトアウトスタンディング数の制限の有無を確認
       * 制限がある場合はライトアウトスタンディング数の空きが出るまでwait
       */
      if (m_write_outstanding_limit != 0) {
        while (m_write_outstanding_limit <= m_aw_outstanding_number) {
          wait(e_decrease_write_outstanding_number);
        }
      }

      /* AWペイロードをTLMソケットに送信 */
      m_primitive.sendAwRequest(m_aw_queue.front().get());

      /* 送信完了待ち */
      wait(e_aw_response_receive);

      /* AWペイロードアウトスタンディング数インクリメント */
      ++m_aw_outstanding_number;

      m_aw_queue.pop();
      e_aw_queue_pop.notify();
    }
  }
}

void
TlmAxi3FiveChannelInterface_AXI_CX::WSender(void) {
  while(1) {
    wait(e_w_sender);

    /* Wペイロードキューが空になるまで動作継続 */
    while (!m_w_queue.empty()) {
      /* ライトアウトスタンディング数の制限の有無を確認
       * 制限がある場合はライトアウトスタンディング数の空きが出るまでwait
       */
      if (m_write_outstanding_limit != 0) {
        while (m_write_outstanding_limit <= m_w_outstanding_number) {
          wait(e_decrease_write_outstanding_number);
        }
      }

      /* WペイロードをTLMソケットに送信 */
      m_primitive.sendWRequest(m_w_queue.front().get());

      /* 送信完了待ち */
      wait(e_w_response_receive);

      /* WLASTならばWペイロードアウトスタンディング数インクリメント */
      if (m_w_queue.front()->getWLAST() == 1) {
        ++m_w_outstanding_number;
      }

      m_w_queue.pop();
      e_w_queue_pop.notify();
    }
  }
}

void
TlmAxi3FiveChannelInterface_AXI_CX::ArSender(void) {
  while(1) {
    wait(e_ar_sender);

    /* ARペイロードキューが空になるまで動作継続 */
    while (!m_ar_queue.empty()) {
      /* リードアウトスタンディング数の制限の有無を確認
       * 制限がある場合はリードアウトスタンディング数の空きが出るまでwait
       */
      if (m_read_outstanding_limit != 0) {
        while (m_read_outstanding_limit <= m_ar_outstanding_number) {
          wait(e_decrease_read_outstanding_number);
        }
      }

      /* ARペイロードをTLMソケットに送信 */
      m_primitive.sendArRequest(m_ar_queue.front().get());

      /* 送信完了待ち */
      wait(e_ar_response_receive);

      /* ARペイロードアウトスタンディング数インクリメント */
      ++m_ar_outstanding_number;

      m_ar_queue.pop();
      e_ar_queue_pop.notify();
    }
  }
}

void
TlmAxi3FiveChannelInterface_AXI_CX::receiveBRequest(TlmAxi3Payload *axi_payload_b) {
  AxiPayloadPtr b_payload(new TlmAxi3Payload(m_bus_width_byte));
  b_payload->copy_from(*axi_payload_b);
  
  if (!m_no_receive_b) {  
    /* Bペイロードキューに取得したBペイロードを格納 */
    m_b_queue.push_back(b_payload);
    e_b_queue_push.notify();
  }

  /* TLMソケットへBペイロード受信を通知 */
  //m_primitive.sendBResponse(axi_payload_b);
  m_primitive.sendBResponse(b_payload.get());

  /* AWペイロードアウトスタンディング数デクリメント
   * Wペイロードアウトスタンディング数デクリメント
   */
  assert ((m_write_outstanding_limit == 0) || (m_aw_outstanding_number>0));
  assert ((m_write_outstanding_limit == 0) || (m_w_outstanding_number>0));

  --m_aw_outstanding_number;
  --m_w_outstanding_number;
  e_decrease_write_outstanding_number.notify();
}

void
TlmAxi3FiveChannelInterface_AXI_CX::receiveRRequest(TlmAxi3Payload *axi_payload_r) {

  AxiPayloadPtr r_payload(new TlmAxi3Payload(m_bus_width_byte));
  r_payload->copy_from(*axi_payload_r);

  if (!m_no_receive_r) {
    /* Rペイロードキューに取得したRペイロードを格納 */
    m_r_queue.push_back(r_payload);
    e_r_queue_push.notify();
  }

  /* TLMソケットへRペイロード受信を通知 */
  //m_primitive.sendRResponse(axi_payload_r);
  m_primitive.sendRResponse(r_payload.get());

  /* RLASTならばARペイローアウトスタンディング数デクリメント */
  if (r_payload->getRLAST() == 1) {
    assert ((m_read_outstanding_limit == 0) || (m_ar_outstanding_number>0));
    --m_ar_outstanding_number;
    e_decrease_read_outstanding_number.notify();
  }
}

} /* namespace fj */
