/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2010
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file tlm_axi_transreceiver.cpp
 * @brief Receive transaction from BusMaster (source)
 */
#include "tlm_axi_transreceiver.h"
#include <iostream>

tlm_axi_transreceiver::tlm_axi_transreceiver(sc_module_name name) :
  sc_module(name),
  m_aw_transaction(NULL),
  m_w_transaction(NULL),
  m_ar_transaction(NULL),
  m_b_transaction(NULL),
  m_r_transaction(NULL),
  m_aw_transaction_bw(NULL),
  m_w_transaction_bw(NULL),
  m_ar_transaction_bw(NULL)
{
#ifdef TLM_AXI_TRANSRECEIVER_DEBUG
  std::cout << "tlm_axi_transreceiver constructor start" << std::endl;
#endif
  SC_THREAD(TransactionController); sensitive << m_clk.pos(); dont_initialize();

#ifdef TLM_AXI_TRANSRECEIVER_DEBUG
  std::cout << "tlm_axi_transreceiver constructor finish" << std::endl;
#endif
}

tlm_axi_transreceiver::~tlm_axi_transreceiver(void)
{
}

tlm::tlm_sync_enum
tlm_axi_transreceiver::target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                            tlm::tlm_phase&           phase,
                                                            sc_core::sc_time&         t) 
{
#ifdef TLM_AXI_TRANSRECEIVER_DEBUG
  cout << __FUNCTION__ << " start "<< sc_time_stamp() << endl;
#endif

  TlmAxi3Payload* tmp_payload_axi = NULL;
  tlm::tlm_sync_enum      result(tlm::TLM_ACCEPTED);

  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);

  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if(!tmp_payload_axi) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check controlAW(SC_THREAD) finished */
  if(m_aw_transaction || m_aw_transaction_bw) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  if(trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) 
  {
    /* Copy axi_generic_payload */
    m_aw_transaction = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
  }
  else
  {
    std::cout << "AW Transaction does not exist." << std::endl;
  }

  return result;
}

tlm::tlm_sync_enum
tlm_axi_transreceiver::target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                           tlm::tlm_phase&           phase,
                                                           sc_core::sc_time&         t) 
{
  TlmAxi3Payload* tmp_payload_axi = NULL;
  tlm::tlm_sync_enum      result(tlm::TLM_ACCEPTED);

  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);

  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if(!tmp_payload_axi) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check controlW(SC_THREAD) finished */
  if(m_w_transaction || m_w_transaction_bw) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  if(trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) 
  {
    /* Copy axi_generic_payload */
    m_w_transaction = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
  }
  else
  {
    std::cout << "W Transaction does not exist." << std::endl;
  }

  return result;
}

tlm::tlm_sync_enum
tlm_axi_transreceiver::target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                            tlm::tlm_phase&           phase,
                                                            sc_core::sc_time&         t) 
{
  TlmAxi3Payload* tmp_payload_axi = NULL;
  tlm::tlm_sync_enum      result(tlm::TLM_ACCEPTED);

  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);

  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if(!tmp_payload_axi) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check controlAR(SC_THREAD) finished */
  if(m_ar_transaction || m_ar_transaction_bw) 
  {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  if(trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) 
  {
    /* Copy axi_generic_payload */
    m_ar_transaction = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
  }
  else
  {
    std::cout << "AR Transaction does not exist." << std::endl;
  }

  return result;
}

tlm::tlm_sync_enum
tlm_axi_transreceiver::target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                           tlm::tlm_phase&           phase,
                                                           sc_core::sc_time&         t) 
{
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

  /* do nothing */
  return result;
}

tlm::tlm_sync_enum
tlm_axi_transreceiver::target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                           tlm::tlm_phase&           phase,
                                                           sc_core::sc_time&         t) 
{
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

  /* do nothing */
  return result;
}

