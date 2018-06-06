/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file TlmAxiArbiter.h
 * @brief TLM-AXI arbiter (header)
 */
#include "TlmAxiArbiter.h"
#include <iostream>

TlmAxiArbiter::TlmAxiArbiter(sc_module_name name,
                             unsigned int number_of_slave_if) :
  sc_module(name),
  m_aw_transaction(NULL),
  m_w_transaction(NULL),
  m_ar_transaction(NULL),
  m_b_transaction(NULL),
  m_r_transaction(NULL),
  m_aw_transaction_bw(NULL),
  m_w_transaction_bw(NULL),
  m_ar_transaction_bw(NULL),
  m_b_transaction_bw(NULL),
  m_r_transaction_bw(NULL),
  m_number_of_slave_if(number_of_slave_if),
  m_current_aw_if(NO_INTERFACE),
  m_current_w_if(NO_INTERFACE),
  m_current_ar_if(NO_INTERFACE),
  m_current_b_if(NO_INTERFACE),
  m_current_r_if(NO_INTERFACE) {

  m_slave_if = new TlmAxiArbiterSlaveInterface*[m_number_of_slave_if];
 
  for (unsigned int i = 0; i < m_number_of_slave_if; ++i) {
    std::stringstream ss;
    std::string if_name;

    ss << "slave" << i;
    ss >> if_name;

    m_slave_if[i] = new TlmAxiArbiterSlaveInterface(if_name.c_str());;
    m_write_priority.push_back(i);
    m_read_priority.push_back(i);
  }

  SC_THREAD(TransactionController); sensitive << m_clk.pos(); dont_initialize();
}

TlmAxiArbiter::~TlmAxiArbiter(void) {
  for (unsigned int i = 0; i < m_number_of_slave_if; ++i) {
    delete m_slave_if[i];
  }
  delete m_slave_if;
}

void
TlmAxiArbiter::TransactionController(void) {
  while (1) {
    /* AW */
    {
      /* backword AW transaction */
      if (m_aw_transaction_bw != NULL) {
        //delete m_aw_transaction_bw;
        m_aw_transaction_bw = NULL;
        m_slave_if[m_current_aw_if]->receiveAw();
        m_current_aw_if = NO_INTERFACE;
      }
    }
    
    /* W */
    {
      /* backword W transaction */
      if (m_w_transaction_bw != NULL) {
        //delete m_w_transaction_bw;
        m_w_transaction_bw =NULL;
        m_slave_if[m_current_w_if]->receiveW();
        m_current_w_if = NO_INTERFACE;
      }
    }

    /* AR */
    {
      /* backword AR transaction */
      if (m_ar_transaction_bw != NULL) {
        //delete m_ar_transaction_bw;
        m_ar_transaction_bw = NULL;
        m_slave_if[m_current_ar_if]->receiveAr();
        m_current_ar_if = NO_INTERFACE;
      }
    }

    /* B */
    {
      /* backward B transaction */
      if ((m_b_transaction_bw != NULL)) {
        if (!m_slave_if[m_current_b_if]->isB()) {
          m_b_transaction_bw = NULL;
        }
      }

      /* forward B transaction */
      if (m_b_transaction != NULL) {
        m_current_b_if = getBIfNumber();
        if (m_current_b_if != NO_INTERFACE) {
          m_slave_if[m_current_b_if]->sendB(m_b_transaction);
          m_b_transaction_bw = m_b_transaction;
          m_b_transaction = NULL;
        }
      }
    }

    /* R */
    {
      /* backward R transaction */
      if ((m_r_transaction_bw != NULL)) {
        if (!m_slave_if[m_current_r_if]->isR()) {
          m_r_transaction_bw = NULL;
        }
      }
      /* forward R transaction */
      if ((m_r_transaction != NULL) && (m_r_transaction_bw == NULL)) {
        m_current_r_if = getRIfNumber();
        if (m_current_r_if != NO_INTERFACE) {
#if 0
          std::cout << "m_slave_if[" << m_current_r_if << "]->sendR(m_r_transaction)" << std::endl;;
#endif
          m_slave_if[m_current_r_if]->sendR(m_r_transaction);
          m_r_transaction_bw = m_r_transaction;
          m_r_transaction = NULL;
        }
      }
    }

    wait();
  }
}


