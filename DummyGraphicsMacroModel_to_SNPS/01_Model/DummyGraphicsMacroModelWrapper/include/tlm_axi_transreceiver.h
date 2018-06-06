/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2010
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file tlm_axi_transreceiver.h
 * @brief Receive transaction from BusMaster (header)
 */
#if !defined TLM_AXI_TRANSRECEIVER_h
#define TLM_AXI_TRANSRECEIVER_h

#include <systemc>
#include <queue>
#include <tlm.h>
#include "TlmAxi3TargetBaseIf.h"
#include "TlmAxi3Payload.h"
#include "fj_datatype.h"

/**
 * @brief Receive transaction from BusMaster 
 *
 * Receive AXI transaction from BusMaster
 * and push/pop internal queue
 *
 * @param data_type write/read data type
*/
class tlm_axi_transreceiver: public sc_module,
                             public TlmAxi3TargetBaseIf
{
public:
  SC_HAS_PROCESS(tlm_axi_transreceiver);

  /**
   * @brief Constructor
   **/
  tlm_axi_transreceiver(sc_module_name name);

  /**
   * @brief Destructor
   **/
  ~tlm_axi_transreceiver(void);

  /**
   * @brief Non-blocking forward transport for AXI channel AW
   *
   * @param[in,out] trans tlm generic payload
   * @param[in,out] phase tlm phase
   * @param[in,out] t     latency
   * @return              response status
   **/
  tlm::tlm_sync_enum
  target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                            tlm::tlm_phase&           phase,
                            sc_core::sc_time&         t);

  /**
   * @brief Non-blocking forward transport for AXI channel W
   *
   * @param[in,out] trans tlm generic payload
   * @param[in,out] phase tlm phase
   * @param[in,out] t     latency
   * @return              response status
   **/
  tlm::tlm_sync_enum
  target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);

  /**
   * @brief Non-blocking forward transport for AXI channel AR
   *
   * @param[in,out] trans tlm generic payload
   * @param[in,out] phase tlm phase
   * @param[in,out] t     latency
   * @return              response status
   **/
  tlm::tlm_sync_enum
  target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                            tlm::tlm_phase&           phase,
                            sc_core::sc_time&         t);

  /**
   * @brief Non-blocking backward transport for AXI channel B
   *
   * @param[in,out] trans tlm generic payload
   * @param[in,out] phase tlm phase
   * @param[in,out] t     latency
   * @return              response status
   **/
  tlm::tlm_sync_enum
  target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);

  /**
   * @brief Non-blocking backward transport for AXI channel R
   *
   * @param[in,out] trans tlm generic payload
   * @param[in,out] phase tlm phase
   * @param[in,out] t     latency
   * @return              response status
   **/
  tlm::tlm_sync_enum
  target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);

  /**
   * @brief Pop front AW Transaction from m_aw_queue
   *
   * @return TlmAxi3Payload
   **/
  TlmAxi3Payload*
  frontAWTransaction(void);

  /**
   * @brief Delete front AW Transaction from m_aw_queue
   **/
  void
  popAWTransaction(void);

  /**
   * @brief Pop front W Transaction from m_w_queue
   *
   * @return TlmAxi3Payload
   **/
  TlmAxi3Payload*
  frontWTransaction(void);

  /**
   * @brief Delete front W Transaction from m_w_queue
   **/
  void
  popWTransaction(void);

  /**
   * @brief Pop front AR Transaction from m_ar_queue
   *
   * @return TlmAxi3Payload
   **/
  TlmAxi3Payload*
  frontARTransaction(void);

  /**
   * @brief Delete front AR Transaction from m_ar_queue
   **/
  void
  popARTransaction(void);

  /**
   * @brief Push B Transaction into m_b_queue
   *
   * @param[in] BTransaction AXIpayload
   **/
  void
  pushBTransaction(TlmAxi3Payload* b_transaction);

  /**
   * @brief Push R Transaction into m_r_queue
   *
   * @param[in] RTransaction AXIpayload
   **/
  void
  pushRTransaction(TlmAxi3Payload* r_transaction);

private:
  /**
   * @brief Controller for All AXI channel's transaction
   **/
  void
  TransactionController(void);

private:
  TlmAxi3Payload* m_aw_transaction; /**< AWTransaction */
  TlmAxi3Payload* m_w_transaction;  /**< WTransaction */
  TlmAxi3Payload* m_ar_transaction; /**< ARTransaction */
  TlmAxi3Payload* m_b_transaction;  /**< WTransaction */
  TlmAxi3Payload* m_r_transaction; /**< ARTransaction */

  TlmAxi3Payload* m_aw_transaction_bw; /**< AWTransaction */
  TlmAxi3Payload* m_w_transaction_bw;  /**< WTransaction */
  TlmAxi3Payload* m_ar_transaction_bw; /**< ARTransaction */

public:
  sc_in_clk m_clk;
};
#endif /* TLM_AXI_TRANSRECEIVER_h */
