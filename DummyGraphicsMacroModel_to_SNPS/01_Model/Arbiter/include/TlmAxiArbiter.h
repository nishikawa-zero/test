/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file TlmAxiArbiter.h
 * @brief TLM-AXI arbiter (header)
 */
#ifndef TLM_AXI_ARBITER_H
#define TLM_AXI_ARBITER_H

#include <systemc>
#include <tlm.h>
#include <list>
#include "TlmAxiArbiterSlaveInterface.h"
#include "TlmAxi3Payload.h"
#include "fj_datatype.h"

class TlmAxiArbiter: public sc_module {
private:
  enum Pramaters {
    NO_INTERFACE = ~0UL
  };
  
  struct History {
    unsigned int axi_id;
    unsigned int if_number;
  };

public:
  SC_HAS_PROCESS(TlmAxiArbiter);

  TlmAxiArbiter(sc_module_name name,
                unsigned int number_of_slave_if);
  ~TlmAxiArbiter(void);

  TlmAxi3Payload *frontAWTransaction(void);
  void popAWTransaction(void);
  TlmAxi3Payload *frontWTransaction(void);
  void popWTransaction(void);
  TlmAxi3Payload *frontARTransaction(void);
  void popARTransaction(void);
  void pushBTransaction(TlmAxi3Payload *b_transaction);
  void pushRTransaction(TlmAxi3Payload *r_transaction);

private:
  unsigned int getAwIfNumber(void);
  unsigned int getWIfNumber(void);
  unsigned int getArIfNumber(void);
  unsigned int getBIfNumber(void);
  unsigned int getRIfNumber(void);

private:
  void TransactionController(void);

private:
  TlmAxi3Payload *m_aw_transaction; /**< AWTransaction */
  TlmAxi3Payload *m_w_transaction;  /**< WTransaction */
  TlmAxi3Payload *m_ar_transaction; /**< ARTransaction */
  TlmAxi3Payload *m_b_transaction;  /**< WTransaction */
  TlmAxi3Payload *m_r_transaction; /**< ARTransaction */

  TlmAxi3Payload *m_aw_transaction_bw; /**< AWTransaction */
  TlmAxi3Payload *m_w_transaction_bw;  /**< WTransaction */
  TlmAxi3Payload *m_ar_transaction_bw; /**< ARTransaction */
  TlmAxi3Payload *m_b_transaction_bw;  /**< WTransaction */
  TlmAxi3Payload *m_r_transaction_bw; /**< ARTransaction */

public:
  TlmAxiArbiterSlaveInterface **m_slave_if;
  sc_in_clk m_clk;

private:
  unsigned int m_number_of_slave_if;

  std::list<unsigned int> m_write_priority;
  std::list<unsigned int> m_read_priority;

  unsigned int m_current_aw_if;
  unsigned int m_current_w_if;
  unsigned int m_current_ar_if;
  unsigned int m_current_b_if;
  unsigned int m_current_r_if;


  std::list<History*> m_w_histories;
  std::list<History*> m_b_histories;
  std::list<History*> m_r_histories;
};
#endif /* TLM_AXI_ARBITER_h */