TlmAxi3Payload*
TlmAxiArbiter::frontAWTransaction(void) {
  /* forword AW transaction */
  if ((m_aw_transaction == NULL) && (m_aw_transaction_bw == NULL)) {
    m_current_aw_if = getAwIfNumber();
    if (m_current_aw_if != NO_INTERFACE) {
      m_aw_transaction = m_slave_if[m_current_aw_if]->referAw();
      
      History *w_history = new History;
      History *b_history = new History;
      
      w_history->axi_id = m_aw_transaction->getAWID();
      w_history->if_number = m_current_aw_if;
      b_history->axi_id = m_aw_transaction->getAWID();
      b_history->if_number = m_current_aw_if;
      
      m_w_histories.push_back(w_history);
      m_b_histories.push_back(b_history);
    }
  }
  return m_aw_transaction;
}

void
TlmAxiArbiter::popAWTransaction(void) {
  if(m_aw_transaction == NULL) {
    std::cout << "AWTransaction already doesn't exist." << std::endl;
  } else {
    // delete m_aw_transaction;
    m_aw_transaction_bw = m_aw_transaction;
    m_aw_transaction = NULL;
  }
}

TlmAxi3Payload*
TlmAxiArbiter::frontWTransaction(void)
{
  /* forword W transaction */
  if ((m_w_transaction == NULL) && (m_w_transaction_bw == NULL)) {
    m_current_w_if = getWIfNumber();
    if (m_current_w_if != NO_INTERFACE) {
      m_w_transaction = m_slave_if[m_current_w_if]->referW();
    }
  }
  return m_w_transaction;
}

void
TlmAxiArbiter::popWTransaction(void) {
  if(m_w_transaction == NULL) {
    std::cout << "WTransaction already doesn't exist." << std::endl;
  } else {
    // delete m_w_transaction;
    m_w_transaction_bw = m_w_transaction;
    m_w_transaction = NULL;
  }
}

TlmAxi3Payload*
TlmAxiArbiter::frontARTransaction(void) {
  /* forword AR transaction */
  if ((m_ar_transaction == NULL) && (m_ar_transaction_bw == NULL)) {
    m_current_ar_if = getArIfNumber();
    if (m_current_ar_if != NO_INTERFACE) {
      m_ar_transaction = m_slave_if[m_current_ar_if]->referAr();
      
      History *r_history = new History;
      
      r_history->axi_id = m_ar_transaction->getARID();
      r_history->if_number = m_current_ar_if;
      
      //std::cout << __FUNCTION__ << " r_history->axi_id=" << r_history->axi_id << ",r_history->if_number=" << r_history->if_number << std::endl;
      
      m_r_histories.push_back(r_history);
    }
  }
  return m_ar_transaction;  
}

void
TlmAxiArbiter::popARTransaction(void) {
  if(m_ar_transaction == NULL) {
    std::cout << "ARTransaction already doesn't exist." << std::endl;
  } else {
    // delete m_ar_transaction;
    m_ar_transaction_bw = m_ar_transaction;
    m_ar_transaction = NULL;
  }
}

void
TlmAxiArbiter::pushBTransaction(TlmAxi3Payload* b_transaction) {
  if (m_b_transaction == NULL) {
    m_b_transaction = b_transaction;
  }
}

void
TlmAxiArbiter::pushRTransaction(TlmAxi3Payload* r_transaction) {
  if (m_r_transaction == NULL) {
    m_r_transaction = r_transaction;
  }
}

