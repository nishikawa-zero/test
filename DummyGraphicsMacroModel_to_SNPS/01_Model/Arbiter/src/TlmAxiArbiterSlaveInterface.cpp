/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file TlmAxiArbiterSlaveInterface.h
 * @brief Slave interface for TLM-AXI arbiter (header)
 */
#include "TlmAxiArbiterSlaveInterface.h"
#include <iostream>

TlmAxiArbiterSlaveInterface::TlmAxiArbiterSlaveInterface(sc_module_name name):
  sc_module(name),
  m_aw_transaction(NULL),
  m_w_transaction(NULL),
  m_ar_transaction(NULL),
  m_b_transaction(NULL),
  m_r_transaction(NULL) {
}

TlmAxiArbiterSlaveInterface::~TlmAxiArbiterSlaveInterface(void) {
}

tlm::tlm_sync_enum
TlmAxiArbiterSlaveInterface::target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                                  tlm::tlm_phase&           phase,
                                                                  sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi = NULL;
  tlm::tlm_sync_enum      result(tlm::TLM_ACCEPTED);
  
  trans.get_extension(tmp_payload_axi);
  
  if (tmp_payload_axi == NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (m_aw_transaction != NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE)  {
    m_aw_transaction = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
  } else {
    std::cout << "AW Transaction does not exist." << std::endl;
  }
  
  return result;
}

tlm::tlm_sync_enum
TlmAxiArbiterSlaveInterface::target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                                 tlm::tlm_phase&           phase,
                                                                 sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi = NULL;
  tlm::tlm_sync_enum      result(tlm::TLM_ACCEPTED);

  trans.get_extension(tmp_payload_axi);

  if (tmp_payload_axi == NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (m_w_transaction != NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    m_w_transaction = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
  } else {
    std::cout << "W Transaction does not exist." << std::endl;
  }
  
  return result;
}

tlm::tlm_sync_enum
TlmAxiArbiterSlaveInterface::target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                                  tlm::tlm_phase&           phase,
                                                                  sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi = NULL;
  tlm::tlm_sync_enum      result(tlm::TLM_ACCEPTED);
  
  trans.get_extension(tmp_payload_axi);
  
  if (tmp_payload_axi == NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (m_ar_transaction != NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    m_ar_transaction = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
  } else {
    std::cout << "AR Transaction does not exist." << std::endl;
  }
  
  return result;
}

tlm::tlm_sync_enum
TlmAxiArbiterSlaveInterface::target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                                 tlm::tlm_phase&           phase,
                                                                 sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

  if (m_b_transaction != NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    m_b_transaction = NULL;
  }

  return result;
}

tlm::tlm_sync_enum
TlmAxiArbiterSlaveInterface::target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                                 tlm::tlm_phase&           phase,
                                                                 sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  if (m_r_transaction != NULL) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
    m_r_transaction = NULL;
  }

  return result;
}

bool
TlmAxiArbiterSlaveInterface::isAw(void) {
  if (m_aw_transaction) {
    return true;
  } else {
    return false;
  }
}

bool
TlmAxiArbiterSlaveInterface::isW(void) {
  if (m_w_transaction) {
    return true;
  } else {
    return false;
  }
}

bool
TlmAxiArbiterSlaveInterface::isAr(void) {
  if (m_ar_transaction) {
    return true;
  } else {
    return false;
  }
}

bool
TlmAxiArbiterSlaveInterface::isB(void) {
  if (m_b_transaction) {
    return true;
  } else {
    return false;
  }
}

bool
TlmAxiArbiterSlaveInterface::isR(void) {
  if (m_r_transaction) {
    return true;
  } else {
    return false;
  }
}

TlmAxi3Payload*
TlmAxiArbiterSlaveInterface::referAw(void) {
  return m_aw_transaction;
}

TlmAxi3Payload*
TlmAxiArbiterSlaveInterface::referW(void) {
  return m_w_transaction;
}

TlmAxi3Payload*
TlmAxiArbiterSlaveInterface::referAr(void) {
  return m_ar_transaction;
}

