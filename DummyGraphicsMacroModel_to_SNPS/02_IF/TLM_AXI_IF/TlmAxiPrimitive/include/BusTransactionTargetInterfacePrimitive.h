/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2010
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file BusTransactionTargetInterfacePrimitive.h
 * @brief Bus transaction target pirimitive interface for AXI-TLM interface(header)
 *
 * @date $Date: 2010/09/02 00:00:00 $
 * @version $Id: BusTransactionTargetInterfacePrimitive.h,v 1.1 2010/09/02 00:00:00 imaizumi Exp $
 */
#ifndef BusTransactionTargetInterfacePrimitive_h
#define BusTransactionTargetInterfacePrimitive_h

#include <systemc.h>
#include <tlm.h>
#include "axi_payload.h"
#include "tlm_axi_target_base_if.h"
#include "BusTransactionTargetInterfacePrimitiveBase.h"
#include "FLxSC.h"

template<class DATA_TYPE = unsigned int>
class BusTransactionTargetInterfacePrimitive: public tlm_axi_target_base_if,
                                              public BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE> {
public:
  /**
   * Constructor
   *
   * Constructor
   **/
  BusTransactionTargetInterfacePrimitive(void);

  /**
   * Destructor
   *
   * Destructor
   **/
  ~BusTransactionTargetInterfacePrimitive(void);

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
  int initializeAw(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_aw);

  /**
   * Send AW transaction response
   *
   * Send AW transaction response
   * @param  payload_aw Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendAwResponse(axi_payload<DATA_TYPE>* payload_aw);

  /**
   * Register AW transaction request receiveing event
   *
   * Register AW transaction request receiveing event
   * @param  event_send_aw_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveAwRequestEvent(sc_event* receive_aw_request_event);

  /**
   * Initiaization for W transaction
   *
   * Register base class object for W transaction
   * @param  object_w pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeW(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_w);

  /**
   * Send W transaction response
   *
   * Send W transaction response
   * @param  payload_w Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendWResponse(axi_payload<DATA_TYPE>* payload_w);

  /**
   * Register W transaction request receiveing event
   *
   * Register W transaction request receiveing event
   * @param  event_send_w_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveWRequestEvent(sc_event* receive_w_request_event);

  /**
   * Initiaization for AR transaction
   *
   * Register base class object for AR transaction
   * @param  object_ar pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeAr(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_ar);

  /**
   * Send AR transaction response
   *
   * Send AR transaction response
   * @param  payload_ar Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendArResponse(axi_payload<DATA_TYPE>* payload_ar);

  /**
   * Register AR transaction request receiveing event
   *
   * Register AR transaction request receiveing event
   * @param  event_send_ar_response event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveArRequestEvent(sc_event* receive_ar_request_event);

  /**
   * Initiaization for B transaction
   *
   * Register base class object for B transaction
   * @param  object_b pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeB(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_b);

  /**
   * Send B transaction request
   *
   * Send B transaction request
   * @param  payload_b Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendBRequest(axi_payload<DATA_TYPE>* payload_b);

  /**
   * Register B transaction response receiving event
   *
   * Register B transaction response receiving event
   * @param  receive_b_response_event event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveBResponseEvent(sc_event* receive_b_response_event);

  /**
   * Initiaization for R transaction
   *
   * Register base class object for R transaction
   * @param  object_r pointer of base class object
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int initializeR(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_r);

  /**
   * Send R transaction request
   *
   * Send R transaction request
   * @param  payload_r Payload for AXI-TLM interface
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int sendRRequest(axi_payload<DATA_TYPE>* payload_r);

  /**
   * Register R transaction response receiving event
   *
   * Register R transaction response receiving event
   * @param  receive_r_response_event event pointer
   * @retval 0<= Successful
   * @retval <0  Error
   */
  int registerReceiveRResponseEvent(sc_event* receive_r_response_event);

private:
  BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* _object_aw;
  BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* _object_w;
  BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* _object_ar;
  BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* _object_b;
  BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* _object_r;
  
  sc_event* _receive_aw_request_event;
  sc_event* _receive_w_request_event;
  sc_event* _receive_ar_request_event;
  sc_event* _receive_b_response_event;
  sc_event* _receive_r_response_event;
};
#endif /* BusTransactionTargetInterfacePrimitive_h */
