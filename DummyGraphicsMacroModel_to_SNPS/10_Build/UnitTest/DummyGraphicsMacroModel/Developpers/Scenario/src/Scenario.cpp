/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  Scenario.cpp
 * @brief Sample Scenario (source)
 */
#include "Scenario.h"

namespace {
  unsigned int g_vcd_id = 0;
  unsigned int g_event_switch_output_buffer_id = 0;
}

void
ScenarioThread(unsigned int model_id, unsigned int thread_id) {
  switch (thread_id) {
  case 0:
    SubScenarioRchAr(model_id);
    break;
  case 1:
    SubScenarioRchR(model_id);
    break;
  case 2:
    SubScenarioWchAw(model_id);
    break;
  case 3:
    SubScenarioWchW(model_id);
    break;
  case 4:
    SubScenarioCore(model_id);
    break;
  default:
    std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
    assert(0);
    break;
  }
}

void
ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id) {
  switch (interrupt_id) {
  case 0:
    SubScenarioInterrupt0(model_id);
    break;
  case 1:
    SubScenarioInterrupt1(model_id);
    break;
  case 2:
    SubScenarioInterrupt2(model_id);
    break;
  case 3:
    SubScenarioInterrupt3(model_id);
    break;
  default:
    std::cout << "[ERROR] no interrupt scenario (interrupt_id=" << interrupt_id << ")" << endl;
    assert(0);
    break;
  }

}

