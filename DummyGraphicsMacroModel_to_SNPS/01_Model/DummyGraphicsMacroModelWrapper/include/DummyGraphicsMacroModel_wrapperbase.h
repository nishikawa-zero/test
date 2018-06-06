/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModel_wrapperbase.h
 * @brief DummyGraphicsMacroModel_wrapperbase (header)
 */
#ifndef DUMMY_GRAPHICS_MACRO_MODEL_WRAPPERBASE_H
#define DUMMY_GRAPHICS_MACRO_MODEL_WRAPPERBASE_H

#include <string.h>

#include "tlm_axi_transreceiver.h"
#include "OutputSignalReceiver.h"
#include "DummyGraphicsMacroModel.h"
#include "fj_datatype.h"

template<class DataType, unsigned int NumberOfAxiIf = 1>
class DummyGraphicsMacroModel_wrapperbase {
public:
  DummyGraphicsMacroModel_wrapperbase(fj::uint32 model_id,
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
                                      const char *output_summary_file_name);
  
  ~DummyGraphicsMacroModel_wrapperbase(void);

public:
  tlm_axi_transreceiver<DataType>   *m_transreceiver[NumberOfAxiIf];
  
  /* input signals */
  sc_signal<bool> m_interrupt[4];

  /* output signals */
  OutputSignalReceiver<bool> *m_output_receiver;

  DummyGraphicsMacroModel<DataType> *m_kernel;

};
#endif /* DUMMY_GRAPHICS_MACRO_MODEL_WRAPPERBASE_H */

