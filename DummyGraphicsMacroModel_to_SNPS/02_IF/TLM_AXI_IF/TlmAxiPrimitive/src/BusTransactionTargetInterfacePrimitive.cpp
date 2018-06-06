/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file BusTransactionTargetInterfacePrimitive.cpp
 * @brief Bus transaction target pirimitive interface for AXI-TLM interface(source)
 *
 * @date $Date: 2009/02/03 00:54:40 $
 * @version $Id: BusTransactionTargetInterfacePrimitive.cpp,v 1.3 2009/02/03 00:54:40 shunsaku Exp $
 */
#include "BusTransactionTargetInterfacePrimitive.h"
#if INFO
#include <iostream>
#endif

template<class DATA_TYPE>
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::BusTransactionTargetInterfacePrimitive(void) :
  _object_aw(NULL),
  _object_w(NULL),
  _object_ar(NULL),
  _object_b(NULL),
  _object_r(NULL),
  _receive_aw_request_event(NULL),
  _receive_w_request_event(NULL),
  _receive_ar_request_event(NULL),
  _receive_b_response_event(NULL),
  _receive_r_response_event(NULL) {
}

template<class DATA_TYPE>
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::~BusTransactionTargetInterfacePrimitive(void) {
  if (_object_aw) {
    _object_aw = NULL;
  }
  if (_object_w) {
    _object_w = NULL;
  }
  if (_object_ar) {
    _object_ar = NULL;
  }
  if (_object_b) {
    _object_b = NULL;
  }
  if (_object_r) {
    _object_r = NULL;
  }
  if (_receive_aw_request_event) {
    _receive_aw_request_event = NULL;
  }
  if (_receive_w_request_event) {
    _receive_w_request_event = NULL;
  }
  if (_receive_ar_request_event) {
    _receive_ar_request_event = NULL;
  }
  if (_receive_b_response_event) {
    _receive_b_response_event = NULL;
  }
  if (_receive_r_response_event) {
    _receive_r_response_event = NULL;
  }
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                                             tlm::tlm_phase&           phase,
                                                                             sc_core::sc_time&         t) {
  axi_payload<DATA_TYPE>* tmp_payload_axi;
  axi_payload<DATA_TYPE>* payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get axi_payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an axi_payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_aw) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy axi_payload */
    payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());

    if (_object_aw) {
      _object_aw->receiveAwRequest(payload_axi);
    }

    if (_receive_aw_request_event) {
      _receive_aw_request_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }
  
  return result;
}
 
template<class DATA_TYPE>
tlm::tlm_sync_enum
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                                            tlm::tlm_phase&           phase,
                                                                            sc_core::sc_time&         t) {
  axi_payload<DATA_TYPE>* tmp_payload_axi;
  axi_payload<DATA_TYPE>* payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get axi_payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an axi_payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_w) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy axi_payload */
    payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());

    if (_object_w) {
      _object_w->receiveWRequest(payload_axi);
    }
    
    if (_receive_w_request_event) {
      _receive_w_request_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }
  
  return result;
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                                             tlm::tlm_phase&           phase,
                                                                             sc_core::sc_time&         t){
  axi_payload<DATA_TYPE>* tmp_payload_axi;
  axi_payload<DATA_TYPE>* payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get axi_payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an axi_payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_ar) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }  

  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy axi_payload */
    payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());

    if (_object_ar) {
      _object_ar->receiveArRequest(payload_axi);
    }

    if (_receive_ar_request_event) {
      _receive_ar_request_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }
  
  return result;
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                                            tlm::tlm_phase&           phase,
                                                                            sc_core::sc_time&         t) {
  axi_payload<DATA_TYPE>* tmp_payload_axi;
  axi_payload<DATA_TYPE>* payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get axi_payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an axi_payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_b) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }  
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy axi_payload */
    payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());
    
    if (_object_b) {
      _object_b->receiveBResponse(payload_axi);
    }

    if (_receive_b_response_event) {
      _receive_b_response_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }
  
  return result;
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                                            tlm::tlm_phase&           phase,
                                                                            sc_core::sc_time&         t) {
  axi_payload<DATA_TYPE>* tmp_payload_axi;
  axi_payload<DATA_TYPE>* payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get axi_payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an axi_payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_r) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }  

  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy axi_payload */
    payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());

    if (_object_r) {
      _object_r->receiveRResponse(payload_axi);
    }

    if (_receive_r_response_event) {
      _receive_r_response_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }
  
  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::initializeAw(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_aw) {
  int result(0);
  
  /* Check argument */
  if (!object_aw) {
    result = -1;
  }

  /* Check first initialization */
  if (_object_aw) {
    result = -1;
  }
  
  if (result == 0) {
    _object_aw = object_aw;
  }

  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::sendAwResponse(axi_payload<DATA_TYPE>* payload_aw) {
  int result(0);
  
  /* Check argument */
  if (!payload_aw) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_aw) {
    result = -1;
  }

  if (result == 0) {
    /* Variable declaration */
    tlm::tlm_phase           phase(tlm::BEGIN_REQ);
    sc_time                  latency(0, SC_NS);
    tlm::tlm_sync_enum       response;
    tlm::tlm_generic_payload payload_aw_tlm;
    axi_payload<DATA_TYPE>*  payload_aw_axi;

    /* Copy axi_payload */
    payload_aw_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(payload_aw->clone());

    /* Set axi_payload to generic_payload */
    payload_aw_tlm.set_extension(payload_aw_axi);

    /* Receive AW response */
    response = target_AW->nb_transport_bw(payload_aw_tlm, phase, latency);
    payload_aw_tlm.release_extension(payload_aw_axi);
    payload_aw_axi = NULL;
  }
  
  return result;  
}

