/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2010
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file BusTransactionInitiatorInterfacePrimitive.h
 * @brief Bus transaction initiator pirimitive interface for AXI-TLM interface(header)
 *
 * @date $Date: 2010/09/02 00:00:00 $
 * @version $Id: BusTransactionInitiatorInterfacePrimitive.h,v 1.1 2010/09/02 00:00:00 imaizumi Exp $
 */
#ifndef BusTransactionInitiatorInterfacePrimitive_h
#define BusTransactionInitiatorInterfacePrimitive_h

#include <systemc.h>
#include <tlm.h>
#include "axi_payload.h"
#include "tlm_axi_initiator_base_if.h"
#include "BusTransactionInitiatorInterfacePrimitiveBase.h"

#ifdef VCD_OUTPUT_FUNC_ON
#include "tb_tr_tlm2.h"
#endif

template<class DATA_TYPE = unsigned int>
class BusTransactionInitiatorInterfacePrimitive: public tlm_axi_initiator_base_if,
                                                 public BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE> {
public:
  /**
   * Constructor
   *
   * Constructor
   **/
  BusTransactionInitiatorInterfacePrimitive(void);

  /**
   * Destructor
   *
   * Destructor
   **/
  ~BusTransactionInitiatorInterfacePrimitive(void);

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
  int initializeAw(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_aw);

  /**
   * Send AW transaction request
   *
   * Send AW transaction request
   * @param  payload_aw Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendAwRequest(axi_payload<DATA_TYPE>* payload_aw);

  /**
   * Register AW transaction response receiveing event
   *
   * Register AW transaction response receiveing event
   * @param  event_send_aw_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveAwResponseEvent(sc_event* receive_aw_response_event);

  /**
   * Initiaization for W transaction
   *
   * Register base class object for W transaction
   * @param  object_w pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeW(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_w);

  /**
   * Send W transaction request
   *
   * Send W transaction request
   * @param  payload_w Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendWRequest(axi_payload<DATA_TYPE>* payload_w);

  /**
   * Register W transaction response receiveing event
   *
   * Register W transaction response receiveing event
   * @param  event_send_w_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveWResponseEvent(sc_event* receive_w_response_event);

  /**
   * Initiaization for AR transaction
   *
   * Register base class object for AR transaction
   * @param  object_ar pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeAr(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_ar);

  /**
   * Send AR transaction request
   *
   * Send AR transaction request
   * @param  payload_ar Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendArRequest(axi_payload<DATA_TYPE>* payload_ar);

  /**
   * Register AR transaction response receiveing event
   *
   * Register AR transaction response receiveing event
   * @param  event_send_ar_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveArResponseEvent(sc_event* receive_ar_response_event);

  /**
   * Initiaization for B transaction
   *
   * Register base class object for B transaction
   * @param  object_b pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeB(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_b);

  /**
   * Send B transaction response
   *
   * Send B transaction response
   * @param  payload_b Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendBResponse(axi_payload<DATA_TYPE>* payload_b);

  /**
   * Register B transaction request receiveing event
   *
   * Register B transaction request receiveing event
   * @param  event_send_b_request event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveBRequestEvent(sc_event* receive_b_request_event);

  /**
   * Initiaization for R transaction
   *
   * Register base class object for R transaction
   * @param  object_r pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeR(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_r);

  /**
   * Send R transaction response
   *
   * Send R transaction response
   * @param  payload_r Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendRResponse(axi_payload<DATA_TYPE>* payload_r);

  /**
   * Register R transaction request receiving event
   *
   * Register R transaction request receiving event
   * @param  receive_r_request_event event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveRRequestEvent(sc_event* receive_r_request_event);

private:
  BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* _object_aw;
  BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* _object_w;
  BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* _object_ar;
  BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* _object_b;
  BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* _object_r;

  sc_event* _receive_aw_response_event;
  sc_event* _receive_w_response_event;
  sc_event* _receive_ar_response_event;
  sc_event* _receive_b_request_event;
  sc_event* _receive_r_request_event;

#ifdef VCD_OUTPUT_FUNC_ON
  tb_tr_tlm2* axi_aw;
  tb_tr_tlm2* axi_w;
  tb_tr_tlm2* axi_b;
  tb_tr_tlm2* axi_ar;
  tb_tr_tlm2* axi_r;
#endif

};
#endif /* BusTransactionInitiatorInterfacePrimitive_h */
