/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3TargetPrimitiveIf.cpp
 * @brief Primitive class of TLM AXI target interface (source)
 */
#include "TlmAxi3TargetPrimitiveIf.h"

TlmAxi3TargetPrimitiveIf::TlmAxi3TargetPrimitiveIf(void) :
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

TlmAxi3TargetPrimitiveIf::~TlmAxi3TargetPrimitiveIf(void) {
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

tlm::tlm_sync_enum
TlmAxi3TargetPrimitiveIf::target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_aw) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy TlmAxi3Payload */
    payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());

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
 
tlm::tlm_sync_enum
TlmAxi3TargetPrimitiveIf::target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                   tlm::tlm_phase&           phase,
                                                   sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_w) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy TlmAxi3Payload */
    payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());

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

tlm::tlm_sync_enum
TlmAxi3TargetPrimitiveIf::target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t){
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_ar) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }  

  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy TlmAxi3Payload */
    payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());

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

tlm::tlm_sync_enum
TlmAxi3TargetPrimitiveIf::target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                   tlm::tlm_phase&           phase,
                                                   sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_b) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }  
  
  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy TlmAxi3Payload */
    payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
    
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

tlm::tlm_sync_enum
TlmAxi3TargetPrimitiveIf::target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                   tlm::tlm_phase&           phase,
                                                   sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
  
  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);
  
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  /* Check Initialize */
  if (!_object_r) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }  

  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy TlmAxi3Payload */
    payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());

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

int
TlmAxi3TargetPrimitiveIf::initializeAw(TlmAxi3TargetPrimitiveIfBase* object_aw) {
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

int
TlmAxi3TargetPrimitiveIf::sendAwResponse(TlmAxi3Payload *payload_aw) {
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
    TlmAxi3Payload *payload_aw_axi;

    /* Copy TlmAxi3Payload */
    payload_aw_axi = reinterpret_cast<TlmAxi3Payload*>(payload_aw->clone());

    /* Set TlmAxi3Payload to generic_payload */
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
int
TlmAxi3TargetPrimitiveIf::registerReceiveAwRequestEvent(sc_event *receive_aw_request_event) {
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

int
TlmAxi3TargetPrimitiveIf::initializeW(TlmAxi3TargetPrimitiveIfBase* object_w) {
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

int
TlmAxi3TargetPrimitiveIf::sendWResponse(TlmAxi3Payload *payload_w) {
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
    TlmAxi3Payload *payload_w_axi;

    /* Copy TlmAxi3Payload */
    payload_w_axi = reinterpret_cast<TlmAxi3Payload*>(payload_w->clone());

    /* Set TlmAxi3Payload to generic_payload */
    payload_w_tlm.set_extension(payload_w_axi);

    /* Receive W response */
    response = target_W->nb_transport_bw(payload_w_tlm, phase, latency);
    payload_w_tlm.release_extension(payload_w_axi);
    payload_w_axi = NULL;
  }
  
  return result;  
}

int
TlmAxi3TargetPrimitiveIf::registerReceiveWRequestEvent(sc_event *receive_w_request_event) {
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

int
TlmAxi3TargetPrimitiveIf::initializeAr(TlmAxi3TargetPrimitiveIfBase* object_ar) {
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

int
TlmAxi3TargetPrimitiveIf::sendArResponse(TlmAxi3Payload *payload_ar) {
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
    TlmAxi3Payload *payload_ar_axi;

    /* Copy TlmAxi3Payload */
    payload_ar_axi = reinterpret_cast<TlmAxi3Payload*>(payload_ar->clone());

    /* Set TlmAxi3Payload to generic_payload */
    payload_ar_tlm.set_extension(payload_ar_axi);

    /* Receive AR response */
    response = target_AR->nb_transport_bw(payload_ar_tlm, phase, latency);
    payload_ar_tlm.release_extension(payload_ar_axi);
    payload_ar_axi = NULL;
  }
  
  return result;  
}

int
TlmAxi3TargetPrimitiveIf::registerReceiveArRequestEvent(sc_event *receive_ar_request_event) {
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

int
TlmAxi3TargetPrimitiveIf::initializeB(TlmAxi3TargetPrimitiveIfBase* object_b) {
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

int
TlmAxi3TargetPrimitiveIf::sendBRequest(TlmAxi3Payload *payload_b) {
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
    TlmAxi3Payload *payload_b_axi;

    /* Copy TlmAxi3Payload */
    payload_b_axi = reinterpret_cast<TlmAxi3Payload*>(payload_b->clone());

    /* Set TlmAxi3Payload to generic_payload */
    payload_b_tlm.set_extension(payload_b_axi);

    /* Send B request */
    response = target_B->nb_transport_fw(payload_b_tlm, phase, latency);
    payload_b_tlm.release_extension(payload_b_axi);
    payload_b_axi = NULL;
  }
  
  return result;  
}

int
TlmAxi3TargetPrimitiveIf::registerReceiveBResponseEvent(sc_event *receive_b_response_event) {
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

int
TlmAxi3TargetPrimitiveIf::initializeR(TlmAxi3TargetPrimitiveIfBase* object_r) {
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

int
TlmAxi3TargetPrimitiveIf::sendRRequest(TlmAxi3Payload *payload_r) {
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
    TlmAxi3Payload *payload_r_axi;

    /* Copy TlmAxi3Payload */
    payload_r_axi = reinterpret_cast<TlmAxi3Payload*>(payload_r->clone());

    /* Set TlmAxi3Payload to generic_payload */
    payload_r_tlm.set_extension(payload_r_axi);

    /* Send R request */
    response = target_R->nb_transport_fw(payload_r_tlm, phase, latency);
    payload_r_tlm.release_extension(payload_r_axi);
    payload_r_axi = NULL;
  }
  
  return result;  
}

int
TlmAxi3TargetPrimitiveIf::registerReceiveRResponseEvent(sc_event *receive_r_response_event) {
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