int
TlmAxiArbiterSlaveInterface::receiveAw(void) {
  int result = 0;

  if (m_aw_transaction == NULL) {
    result = -1;
  } else {
    tlm::tlm_phase phase(tlm::BEGIN_REQ);
    sc_time latency(0, SC_NS);
    
    /* Variable declaration */
    tlm::tlm_generic_payload payload_tlm;
    TlmAxi3Payload *tmp_payload_axi = NULL;
    
    /* Set TlmAxi3Payload to tlm_generic_payload */
    tmp_payload_axi = new TlmAxi3Payload(m_aw_transaction->getByteSize()); // 抽象プロでget_extensionしているので
    payload_tlm.set_extension(tmp_payload_axi);     // 仮で詰めておく
    
    /* Receive W response */
    target_AW->nb_transport_bw(payload_tlm, phase, latency);
    
    /* Delete TlmAxi3Payload */
    payload_tlm.release_extension(tmp_payload_axi);
    tmp_payload_axi = NULL;

    delete m_aw_transaction;
    m_aw_transaction = NULL;
  }

  return result;
}

int
TlmAxiArbiterSlaveInterface::receiveW(void) {
  int result = 0;

  if (m_w_transaction == NULL) {
    result = -1;
  } else {
    tlm::tlm_phase phase(tlm::BEGIN_REQ);
    sc_time latency(0, SC_NS);
    
    /* Variable declaration */
    tlm::tlm_generic_payload payload_tlm;
    TlmAxi3Payload *tmp_payload_axi = NULL;
    
    /* Set TlmAxi3Payload to tlm_generic_payload */
    tmp_payload_axi = new TlmAxi3Payload(m_w_transaction->getByteSize()); // 抽象プロでget_extensionしているので
    payload_tlm.set_extension(tmp_payload_axi);     // 仮で詰めておく
    
    /* Receive W response */
    target_W->nb_transport_bw(payload_tlm, phase, latency);
    
    /* Delete TlmAxi3Payload */
    payload_tlm.release_extension(tmp_payload_axi);
    tmp_payload_axi = NULL;

    delete m_w_transaction;
    m_w_transaction = NULL;
  }

  return result;
}

int
TlmAxiArbiterSlaveInterface::receiveAr(void) {
  int result = 0;

  if (m_ar_transaction == NULL) {
    result = -1;
  } else {
    tlm::tlm_phase phase(tlm::BEGIN_REQ);
    sc_time latency(0, SC_NS);
    
    /* Variable declaration */
    tlm::tlm_generic_payload payload_tlm;
    TlmAxi3Payload *tmp_payload_axi = NULL;
    
    /* Set TlmAxi3Payload to tlm_generic_payload */
    tmp_payload_axi = new TlmAxi3Payload(m_ar_transaction->getByteSize()); // 抽象プロでget_extensionしているので
    payload_tlm.set_extension(tmp_payload_axi);     // 仮で詰めておく
    
    /* Receive W response */
    target_AR->nb_transport_bw(payload_tlm, phase, latency);
    
    /* Delete TlmAxi3Payload */
    payload_tlm.release_extension(tmp_payload_axi);
    tmp_payload_axi = NULL;

    delete m_ar_transaction;
    m_ar_transaction = NULL;
  }

  return result;
}

int
TlmAxiArbiterSlaveInterface::sendB(TlmAxi3Payload *b_transaction) {
  int result = 0;
  
  if ((b_transaction == NULL) || (m_b_transaction != NULL)) {
    result = -1;
  } else {
    tlm::tlm_phase phase(tlm::BEGIN_REQ);
    sc_time latency(0, SC_NS);
    tlm::tlm_generic_payload payload_tlm;

    m_b_transaction = b_transaction;
    payload_tlm.set_extension(m_b_transaction);
    target_B->nb_transport_fw(payload_tlm, phase, latency);
    
    payload_tlm.release_extension(m_b_transaction);
  }

  return result;
}

int
TlmAxiArbiterSlaveInterface::sendR(TlmAxi3Payload *r_transaction) {
  int result = 0;
  
  if ((r_transaction == NULL) || (m_r_transaction != NULL)) {
    result = -1;
  } else {
    tlm::tlm_phase phase(tlm::BEGIN_REQ);
    sc_time latency(0, SC_NS);
    tlm::tlm_generic_payload payload_tlm;

    m_r_transaction = r_transaction;
    payload_tlm.set_extension(m_r_transaction);

    target_R->nb_transport_fw(payload_tlm, phase, latency);
    
    payload_tlm.release_extension(m_r_transaction);
  }

  return result;
}
