/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModelScenarioApi.cpp
 * @brief DummyGraphicsMacroModelScenarioApi (source)
 */
#include "DummyGraphicsMacroModelScenarioApi.h"

int
sendAw(const unsigned int model_id,
       const unsigned int axi_if_id,
       const unsigned int AWID,
       const unsigned int AWADDR,
       const unsigned int AWLEN,
       const unsigned int AWSIZE,
       const unsigned int AWBURST,
       const unsigned int AWLOCK,
       const unsigned int AWCACHE,
       const unsigned int AWPROT,
       const unsigned int AWUSER) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << AWID << "," << std::hex << std::showbase << AWADDR << std::dec << std::noshowbase << "," << AWLEN << "," << AWSIZE << "," << AWBURST << "," << AWLOCK << "," << AWCACHE << ","  << AWPROT << "," << AWUSER << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->sendAw(axi_if_id, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
}


int
sendAwWithNoWait(const unsigned int model_id,
                 const unsigned int axi_if_id,
                 const unsigned int AWID,
                 const unsigned int AWADDR,
                 const unsigned int AWLEN,
                 const unsigned int AWSIZE,
                 const unsigned int AWBURST,
                 const unsigned int AWLOCK,
                 const unsigned int AWCACHE,
                 const unsigned int AWPROT,
                 const unsigned int AWUSER) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << AWID << "," << std::hex << std::showbase << AWADDR << std::dec << std::noshowbase << "," << AWLEN << "," << AWSIZE << "," << AWBURST << "," << AWLOCK << "," << AWCACHE << ","  << AWPROT << "," << AWUSER << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->sendAwWithNoWait(axi_if_id, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
}

int
sendW(const unsigned int model_id,
      const unsigned int axi_if_id,
      const unsigned int WID,
      const unsigned int WLAST,
      const unsigned char* wdata,
      const unsigned char* wstrb) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << WID << "," << WLAST << "," << (void*)wdata << "," << (void*)wstrb << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->sendW(axi_if_id, WID, WLAST, wdata, wstrb);
}

int
sendWWithNoWait(const unsigned int model_id,
                const unsigned int axi_if_id,
                const unsigned int WID,
                const unsigned int WLAST,
                const unsigned char* wdata,
                const unsigned char* wstrb) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << WID << "," << WLAST << "," << (void*)wdata << "," << (void*)wstrb << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->sendWWithNoWait(axi_if_id, WID, WLAST, wdata, wstrb);
}

int
receiveB(const unsigned int model_id,
         const unsigned int axi_if_id,
         unsigned int *BID,
         unsigned int *BRESP) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << *BID << "," << *BRESP << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveB(axi_if_id, BID, BRESP);
}

int
receiveBWithNoWait(const unsigned int model_id,
                   const unsigned int axi_if_id,
                   unsigned int *BID,
                   unsigned int *BRESP) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << *BID << "," << *BRESP << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveBWithNoWait(axi_if_id, BID, BRESP);
}

int
receiveBById(const unsigned int model_id,
             const unsigned int axi_if_id,
             const unsigned int BID,
             unsigned int *BRESP) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << BID << "," << *BRESP << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveBById(axi_if_id, BID, BRESP);
}

int
receiveBByIdWithNoWait(const unsigned int model_id,
                       const unsigned int axi_if_id,
                       const unsigned int BID,
                       unsigned int *BRESP) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << BID << "," << *BRESP << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveBByIdWithNoWait(axi_if_id, BID, BRESP);
}

int
sendAr(const unsigned int model_id,
       const unsigned int axi_if_id,
       const unsigned int ARID,
       const unsigned int ARADDR,
       const unsigned int ARLEN,
       const unsigned int ARSIZE,
       const unsigned int ARBURST,
       const unsigned int ARLOCK,
       const unsigned int ARCACHE,
       const unsigned int ARPROT,
       const unsigned int ARUSER) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id<< "," << ARID<< "," << std::hex << std::showbase << ARADDR << std::dec << std::noshowbase << "," << ARLEN << "," << ARSIZE << "," << ARBURST << "," << ARLOCK << "," << ARCACHE << "," << ARPROT << "," << ARUSER<< ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->sendAr(axi_if_id, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
}

