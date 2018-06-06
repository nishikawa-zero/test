/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file TlmAxiArbiterSlaveInterface.h
 * @brief Slave interface for TLM-AXI arbiter (header)
 */
#ifndef TLM_AXI_ARBITER_SLAVE_INTERFACE_H
#define TLM_AXI_ARBITER_SLAVE_INTERFACE_H

#include <systemc>
#include <queue>
#include <tlm.h>
#include "TlmAxi3TargetBaseIf.h"
#include "TlmAxi3Payload.h"
#include "fj_datatype.h"

class TlmAxiArbiterSlaveInterface: public sc_module,
                                   public TlmAxi3TargetBaseIf {
public:
  SC_HAS_PROCESS(TlmAxiArbiterSlaveInterface);
  
  TlmAxiArbiterSlaveInterface(sc_module_name name);
  ~TlmAxiArbiterSlaveInterface(void);
  
  tlm::tlm_sync_enum target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                               tlm::tlm_phase&           phase,
                                               sc_core::sc_time&         t);
  tlm::tlm_sync_enum target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase&           phase,
                                              sc_core::sc_time&         t);
  tlm::tlm_sync_enum target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                               tlm::tlm_phase&           phase,
                                               sc_core::sc_time&         t);
  tlm::tlm_sync_enum target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase&           phase,
                                              sc_core::sc_time&         t);
  tlm::tlm_sync_enum target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                              tlm::tlm_phase&           phase,
                                              sc_core::sc_time&         t);
  
  bool isAw(void);
  bool isW(void);
  bool isAr(void);
  bool isB(void);
  bool isR(void);

  TlmAxi3Payload* referAw(void);
  TlmAxi3Payload* referW(void);
  TlmAxi3Payload* referAr(void);
  
  int receiveAw(void);
  int receiveW(void);
  int receiveAr(void);
  
  int sendB(TlmAxi3Payload *b_transaction);
  int sendR(TlmAxi3Payload *r_transaction);

private:
  TlmAxi3Payload *m_aw_transaction; /**< AWTransaction */
  TlmAxi3Payload *m_w_transaction;  /**< WTransaction */
  TlmAxi3Payload *m_ar_transaction; /**< ARTransaction */
  TlmAxi3Payload *m_b_transaction;  /**< WTransaction */
  TlmAxi3Payload *m_r_transaction; /**< ARTransaction */
};
#endif /* TLM_AXI_ARBITER_SLAVE_INTERFACE_H */
