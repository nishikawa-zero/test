/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModelScenarioApi.h
 * @brief DummyGraphicsMacroModelScenarioApi (header)
 */
#include "DummyGraphicsMacroModelPointerApi.h"

#ifndef DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API_H
#define DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API_H

/* AXI */
int sendAw(const unsigned int model_id,
           const unsigned int axi_if_id,
           const unsigned int AWID,
           const unsigned int AWADDR,
           const unsigned int AWLEN,
           const unsigned int AWSIZE,
           const unsigned int AWBURST,
           const unsigned int AWLOCK,
           const unsigned int AWCACHE,
           const unsigned int AWPROT,
           const unsigned int AWUSER);
int sendAwWithNoWait(const unsigned int model_id,
                     const unsigned int axi_if_id,
                     const unsigned int AWID,
                     const unsigned int AWADDR,
                     const unsigned int AWLEN,
                     const unsigned int AWSIZE,
                     const unsigned int AWBURST,
                     const unsigned int AWLOCK,
                     const unsigned int AWCACHE,
                     const unsigned int AWPROT,
                     const unsigned int AWUSER);
int sendW(const unsigned int model_id,
          const unsigned int axi_if_id,
          const unsigned int WID,
          const unsigned int WLAST,
          const unsigned char* wdata,
          const unsigned char* wstrb);
int sendWWithNoWait(const unsigned int model_id,
                    const unsigned int axi_if_id,
                    const unsigned int WID,
                    const unsigned int WLAST,
                    const unsigned char* wdata,
                    const unsigned char* wstrb);
int receiveB(const unsigned int model_id,
             const unsigned int axi_if_id,
             unsigned int *BID,
             unsigned int *BRESP);
int receiveBWithNoWait(const unsigned int model_id,
                       const unsigned int axi_if_id,
                       unsigned int *BID,
                       unsigned int *BRESP);
int receiveBById(const unsigned int model_id,
                 const unsigned int axi_if_id,
                 const unsigned int BID,
                 unsigned int *BRESP);
int receiveBByIdWithNoWait(const unsigned int model_id,
                           const unsigned int axi_if_id,
                           const unsigned int BID,
                           unsigned int *BRESP);
int sendAr(const unsigned int model_id,
           const unsigned int axi_if_id,
           const unsigned int ARID,
           const unsigned int ARADDR,
           const unsigned int ARLEN,
           const unsigned int ARSIZE,
           const unsigned int ARBURST,
           const unsigned int ARLOCK,
           const unsigned int ARCACHE,
           const unsigned int ARPROT,
           const unsigned int ARUSER);
int sendArWithNoWait(const unsigned int model_id,
                     const unsigned int axi_if_id,
                     const unsigned int ARID,
                     const unsigned int ARADDR,
                     const unsigned int ARLEN,
                     const unsigned int ARSIZE,
                     const unsigned int ARBURST,
                     const unsigned int ARLOCK,
                     const unsigned int ARCACHE,
                     const unsigned int ARPROT,
                     const unsigned int ARUSER);
int receiveR(const unsigned int model_id,
             const unsigned int axi_if_id,
             unsigned int *RID,
             unsigned int *RLAST,
             unsigned int *RRESP,
             unsigned char *rdata);
int receiveRWithNoWait(const unsigned int model_id,
                       const unsigned int axi_if_id,
                       unsigned int *RID,
                       unsigned int *RLAST,
                       unsigned int *RRESP,
                       unsigned char *rdata);
int receiveRById(const unsigned int model_id,
                 const unsigned int axi_if_id,
                 const unsigned int RID,
                 unsigned int *RLAST,
                 unsigned int *RRESP,
                 unsigned char *rdata);
int receiveRByIdWithNoWait(const unsigned int model_id,
                           const unsigned int axi_if_id,
                           const unsigned int RID,
                           unsigned int *RLAST,
                           unsigned int *RRESP,
                           unsigned char *rdata);
/* Wait */
void waitAxiCycle(const unsigned int model_id,
                  const unsigned int cycle);
void waitCoreCycle(const unsigned int model_id,
                   const unsigned int cycle);
/* Signal */
void setOutputSignal(const unsigned int model_id,
                     const unsigned int output_signal_id,
                     const bool value);
bool getOutputSignal(const unsigned int model_id,
                     const unsigned int output_signal_id);
bool getInterruptSignal(const unsigned int model_id,
                        const unsigned int interrupt_id);
/* RreadyControl */
void setRreadyValue(const unsigned int model_id,
                    const bool value);
void releaseRreadyControl(const unsigned int model_id);
/* Event */
void waitEvent(const unsigned int model_id,
               const unsigned int event_id);
void notifyEvent(const unsigned int model_id,
                 const unsigned int event_id);
/* Thread */
void setThreadStatus(const unsigned int model_id,
                     const unsigned int core_id,
                     const unsigned int status);
unsigned int getThreadStatus(const unsigned int model_id,
                           const unsigned int core_id);
/* Logging */
void enableLogging(const unsigned int model_id);
void disableLogging(const unsigned int model_id);
/* Buffer */
int writeBuffer(const unsigned int model_id,
                const unsigned int buffer_id,
                const unsigned char *data);
int writeBufferWithNoWait(const unsigned int model_id,
                          const unsigned int buffer_id,
                          const unsigned char *data);