int
sendArWithNoWait(const unsigned int model_id,
                 const unsigned int axi_if_id,
                 const unsigned int ARID,
                 const unsigned int ARADDR,
                 const unsigned int ARLEN,
                 const unsigned int ARSIZE,
                 const unsigned int ARBURST,
                 const unsigned int ARLOCK,
                 const unsigned int ARCACHE,
                 const unsigned int ARPROT,
                 const unsigned int ARUSER) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id<< "," << ARID<< "," << std::hex << std::showbase << ARADDR << std::dec << std::noshowbase << "," << ARLEN << "," << ARSIZE << "," << ARBURST << "," << ARLOCK << "," << ARCACHE << "," << ARPROT << "," << ARUSER<< ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->sendArWithNoWait(axi_if_id, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
}

int
receiveR(const unsigned int model_id,
         const unsigned int axi_if_id,
         unsigned int *RID,
         unsigned int *RLAST,
         unsigned int *RRESP,
         unsigned char *rdata) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << *RID << "," << *RLAST << "," << *RRESP << "," << (void*)rdata << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveR(axi_if_id, RID, RLAST, RRESP, rdata);
}

int
receiveRWithNoWait(const unsigned int model_id,
                   const unsigned int axi_if_id,
                   unsigned int *RID,
                   unsigned int *RLAST,
                   unsigned int *RRESP,
                   unsigned char *rdata) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << *RID << "," << *RLAST << "," << *RRESP << "," << (void*)rdata << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveRWithNoWait(axi_if_id, RID, RLAST, RRESP, rdata);
}

int
receiveRById(const unsigned int model_id,
             const unsigned int axi_if_id,
             const unsigned int RID,
             unsigned int *RLAST,
             unsigned int *RRESP,
             unsigned char *rdata) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << RID << "," << *RLAST << "," << *RRESP << "," << (void*)rdata << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveRById(axi_if_id, RID, RLAST, RRESP, rdata);
}

int
receiveRByIdWithNoWait(const unsigned int model_id,
                       const unsigned int axi_if_id,
                       const unsigned int RID,
                       unsigned int *RLAST,
                       unsigned int *RRESP,
                       unsigned char *rdata) { 
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << axi_if_id << "," << RID << "," << *RLAST << "," << *RRESP << "," << (void*)rdata << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->receiveRByIdWithNoWait(axi_if_id, RID, RLAST, RRESP, rdata);
}

void
waitAxiCycle(const unsigned int model_id,
             const unsigned int cycle) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << cycle << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->waitAxiCycle(cycle);
}

void
waitCoreCycle(const unsigned int model_id,
              const unsigned int cycle) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << cycle << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->waitCoreCycle(cycle);
}


void
setOutputSignal(const unsigned int model_id,
                const unsigned int output_signal_id,
                bool value) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << output_signal_id << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->setOutputSignal(output_signal_id, value);
}

bool
getOutputSignal(const unsigned int model_id,
                const unsigned int output_signal_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << output_signal_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->getOutputSignal(output_signal_id);
}

bool
getInterruptSignal(const unsigned int model_id,
                   const unsigned int interrupt_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << interrupt_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->getInterruptSignal(interrupt_id) ;
}

void
setRreadyValue(const unsigned int model_id,
               const bool value) {
  getDummyGraphicsMacroModelBasePointer(model_id)->setRreadyValue(value);
}

void
releaseRreadyControl(const unsigned int model_id) {
  getDummyGraphicsMacroModelBasePointer(model_id)->releaseRreadyControl();
}

void
waitEvent(const unsigned int model_id,
          const unsigned int event_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << event_id << "," << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->waitEvent(event_id);
}

void
notifyEvent(const unsigned int model_id,
            const unsigned int event_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << event_id << "," << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->notifyEvent(event_id) ;
}


void
setThreadStatus(const unsigned int model_id,
                const unsigned int core_id,
                const unsigned int status) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << core_id << "," << status << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->setThreadStatus(core_id, status);
}