void
tlm_axi_transreceiver::TransactionController(void)
{
  while (1) {
     /* backword AW transaction */
    {
      if (m_aw_transaction_bw != NULL) {
        tlm::tlm_phase phase(tlm::BEGIN_REQ);
        sc_time latency(0, SC_NS);
        
        /* Variable declaration */
        tlm::tlm_generic_payload payload_tlm;
        TlmAxi3Payload*  tmp_payload_axi = NULL;
        
        /* Set TlmAxi3Payload to tlm_generic_payload */
        tmp_payload_axi = new TlmAxi3Payload(m_aw_transaction_bw->getByteSize()); // ’ŠÛƒvƒ‚Åget_extension‚µ‚Ä‚¢‚é‚Ì‚Å
        payload_tlm.set_extension(tmp_payload_axi);     // ‰¼‚Å‹l‚ß‚Ä‚¨‚­
        
        /* Receive W response */
        target_AW->nb_transport_bw(payload_tlm, phase, latency);
        
        /* Delete TlmAxi3Payload */
        payload_tlm.release_extension(tmp_payload_axi);
        tmp_payload_axi = NULL;

        delete m_aw_transaction_bw;
        m_aw_transaction_bw =NULL;
      }
    }

    /* backword W transaction */
    {
      if (m_w_transaction_bw != NULL) {
        tlm::tlm_phase phase(tlm::BEGIN_REQ);
        sc_time latency(0, SC_NS);
        
        /* Variable declaration */
        tlm::tlm_generic_payload payload_tlm;
        TlmAxi3Payload*  tmp_payload_axi = NULL;
        
        /* Set TlmAxi3Payload to tlm_generic_payload */
        tmp_payload_axi = new TlmAxi3Payload(m_w_transaction_bw->getByteSize()); // ’ŠÛƒvƒ‚Åget_extension‚µ‚Ä‚¢‚é‚Ì‚Å
        payload_tlm.set_extension(tmp_payload_axi);     // ‰¼‚Å‹l‚ß‚Ä‚¨‚­
        
        /* Receive W response */
        target_W->nb_transport_bw(payload_tlm, phase, latency);
        
        /* Delete TlmAxi3Payload */
        payload_tlm.release_extension(tmp_payload_axi);
        tmp_payload_axi = NULL;

        delete m_w_transaction_bw;
        m_w_transaction_bw =NULL;
      }
    }    

    /* backword AR transaction */
    {
      if (m_ar_transaction_bw != NULL) {
        tlm::tlm_phase phase(tlm::BEGIN_REQ);
        sc_time latency(0, SC_NS);
        
        /* Variable declaration */
        tlm::tlm_generic_payload payload_tlm;
        TlmAxi3Payload*  tmp_payload_axi = NULL;
        
        /* Set TlmAxi3Payload to tlm_generic_payload */
        tmp_payload_axi = new TlmAxi3Payload(m_ar_transaction_bw->getByteSize()); // ’ŠÛƒvƒ‚Åget_extension‚µ‚Ä‚¢‚é‚Ì‚Å
        payload_tlm.set_extension(tmp_payload_axi);     // ‰¼‚Å‹l‚ß‚Ä‚¨‚­
        
        /* Receive W response */
        target_AR->nb_transport_bw(payload_tlm, phase, latency);
        
        /* Delete TlmAxi3Payload */
        payload_tlm.release_extension(tmp_payload_axi);
        tmp_payload_axi = NULL;

        delete m_ar_transaction_bw;
        m_ar_transaction_bw =NULL;
      }
    }

    /* forward B transaction */
    {
      if(m_b_transaction != NULL) {
        tlm::tlm_phase phase(tlm::BEGIN_REQ);
        sc_time latency(0, SC_NS);
        tlm::tlm_generic_payload payload_tlm;
        
        /* Check BRESP */
        switch(m_b_transaction->getBRESP()) {
        case 0x0:
          break;
        case 0x1:
          break;
        case 0x2:
          std::cout << "B Transaction slave error." << std::endl;
          break;
        case 0x3:
          std::cout << "B Transaction decode error." << std::endl;
          break;
        default:
          std::cout << "Undefined value BRESP." << std::endl;
          break;
        }
        
        /* Set TlmAxi3Payload to generic_payload */
        payload_tlm.set_extension(m_b_transaction);
        
        /* Send B request */
        target_B->nb_transport_fw(payload_tlm, phase, latency);

        payload_tlm.release_extension(m_b_transaction); // free B transaction
        m_b_transaction = NULL;        
      }
    }
    
    /* forward R transaction */
    {
      if (m_r_transaction != NULL) {
        tlm::tlm_phase phase(tlm::BEGIN_REQ);
        sc_time latency(0, SC_NS);
        tlm::tlm_generic_payload payload_tlm;
        
        /* Check RRESP */
        switch(m_r_transaction->getRRESP()) {
        case 0x0:
          break;
        case 0x1:
          break;
        case 0x2:
          std::cout << "R Transaction slave error." << std::endl;
          break;
        case 0x3:
          std::cout << "R Transaction decode error." << std::endl;
          break;
        default:
          std::cout << "Undefined value RRESP." << std::endl;
          break;
        }
        
        /* Set TlmAxi3Payload to generic_payload */
        payload_tlm.set_extension(m_r_transaction);
        
        /* Send R request */
#if 0
        std::cout << sc_time_stamp() <<" target_R->nb_transport_fw begin" << std::endl;
#endif
        target_R->nb_transport_fw(payload_tlm, phase, latency);
#if 0
        std::cout << sc_time_stamp() <<" target_R->nb_transport_fw end" << std::endl;
#endif
        payload_tlm.release_extension(m_r_transaction); // free R transaction
        m_r_transaction = NULL;
      }
    }

    wait();
  }
}