/**
 * Register event(sc_event) at AW transaction request
 *
 * Register event(sc_event) at AW transaction request
 * @param  receive_aw_request_event Event(sc_event) pointer
 * @retval 0<= Successful
 * @retval <0  Error
 */
template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::registerReceiveAwRequestEvent(sc_event* receive_aw_request_event) {
  int result(0);

  /* Check argument */
  if (!receive_aw_request_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_aw) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_aw_request_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_aw_request_event = receive_aw_request_event;
  }
  
  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::initializeW(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_w) {
  int result(0);
  
  /* Check argument */
  if (!object_w) {
    result = -1;
  }

  /* Check first initialization */
  if (_object_w) {
    result = -1;
  }
  
  if (result == 0) {
    _object_w = object_w;
  }

  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::sendWResponse(axi_payload<DATA_TYPE>* payload_w) {
  int result(0);
  
  /* Check argument */
  if (!payload_w) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_w) {
    result = -1;
  }

  if (result == 0) {
    /* Variable declaration */
    tlm::tlm_phase           phase(tlm::BEGIN_REQ);
    sc_time                  latency(0, SC_NS);
    tlm::tlm_sync_enum       response;
    tlm::tlm_generic_payload payload_w_tlm;
    axi_payload<DATA_TYPE>*  payload_w_axi;

    /* Copy axi_payload */
    payload_w_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(payload_w->clone());

    /* Set axi_payload to generic_payload */
    payload_w_tlm.set_extension(payload_w_axi);

    /* Receive W response */
    response = target_W->nb_transport_bw(payload_w_tlm, phase, latency);
    payload_w_tlm.release_extension(payload_w_axi);
    payload_w_axi = NULL;
  }
  
  return result;  
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::registerReceiveWRequestEvent(sc_event* receive_w_request_event) {
  int result(0);

  /* Check argument */
  if (!receive_w_request_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_w) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_w_request_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_w_request_event = receive_w_request_event;
  }
  
  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::initializeAr(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_ar) {
  int result(0);
  
  /* Check argument */
  if (!object_ar) {
    result = -1;
  }

  /* Check first initialization */
  if (_object_ar) {
    result = -1;
  }
  
  if (result == 0) {
    _object_ar = object_ar;
  }

  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::sendArResponse(axi_payload<DATA_TYPE>* payload_ar) {
  int result(0);
  
  /* Check argument */
  if (!payload_ar) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_ar) {
    result = -1;
  }

  if (result == 0) {
    /* Variable declaration */
    tlm::tlm_phase           phase(tlm::BEGIN_REQ);
    sc_time                  latency(0, SC_NS);
    tlm::tlm_sync_enum       response;
    tlm::tlm_generic_payload payload_ar_tlm;
    axi_payload<DATA_TYPE>*  payload_ar_axi;

    /* Copy axi_payload */
    payload_ar_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(payload_ar->clone());

    /* Set axi_payload to generic_payload */
    payload_ar_tlm.set_extension(payload_ar_axi);

    /* Receive AR response */
    response = target_AR->nb_transport_bw(payload_ar_tlm, phase, latency);
    payload_ar_tlm.release_extension(payload_ar_axi);
    payload_ar_axi = NULL;
  }
  
  return result;  
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::registerReceiveArRequestEvent(sc_event* receive_ar_request_event) {
  int result(0);

  /* Check argument */
  if (!receive_ar_request_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_ar) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_ar_request_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_ar_request_event = receive_ar_request_event;
  }
  
  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::initializeB(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_b) {
  int result(0);
  
  /* Check argument */
  if (!object_b) {
    result = -1;
  }

  /* Check first initialization */
  if (_object_b) {
    result = -1;
  }
  
  if (result == 0) {
    _object_b = object_b;
  }

  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::sendBRequest(axi_payload<DATA_TYPE>* payload_b) {
  int result(0);
  
  /* Check bgument */
  if (!payload_b) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_b) {
    result = -1;
  }

  if (result == 0) {
    /* Vbiable declbation */
    tlm::tlm_phase           phase(tlm::BEGIN_REQ);
    sc_time                  latency(0, SC_NS);
    tlm::tlm_sync_enum       response;
    tlm::tlm_generic_payload payload_b_tlm;
    axi_payload<DATA_TYPE>*  payload_b_axi;

    /* Copy axi_payload */
    payload_b_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(payload_b->clone());

    /* Set axi_payload to generic_payload */
    payload_b_tlm.set_extension(payload_b_axi);

    /* Send B request */
    response = target_B->nb_transport_fw(payload_b_tlm, phase, latency);
    payload_b_tlm.release_extension(payload_b_axi);
    payload_b_axi = NULL;
  }
  
  return result;  
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::registerReceiveBResponseEvent(sc_event* receive_b_response_event) {
  int result(0);

  /* Check argument */
  if (!receive_b_response_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_b) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_b_response_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_b_response_event = receive_b_response_event;
  }
  
  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::initializeR(BusTransactionTargetInterfacePrimitiveBase<DATA_TYPE>* object_r) {
  int result(0);
  
  /* Check argument */
  if (!object_r) {
    result = -1;
  }

  /* Check first initialization */
  if (_object_r) {
    result = -1;
  }
  
  if (result == 0) {
    _object_r = object_r;
  }

  return result;
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::sendRRequest(axi_payload<DATA_TYPE>* payload_r) {
  int result(0);
  
  /* Check rgument */
  if (!payload_r) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_r) {
    result = -1;
  }

  if (result == 0) {
    /* Vriable declration */
    tlm::tlm_phase           phase(tlm::BEGIN_REQ);
    sc_time                  latency(0, SC_NS);
    tlm::tlm_sync_enum       response;
    tlm::tlm_generic_payload payload_r_tlm;
    axi_payload<DATA_TYPE>*  payload_r_axi;

    /* Copy axi_payload */
    payload_r_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(payload_r->clone());

    /* Set axi_payload to generic_payload */
    payload_r_tlm.set_extension(payload_r_axi);

    /* Send R request */
    response = target_R->nb_transport_fw(payload_r_tlm, phase, latency);
    payload_r_tlm.release_extension(payload_r_axi);
    payload_r_axi = NULL;
  }
  
  return result;  
}

template<class DATA_TYPE>
int
BusTransactionTargetInterfacePrimitive<DATA_TYPE>::registerReceiveRResponseEvent(sc_event* receive_r_response_event) {
  int result(0);

  /* Check rgument */
  if (!receive_r_response_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_r) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_r_response_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_r_response_event = receive_r_response_event;
  }
  
  return result;
}

template class BusTransactionTargetInterfacePrimitive<unsigned int>;
template class BusTransactionTargetInterfacePrimitive<unsigned long long>;