unsigned int
getThreadStatus(const unsigned int model_id,
                const unsigned int core_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << core_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->getThreadStatus(core_id);
}

void
enableLogging(const unsigned int model_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->enableLogging();
}

void
disableLogging(const unsigned int model_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->disableLogging();
}

int
writeBuffer(const unsigned int model_id,
            const unsigned int buffer_id,
            const unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->writeBuffer(buffer_id, data) ;
}

int
writeBufferWithNoWait(const unsigned int model_id,
                      const unsigned int buffer_id,
                      const unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->writeBufferWithNoWait(buffer_id, data);
}

int
readBuffer(const unsigned int model_id,
           const unsigned int buffer_id,
           unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->readBuffer(buffer_id, data) ;
}

int
readBufferWithNoWait(const unsigned int model_id,
                     const unsigned int buffer_id,
                     unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->readBufferWithNoWait(buffer_id, data);
}

unsigned int
getWriteBufferSize(const unsigned int model_id,
                   const unsigned int buffer_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->getWriteBufferSize(buffer_id);
}

unsigned int
getReadBufferSize(const unsigned int model_id,
                  const unsigned int buffer_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->getReadBufferSize(buffer_id);
}

void
waitWriteBufferStatus(const unsigned int model_id,
                      const unsigned int buffer_id,
                      const unsigned char status) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << "," << (int)status << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->waitWriteBufferStatus(buffer_id, status);  
}

void
waitReadBufferStatus(const unsigned int model_id,
                     const unsigned int buffer_id,
                     const unsigned char status) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << "," << (int)status << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->waitReadBufferStatus(buffer_id, status);
}

void
switchWriteBuffer(const unsigned int model_id,
                  const unsigned int buffer_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->switchWriteBuffer(buffer_id);
}

void
switchReadBuffer(const unsigned int model_id,
                 const unsigned int buffer_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->switchReadBuffer(buffer_id);
}

bool
isPossibleToSwitchWriteBuffer(const unsigned int model_id,
                              const unsigned int buffer_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->isPossibleToSwitchWriteBuffer(buffer_id);
}

bool
isPossibleToSwitchReadBuffer(const unsigned int model_id,
                             const unsigned int buffer_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << buffer_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->isPossibleToSwitchReadBuffer(buffer_id);
}

int
writeFifo(const unsigned int model_id,
          const unsigned int fifo_id,
          const unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << fifo_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->writeFifo(fifo_id, data);
}

int
writeFifoWithNoWait(const unsigned int model_id,
                    const unsigned int fifo_id,
                    const unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << fifo_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->writeFifoWithNoWait(fifo_id, data);
}

int
readFifo(const unsigned int model_id,
         const unsigned int fifo_id,
         unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << fifo_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->readFifo(fifo_id, data);
}

int
readFifoWithNoWait(const unsigned int model_id,
                   const unsigned int fifo_id,
                   unsigned char *data) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << fifo_id << "," << (void*)data << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->readFifoWithNoWait(fifo_id, data);
}

unsigned int
getFifoSize(const unsigned int model_id,
            const unsigned int fifo_id) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << fifo_id << ")" << std::endl;
#endif
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoSize(fifo_id);
}

void
waitFifoStatus(const unsigned int model_id,
               const unsigned int fifo_id,
               const unsigned char status) {
#ifdef DEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
  std::cout << sc_time_stamp() << " " << __FUNCTION__ << "(" << model_id << "," << fifo_id << "," << (int)status << ")" << std::endl;
#endif
  getDummyGraphicsMacroModelBasePointer(model_id)->waitFifoStatus(fifo_id, status);
}

int
makeVcdValue(const unsigned int model_id,
             const char *name,
             const unsigned int vcd_id,
             const unsigned int width,
             const unsigned long long initial_value) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->makeVcdValue(name, vcd_id, width, initial_value);
}

int
setVcdValue(const unsigned int model_id,
            const unsigned int vcd_id,
            const unsigned long long value) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->setVcdValue(vcd_id, value);
}

void
dumpSimulationTime(const unsigned int model_id) {
  getDummyGraphicsMacroModelBasePointer(model_id)->dumpSimulationTime();
}


