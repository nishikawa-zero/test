/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3InitiatorBaseIf.h
 * @brief TLM AXI3 base interface class (source)
 */
#include "TlmAxi3InitiatorBaseIf.h"

namespace {
  unsigned int g_TlmAxi3InitiatorBaseIf_number;
}

/**
 * コンストラクタ
 *
 * コンストラクタ。
 **/
TlmAxi3InitiatorBaseIf::TlmAxi3InitiatorBaseIf(const char* name) :
  initiator_AW("initiator_AW"),
  initiator_W("initiator_W"),
  initiator_B("initiator_B"),
  initiator_AR("initiator_AR"),
  initiator_R("initiator_R"),
  _is_print(false)
{
	//std::cout << "IN : " << __FILE__ << " / " << __FUNCTION__ << std::endl;

  /* nb_transport_fwメソッドのInitiator(_B,_R)ソケットへの登録 */
  initiator_B.register_nb_transport_fw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_nb_transport_fw);
  initiator_R.register_nb_transport_fw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_nb_transport_fw);

  /* nb_transport_bwメソッドのinitiator(_AW,_W,_AR)ソケットへの登録 */
  initiator_AW.register_nb_transport_bw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AW_nb_transport_bw);
  initiator_W.register_nb_transport_bw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_W_nb_transport_bw);
  initiator_AR.register_nb_transport_bw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AR_nb_transport_bw);

  /* b_transportメソッドのinitiator(_B,_R)ソケットへの登録 */
  initiator_B.register_b_transport(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_b_transport);
  initiator_R.register_b_transport(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_b_transport);

  /* get_direct_mem_ptrメソッドのinitiator(_B,_R)ソケットへの登録 */
  initiator_B.register_get_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_get_direct_mem_ptr);
  initiator_R.register_get_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_get_direct_mem_ptr);

  /* invalidate_direct_mem_ptrメソッドのinitiator(_AW,_W,_AR)ソケットへの登録 */
  initiator_AW.register_invalidate_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AW_invalidate_direct_mem_ptr);
  initiator_W.register_invalidate_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_W_invalidate_direct_mem_ptr);
  initiator_AR.register_invalidate_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AR_invalidate_direct_mem_ptr);

  /* transport_dbgメソッドのinitiator(_B,_R)ソケットへの登録 */
  initiator_B.register_transport_dbg(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_transport_dbg);
  initiator_R.register_transport_dbg(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_transport_dbg);

  /* 各カウンタの初期化 */
  for (unsigned int i = 0; i < SizeOfInitiatorChannels; i++) {
    _nb_transport_bw_counter[i]           = 0;
    _invalidate_direct_mem_ptr_counter[i] = 0;
  }

  for (unsigned int i = 0; i < SizeOfTargetChannels; i++) {
    _nb_transport_fw_counter[i]    = 0;
    _b_transport_counter[i]        = 0;
    _get_direct_mem_ptr_counter[i] = 0;
    _transport_dbg_counter[i]      = 0;
  }

  /* I/F名の初期化 */
  if (name) {
    _name = name;
  } else {
    std::stringstream ss;
    ss << "TlmAxi3InitiatorBaseIf_" << g_TlmAxi3InitiatorBaseIf_number;
    ss >> _name;
    g_TlmAxi3InitiatorBaseIf_number++;
  }
}


/**
 * デストラクタ
 *
 * デストラクタ。
 **/
TlmAxi3InitiatorBaseIf::~TlmAxi3InitiatorBaseIf(void) {
}

/**
 * AXI-Bチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)仮想関数
 *
 * Forward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf :: not support nb_transport_fw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-Wチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)仮想関数
 *
 * Forward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf :: not support nb_transport_fw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AWI-AWチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)仮想関数
 *
 * Backward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t 遅延時間
 * @return 応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase&           phase,
                                                     sc_core::sc_time&         t)
{
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AWI-Wチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)仮想関数
 *
 * Backward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t 遅延時間
 * @return 応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t)
{
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AWI-ARチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)仮想関数
 *
 * Backward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t 遅延時間
 * @return 応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase&           phase,
                                                     sc_core::sc_time&         t)
{
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-Bチャネル initiatorソケット ブロッキング転送仮想関数
 *
 * ブロッキング転送を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
 **/
void
TlmAxi3InitiatorBaseIf::initiator_B_b_transport(tlm::tlm_generic_payload& trans,
                                                sc_core::sc_time&         delay_time) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support b_transport" << endl;
#endif
  return;
}

/**
 * AXI-Rチャネル initiatorソケット ブロッキング転送仮想関数
 *
 * ブロッキング転送を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
 **/
void
TlmAxi3InitiatorBaseIf::initiator_R_b_transport(tlm::tlm_generic_payload& trans,
                                                sc_core::sc_time&         delay_time) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support b_transport" << endl;
#endif
  return;
}

