/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file BufferlessModel_wrapperbase.h
 * @brief BufferlessModel_wrapperbase (header)
 */
#ifndef BufferlessModel_WRAPPERBASE_H
#define BufferlessModel_WRAPPERBASE_H

#include <string.h>

#include "TlmAxiArbiter.h"
#include "OutputSignalReceiver.h"
#include "DummyGraphicsMacroModel.h"
#include "fj_datatype.h"

class BufferlessModel_wrapperbase {
public:
  BufferlessModel_wrapperbase(fj::uint32 model_id,
                  fj::uint32 axi_bus_width,
                  fj::uint32 number_of_thread,
                  fj::uint32 number_of_read_outstanding,
                  fj::uint32 number_of_write_outstanding,
                  bool no_r_receive,
                  bool no_b_receive,
                  sc_time_unit time_unit,
                  fj::uint32 axi_clock,
                  fj::uint32 core_clock,
                  const char *buffer_parameter_file_name,
                  const char *fifo_parameter_file_name,
                  const char *output_vcd_file_name,
                  const char *output_csv_file_name,
                  const char *output_summary_file_name
                   );
  
  ~BufferlessModel_wrapperbase(void);

public:
  TlmAxiArbiter *m_arbiter;
  
  /* input signals */
  sc_signal<bool> m_interrupt[4];

  /* output signals */
  OutputSignalReceiver<bool> *m_output_receiver;

  DummyGraphicsMacroModel *m_kernel;

};
#endif /* BufferlessModel_WRAPPERBASE_H */