TlmAxi3Payload*
tlm_axi_transreceiver::frontAWTransaction(void)
{
  if(m_aw_transaction == NULL)
  {
    /* AW Transaction does not exist */
    return NULL;
  }
  else
  {
    /* AW Transaction exists */
    return m_aw_transaction;
  }
}

void
tlm_axi_transreceiver::popAWTransaction(void)
{
  if(m_aw_transaction == NULL)
  {
    std::cout << "AWTransaction already doesn't exist." << std::endl;
  }
  else
  {
    // delete m_aw_transaction;
    m_aw_transaction_bw = m_aw_transaction;
    m_aw_transaction = NULL;
  }
}

TlmAxi3Payload*
tlm_axi_transreceiver::frontWTransaction(void)
{
  if(m_w_transaction == NULL)
  {
    /* W Transaction does not exist */
    return NULL;
  }
  else
  {
    /* W Transaction exists */
    return m_w_transaction;
  }
}

void
tlm_axi_transreceiver::popWTransaction(void)
{
  if(m_w_transaction == NULL)
  {
    std::cout << "WTransaction already doesn't exist." << std::endl;
  }
  else
  {
    // delete m_w_transaction;
    m_w_transaction_bw = m_w_transaction;
    m_w_transaction = NULL;
  }
}

TlmAxi3Payload*
tlm_axi_transreceiver::frontARTransaction(void)
{
  if(m_ar_transaction == NULL)
  {
    /* AR Transaction does not exist */
    return NULL;
  }
  else
  {
    /* AR Transaction exists */
    return m_ar_transaction;
  }
}

void
tlm_axi_transreceiver::popARTransaction(void)
{
  if(m_ar_transaction == NULL)
  {
    std::cout << "ARTransaction already doesn't exist." << std::endl;
  }
  else
  {
    // delete m_ar_transaction;
    m_ar_transaction_bw = m_ar_transaction;
    m_ar_transaction = NULL;
  }
}

void
tlm_axi_transreceiver::pushBTransaction(TlmAxi3Payload* b_transaction)
{
  if (m_b_transaction == NULL) {
    m_b_transaction = b_transaction;
  }
}

void
tlm_axi_transreceiver::pushRTransaction(TlmAxi3Payload* r_transaction)
{
  if (m_r_transaction == NULL) {
    m_r_transaction = r_transaction;
  }
}
