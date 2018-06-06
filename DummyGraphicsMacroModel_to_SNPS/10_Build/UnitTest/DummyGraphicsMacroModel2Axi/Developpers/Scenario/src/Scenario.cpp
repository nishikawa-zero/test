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
}

void
ScenarioRch(unsigned int model_id, unsigned int rch_id) {
  switch (rch_id) {
  case 0:
    SubScenarioRch0(model_id);
    break;
  case 1:
    SubScenarioRch1(model_id);
    break;
  default:
    std::cout << "[ERROR] no rch scenario (rch_id=" << rch_id << ")" << endl;
    assert(0);
    break;
  }

}

void
ScenarioWch(unsigned int model_id, unsigned int wch_id) {
  switch (wch_id) {
  case 0:
    SubScenarioWch0(model_id);
    break;
  case 1:
    SubScenarioWch1(model_id);
    break;
  default:
    std::cout << "[ERROR] no wch scenario (wch_id=" << wch_id << ")" << endl;
    assert(0);
    break;
  }

}

void
ScenarioCore(unsigned int model_id, unsigned int core_id) {
  switch (core_id) {
  case 0:
    SubScenarioCore0(model_id);
    break;
  default:
    std::cout << "[ERROR] no core scenario (core_id=" << core_id << ")" << endl;
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
SubScenarioRch0(unsigned int model_id) {
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
  unsigned int input_buffer_id = 0;
  unsigned int input_internal_buffer_id = 0;

  unsigned int send_ar_kind = 0;

  dumpSimulationTime(model_id);
  std::cout << "SubScenarioRch0 start" << std::endl;

  dumpSimulationTime(model_id);
  std::cout << "SubScenarioRch0 waitEvent(" << SCENARIO_EVENT_START << ")" << std::endl;
  waitEvent(model_id, SCENARIO_EVENT_START);

  enableLogging(model_id);
  
  for (unsigned int j = 0; j < SCENARIO_LOOP;) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitInputbufferStatus(" << input_buffer_id << "," << input_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_EMPTY << ")" << std::endl;
    waitInputBufferStatus(model_id, input_buffer_id, input_internal_buffer_id, SCENARIO_BUFFER_STATUS_EMPTY);

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setInputbufferStatus(" << input_buffer_id << "," << input_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_RESERVED << ")" << std::endl;
    setInputBufferStatus(model_id, input_buffer_id, input_internal_buffer_id, SCENARIO_BUFFER_STATUS_RESERVED);

    for (unsigned int i = 0; i < ((SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH) / (SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH)); ++i) {
      int result;
      switch (send_ar_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " sendAr(" << axi_if_id << ")" << std::endl;
        sendAr(model_id, axi_if_id, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " sendArWithNoWait(" << axi_if_id << ")" << std::endl;
          result = sendArWithNoWait(model_id, axi_if_id, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);

          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      }

      axi_if_id = (axi_if_id + 1) % 0x2;
      send_ar_kind = (send_ar_kind + 1) % 0x2;
      
      ARADDR += SCENARIO_BUFFER_WIDTH * SCENARIO_BURST_LENGTH;
      ++j;
    }

    input_internal_buffer_id = (input_internal_buffer_id + 1) & 0x1;
  }
  
  dumpSimulationTime(model_id);
  std::cout << "SubScenarioRch0 finish" << std::endl;
}

void
SubScenarioRch1(unsigned int model_id) {
  unsigned int RID = 0;
  unsigned int RLAST;
  unsigned int RRESP;
  unsigned char rdata[SCENARIO_BURST_SIZE];
  
  unsigned int stored_byte = 0;
  unsigned int axi_if_id = 0;
  unsigned int input_buffer_id = 0;
  unsigned int input_internal_buffer_id = 0;

  unsigned int write_input_buffer_kind = 0;
  unsigned int receive_r_kind = 0;
  
  unsigned int stored_byte_vcd_id = g_vcd_id++;
  
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;
  
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " makeVcdValue(rch1_storeed_byte)" << std::endl;
  makeVcdValue(model_id, "rch1_storeed_byte", stored_byte_vcd_id, 32, 0);

  while (1) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitInputbufferStatus(" << input_buffer_id << "," << input_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_RESERVED << ")" << std::endl;
    waitInputBufferStatus(model_id, input_buffer_id, input_internal_buffer_id, SCENARIO_BUFFER_STATUS_RESERVED);

    while (stored_byte < (SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH)) {
      int result;
      switch (receive_r_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " receiveR(" << axi_if_id << ")" << std::endl;
        receiveR(model_id, axi_if_id, &RID, &RLAST, &RRESP, rdata);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " receiveRWithNoWait(" << axi_if_id << ")" << std::endl;
          result = receiveRWithNoWait(model_id, axi_if_id, &RID, &RLAST, &RRESP, rdata);
          
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      case 2:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " receiveRById(" << axi_if_id << ")" << std::endl;
        receiveRById(model_id, axi_if_id, RID, &RLAST, &RRESP, rdata);
        break;
      case 3:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " receiveRByIdWithNoWait(" << axi_if_id << ")" << std::endl;
          result = receiveRByIdWithNoWait(model_id, axi_if_id, RID, &RLAST, &RRESP, rdata);

          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
          waitAxiCycle(model_id, 1);
        } while (result != 0);
        break;
      }

      if (RLAST == 1) {
        axi_if_id = (axi_if_id + 1) % 0x2;
      }
      receive_r_kind = (receive_r_kind + 1) % 0x4;

      switch (write_input_buffer_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " writeInputBuffer(" << input_buffer_id << "," << input_internal_buffer_id << ")" << std::endl;
        writeInputBuffer(model_id, input_buffer_id, input_internal_buffer_id, rdata);
        break;
      case 1:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " writeInputBufferWithNoWait(" << input_buffer_id << "," << input_internal_buffer_id << ")" << std::endl;
        writeInputBufferWithNoWait(model_id, input_buffer_id, input_internal_buffer_id, rdata);

        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " waitCoreCycle(1)" << std::endl;
        waitCoreCycle(model_id, 1);
        break;
      }

      write_input_buffer_kind = (write_input_buffer_kind + 1) % 0x2;
      stored_byte += SCENARIO_BURST_SIZE;

      dumpSimulationTime(model_id);
      std::cout << __FUNCTION__ << " setVcdValue(stored_byte=" << stored_byte <<")" << std::endl;
      setVcdValue(model_id, stored_byte_vcd_id, stored_byte);
    }

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setInputBufferStatus(" << input_buffer_id << "," << input_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    setInputBufferStatus(model_id, input_buffer_id, input_internal_buffer_id, SCENARIO_BUFFER_STATUS_FULL);

    stored_byte = 0;
    input_internal_buffer_id = (input_internal_buffer_id + 1) & 0x1;
  }
   
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
SubScenarioWch0(unsigned int model_id) {
  unsigned int AWID = 0;
  unsigned int AWADDR = 0x1000;
  unsigned int AWLEN = SCENARIO_BURST_LENGTH - 1;
  unsigned int AWSIZE = 0x3; /* 8-Byte*/
  unsigned int AWBURST = 1; /* INCR */
  unsigned int AWLOCK = 0;
  unsigned int AWCACHE = 0;
  unsigned int AWPROT = 0;
  unsigned int AWUSER = 0;

  unsigned int axi_if_id = 0;
  unsigned int output_buffer_id = 0;
  unsigned int output_internal_buffer_id = 0;

  unsigned int send_aw_kind = 0;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  while (1) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitOutputBufferStatus(" << output_buffer_id << "," << output_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    waitOutputBufferStatus(model_id, output_buffer_id, output_internal_buffer_id, SCENARIO_BUFFER_STATUS_FULL);

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setOutputBufferStatus(" << output_buffer_id << "," << output_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_USED << ")" << std::endl;
    setOutputBufferStatus(model_id, output_buffer_id, output_internal_buffer_id, SCENARIO_BUFFER_STATUS_USED);
    
    for (unsigned int i = 0; i < ((SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH) / (SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH)); ++i) {
      switch (send_aw_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " sendAw(" << axi_if_id << ")" << std::endl;
        sendAw(model_id, axi_if_id, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
        break;
      case 1:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " sendAwWithNoWait(" << axi_if_id << ")" << std::endl;
        sendAw(model_id, axi_if_id, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
        waitAxiCycle(model_id, 1);
        break;
      }
      AWADDR += SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH;
      axi_if_id = (axi_if_id + 1) % 0x2;
      send_aw_kind = (send_aw_kind + 1) % 0x2;
    }

    output_internal_buffer_id = (output_internal_buffer_id + 1) & 0x1;
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " finish" << std::endl;
}

void
SubScenarioWch1(unsigned int model_id) {
  unsigned int WID = 0;
  unsigned int WLAST;
  unsigned char wdata[SCENARIO_BURST_SIZE];
  unsigned char wstrb[SCENARIO_BURST_SIZE];

  unsigned int loaded_byte = 0;
  unsigned int axi_if_id = 0;
  unsigned int output_buffer_id = 0;
  unsigned int output_internal_buffer_id = 0;
  unsigned int burst_count = 0;
  unsigned int transfered_byte = 0;

  unsigned int read_output_buffer_kind = 0;
  unsigned int send_w_kind = 0;

  unsigned int transfered_byte_vcd_id = g_vcd_id++;

  dumpSimulationTime(model_id);
  std::cout << "SubScenarioWch1 start" << std::endl;

  for (unsigned int i = 0; i < SCENARIO_BURST_SIZE; ++i) {
    wstrb[i] = 0xFF;
  }

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " makeVcdValue(wch1_transfered_byte)" << std::endl;
  makeVcdValue(model_id, "wch1_transfered_byte", transfered_byte_vcd_id, 32, 0);

  while (1) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitOutputBufferStatus(" << output_buffer_id << "," << output_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_USED << ")" << std::endl;
    waitOutputBufferStatus(model_id, output_buffer_id, output_internal_buffer_id, SCENARIO_BUFFER_STATUS_USED);

    while (loaded_byte < (SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH)) {
      int result;
      switch (read_output_buffer_kind) {
      default:
      case 0:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " readOutputBuffer(" << output_buffer_id << "," << output_internal_buffer_id << ")" << std::endl;
        readOutputBuffer(model_id, output_buffer_id, output_internal_buffer_id, wdata);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " readOutputBufferWithNoWait(" << output_buffer_id << "," << output_internal_buffer_id << ")" << std::endl;
          result = readOutputBufferWithNoWait(model_id, output_buffer_id, output_internal_buffer_id, wdata);

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
        std::cout << __FUNCTION__ << " sendW(" << axi_if_id << ")" << std::endl;
        sendW(model_id, axi_if_id, WID, WLAST, wdata, wstrb);
        break;
      case 1:
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " sendWWithNoWait(" << axi_if_id << ")" << std::endl;
        sendWWithNoWait(model_id, axi_if_id, WID, WLAST, wdata, wstrb);

        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " waitAxiCycle(1)" << std::endl;
        waitAxiCycle(model_id, 1);
        break;
      }
      transfered_byte += SCENARIO_BURST_SIZE;
      if (WLAST == 1) {
        axi_if_id = (axi_if_id + 1) % 0x2;
      }
      send_w_kind = (send_w_kind + 1) % 0x2;

      dumpSimulationTime(model_id);
      std::cout << __FUNCTION__ << " setVcdValue(transfered_byte=" << transfered_byte <<")" << std::endl;
      setVcdValue(model_id, transfered_byte_vcd_id, transfered_byte);
    }

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setOutputBufferStatus(" << output_buffer_id << "," << output_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_EMPTY << ")" << std::endl;
    setOutputBufferStatus(model_id, output_buffer_id, output_internal_buffer_id, SCENARIO_BUFFER_STATUS_EMPTY);

    loaded_byte = 0;
    output_internal_buffer_id = (output_internal_buffer_id + 1) & 0x1;

    if (SCENARIO_BURST_SIZE * SCENARIO_BURST_LENGTH * SCENARIO_LOOP <= transfered_byte) {
      break;
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
SubScenarioCore0(unsigned int model_id) {
  unsigned int loaded_byte = 0;
  unsigned int stored_byte = 0;
  unsigned int input_buffer_id = 0;
  unsigned int input_internal_buffer_id = 0;
  unsigned int output_buffer_id = 0;
  unsigned int output_internal_buffer_id = 0;
  unsigned char data[SCENARIO_BURST_SIZE];
  unsigned int core_id = 0;

  unsigned int read_input_buffer_kind = 0;
  unsigned int write_output_buffer_kind = 0;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " start" << std::endl;

  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << " setCoreStatus(" << model_id << "," << core_id << ","  << SCENARIO_CORE_STATUS_INIT << ")" << std::endl;
  setCoreStatus(model_id, core_id, SCENARIO_CORE_STATUS_INIT);

  while (1) {
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitInputBufferStatus(" << input_buffer_id << "," << input_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    waitInputBufferStatus(model_id, input_buffer_id, input_internal_buffer_id, SCENARIO_BUFFER_STATUS_FULL);

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " waitOutputBufferStatus(" << output_buffer_id << "," << output_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_EMPTY << ")" << std::endl;
    waitOutputBufferStatus(model_id, output_buffer_id, output_internal_buffer_id, SCENARIO_BUFFER_STATUS_EMPTY);

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setCoreStatus(" << model_id << "," << core_id << ","  << SCENARIO_CORE_STATUS_BUSY << ")" << std::endl;
    setCoreStatus(model_id, core_id, SCENARIO_CORE_STATUS_BUSY);

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setOutputBufferStatus(" << output_buffer_id << "," << output_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_USING << ")" << std::endl;
    setOutputBufferStatus(model_id, output_buffer_id, output_internal_buffer_id, SCENARIO_BUFFER_STATUS_USING);

    while (loaded_byte < (SCENARIO_BUFFER_WIDTH * SCENARIO_BUFFER_DEPTH)) { 
      int result;
      switch (read_input_buffer_kind) {
      default:
      case 0:        
        dumpSimulationTime(model_id);
        std::cout << __FUNCTION__ << " readInputBuffer(" << input_buffer_id << "," << input_internal_buffer_id << ")" << std::endl;
        readInputBuffer(model_id, input_buffer_id, input_internal_buffer_id, data);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " readInputBufferWithNoWait(" << input_buffer_id << "," << input_internal_buffer_id << ")" << std::endl;
          result = readInputBufferWithNoWait(model_id, input_buffer_id, input_internal_buffer_id, data);

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
        std::cout << __FUNCTION__ << " writeOutputBuffer(" << output_buffer_id << "," << output_internal_buffer_id << ")" << std::endl;
        writeOutputBuffer(model_id, output_buffer_id, output_internal_buffer_id, data);
        break;
      case 1:
        do {
          dumpSimulationTime(model_id);
          std::cout << __FUNCTION__ << " writeOutputBuffer(" << output_buffer_id << "," << output_internal_buffer_id << ")" << std::endl;
          result = writeOutputBuffer(model_id, output_buffer_id, output_internal_buffer_id, data);

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
    std::cout << __FUNCTION__ << " setInputBufferSutatus(" << input_buffer_id << "," << input_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_EMPTY << ")" << std::endl;
    setInputBufferStatus(model_id, input_buffer_id, input_internal_buffer_id, SCENARIO_BUFFER_STATUS_EMPTY);

    loaded_byte = 0;
    input_internal_buffer_id = (input_internal_buffer_id + 1) & 0x1;

    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setOutputBufferStatus(" << output_buffer_id << "," << output_internal_buffer_id << "," << SCENARIO_BUFFER_STATUS_FULL << ")" << std::endl;
    setOutputBufferStatus(model_id, output_buffer_id, output_internal_buffer_id, SCENARIO_BUFFER_STATUS_FULL);

    stored_byte = 0;
    output_internal_buffer_id = (output_internal_buffer_id + 1) & 0x1;
 
    dumpSimulationTime(model_id);
    std::cout << __FUNCTION__ << " setCoreStatus(" << model_id << "," << core_id << ","  << SCENARIO_CORE_STATUS_IDLE << ")" << std::endl;
    setCoreStatus(model_id, core_id, SCENARIO_CORE_STATUS_IDLE);
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
    std::cout << "ax_if_number=" << getAxiIfNumber(model_id) << std::endl;
    std::cout << "interrupt_number=" << getInterruptNumber(model_id) << std::endl;
    std::cout << "output_signal_number=" << getOutputSignalNumber(model_id) << std::endl;
    std::cout << "input_buffer_number=" << getInputBufferNumber(model_id) << std::endl;
    std::cout << "output_buffer_number=" << getOutputBufferNumber(model_id) << std::endl;
    std::cout << "rch_number=" << getRchNumber(model_id) << std::endl;
    std::cout << "wch_number=" << getWchNumber(model_id) << std::endl;
    std::cout << "core_number=" << getCoreNumber(model_id) << std::endl;
    std::cout << "read_outstanding_number=" << getReadOutStandingNumber(model_id) << std::endl;
    std::cout << "write_outstanding_number=" << getWriteOutStandingNumber(model_id) << std::endl;
    std::cout << "no_r_receive=" << getNoRReceive(model_id) << std::endl;
    std::cout << "no_b_receive=" << getNoBReceive(model_id) << std::endl;
    std::cout << "buffer_parameter_file_name=" << getBufferParameterFileName(model_id) << std::endl;
    std::cout << "output_vcd_file_name=" << getOutputVcdFileName(model_id) << std::endl;
    std::cout << "output_csv_file_name=" << getOutputCsvFileName(model_id) << std::endl;
    std::cout << "output_summary_file_name=" << getOutputSummaryFileName(model_id) << std::endl;
    std::cout << "time_unit=" << getTimeUnit(model_id) << std::endl;
    std::cout << "axi_clock=" << getAxiClock(model_id) << std::endl;
    std::cout << "core_clock=" << getCoreClock(model_id) << std::endl;
    for (unsigned int i = 0; i < getInputBufferNumber(model_id); ++i)  {
      std::cout << "input_buffer_" << i << ".internal_buffer_number=" << getInputInternalBufferNumber(model_id, i) << std::endl;
      for (unsigned int j = 0; j < getInputInternalBufferNumber(model_id, i); ++j)  {
        std::cout << "input_buffer_" << i << ".internal_buffer_" << j << ".width=" << getInputInternalBufferWidth(model_id, i, j) << std::endl;
        std::cout << "input_buffer_" << i << ".internal_buffer_" << j << ".depth=" << getInputInternalBufferDepth(model_id, i, j) << std::endl;
        std::cout << "input_buffer_" << i << ".internal_buffer_" << j << ".read_latency=" << getInputBufferReadLatency(model_id, i, j) << std::endl;
        std::cout << "input_buffer_" << i << ".internal_buffer_" << j << ".write_latency=" << getInputBufferWriteLatency(model_id, i, j) << std::endl;
      }
    }
    for (unsigned int i = 0; i < getOutputBufferNumber(model_id); ++i)  {
      std::cout << "output_buffer_" << i << ".internal_buffer_number=" << getOutputInternalBufferNumber(model_id, i) << std::endl;
      for (unsigned int j = 0; j < getOutputInternalBufferNumber(model_id, i); ++j)  {
        std::cout << "output_buffer_" << i << ".internal_buffer_" << j << ".width=" << getOutputInternalBufferWidth(model_id, i, j) << std::endl;
        std::cout << "output_buffer_" << i << ".internal_buffer_" << j << ".depth=" <<  getOutputInternalBufferDepth(model_id, i, j) << std::endl;
        std::cout << "output_buffer_" << i << ".internal_buffer_" << j << ".read_latency=" << getOutputBufferReadLatency(model_id, i, j) << std::endl;
        std::cout << "output_buffer_" << i << ".internal_buffer_" << j << ".write_latency=" << getOutputBufferWriteLatency(model_id, i, j) << std::endl;
      }
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
