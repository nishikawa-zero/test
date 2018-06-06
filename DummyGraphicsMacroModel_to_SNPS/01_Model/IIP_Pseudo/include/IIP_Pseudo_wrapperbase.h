/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file IIP_Pseudo_wrapperbase.h
 * @brief IIP_Pseudo_wrapperbase (header)
 */
#ifndef IIP_Pseudo_WRAPPERBASE_H
#define IIP_Pseudo_WRAPPERBASE_H

#include <string.h>

#include "TlmAxiArbiter.h"
#include "OutputSignalReceiver.h"
#include "DummyGraphicsMacroModel.h"
#include "fj_datatype.h"

class IIP_Pseudo_wrapperbase {
public:
  IIP_Pseudo_wrapperbase(fj::uint32 model_id,
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
  
  ~IIP_Pseudo_wrapperbase(void);

public:
  TlmAxiArbiter *m_arbiter[1];
  
  /* input signals */
  sc_signal<bool> m_interrupt[4];

  /* output signals */
  OutputSignalReceiver<bool> *m_output_receiver;
  OutputSignalReceiver<fj::uint32> *m_data_out_receiver;
  OutputSignalReceiver<bool> *m_busy_out_receiver;

  /* stub */
  sc_signal<fj::uint32> m_data_in[2];
  sc_signal<bool> m_busy_in[2];

  DummyGraphicsMacroModel *m_kernel;

};
#endif /* IIP_Pseudo_WRAPPERBASE_H */

