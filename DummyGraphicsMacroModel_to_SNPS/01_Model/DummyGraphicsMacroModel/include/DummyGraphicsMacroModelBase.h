/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModelBase.h
 * @brief DummyGraphicsMacroModelBase (header)
 */
#include <systemc.h>

#ifndef DUMMY_GRAPHICS_MACRO_MODEL_BASE_H
#define DUMMY_GRAPHICS_MACRO_MODEL_BASE_H

class DummyGraphicsMacroModelBase {
public:
  /* AXI */
  virtual int sendAw(const unsigned int axi_if_id,
                     const unsigned int AWID,
                     const unsigned int AWADDR,
                     const unsigned int AWLEN,
                     const unsigned int AWSIZE,
                     const unsigned int AWBURST,
                     const unsigned int AWLOCK,
                     const unsigned int AWCACHE,
                     const unsigned int AWPROT,
                     const unsigned int AWUSER) = 0;
  virtual int sendAwWithNoWait(const unsigned int axi_if_id,
                               const unsigned int AWID,
                               const unsigned int AWADDR,
                               const unsigned int AWLEN,
                               const unsigned int AWSIZE,
                               const unsigned int AWBURST,
                               const unsigned int AWLOCK,
                               const unsigned int AWCACHE,
                               const unsigned int AWPROT,
                               const unsigned int AWUSER) = 0;
  virtual int sendW(const unsigned int axi_if_id,
                    const unsigned int WID,
                    const unsigned int WLAST,
                    const unsigned char* wdata,
                    const unsigned char* wstrb) = 0;
  virtual int sendWWithNoWait(const unsigned int axi_if_id,
                              const unsigned int WID,
                              const unsigned int WLAST,
                              const unsigned char* wdata,
                              const unsigned char* wstrb) = 0;
  virtual int receiveB(const unsigned int axi_if_id,
                       unsigned int *BID,
                       unsigned int *BRESP) = 0;
  virtual int receiveBWithNoWait(const unsigned int axi_if_id,
                                 unsigned int *BID,
                                 unsigned int *BRESP) = 0;
  virtual int receiveBById(const unsigned int axi_if_id,
                           const unsigned int BID,
                           unsigned int *BRESP) = 0;
  virtual int receiveBByIdWithNoWait(const unsigned int axi_if_id,
                                     const unsigned int BID,
                                     unsigned int *BRESP) = 0;
  virtual int sendAr(const unsigned int axi_if_id,
                     const unsigned int ARID,
                     const unsigned int ARADDR,
                     const unsigned int ARLEN,
                     const unsigned int ARSIZE,
                     const unsigned int ARBURST,
                     const unsigned int ARLOCK,
                     const unsigned int ARCACHE,
                     const unsigned int ARPROT,
                     const unsigned int ARUSER) = 0;
  virtual int sendArWithNoWait(const unsigned int axi_if_id,
                               const unsigned int ARID,
                               const unsigned int ARADDR,
                               const unsigned int ARLEN,
                               const unsigned int ARSIZE,
                               const unsigned int ARBURST,
                               const unsigned int ARLOCK,
                               const unsigned int ARCACHE,
                               const unsigned int ARPROT,
                               const unsigned int ARUSER) = 0;
  virtual int receiveR(const unsigned int axi_if_id,
                       unsigned int *RID,
                       unsigned int *RLAST,
                       unsigned int *RRESP,
                       unsigned char *rdata) = 0;
  virtual int receiveRWithNoWait(const unsigned int axi_if_id,
                                 unsigned int *RID,
                                 unsigned int *RLAST,
                                 unsigned int *RRESP,
                                 unsigned char *rdata) = 0;
  virtual int receiveRById(const unsigned int axi_if_id,
                           const unsigned int RID,
                           unsigned int *RLAST,
                           unsigned int *RRESP,
                           unsigned char *rdata) = 0;
  virtual int receiveRByIdWithNoWait(const unsigned int axi_if_id,
                                     const unsigned int RID,
                                     unsigned int *RLAST,
                                     unsigned int *RRESP,
                                     unsigned char *rdata) = 0;
  /* Wait */
  virtual void waitAxiCycle(const unsigned int cycle) = 0;
  virtual void waitCoreCycle(const unsigned int cycle) = 0;
  /* Signal */
  virtual void setOutputSignal(const unsigned int output_signal_id,
                               const bool value) = 0;
  virtual bool getOutputSignal(const unsigned int output_signal_id) = 0;
  virtual bool getInterruptSignal(const unsigned int interrupt_id) = 0;
  /* RreadyControl */
  virtual void setRreadyValue(const bool value) = 0;
  virtual void releaseRreadyControl(void) = 0;
  virtual bool getRreadyValue(void) = 0;
  virtual bool isValidateRreadyControl(void) = 0;
  /* Event */
  virtual void waitEvent(const unsigned int event_id) = 0;
  virtual void notifyEvent(const unsigned int event_id) = 0;
  /* Thread */
  virtual void setThreadStatus(const unsigned int thread_id,
                               const unsigned int status) = 0;
  virtual unsigned int getThreadStatus(const unsigned int thread_id) = 0;
  /* Logging */
  virtual void enableLogging(void) = 0;
  virtual void disableLogging(void) = 0;
  /* Buffer */
  virtual int writeBuffer(const unsigned int buffer_id,
                          const unsigned char *data) = 0;
  virtual int writeBufferWithNoWait(const unsigned int buffer_id,
                                    const unsigned char *data) = 0;
  virtual int readBuffer(const unsigned int buffer_id,
                         unsigned char *data) = 0;
  virtual int readBufferWithNoWait(const unsigned int buffer_id,
                                   unsigned char *data) = 0;
  virtual unsigned int getWriteBufferSize(const unsigned int buffer_id) = 0;
  virtual unsigned int getReadBufferSize(const unsigned int buffer_id) = 0;
  virtual void waitWriteBufferStatus(const unsigned int buffer_id,
                                     const unsigned char status) = 0;
  virtual void waitReadBufferStatus(const unsigned int buffer_id,
                                    const unsigned char status) = 0;
  virtual void switchWriteBuffer(const unsigned int buffer_id) = 0;
  virtual void switchReadBuffer(const unsigned int buffer_id) = 0;
  virtual bool isPossibleToSwitchWriteBuffer(const unsigned int buffer_id) = 0;
  virtual bool isPossibleToSwitchReadBuffer(const unsigned int buffer_id) = 0;
  /* Fifo */
  virtual int writeFifo(const unsigned int fifo_id,
                        const unsigned char *data) = 0;
  virtual int writeFifoWithNoWait(const unsigned int fifo_id,
                                  const unsigned char *data) = 0;
  virtual int readFifo(const unsigned int fifo_id,
                       unsigned char *data) = 0;
  virtual int readFifoWithNoWait(const unsigned int fifo_id,
                                   unsigned char *data) = 0;
  virtual unsigned int getFifoSize(const unsigned int fifo_id) = 0;
  virtual void waitFifoStatus(const unsigned int fifo_id,
                              const unsigned char status) = 0;
  /* Utility */
  virtual int makeVcdValue(const char *name,
                           const unsigned int vcd_id,
                           const unsigned int width,
                           const unsigned long long initiali_value) = 0;
  virtual int setVcdValue(const unsigned int vcd_id,
                          const unsigned long long value) = 0;
  virtual void dumpSimulationTime(void) = 0;
  /* Parameter */
  virtual unsigned int getNumberOfAxiIf(void) = 0;
  virtual unsigned int getNumberOfInterrupt(void) = 0;
  virtual unsigned int getNumberOfOutputSignal(void) = 0;
  virtual unsigned int getNumberOfBuffer(void) = 0;
  virtual unsigned int getNumberOfFifo(void) = 0;
  virtual unsigned int getNumberOfThread(void) = 0;
  virtual unsigned int getNumberOfReadOutStanding(void) = 0;
  virtual unsigned int getNumberOfWriteOutStanding(void) = 0;
  virtual bool getNoRReceive(void) = 0;
  virtual bool getNoBReceive(void) = 0;
  virtual const char* getBufferParameterFileName(void) = 0;
  virtual const char* getFifoParameterFileName(void) = 0;
  virtual const char* getOutputVcdFileName(void) = 0;
  virtual const char* getOutputCsvFileName(void) = 0;
  virtual const char* getOutputSummaryFileName(void) = 0;
  virtual sc_time_unit getTimeUnit(void) = 0;
  virtual unsigned int getAxiClock(void) = 0;
  virtual unsigned int getCoreClock(void) = 0;
  virtual unsigned int getNumberOfInternalBuffer(const unsigned int buffer_id) = 0;
  virtual unsigned int getBufferWidth(const unsigned int buffer_id) = 0;
  virtual unsigned int getBufferDepth(const unsigned int buffer_id) = 0;
  virtual unsigned int getBufferWriteClock(const unsigned int buffer_id) = 0;
  virtual unsigned int getBufferReadClock(const unsigned int buffer_id) = 0;
  virtual unsigned int getBufferWriteLatency(const unsigned int buffer_id) = 0;
  virtual unsigned int getBufferReadLatency(const unsigned int buffer_id) = 0;
  virtual unsigned int getFifoWidth(const unsigned int fifo_id) = 0;
  virtual unsigned int getFifoDepth(const unsigned int fifo_id) = 0;
  virtual unsigned int getFifoWriteClock(const unsigned int fifo_id) = 0;
  virtual unsigned int getFifoReadClock(const unsigned int fifo_id) = 0;
  virtual unsigned int getFifoWriteLatency(const unsigned int fifo_id) = 0;
  virtual unsigned int getFifoReadLatency(const unsigned int fifo_id) = 0;
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  /* Cooperarion */
  virtual bool getDataInSignal(unsigned int coop_signal_id, 
                               unsigned int *value) = 0;
  virtual void setDataOutSignal(unsigned int coop_signal_id, 
                                unsigned int value) = 0;
  virtual unsigned int getDataOutSignal(unsigned int coop_signal_id) = 0;

  virtual bool getBusyInSignal(unsigned int coop_signal_id) = 0;
  virtual void setBusyOutSignalWithInit(unsigned int coop_signal_id, 
                                        unsigned int value) = 0;
  virtual bool getBusyOutSignal(unsigned int coop_signal_id) = 0;
#endif
};
#endif /* DUMMY_GRAPHICS_MACRO_MODEL_BASE_H */