/**
 * AXI-Bチャネル向け initiatorソケット ダイレクトメモリポインタ取得仮想関数
 *
 * メモリポインタの取得を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                       tlm::tlm_dmi&             data) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support get_direct_mem_ptr" << endl;
#endif
  return false;
}

/**
 * AXI-Rチャネル向け initiatorソケット ダイレクトメモリポインタ取得仮想関数
 *
 * メモリポインタの取得を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                       tlm::tlm_dmi&             data) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support get_direct_mem_ptr" << endl;
#endif
  return false;
}

/**
 * AXI-AWチャネル向け initiatorソケット メモリポインタ使用負荷通知仮想関数
 *
 * イニシエータにメモリポインタの使用負荷を通知する。
 * @param start_range 開始アドレス
 * @param end_range 終了アドレス
 */
void
TlmAxi3InitiatorBaseIf::initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                               sc_dt::uint64 end_range) {
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-Wチャネル向け initiatorソケット メモリポインタ使用負荷通知仮想関数
 *
 * イニシエータにメモリポインタの使用負荷を通知する。
 * @param start_range 開始アドレス
 * @param end_range 終了アドレス
 */
void
TlmAxi3InitiatorBaseIf::initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                              sc_dt::uint64 end_range) {
#if defined(TLM_INITIATOR_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-ARチャネル向け initiatorソケット メモリポインタ使用負荷通知仮想関数
 *
 * イニシエータにメモリポインタの使用負荷を通知する。
 * @param start_range 開始アドレス
 * @param end_range 終了アドレス
 */
void
TlmAxi3InitiatorBaseIf::initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                               sc_dt::uint64 end_range) {
#if defined(TLM_INITIATOR_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-Bチャネル向け initiatorソケット デバッグ用転送仮想関数
 *
 * デバッグ用転送を行なう。
 * @param payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::initiator_B_transport_dbg(tlm::tlm_generic_payload& payload) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support transport_dbg" << endl;
#endif
  return 0;
}

/**
 * AXI-Rチャネル向け initiatorソケット デバッグ用転送仮想関数
 *
 * デバッグ用転送を行なう。
 * @param payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::initiator_R_transport_dbg(tlm::tlm_generic_payload& payload) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support transport_dbg" << endl;
#endif
  return 0;
}

/*
 * 中継関数
 */

/**
 * AXI-Bチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)中継関数
 *
 * Forward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::relay_initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t)
{
	//std::cout << "IN : " << __FILE__ << " / " << __FUNCTION__ << std::endl;

  tlm::tlm_sync_enum result;

  if (_is_print) {
    printForwardAxiPayload(B, trans);
  }

  result = initiator_B_nb_transport_fw(trans, phase, t);

  _nb_transport_fw_counter[B]++;

  return result;
}

/**
 * AXI-Rチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)中継関数
 *
 * Forward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::relay_initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
    printForwardAxiPayload(R, trans);
  }

  result = initiator_R_nb_transport_fw(trans, phase, t);

  _nb_transport_fw_counter[R]++;

  return result;
}

/**
 * AXI-AWチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)中継関数
 *
 * Backward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::relay_initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                           tlm::tlm_phase&           phase,
                                                           sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = initiator_AW_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[AW]++;

  return result;
}

/**
 * AXI-Wチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)中継関数
 *
 * Backward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::relay_initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = initiator_W_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[W]++;

  return result;
}

/**
 * AXI-ARチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)中継関数
 *
 * Backward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::relay_initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                           tlm::tlm_phase&           phase,
                                                           sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = initiator_AR_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[AR]++;

  return result;
}

/**
 * AXI-Bチャネル向け initiatorソケット ブロッキング転送中継関数
 *
 * ブロッキング転送の中継を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
 **/
void
TlmAxi3InitiatorBaseIf::relay_initiator_B_b_transport(tlm::tlm_generic_payload& payload,
                                                      sc_core::sc_time&         delay_time) {
  if (_is_print) {
  }

  initiator_B_b_transport(payload, delay_time);

  _b_transport_counter[B]++;
}

/**
 * AXI-Rチャネル向け initiatorソケット ブロッキング転送中継関数
 *
 * ブロッキング転送の中継を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
 **/
void
TlmAxi3InitiatorBaseIf::relay_initiator_R_b_transport(tlm::tlm_generic_payload& payload,
                                                      sc_core::sc_time&         delay_time) {
  if (_is_print) {
  }

  initiator_R_b_transport(payload, delay_time);

  _b_transport_counter[R]++;
}

