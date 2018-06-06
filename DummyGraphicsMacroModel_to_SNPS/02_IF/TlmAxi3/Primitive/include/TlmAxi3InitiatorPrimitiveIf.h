/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3InitiatorPrimitiveIf.h
 * @brief Primitive class of TLM AXI initiator interface (header)
 */
#ifndef TLM_AXI3_INITIATOR_PRIMITIVE_IF_H
#define TLM_AXI3_INITIATOR_PRIMITIVE_IF_H

#include <systemc.h>
#include <tlm.h>
#include "TlmAxi3Payload.h"
#include "TlmAxi3InitiatorBaseIf.h"
#include "TlmAxi3InitiatorPrimitiveIfBase.h"

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
#include "tb_tr_tlm2.h"
#endif

class TlmAxi3InitiatorPrimitiveIf: public TlmAxi3InitiatorBaseIf,
                                   public TlmAxi3InitiatorPrimitiveIfBase {
 public:
  /**
   * Constructor
   *
   * Constructor
   **/
  TlmAxi3InitiatorPrimitiveIf(void);

  /**
   * Destructor
   *
   * Destructor
   **/
  ~TlmAxi3InitiatorPrimitiveIf(void);

  /**
   * Non-blocking forward transport for AXI channel B
   *
   * Do non-blocking forward transporting for AXI channel B
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       response status
   **/
  tlm::tlm_sync_enum
  initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase&           phase,
                              sc_core::sc_time&         t);

  /**
   * Non-blocking forward transport for AXI channel R
   *
   * Do non-blocking forward transporting for AXI channel R
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       response status
   **/
  tlm::tlm_sync_enum
  initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase&           phase,
                              sc_core::sc_time&         t);

  /**
   * Non-blocking backward transport for AXI channel AW
   *
   * Do non-blocking backward transporting for AXI channel AW
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       response status
   **/
  tlm::tlm_sync_enum
  initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                               sc_core::sc_time&         t);
  /**
   * Non-blocking backward transport for AXI channel W
   *
   * Do non-blocking backward transporting for AXI channel W
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       response status
   **/
  tlm::tlm_sync_enum
  initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase&           phase,
                              sc_core::sc_time&         t);
  /**
   * Non-blocking backward transport for AXI channel AR
   *
   * Do non-blocking backward transporting for AXI channel AR
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       response status
   **/
  tlm::tlm_sync_enum
  initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                               sc_core::sc_time&         t);

public:
  /**
   * Initiaization for AW transaction
   *
   * Register base class object for AW transaction
   * @param  object_aw pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeAw(TlmAxi3InitiatorPrimitiveIfBase *object_aw);

  /**
   * Send AW transaction request
   *
   * Send AW transaction request
   * @param  payload_aw Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendAwRequest(TlmAxi3Payload *payload_aw);

  /**
   * Register AW transaction response receiveing event
   *
   * Register AW transaction response receiveing event
   * @param  event_send_aw_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveAwResponseEvent(sc_event *receive_aw_response_event);

  /**
   * Initiaization for W transaction
   *
   * Register base class object for W transaction
   * @param  object_w pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeW(TlmAxi3InitiatorPrimitiveIfBase *object_w);

  /**
   * Send W transaction request
   *
   * Send W transaction request
   * @param  payload_w Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendWRequest(TlmAxi3Payload *payload_w);

  /**
   * Register W transaction response receiveing event
   *
   * Register W transaction response receiveing event
   * @param  event_send_w_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveWResponseEvent(sc_event *receive_w_response_event);

  /**
   * Initiaization for AR transaction
   *
   * Register base class object for AR transaction
   * @param  object_ar pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeAr(TlmAxi3InitiatorPrimitiveIfBase *object_ar);

  /**
   * Send AR transaction request
   *
   * Send AR transaction request
   * @param  payload_ar Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendArRequest(TlmAxi3Payload *payload_ar);

  /**
   * Register AR transaction response receiveing event
   *
   * Register AR transaction response receiveing event
   * @param  event_send_ar_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveArResponseEvent(sc_event *receive_ar_response_event);

  /**
   * Initiaization for B transaction
   *
   * Register base class object for B transaction
   * @param  object_b pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeB(TlmAxi3InitiatorPrimitiveIfBase *object_b);

  /**
   * Send B transaction response
   *
   * Send B transaction response
   * @param  payload_b Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendBResponse(TlmAxi3Payload *payload_b);

  /**
   * Register B transaction request receiveing event
   *
   * Register B transaction request receiveing event
   * @param  event_send_b_request event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveBRequestEvent(sc_event *receive_b_request_event);

  /**
   * Initiaization for R transaction
   *
   * Register base class object for R transaction
   * @param  object_r pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeR(TlmAxi3InitiatorPrimitiveIfBase *object_r);

  /**
   * Send R transaction response
   *
   * Send R transaction response
   * @param  payload_r Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendRResponse(TlmAxi3Payload *payload_r);

  /**
   * Register R transaction request receiving event
   *
   * Register R transaction request receiving event
   * @param  receive_r_request_event event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveRRequestEvent(sc_event *receive_r_request_event);

private:
  TlmAxi3InitiatorPrimitiveIfBase *_object_aw;
  TlmAxi3InitiatorPrimitiveIfBase *_object_w;
  TlmAxi3InitiatorPrimitiveIfBase *_object_ar;
  TlmAxi3InitiatorPrimitiveIfBase *_object_b;
  TlmAxi3InitiatorPrimitiveIfBase *_object_r;

  sc_event *_receive_aw_response_event;
  sc_event *_receive_w_response_event;
  sc_event *_receive_ar_response_event;
  sc_event *_receive_b_request_event;
  sc_event *_receive_r_request_event;

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
  tb_tr_tlm2* axi_aw;
  tb_tr_tlm2* axi_w;
  tb_tr_tlm2* axi_b;
  tb_tr_tlm2* axi_ar;
  tb_tr_tlm2* axi_r;
#endif

};
#endif /* TLM_AXI3_INITIATOR_PRIMITIVE_IF_H */