void
SubScenarioRchAr(unsigned int model_id) {
  unsigned int ARID = 0;
  unsigned int ARADDR = 0;
  unsigned int ARLEN = SCENARIO_BURST_LENGTH - 1;
  unsigned int ARSIZE = 0x3; /* 8-Byte*/
  unsigned int ARBURST = 1; /* INCR */
  unsigned int ARLOCK = 0;
  unsigned int ARCACHE = 0;
  unsigned int ARPROT = 0;
  unsigned int ARUSER = 0;

  unsigned int axi_if_id = 0;
  unsigned int input_buffer_id = SENARIO_INPUT_BUFFER_ID;

  unsigned int send_ar_kind = 0;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " waitEvent(" << SCENARIO_EVENT_START << ")" << std::endl;
  waitEvent(model_id, SCENARIO_EVENT_START);

  enableLogging(model_id);
  
  for (unsigned int j = 0; j < SCENARIO_LOOP;) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitWriteBufferStatus(" << input_buffer_id << "," << SCENARIO_BUFFER_STATUS_EMPTY << ")" << std::endl;
    waitWriteBufferStatus(model_id, input_buffer_id, SCENARIO_BUFFER_STATUS_EMPTY);

    for (unsigned int i = 0; i < ((SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH) / (SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH)); ++i) {
      int result;
      switch (send_ar_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " sendAr" << std::endl;
        sendAr(model_id, SCENARIO_AXI_IF_ID, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " sendArWithNoWait(" << axi_if_id << ")" << std::endl;
          result = sendArWithNoWait(model_id, SCENARIO_AXI_IF_ID, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
          
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      }
      
      send_ar_kind = (send_ar_kind + 1) % 0x2;
      
      ARADDR += SCENARIO_BUFFER_WIDTH * SCENARIO_BURST_LENGTH;
      ++j;
    }

#if 1
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitWriteBufferStatus(" << input_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    waitWriteBufferStatus(model_id, input_buffer_id, SCENARIO_BUFFER_STATUS_FULL);
#endif


  }
  
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
SubScenarioRchR(unsigned int model_id) {
  unsigned int RID = 0;
  unsigned int RLAST;
  unsigned int RRESP;
  unsigned char rdata[SCENARIO_BURST_SIZE];
  
  unsigned int stored_byte = 0;
  unsigned int input_buffer_id = SENARIO_INPUT_BUFFER_ID;

  unsigned int write_buffer_kind = 0;
  unsigned int receive_r_kind = 0;
  
  unsigned int stored_byte_vcd_id = g_vcd_id++;
  
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;
  
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " makeVcdValue(rch1_storeed_byte)" << std::endl;
  makeVcdValue(model_id, "rch1_storeed_byte", stored_byte_vcd_id, 32, 0);

  while (1) {
    while (stored_byte < (SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH)) {
      int result;
      switch (receive_r_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " receiveR" << std::endl;
        receiveR(model_id, SCENARIO_AXI_IF_ID, &RID, &RLAST, &RRESP, rdata);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " receiveRWithNoWait" << std::endl;
          result = receiveRWithNoWait(model_id, SCENARIO_AXI_IF_ID, &RID, &RLAST, &RRESP, rdata);
          
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      case 2:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " receiveRById" << std::endl;
        receiveRById(model_id, SCENARIO_AXI_IF_ID, RID, &RLAST, &RRESP, rdata);
        break;
      case 3:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " receiveRByIdWithNoWait" << std::endl;
          result = receiveRByIdWithNoWait(model_id, SCENARIO_AXI_IF_ID, RID, &RLAST, &RRESP, rdata);

          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      }

      receive_r_kind = (receive_r_kind + 1) % 0x4;

      switch (write_buffer_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " writeBuffer(" << input_buffer_id << ")" << std::endl;
        writeBuffer(model_id, input_buffer_id, rdata);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " writeBufferWithNoWait(" << input_buffer_id << ")" << std::endl;
          result = writeBufferWithNoWait(model_id, input_buffer_id, rdata);
          
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitCoreCycle(1)" << std::endl;
          waitCoreCycle(model_id, 1);
        } while (result != 0);
        break;
      }

      write_buffer_kind = (write_buffer_kind + 1) % 0x2;
      stored_byte += SCENARIO_BURST_SIZE;

      dumpSimulationTime(model_id);
      std::cout << __FUNCTION__ << " setVcdValue(stored_byte=" << stored_byte <<")" << std::endl;
      setVcdValue(model_id, stored_byte_vcd_id, stored_byte);
    }

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " switchWriteBuffer(" << input_buffer_id << ")" << std::endl;
    switchWriteBuffer(model_id, input_buffer_id);

    stored_byte = 0;
  }
   
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
SubScenarioWchAw(unsigned int model_id) {
  unsigned int AWID = 0;
  unsigned int AWADDR = 0x1000;
  unsigned int AWLEN = SCENARIO_BURST_LENGTH - 1;
  unsigned int AWSIZE = 0x3; /* 8-Byte*/
  unsigned int AWBURST = 1; /* INCR */
  unsigned int AWLOCK = 0;
  unsigned int AWCACHE = 0;
  unsigned int AWPROT = 0;
  unsigned int AWUSER = 0;

  unsigned int output_buffer_id = SENARIO_OUTPUT_BUFFER_ID;

  unsigned int send_aw_kind = 0;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  while (1) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitReadBufferStatus(" << output_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    waitReadBufferStatus(model_id, output_buffer_id, SCENARIO_BUFFER_STATUS_FULL);
    
    for (unsigned int i = 0; i < ((SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH) / (SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH)); ++i) {
      int result;
      switch (send_aw_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " sendAw" << std::endl;
        sendAw(model_id, SCENARIO_AXI_IF_ID, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " sendAwWithNoWait" << std::endl;
          result = sendAw(model_id, SCENARIO_AXI_IF_ID, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      }
      AWADDR += SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH;
      send_aw_kind = (send_aw_kind + 1) % 2;
    }

#if 1
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitReadBufferStatus(" << output_buffer_id << "," << SCENARIO_BUFFER_STATUS_EMPTY << ")" << std::endl;
    waitReadBufferStatus(model_id, output_buffer_id, SCENARIO_BUFFER_STATUS_EMPTY);
#endif
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
SubScenarioWchW(unsigned int model_id) {
  unsigned int WID = 0;
  unsigned int WLAST;
  unsigned char wdata[SCENARIO_BURST_SIZE];
  unsigned char wstrb[SCENARIO_BURST_SIZE];

  unsigned int loaded_byte = 0;
  unsigned int output_buffer_id = SENARIO_OUTPUT_BUFFER_ID;
  unsigned int burst_count = 0;
  unsigned int transfered_byte = 0;

  unsigned int read_output_buffer_kind = 0;
  unsigned int send_w_kind = 0;

  unsigned int transfered_byte_vcd_id = g_vcd_id++;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  for (unsigned int i = 0; i < SCENARIO_BURST_SIZE; ++i) {
    wstrb[i] = 0xFF;
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " makeVcdValue(wch1_transfered_byte)" << std::endl;
  makeVcdValue(model_id, "wch1_transfered_byte", transfered_byte_vcd_id, 32, 0);

  while (1) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitReadBufferStatus(" << output_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    waitReadBufferStatus(model_id, output_buffer_id, SCENARIO_BUFFER_STATUS_FULL);

    while (loaded_byte < (SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH)) {
      int result;
      switch (read_output_buffer_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " readBuffer(" << output_buffer_id << ")" << std::endl;
        readBuffer(model_id, output_buffer_id, wdata);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " readBufferWithNoWait(" << output_buffer_id << ")" << std::endl;
          result = readBufferWithNoWait(model_id, output_buffer_id, wdata);

          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitCoreCycle(1)" << std::endl;
          waitCoreCycle(model_id, 1);
        } while (result != 0);
        break;
      }    
      loaded_byte += SCENARIO_BURST_SIZE;
      read_output_buffer_kind = (read_output_buffer_kind + 1) % 2;

      ++burst_count;
      if (burst_count ==  SCENARIO_BURST_LENGTH) {
        WLAST = 1;
        burst_count = 0;
      } else {
        WLAST = 0;
      }
      switch (send_w_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " sendW" << std::endl;
        sendW(model_id, SCENARIO_AXI_IF_ID, WID, WLAST, wdata, wstrb);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " sendWWithNoWait" << std::endl;
          result = sendWWithNoWait(model_id, SCENARIO_AXI_IF_ID, WID, WLAST, wdata, wstrb);
          
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      }
      transfered_byte += SCENARIO_BURST_SIZE;
      send_w_kind = (send_w_kind + 1) % 2;

      dumpSimulationTime(model_id);
      std::cout << __FUNCTION__ << " setVcdValue(transfered_byte=" << transfered_byte <<")" << std::endl;
      setVcdValue(model_id, transfered_byte_vcd_id, transfered_byte);
    }


    loaded_byte = 0;

    if (SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH * SCENARIO_LOOP <= transfered_byte) {
      break;
    } else {
      dumpSimulationTime(model_id);
      std::cout << __FUNCTION__ << " switchReadBuffer(" << output_buffer_id << ")" << std::endl;
      switchReadBuffer(model_id, output_buffer_id);
    }
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " waitAxiCycle(1000)" << std::endl;
  waitAxiCycle(model_id, 1000);

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " disableLogging()" << std::endl;
  disableLogging(model_id);

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " waitAxiCycle(1000)" << std::endl;
  waitAxiCycle(model_id, 1000);

  sc_stop();

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
SubScenarioCore(unsigned int model_id) {
  unsigned int loaded_byte = 0;
  unsigned int stored_byte = 0;
  unsigned int input_buffer_id = SENARIO_INPUT_BUFFER_ID;
  unsigned int output_buffer_id = SENARIO_OUTPUT_BUFFER_ID;
  unsigned char data[SCENARIO_BURST_SIZE];
  unsigned int thread_id = 0;

  unsigned int read_input_buffer_kind = 0;
  unsigned int write_output_buffer_kind = 0;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " setThreadStatus(" << model_id << "," << thread_id << ","  << SCENARIO_CORE_STATUS_INIT << ")" << std::endl;
  setThreadStatus(model_id, thread_id, SCENARIO_CORE_STATUS_INIT);

  while (1) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setThreadStatus(" << model_id << "," << thread_id << ","  << SCENARIO_CORE_STATUS_BUSY << ")" << std::endl;
    setThreadStatus(model_id, thread_id, SCENARIO_CORE_STATUS_BUSY);

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitReadBufferStatus(" << input_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    waitReadBufferStatus(model_id, input_buffer_id, SCENARIO_BUFFER_STATUS_FULL);
    
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitWriteBufferStatus(" << output_buffer_id << "," << SCENARIO_BUFFER_STATUS_EMPTY << ")" << std::endl;
    waitWriteBufferStatus(model_id, output_buffer_id, SCENARIO_BUFFER_STATUS_EMPTY);

    while (loaded_byte < (SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH)) { 
      int result;
      switch (read_input_buffer_kind) {
      default:
      case 0:        
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " readBuffer(" << input_buffer_id << ")" << std::endl;
        readBuffer(model_id, input_buffer_id, data);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " readBufferWithNoWait(" << input_buffer_id << ")" << std::endl;
          result = readBufferWithNoWait(model_id, input_buffer_id, data);

          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitCoreCycle(1)" << std::endl;
          waitCoreCycle(model_id, 1);
        } while (result != 0);
        break;
      }

      read_input_buffer_kind = (read_input_buffer_kind + 1) % 0x2;
      loaded_byte += 8;

      dumpSimulationTime(model_id);
      std::cout << __FUNCTION__ << " waitCoreCycle(10)" << std::endl;
      waitCoreCycle(model_id, 10);
      
      switch (write_output_buffer_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " writeBuffer(" << output_buffer_id << ")" << std::endl;
        writeBuffer(model_id, output_buffer_id, data);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " writeBuffer(" << output_buffer_id << ")" << std::endl;
          result = writeBuffer(model_id, output_buffer_id, data);

          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitCoreCycle(10)" << std::endl;
          waitCoreCycle(model_id, 10);
        } while (result != 0);
        break;
      }

      write_output_buffer_kind = (write_output_buffer_kind + 1) % 0x2;
      stored_byte += 8;
    }

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " switchWriteBuffer(" << output_buffer_id << ")" << std::endl;
    switchWriteBuffer(model_id, output_buffer_id);

    stored_byte = 0;
    
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " switchReadBuffer(" << input_buffer_id << ")" << std::endl;
    switchReadBuffer(model_id, input_buffer_id);

    loaded_byte = 0;

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setThreadStatus(" << model_id << "," << thread_id << ","  << SCENARIO_CORE_STATUS_IDLE << ")" << std::endl;
    setThreadStatus(model_id, thread_id, SCENARIO_CORE_STATUS_IDLE);
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
SubScenarioInterrupt0(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt0" << std::endl;

  if (getInterruptSignal(model_id, 0) == 1) {
    std::cout << "---- display parameters start ----------------" << std::endl;
    std::cout << "model_id=" << model_id << std::endl;
    std::cout << "number_of_ax_if=" << getNumberOfAxiIf(model_id) << std::endl;
    std::cout << "number_of_interrupt=" << getNumberOfInterrupt(model_id) << std::endl;
    std::cout << "number_of_output_signal=" << getNumberOfOutputSignal(model_id) << std::endl;
    std::cout << "number_of_buffer=" << getNumberOfBuffer(model_id) << std::endl;
    std::cout << "number_of_thread=" << getNumberOfThread(model_id) << std::endl;
    std::cout << "number_of_read_outstanding=" << getNumberOfReadOutStanding(model_id) << std::endl;
    std::cout << "number_of_write_outstanding=" << getNumberOfWriteOutStanding(model_id) << std::endl;
    std::cout << "no_r_receive=" << getNoRReceive(model_id) << std::endl;
    std::cout << "no_b_receive=" << getNoBReceive(model_id) << std::endl;
    std::cout << "buffer_parameter_file_name=" << getBufferParameterFileName(model_id) << std::endl;
    std::cout << "fifo_parameter_file_name=" << getFifoParameterFileName(model_id) << std::endl;
    std::cout << "output_vcd_file_name=" << getOutputVcdFileName(model_id) << std::endl;
    std::cout << "output_csv_file_name=" << getOutputCsvFileName(model_id) << std::endl;
    std::cout << "output_summary_file_name=" << getOutputSummaryFileName(model_id) << std::endl;
    std::cout << "time_unit=" << getTimeUnit(model_id) << std::endl;
    std::cout << "axi_clock=" << getAxiClock(model_id) << std::endl;
    std::cout << "core_clock=" << getCoreClock(model_id) << std::endl;
    for (unsigned int i = 0; i < getNumberOfBuffer(model_id); ++i)  {
      std::cout << "buffer_" << i << ".number_of_internal_buffer=" << getNumberOfInternalBuffer(model_id, i) << std::endl;
      std::cout << "buffer_" << i << ".width=" << getBufferWidth(model_id, i) << std::endl;
      std::cout << "buffer_" << i << ".depth=" << getBufferDepth(model_id, i) << std::endl;
      std::cout << "buffer_" << i << ".write_clock=" << getBufferWriteClock(model_id, i) << std::endl;
      std::cout << "buffer_" << i << ".read_clock=" << getBufferReadClock(model_id, i) << std::endl;
      std::cout << "buffer_" << i << ".write_latency=" << getBufferWriteLatency(model_id, i) << std::endl;
      std::cout << "buffer_" << i << ".read_latency=" << getBufferReadLatency(model_id, i) << std::endl;
    }
    std::cout << "---- display parameters end ----------------" << std::endl;
  }
}

void
SubScenarioInterrupt1(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt1" << std::endl;
}

void
SubScenarioInterrupt2(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt2" << std::endl;
  notifyEvent(model_id, SCENARIO_EVENT_START);
}

void
SubScenarioInterrupt3(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt3" << std::endl;
}