int readBuffer(const unsigned int model_id,
               const unsigned int buffer_id,
               unsigned char *data);
int readBufferWithNoWait(const unsigned int model_id,
                         const unsigned int buffer_id,
                         unsigned char *data);
unsigned int getWriteBufferSize(const unsigned int model_id,
                                const unsigned int buffer_id);
unsigned int getReadBufferSize(const unsigned int model_id,
                               const unsigned int buffer_id);
void waitWriteBufferStatus(const unsigned int model_id,
                           const unsigned int buffer_id,
                           const unsigned char status);
void waitReadBufferStatus(const unsigned int model_id,
                          const unsigned int buffer_id,
                          const unsigned char status);
void switchWriteBuffer(const unsigned int model_id,
                       const unsigned int buffer_id);
void switchReadBuffer(const unsigned int model_id,
                      const unsigned int buffer_id);
bool isPossibleToSwitchWriteBuffer(const unsigned int model_id,
                                   const unsigned int buffer_id);
bool isPossibleToSwitchReadBuffer(const unsigned int model_id,
                                  const unsigned int buffer_id);
/* Fifo */
int writeFifo(const unsigned int model_id,
              const unsigned int fifo_id,
              const unsigned char *data);
int writeFifoWithNoWait(const unsigned int model_id,
                        const unsigned int fifo_id,
                        const unsigned char *data);
int readFifo(const unsigned int model_id,
             const unsigned int fifo_id,
             unsigned char *data);
int readFifoWithNoWait(const unsigned int model_id,
                       const unsigned int fifo_id,
                       unsigned char *data);
unsigned int getFifoSize(const unsigned int model_id,
                         const unsigned int fifo_id);
void waitFifoStatus(const unsigned int model_id,
                    const unsigned int fifo_id,
                    const unsigned char status);
/* Utility */
int makeVcdValue(const unsigned int model_id,
                 const char *name,
                 const unsigned int vcd_id,
                 const unsigned int width,
                 const unsigned long long initial_value);
int setVcdValue(const unsigned int model_id,
                const unsigned int vcd_id,
                const unsigned long long value);
void dumpSimulationTime(const unsigned int model_id);
/* Parameter */
unsigned int getNumberOfAxiIf(const unsigned int model_id);
unsigned int getNumberOfInterrupt(const unsigned int model_id);
unsigned int getNumberOfOutputSignal(const unsigned int model_id);
unsigned int getNumberOfBuffer(const unsigned int model_id);
unsigned int getNumberOfFifo(const unsigned int model_id);
unsigned int getNumberOfThread(const unsigned int model_id);
unsigned int getNumberOfReadOutStanding(const unsigned int model_id);
unsigned int getNumberOfWriteOutStanding(const unsigned int model_id);
bool getNoRReceive(const unsigned int model_id);
bool getNoBReceive(const unsigned int model_id);
const char* getBufferParameterFileName(const unsigned int model_id);
const char* getFifoParameterFileName(const unsigned int model_id);
const char* getOutputVcdFileName(const unsigned int model_id);
const char* getOutputCsvFileName(const unsigned int model_id);
const char* getOutputSummaryFileName(const unsigned int model_id);
sc_time_unit getTimeUnit(const unsigned int model_id);
unsigned int getAxiClock(const unsigned int model_id);
unsigned int getCoreClock(const unsigned int model_id);
unsigned int getNumberOfInternalBuffer(const unsigned int model_id,
                                       const unsigned int buffer_id);
unsigned int getBufferWidth(const unsigned int model_id,
                            const unsigned int buffer_id);
unsigned int getBufferDepth(const unsigned int model_id,
                            const unsigned int buffer_id);
unsigned int getBufferWriteClock(const unsigned int model_id,
                                 const unsigned int buffer_id);
unsigned int getBufferReadClock(const unsigned int model_id,
                                const unsigned int buffer_id);
unsigned int getBufferWriteLatency(const unsigned int model_id,
                                   const unsigned int buffer_id);
unsigned int getBufferReadLatency(const unsigned int model_id,
                                  const unsigned int buffer_id);
unsigned int getFifoWidth(const unsigned int model_id,
                          const unsigned int fifo_id);
unsigned int getFifoDepth(const unsigned int model_id,
                          const unsigned int fifo_id);
unsigned int getFifoWriteClock(const unsigned int model_id,
                               const unsigned int fifo_id);
unsigned int getFifoReadClock(const unsigned int model_id,
                              const unsigned int fifo_id);
unsigned int getFifoWriteLatency(const unsigned int model_id,
                                 const unsigned int fifo_id);
unsigned int getFifoReadLatency(const unsigned int model_id,
                                const unsigned int fifo_id);

#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
/* Cooperarion */
bool getDataInSignal(unsigned int model_id,
                     unsigned int coop_signal_id, 
                     unsigned int *value);
void setDataOutSignal(unsigned int model_id,
                      unsigned int coop_signal_id, 
                      unsigned int value);
unsigned int getDataOutSignal(unsigned int model_id,
                              unsigned int coop_signal_id);

bool getBusyInSignal(unsigned int model_id,
                      unsigned int coop_signal_id);
void setBusyOutSignalWithInit(unsigned int model_id,
                              unsigned int coop_signal_id, 
                              unsigned int value);
bool getBusyOutSignal(unsigned int model_id,
                      unsigned int coop_signal_id);
#endif 

#endif /* DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API_H */
