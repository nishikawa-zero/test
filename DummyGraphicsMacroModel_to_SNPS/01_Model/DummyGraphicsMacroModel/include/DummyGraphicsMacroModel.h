/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModel.h
 * @brief DummyGraphicsMacroModel (header)
 */
#include <systemc.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include "DummyGraphicsMacroModelBase.h"
#include "DummyGraphicsMacroModelPointerApi.h"
#include "TlmAxi3FiveChannelInterface_AXI_CX.h"
#include "DummyGraphicsMacroModelBuffer.h"
#include "DummyGraphicsMacroModelFifo.h"
#include "VcdMaker.h"
#include "CsvParser.h"

#ifndef DUMMY_GRAPHICS_MACRO_MODEL_H
#define DUMMY_GRAPHICS_MACRO_MODEL_H

class DummyGraphicsMacroModel: public sc_module,
                               public DummyGraphicsMacroModelBase {
private:
  typedef std::map<unsigned char, sc_time> StatusTimerMap;
  typedef StatusTimerMap::iterator StatusTimerMapItr ;

  enum BufferParameterFileFormat {
    NUMBER_OF_INTERNAL_BUFFER,
    BUFFER_WIDTH,
    BUFFER_DEPTH,
    BUFFER_WRITE_CLOCK,
    BUFFER_READ_CLOCK,
    BUFFER_WRITE_LATENCY,
    BUFFER_READ_LATENCY,
    SizeOfBufferParameterFileFormat
  };

  enum FifoParameterFileFormat {
    FIFO_WIDTH,
    FIFO_DEPTH,
    FIFO_WRITE_CLOCK,
    FIFO_READ_CLOCK,
    FIFO_WRITE_LATENCY,
    FIFO_READ_LATENCY,
    SizeOfFifoParameterFileFormat
  };

  struct LoggingParameters {
    unsigned int vcd_id;
    sc_time status_start_time;
    StatusTimerMap status_timer_map;
  };

public:
  /*
   * Model Interface
   */
  fj::TlmAxi3FiveChannelInterface_AXI_CX **AXI;
  sc_in<bool> *interrupt;
  sc_out<bool> *output;
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  sc_in<unsigned int>  *data_in;
  sc_in<bool>          *busy_in;
  sc_out<unsigned int> *data_out;
  sc_out<bool>         *busy_out;
#endif

public:
  SC_HAS_PROCESS(DummyGraphicsMacroModel);
  /*
   * Constructor & Destructor
   */
  DummyGraphicsMacroModel(const sc_module_name name,
                          const unsigned int model_id,
                          const unsigned int axi_bus_width,
                          const unsigned int number_of_axi_if,
                          const unsigned int number_of_interrupt,
                          const unsigned int number_of_output_signal,
                          const unsigned int number_of_thread,
                          const unsigned int number_of_read_outstanding,
                          const unsigned int number_of_write_outstanding,
                          const bool no_r_receive,
                          const bool no_b_receive,
                          const sc_time_unit time_unit,
                          const unsigned int axi_clock,
                          const unsigned int core_clock,
                          const char *buffer_parameter_file_name,
                          const char *fifo_parameter_file_name,
                          const char *output_vcd_file_name,
                          const char *output_csv_file_name,
                          const char *output_summary_file_name);
  ~DummyGraphicsMacroModel(void);

  /*
   * Model Setting APIs
   */
  int registerThreadScenario(void (* scenario)(unsigned int, unsigned int));
  int registerInterruptScenario(void (* scenario)(unsigned int, unsigned int));

  int setNumberOfBuffer(const unsigned int number_of_buffer);
  int setNumberOfInternalBuffer(const unsigned int number_of_buffer,
                                const unsigned int number_of_internal_buffer);

private:
  /*
   * Processing Threads
   */
  void spawnThreads(void);
  void Thread(const unsigned int thread_id);
  void Interrupt(const unsigned int interrupt_id);


  /*
   * OutputSignalUpdate Method
   */
  void OutputSignalUpdate(void);

private:
  /*
   * Internal Functions
   */
  inline void checkAxiIfId(const unsigned int axi_if_id);
  inline void checkInterruptId(const unsigned int interrupt_id);
  inline void checkOutputSignalId(const unsigned int output_signal_id);
  inline void checkBufferId(const unsigned int buffer_id);
  inline void checkInternalBufferId(const unsigned int buffer_id,
                                    const unsigned int internal_buffer_id);
  inline void checkFifoId(const unsigned int fif_id);
  inline void checkThreadId(const unsigned int rch_id);
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  inline void checkCoopSignalId(unsigned int coop_signal_id);
#endif
  void readBufferParameterFile(void);
  void readFifoParameterFile(void);
  void openCsvFile(void);
  void dumpCsv(void);
  void flushCsv(void);
  void openSummaryFile(void);
  void dumpSummary(void);

  void end_of_elaboration(void);
  void end_of_simulation(void);

public:
  /*
   * Sceanrio APIs
   */
  /* AXI */
  int sendAw(const unsigned int axi_if_id,
             const unsigned int AWID,
             const unsigned int AWADDR,
             const unsigned int AWLEN,
             const unsigned int AWSIZE,
             const unsigned int AWBURST,
             const unsigned int AWLOCK,
             const unsigned int AWCACHE,
             const unsigned int AWPROT,
             const unsigned int AWUSER);
  int sendAwWithNoWait(const unsigned int axi_if_id,
                       const unsigned int AWID,
                       const unsigned int AWADDR,
                       const unsigned int AWLEN,
                       const unsigned int AWSIZE,
                       const unsigned int AWBURST,
                       const unsigned int AWLOCK,
                       const unsigned int AWCACHE,
                       const unsigned int AWPROT,
                       const unsigned int AWUSER);
  int sendW(const unsigned int axi_if_id,
            const unsigned int WID,
            const unsigned int WLAST,
            const unsigned char* wdata,
            const unsigned char* wstrb);
  int sendWWithNoWait(const unsigned int axi_if_id,
                      const unsigned int WID,
                      const unsigned int WLAST,
                      const unsigned char* wdata,
                      const unsigned char* wstrb);
  int receiveB(const unsigned int axi_if_id,
               unsigned int *BID,
               unsigned int *BRESP);
  int receiveBWithNoWait(const unsigned int axi_if_id,
                         unsigned int *BID,
                         unsigned int *BRESP);
  int receiveBById(const unsigned int axi_if_id,
                   const unsigned int BID,
                   unsigned int *BRESP);
  int receiveBByIdWithNoWait(const unsigned int axi_if_id,
                             const unsigned int BID,
                             unsigned int *BRESP);
  int sendAr(const unsigned int axi_if_id,
             const unsigned int ARID,
             const unsigned int ARADDR,
             const unsigned int ARLEN,
             const unsigned int ARSIZE,
             const unsigned int ARBURST,
             const unsigned int ARLOCK,
             const unsigned int ARCACHE,
             const unsigned int ARPROT,
             const unsigned int ARUSER);
  int sendArWithNoWait(const unsigned int axi_if_id,
                       const unsigned int ARID,
                       const unsigned int ARADDR,
                       const unsigned int ARLEN,
                       const unsigned int ARSIZE,
                       const unsigned int ARBURST,
                       const unsigned int ARLOCK,
                       const unsigned int ARCACHE,
                       const unsigned int ARPROT,
                       const unsigned int ARUSER);
  int receiveR(const unsigned int axi_if_id,
               unsigned int *RID,
               unsigned int *RLAST,
               unsigned int *RRESP,
               unsigned char *rdata);
  int receiveRWithNoWait(const unsigned int axi_if_id,
                         unsigned int *RID,
                         unsigned int *RLAST,
                         unsigned int *RRESP,
                         unsigned char *rdata);
  int receiveRById(const unsigned int axi_if_id,
                   const unsigned int RID,
                   unsigned int *RLAST,
                   unsigned int *RRESP,
                   unsigned char *rdata);
  int receiveRByIdWithNoWait(const unsigned int axi_if_id,
                             const unsigned int RID,
                             unsigned int *RLAST,
                             unsigned int *RRESP,
                             unsigned char *rdata);
  /* Wait */
  void waitAxiCycle(const unsigned int cycle);
  void waitCoreCycle(const unsigned int cycle);
  /* Signal */
  void setOutputSignal(const unsigned int output_signal_id,
                       const bool value);
  bool getOutputSignal(const unsigned int output_signal_id);
  bool getInterruptSignal(const unsigned int interrupt_id);
  /* RreadyControl */
  void setRreadyValue(const bool value);
  void releaseRreadyControl(void);
  bool getRreadyValue(void);
  bool isValidateRreadyControl(void);
  /* Event */
  void waitEvent(const unsigned int event_id);
  void notifyEvent(const unsigned int event_id);
  /* Thread */
  void setThreadStatus(const unsigned int thread_id,
                       const unsigned int status);
  unsigned int getThreadStatus(const unsigned int core_id);
  /* Logging */
  void enableLogging(void);
  void disableLogging(void);
  /* Buffer */
  int writeBuffer(const unsigned int buffer_id,
                  const unsigned char *data);
  int writeBufferWithNoWait(const unsigned int buffer_id,
                            const unsigned char *data);
  int readBuffer(const unsigned int buffer_id,
                 unsigned char *data);
  int readBufferWithNoWait(const unsigned int buffer_id,
                           unsigned char *data);
  unsigned int getWriteBufferSize(const unsigned int buffer_id);
  unsigned int getReadBufferSize(const unsigned int buffer_id);
  void waitWriteBufferStatus(const unsigned int buffer_id,
                             const unsigned char status);
  void waitReadBufferStatus(const unsigned int buffer_id,
                            const unsigned char status);
  void switchWriteBuffer(const unsigned int buffer_id);
  void switchReadBuffer(const unsigned int buffer_id);
  bool isPossibleToSwitchWriteBuffer(const unsigned int buffer_id);
  bool isPossibleToSwitchReadBuffer(const unsigned int buffer_id);
  /* Fifo */
  int writeFifo(const unsigned int fifo_id,
                const unsigned char *data);
  int writeFifoWithNoWait(const unsigned int fifo_id,
                          const unsigned char *data);
  int readFifo(const unsigned int fifo_id,
               unsigned char *data);
  int readFifoWithNoWait(const unsigned int fifo_id,
                         unsigned char *data);
  unsigned int getFifoSize(const unsigned int fifo_id);
  void waitFifoStatus(const unsigned int fifo_id,
                      const unsigned char status);
  /* Utility */
  int makeVcdValue(const char *name,
                   const unsigned int vcd_id,
                   const unsigned int width,
                   const unsigned long long initial_value);
  int setVcdValue(const unsigned int vcd_id,
                   const unsigned long long value);
  void dumpSimulationTime(void);
  /* Parameter */
  inline unsigned int getNumberOfAxiIf(void);
  inline unsigned int getNumberOfInterrupt(void);
  inline unsigned int getNumberOfOutputSignal(void);
  inline unsigned int getNumberOfBuffer(void);
  inline unsigned int getNumberOfFifo(void);
  inline unsigned int getNumberOfThread(void);
  inline unsigned int getNumberOfReadOutStanding(void);
  inline unsigned int getNumberOfWriteOutStanding(void);
  inline bool getNoRReceive(void);
  inline bool getNoBReceive(void);
  inline const char* getBufferParameterFileName(void);
  inline const char* getFifoParameterFileName(void);
  inline const char* getOutputVcdFileName(void);
  inline const char* getOutputCsvFileName(void);
  inline const char* getOutputSummaryFileName(void);
  inline sc_time_unit getTimeUnit(void);
  inline unsigned int getAxiClock(void);
  inline unsigned int getCoreClock(void);
  inline unsigned int getNumberOfInternalBuffer(const unsigned int buffer_id);
  inline unsigned int getBufferWidth(const unsigned int buffer_id);
  inline unsigned int getBufferDepth(const unsigned int buffer_id);
  inline unsigned int getBufferWriteClock(const unsigned int buffer_id);
  inline unsigned int getBufferReadClock(const unsigned int buffer_id);
  inline unsigned int getBufferWriteLatency(const unsigned int buffer_id);
  inline unsigned int getBufferReadLatency(const unsigned int buffer_id);
  inline unsigned int getFifoWidth(const unsigned int fifo_id);
  inline unsigned int getFifoDepth(const unsigned int fifo_id);
  inline unsigned int getFifoWriteClock(const unsigned int fifo_id);
  inline unsigned int getFifoReadClock(const unsigned int fifo_id);
  inline unsigned int getFifoWriteLatency(const unsigned int fifo_id);
  inline unsigned int getFifoReadLatency(const unsigned int fifo_id);
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  /* Cooperarion */
  bool getDataInSignal(unsigned int coop_signal_id, 
                       unsigned int *value);
  void setDataOutSignal(unsigned int coop_signal_id, 
                        unsigned int value);
  unsigned int getDataOutSignal(unsigned int coop_signal_id);

  bool getBusyInSignal(unsigned int coop_signal_id);
  void setBusyOutSignalWithInit(unsigned int coop_signal_id, 
                                unsigned int value);
  bool getBusyOutSignal(unsigned int coop_signal_id);
#endif

private:
  unsigned int m_model_id;
  unsigned int m_axi_bus_width;
  unsigned int m_number_of_axi_if;
  unsigned int m_number_of_interrupt;
  unsigned int m_number_of_output_signal;
  unsigned int m_number_of_thread;
  unsigned int m_number_of_read_outstanding;
  unsigned int m_number_of_write_outstanding;
  bool m_no_r_receive;
  bool m_no_b_receive;
  bool m_rready_validate;
  bool m_rready_value;
  std::string m_buffer_parameter_file_name;
  std::string m_fifo_parameter_file_name;
  std::string m_output_vcd_file_name;
  std::string m_output_csv_file_name;
  std::string m_output_summary_file_name;

  sc_time_unit m_time_unit;
  unsigned int m_axi_clock;
  unsigned int m_core_clock;

  void (* m_thread_scenario)(unsigned int, unsigned int);
  void (* m_interrupt_scenario)(unsigned int, unsigned int);

  unsigned int m_number_of_buffer;
  std::vector<DummyGraphicsMacroModelBuffer*> m_buffers;

  unsigned int m_number_of_fifo;
  std::vector<DummyGraphicsMacroModelFifo*> m_fifos;

  sc_time m_base_time;

  std::map<unsigned int, sc_event> m_event_map;

  sc_event m_outputsignal_update_event;
  bool *m_output;
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  unsigned int *m_data_out;
  bool *m_busy_out;
#endif

  /* for logging */
  bool m_is_logging;
  sc_time m_logging_start_time;
  sc_time m_total_logging_time;

  std::vector<std::vector<LoggingParameters*> > m_buffer_logging_parameters;
  std::vector<LoggingParameters*> m_fifo_logging_parameters;
  std::vector<LoggingParameters*> m_thread_logging_parameters;
  
  std::vector<unsigned char> m_thread_status;

  /* VCD */
  VcdMaker *m_vcd_maker;

  unsigned int m_buffer_vcd_id_count;
  unsigned int m_fifo_vcd_id_count;
  unsigned int m_thread_vcd_id_count;

  const char m_buffer_size_vcd_category;
  const char m_buffer_status_vcd_category;
  const char m_fifo_size_vcd_category;
  const char m_fifo_status_vcd_category;
  const char m_thread_status_vcd_category;
  const char m_user_vcd_category;
  const char m_logging_enable_vcd_category;

  /* CSV */
  sc_time m_pre_dump_csv_time;
  std::stringstream m_tmp_csv_log;
  std::ofstream m_ofs_csv;

  /* summary */
  std::map<unsigned char, unsigned char> m_status_list;
  std::ofstream m_ofs_summary;

#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  /* Cooperarion */
  unsigned int m_previous_data_in[2];
#endif
};
#endif /* DUMMY_GRAPHICS_MACRO_MODEL_H */
