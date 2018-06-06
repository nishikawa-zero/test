/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file BufferlessModel_wrapperbase.cpp
 * @brief BufferlessModel_wrapperbase (source)
 */
#include "BufferlessModel_wrapperbase.h"
#include "BufferlessModel_Scenario.h"

BufferlessModel_wrapperbase::BufferlessModel_wrapperbase(fj::uint32 model_id,
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
                                 ) {
  
  m_arbiter = new TlmAxiArbiter("arbiter", 1);
  
  m_output_receiver = new OutputSignalReceiver<bool>("output_transreceiver", 4, false);
  
  m_kernel = new DummyGraphicsMacroModel("kernel",                    /* name */
                                         model_id,                    /* model_id */
                                         axi_bus_width,               /* axi_bus_width */
                                         1,                           /* ax_if_number */
                                         4,                           /* interrupt_number */
                                         4,                           /* output_signal_number */
                                         number_of_thread,            /* number_of_thread */
                                         number_of_read_outstanding,  /* number_of_read_outstanding */
                                         number_of_write_outstanding, /* number_of_write_outstanding */
                                         no_r_receive,                /* no_r_receive */
                                         no_b_receive,                /* no_b_receive */
                                         time_unit,                   /* time_unit */
                                         axi_clock,                   /* axi_clock */
                                         core_clock,                  /* core_clock */
                                         buffer_parameter_file_name,  /* buffer_parameter_file_name */
                                         fifo_parameter_file_name,    /* fifo_parameter_file_name */
                                         output_vcd_file_name,        /* output_vcd_file_name */
                                         output_csv_file_name,        /* output_csv_file_name */
                                         output_summary_file_name     /* output_summary_file_name */
                                         );
  
  m_kernel->interrupt[0](m_interrupt[0]);
  m_kernel->interrupt[1](m_interrupt[1]);
  m_kernel->interrupt[2](m_interrupt[2]);
  m_kernel->interrupt[3](m_interrupt[3]);
  m_kernel->output[0](m_output_receiver->signals[0]);
  m_kernel->output[1](m_output_receiver->signals[1]);
  m_kernel->output[2](m_output_receiver->signals[2]);
  m_kernel->output[3](m_output_receiver->signals[3]);

  m_kernel->registerThreadScenario(BufferlessModel_ScenarioThread);
  m_kernel->registerInterruptScenario(BufferlessModel_ScenarioInterrupt);

  m_kernel->AXI[0]->m_primitive.initiator_AW(m_arbiter->m_slave_if[0]->target_AW);
  m_kernel->AXI[0]->m_primitive.initiator_W(m_arbiter->m_slave_if[0]->target_W);
  m_arbiter->m_slave_if[0]->target_B(m_kernel->AXI[0]->m_primitive.initiator_B);
  m_kernel->AXI[0]->m_primitive.initiator_AR(m_arbiter->m_slave_if[0]->target_AR);
  m_arbiter->m_slave_if[0]->target_R(m_kernel->AXI[0]->m_primitive.initiator_R);
  
}

BufferlessModel_wrapperbase ::~BufferlessModel_wrapperbase(void) {
  delete m_arbiter;
  delete m_output_receiver;
  delete m_kernel;
}

