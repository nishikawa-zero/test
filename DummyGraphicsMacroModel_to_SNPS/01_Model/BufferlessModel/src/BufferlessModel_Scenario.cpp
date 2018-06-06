/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  BufferlessModel_Scenario.cpp
 * @brief Sample BufferlessModel_Scenario (source)
 */
#include "BufferlessModel_Scenario.h"


void
BufferlessModel_ScenarioThread(unsigned int model_id, unsigned int thread_id) {
  std::cout << __FUNCTION__ << " (thread_id=" << thread_id << ")" << std::endl;
  switch (thread_id) {
  case BufferlessModel_THREAD_ID_AR:
    BufferlessModel_SubScenarioAr(model_id, thread_id);
    break;
  case BufferlessModel_THREAD_ID_R:
    BufferlessModel_SubScenarioR(model_id, thread_id);
    break;
  case BufferlessModel_THREAD_ID_AW_W:
    BufferlessModel_SubScenarioAw_W(model_id, thread_id);
    break;
  default:
    std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
    assert(0);
    break;
  }
}

void
BufferlessModel_ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id) {
  switch (interrupt_id) {
  case 0:
    BufferlessModel_SubScenarioInterrupt0(model_id);
    break;
  case 1:
    BufferlessModel_SubScenarioInterrupt1(model_id);
    break;
  case 2:
    BufferlessModel_SubScenarioInterrupt2(model_id);
    break;
  case 3:
    BufferlessModel_SubScenarioInterrupt3(model_id);
    break;
  default:
    std::cout << "[ERROR] no interrupt scenario (interrupt_id=" << interrupt_id << ")" << endl;
    assert(0);
    break;
  }
}

void
BufferlessModel_SubScenarioAr(unsigned int model_id, unsigned int thread_id) {
  unsigned int ARID    = 0;
  unsigned int ARADDR  = 0;
  unsigned int ARLEN   = 0xF; /* 16burst */
  unsigned int ARSIZE  = 0x4; /* 16byte */
  unsigned int ARBURST = 1;   /* INCR */
  unsigned int ARLOCK  = 0;
  unsigned int ARCACHE = 0;
  unsigned int ARPROT  = 0;
  unsigned int ARUSER  = 0;

  unsigned int axi_if_id = BufferlessModel_AXI_IF_ID_0;

  unsigned int request_count = 0;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  /* 割り込み(0)待ち */
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " wait start event(interrupt0)" << std::endl;
  waitEvent(model_id, BufferlessModel_EVENT_ID_0);
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start event received" << std::endl;

  /* リードリクエスト送信 */
  while(request_count < BufferlessModel_REQUEST_LIMIT) {
    sendAr(model_id, axi_if_id, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
    ARADDR += (ARLEN + 1) * (1 << ARSIZE);
    request_count++;
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
BufferlessModel_SubScenarioR(unsigned int model_id, unsigned int thread_id) {
  unsigned int  RID   = 0;
  unsigned int  RLAST = 0;
  unsigned int  RRESP = 0;
  unsigned char rdata[BufferlessModel_BUSWIDTH_BYTE] = {0};

  unsigned int axi_if_id = BufferlessModel_AXI_IF_ID_0;
  unsigned int fifo_id   = BufferlessModel_FIFO_ID_0;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  while(1) {
    /* リードデータを取得 */
    receiveR(model_id, axi_if_id, &RID, &RLAST, &RRESP, rdata);

    /* リードデータをFIFOに格納 */
    writeFifo(model_id, fifo_id, rdata);
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}


void
BufferlessModel_SubScenarioAw_W(unsigned int model_id, unsigned int thread_id) {
  unsigned int AWID    = 0;
  unsigned int AWADDR  = 0;
  unsigned int AWLEN   = 0xF; /* 16burst */
  unsigned int AWSIZE  = 0x4; /* 16byte */
  unsigned int AWBURST = 1;   /* INCR */
  unsigned int AWLOCK  = 0;
  unsigned int AWCACHE = 0;
  unsigned int AWPROT  = 0;
  unsigned int AWUSER  = 0;
  unsigned int WID     = 0;
  unsigned int WLAST   = 0;
  unsigned char wdata[BufferlessModel_BUSWIDTH_BYTE];
  unsigned char wstrb[BufferlessModel_BUSWIDTH_BYTE];

  unsigned int axi_if_id = BufferlessModel_AXI_IF_ID_0;
  unsigned int fifo_id   = BufferlessModel_FIFO_ID_0;

  unsigned int burst_count = 0;
  unsigned int request_count = 0;

  /* init */
  for (unsigned int i = 0; i < BufferlessModel_BUSWIDTH_BYTE; i++) {
    wdata[i] = 0;
    wstrb[i] = 1;
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  while(1) {
    /* FIFOからデータを取得。データがなければ取得できるまで待つ */
    readFifo(model_id, fifo_id, wdata);

    /* ライトデータに必要な分のライトリクエストを送信 */
    if(burst_count % (AWLEN + 1) == 0) {
      sendAwWithNoWait(model_id, axi_if_id, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
      AWADDR += (AWLEN + 1) * (1 << AWSIZE);
      request_count++;
    }
    /* 最終データ情報付与 */
    /* ラッパーにて最終データ情報からB応答を生成しリクエスト完了させている */
    WLAST = (burst_count == AWLEN) ? 1 : 0;

    /* ライトデータ送信 */
    sendW(model_id, axi_if_id, WID, WLAST, wdata, wstrb);
    if (burst_count == AWLEN) {
      burst_count = 0;
      if(request_count == BufferlessModel_REQUEST_LIMIT) {
        break;
      }
    } else {
      burst_count++;
    }
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
BufferlessModel_SubScenarioInterrupt0(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt0" << std::endl;

  /* 割り込みを受信し、イベント通知 */
  if (getInterruptSignal(model_id, BufferlessModel_IN_PORT_ID_0) == 1) {
    notifyEvent(model_id, BufferlessModel_EVENT_ID_0);
  }
}

void
BufferlessModel_SubScenarioInterrupt1(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt1" << std::endl;
}

void
BufferlessModel_SubScenarioInterrupt2(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt2" << std::endl;
}

void
BufferlessModel_SubScenarioInterrupt3(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt3" << std::endl;
}

 