/**
 * AXI-Bチャネル向け initiatorソケット ダイレクトメモリポインタ取得中継関数
 *
 * メモリポインタ取得の中継を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::relay_initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                             tlm::tlm_dmi&             data) {
  bool result;

  if (_is_print) {
  }

  result = initiator_B_get_direct_mem_ptr(payload, data);

  _get_direct_mem_ptr_counter[B]++;

  return result;
}

/**
 * AXI-Rチャネル向け initiatorソケット ダイレクトメモリポインタ取得中継関数
 *
 * メモリポインタ取得の中継を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::relay_initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                             tlm::tlm_dmi&             data) {
  bool result;

  if (_is_print) {
  }

  result = initiator_R_get_direct_mem_ptr(payload, data);

  _get_direct_mem_ptr_counter[R]++;

  return result;
}

/**
 * AXI-AWチャネル向けinitiatorソケット メモリポインタ使用負荷通知中継関数
 *
 * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
 * @param start_range 開始アドレス
 * @param end_range   終了アドレス
 */
void
TlmAxi3InitiatorBaseIf::relay_initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                     sc_dt::uint64 end_range) {
  if (_is_print) {
  }

  initiator_AW_invalidate_direct_mem_ptr(start_range, end_range);

  _invalidate_direct_mem_ptr_counter[AW]++;
}

/**
 * AXI-Wチャネル向けinitiatorソケット メモリポインタ使用負荷通知中継関数
 *
 * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
 * @param start_range 開始アドレス
 * @param end_range   終了アドレス
 */
void
TlmAxi3InitiatorBaseIf::relay_initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                    sc_dt::uint64 end_range) {
  if (_is_print) {
  }
  
  initiator_W_invalidate_direct_mem_ptr(start_range, end_range);
  
  _invalidate_direct_mem_ptr_counter[W]++;
}

/**
 * AXI-ARチャネル向けinitiatorソケット メモリポインタ使用負荷通知中継関数
 *
 * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
 * @param start_range 開始アドレス
 * @param end_range   終了アドレス
 */
void
TlmAxi3InitiatorBaseIf::relay_initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                     sc_dt::uint64 end_range) {
  if (_is_print) {
  }

  initiator_AR_invalidate_direct_mem_ptr(start_range, end_range);

  _invalidate_direct_mem_ptr_counter[AR]++;
}

/**
 * AXI-Bチャネル向け initiatorソケット デバッグ用転送中継関数
 *
 * デバッグ用転送の中継を行なう。
 * @param  payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::relay_initiator_B_transport_dbg(tlm::tlm_generic_payload& payload) {
  unsigned int result;

  if (_is_print) {
  }

  result = initiator_B_transport_dbg(payload);

  _transport_dbg_counter[B]++;

  return result;
}

/**
 * AXI-Rチャネル向け initiatorソケット デバッグ用転送中継関数
 *
 * デバッグ用転送の中継を行なう。
 * @param  payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::relay_initiator_R_transport_dbg(tlm::tlm_generic_payload& payload) {
  unsigned int result;

  if (_is_print) {
  }

  result = initiator_R_transport_dbg(payload);

  _transport_dbg_counter[R]++;

  return result;
}

/**
 * 送信AXI payload出力開始関数
 *
 * イニシエータから送信されるAXI payloadの出力を開始する
 */
void
TlmAxi3InitiatorBaseIf::startPrintForwardAxiPayload(void) {
  _is_print = true;
}

/**
 * 送信AXI payload出力停止関数
 *
 * イニシエータから送信されるAXI payloadの出力を停止する
 */
void
TlmAxi3InitiatorBaseIf::finishPrintForwardAxiPayload(void) {
  _is_print = false;
}

/**
 * 送信AXI payload出力関数
 *
 * イニシエータから送信されるAXI payloadの内容を出力する
 * @param initiator_channel 送信チャネル
 * @param payload           tlm_generic_payload
 **/
void
TlmAxi3InitiatorBaseIf::printForwardAxiPayload(unsigned int              initiator_channel,
                                               tlm::tlm_generic_payload& payload) {
  TlmAxi3Payload* axi(NULL);
  
  payload.get_extension(axi);
  
  if (axi) {
    std::cout << "[TlmAxi3InitiatorBaseIf] "
              << sc_time_stamp()
              << " @"
              << _name
              << ":";

    switch (initiator_channel) {
    case B:
      std::cout << std::dec
                << "  B = {count="
                << _nb_transport_fw_counter[B];
      std::cout << std::hex
                << ",RESP="
                << static_cast<unsigned int>(axi->getBRESP())
                << ",ID="
                << static_cast<unsigned int>(axi->getBID());
      std::cout << "}";
    case R:
      std::cout << std::dec
                << "  R = {count="
                << _nb_transport_fw_counter[R];
      std::cout << std::hex
                << ",LAST="
                << axi->getRLAST();
      for (unsigned int i = 0; i < axi->getByteSize(); ++i) {
        std::cout << ",DATA[" << i << "]="
                  << std::hex
                  << std::showbase
                  << (axi->getRDATA())[i]
                  << std::dec;
      }
      std::cout << ",RESP="
                << static_cast<unsigned int>(axi->getRRESP())
                << ",ID="
                << static_cast<unsigned int>(axi->getRID());
      std::cout << "}";
      break;
    default:
      break;
    }
  }
  
  std::cout << std::endl;
}