unsigned int
TlmAxiArbiter::getAwIfNumber(void) {
  unsigned int result = NO_INTERFACE;
  std::list<unsigned int>::iterator itr = m_write_priority.begin();

  while (itr != m_write_priority.end()) {
    if (m_slave_if[*itr]->isAw()){
      result = *itr;
      m_write_priority.erase(itr);
      m_write_priority.push_back(result);
      break;
    }
    ++itr;
  }

  return result;
}

unsigned int
TlmAxiArbiter::getWIfNumber(void) {
  unsigned int result = NO_INTERFACE;  

  if (!m_w_histories.empty()) {
    unsigned int if_number = m_w_histories.front()->if_number;
    unsigned int axi_id = m_w_histories.front()->axi_id;

    //std::cout << sc_time_stamp() << __FUNCTION__ << " if_number=" << if_number << ",axi_id=" << axi_id << ",m_w_histories.size()=" << m_w_histories.size() << std::endl;
    if (m_slave_if[if_number]->isW()) {
      if (m_slave_if[if_number]->referW()->getWID() == axi_id) {
        result = if_number;
        if (m_slave_if[if_number]->referW()->getWLAST() == 1) {
          delete m_w_histories.front();
          m_w_histories.pop_front();
        }
      } else {
        std::cout << "[ERROR] illigal WID (AWID=" << axi_id << ",WID=" << m_slave_if[if_number]->referW()->getWID() << ")" << std::endl;
        assert(0);
      }
    }
  }

  return result;
}

unsigned int
TlmAxiArbiter::getArIfNumber(void) {
  unsigned int result = NO_INTERFACE;
  std::list<unsigned int>::iterator itr = m_read_priority.begin();

  while (itr != m_read_priority.end()) {
    if (m_slave_if[*itr]->isAr()){
      result = *itr;
      m_read_priority.erase(itr);
      m_read_priority.push_back(result);
      break;
    }
    ++itr;
  }

  return result;

}

unsigned int
TlmAxiArbiter::getBIfNumber(void) {
  unsigned int result = NO_INTERFACE;  
  bool is_found = false;
  unsigned int axi_id = m_b_transaction->getBID();

  if (!m_b_histories.empty()) {
    std::list<History*>::iterator itr = m_b_histories.begin();
    
    while (itr != m_b_histories.end()) {
      if (axi_id == (*itr)->axi_id) {
        is_found = true;
        if (!m_slave_if[(*itr)->if_number]->isB()) {
          result = (*itr)->if_number;
          delete (*itr);
          m_b_histories.erase(itr);
        }
        break;
      }
      ++itr;
    }
  }

  if (!is_found) {
    std::cout << "[ERROR] illigal BID (BID=" << axi_id << ")" << std::endl;
    assert(0);
  }

  return result;
}

unsigned int
TlmAxiArbiter::getRIfNumber(void) {
  unsigned int result = NO_INTERFACE;  
  bool is_found = false;
  unsigned int axi_id = m_r_transaction->getRID();

  if (!m_r_histories.empty()) {
    std::list<History*>::iterator itr = m_r_histories.begin();
    //unsigned int count = 0;
    
    while (itr != m_r_histories.end()) {
      //std::cout << sc_time_stamp() << __FUNCTION__ << "(*itr)->if_number=" << (*itr)->if_number << ",(*itr)->axi_id)=" << (*itr)->axi_id << "count=" << count++ << std::endl;
      if (axi_id == (*itr)->axi_id) {
        is_found = true;
        if (!m_slave_if[(*itr)->if_number]->isR()) {
          result = (*itr)->if_number;
          if (m_r_transaction->getRLAST() == 1) {
            //std::cout << __FUNCTION__ << " m_r_histories.erase(itr)" << std::endl;
            delete (*itr);
            m_r_histories.erase(itr);
          }
        }
        break;
      }
      ++itr;
    }
  }

  if (!is_found) {
    std::cout << "[ERROR] illigal RID (RID=" << axi_id << ")" << std::endl;
    assert(0);
  }

  return result;
}
