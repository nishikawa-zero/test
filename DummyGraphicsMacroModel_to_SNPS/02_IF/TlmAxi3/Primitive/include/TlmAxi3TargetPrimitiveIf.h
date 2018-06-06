/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3TargetPrimitiveIf.h
 * @brief Primitive class of TLM AXI target interface (header)
 */
#ifndef TLM_AXI3_TARGET_PRIMITIVE_IF_H
#define TLM_AXI3_TARGET_PRIMITIVE_IF_H

#include <systemc.h>
#include <tlm.h>
#include "TlmAxi3Payload.h"
#include "TlmAxi3TargetBaseIf.h"
#include "TlmAxi3TargetPrimitiveIfBase.h"

class TlmAxi3TargetPrimitiveIf: public TlmAxi3TargetBaseIf,
                                public TlmAxi3TargetPrimitiveIfBase {
public:
  /**
   * Constructor
   *
   * Constructor
   **/
  TlmAxi3TargetPrimitiveIf(void);

  /**
   * Destructor
   *
   * Destructor
   **/
  ~TlmAxi3TargetPrimitiveIf(void);

  /**
   * Non-blocking forward transport for AXI channel AW
   *
   * Do non-blocking forward transporting for AXI channel AW
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       request status
   **/
  tlm::tlm_sync_enum
  target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                            tlm::tlm_phase&           phase,
                            sc_core::sc_time&         t);
  /**
   * Non-blocking forward transport for AXI channel W
   *
   * Do non-blocking forward transporting for AXI channel W
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       request status
   **/
  tlm::tlm_sync_enum
  target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);
  /**
   * Non-blocking forward transport for AXI channel AR
   *
   * Do non-blocking forward transporting for AXI channel AR
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       request status
   **/
  tlm::tlm_sync_enum
  target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                            tlm::tlm_phase&           phase,
                            sc_core::sc_time&         t);

  /**
   * Non-blocking backward transport for AXI channel B
   *
   * Do non-blocking backward transporting for AXI channel B
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       request status
   **/
  tlm::tlm_sync_enum
  target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);

  /**
   * Non-blocking backward transport for AXI channel R
   *
   * Do non-blocking backward transporting for AXI channel R
   * @param  trans tlm generic payload
   * @param  phase tlm phase
   * @param  t     latency
   * @return       request status
   **/
  tlm::tlm_sync_enum
  target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
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
  int initializeAw(TlmAxi3TargetPrimitiveIfBase *object_aw);

  /**
   * Send AW transaction response
   *
   * Send AW transaction response
   * @param  payload_aw Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendAwResponse(TlmAxi3Payload *payload_aw);

  /**
   * Register AW transaction request receiveing event
   *
   * Register AW transaction request receiveing event
   * @param  event_send_aw_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveAwRequestEvent(sc_event *receive_aw_request_event);

  /**
   * Initiaization for W transaction
   *
   * Register base class object for W transaction
   * @param  object_w pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeW(TlmAxi3TargetPrimitiveIfBase *object_w);

  /**
   * Send W transaction response
   *
   * Send W transaction response
   * @param  payload_w Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendWResponse(TlmAxi3Payload *payload_w);

  /**
   * Register W transaction request receiveing event
   *
   * Register W transaction request receiveing event
   * @param  event_send_w_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveWRequestEvent(sc_event *receive_w_request_event);

  /**
   * Initiaization for AR transaction
   *
   * Register base class object for AR transaction
   * @param  object_ar pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeAr(TlmAxi3TargetPrimitiveIfBase *object_ar);

  /**
   * Send AR transaction response
   *
   * Send AR transaction response
   * @param  payload_ar Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendArResponse(TlmAxi3Payload *payload_ar);

  /**
   * Register AR transaction request receiveing event
   *
   * Register AR transaction request receiveing event
   * @param  event_send_ar_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveArRequestEvent(sc_event *receive_ar_request_event);

  /**
   * Initiaization for B transaction
   *
   * Register base class object for B transaction
   * @param  object_b pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeB(TlmAxi3TargetPrimitiveIfBase *object_b);

  /**
   * Send B transaction request
   *
   * Send B transaction request
   * @param  payload_b Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendBRequest(TlmAxi3Payload *payload_b);

  /**
   * Register B transaction response receiving event
   *
   * Register B transaction response receiving event
   * @param  receive_b_response_event event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveBResponseEvent(sc_event *receive_b_response_event);

  /**
   * Initiaization for R transaction
   *
   * Register base class object for R transaction
   * @param  object_r pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeR(TlmAxi3TargetPrimitiveIfBase *object_r);

  /**
   * Send R transaction request
   *
   * Send R transaction request
   * @param  payload_r Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendRRequest(TlmAxi3Payload *payload_r);

  /**
   * Register R transaction response receiving event
   *
   * Register R transaction response receiving event
   * @param  receive_r_response_event event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveRResponseEvent(sc_event *receive_r_response_event);

private:
  TlmAxi3TargetPrimitiveIfBase *_object_aw;
  TlmAxi3TargetPrimitiveIfBase *_object_w;
  TlmAxi3TargetPrimitiveIfBase *_object_ar;
  TlmAxi3TargetPrimitiveIfBase *_object_b;
  TlmAxi3TargetPrimitiveIfBase *_object_r;
  
  sc_event *_receive_aw_request_event;
  sc_event *_receive_w_request_event;
  sc_event *_receive_ar_request_event;
  sc_event *_receive_b_response_event;
  sc_event *_receive_r_response_event;
};
#endif /* TLM_AXI3_TARGET_PRIMITIVE_IF_H */