unsigned int
getNumberOfAxiIf(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfAxiIf();
}

unsigned int
getNumberOfInterrupt(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfInterrupt();
}

unsigned int
getNumberOfOutputSignal(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfOutputSignal();
}

unsigned int
getNumberOfBuffer(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfBuffer();
}

unsigned int
getNumberOfFifo(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfFifo();
}

unsigned int
getNumberOfThread(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfThread();
}

unsigned int
getNumberOfReadOutStanding(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfReadOutStanding();
}

unsigned int
getNumberOfWriteOutStanding(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfWriteOutStanding();
}

bool
getNoRReceive(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNoRReceive();
}

bool
getNoBReceive(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNoBReceive();
}

const char*
getBufferParameterFileName(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBufferParameterFileName();
}

const char*
getFifoParameterFileName(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoParameterFileName();
}

const char*
getOutputVcdFileName(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getOutputVcdFileName();
}

const char*
getOutputCsvFileName(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getOutputCsvFileName();
}

const char*
getOutputSummaryFileName(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getOutputSummaryFileName();
}

sc_time_unit getTimeUnit(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getTimeUnit();
}

unsigned int
getAxiClock(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getAxiClock();
}

unsigned int
getCoreClock(const unsigned int model_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getCoreClock();
}

unsigned int
getNumberOfInternalBuffer(const unsigned int model_id,
                          const unsigned int buffer_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getNumberOfInternalBuffer(buffer_id);
}

unsigned int
getBufferWidth(const unsigned int model_id,
               const unsigned int buffer_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBufferWidth(buffer_id);
}

unsigned int
getBufferDepth(const unsigned int model_id,
               const unsigned int buffer_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBufferDepth(buffer_id);
}

unsigned int
getBufferWriteClock(const unsigned int model_id,
                    const unsigned int buffer_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBufferWriteClock(buffer_id);
}

unsigned int
getBufferReadClock(const unsigned int model_id,
                   const unsigned int buffer_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBufferReadClock(buffer_id);
}

unsigned int
getBufferWriteLatency(const unsigned int model_id,
                      const unsigned int buffer_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBufferWriteLatency(buffer_id);
}

unsigned int
getBufferReadLatency(const unsigned int model_id,
                     const unsigned int buffer_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBufferReadLatency(buffer_id);
}

unsigned int
getFifoWidth(const unsigned int model_id,
             const unsigned int fifo_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoWidth(fifo_id);
}

unsigned int
getFifoDepth(const unsigned int model_id,
             const unsigned int fifo_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoDepth(fifo_id);
}

unsigned int
getFifoWriteClock(const unsigned int model_id,
                  const unsigned int fifo_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoWriteClock(fifo_id);
}

unsigned int
getFifoReadClock(const unsigned int model_id,
                 const unsigned int fifo_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoReadClock(fifo_id);
}

unsigned int
getFifoWriteLatency(const unsigned int model_id,
                    const unsigned int fifo_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoWriteLatency(fifo_id);
}

unsigned int
getFifoReadLatency(const unsigned int model_id,
                   const unsigned int fifo_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getFifoReadLatency(fifo_id);
}

#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
bool
getDataInSignal(unsigned int model_id,
                unsigned int coop_signal_id, 
                unsigned int *value) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getDataInSignal(coop_signal_id, value);
}

void
setDataOutSignal(unsigned int model_id,
                 unsigned int coop_signal_id, 
                 unsigned int value) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->setDataOutSignal(coop_signal_id, value);
}

unsigned int
getDataOutSignal(unsigned int model_id,
                 unsigned int coop_signal_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getDataOutSignal(coop_signal_id);
}

bool
getBusyInSignal(unsigned int model_id,
                unsigned int coop_signal_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBusyInSignal(coop_signal_id);
}

void
setBusyOutSignalWithInit(unsigned int model_id,
                         unsigned int coop_signal_id, 
                         unsigned int value) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->setBusyOutSignalWithInit(coop_signal_id, value);
}

bool
getBusyOutSignal(unsigned int model_id,
                 unsigned int coop_signal_id) {
  return getDummyGraphicsMacroModelBasePointer(model_id)->getBusyOutSignal(coop_signal_id);
}
#endif 

