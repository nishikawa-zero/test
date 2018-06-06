/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3InitiatorPrimitiveIf.cpp
 * @brief Primitive class of TLM AXI initiator interface (source)
 */
#include "TlmAxi3InitiatorPrimitiveIf.h"

TlmAxi3InitiatorPrimitiveIf:: TlmAxi3InitiatorPrimitiveIf(void) :
  _object_aw(NULL),
	_object_w(NULL),
	_object_ar(NULL),
	_object_b(NULL),
	_object_r(NULL),
	_receive_aw_response_event(NULL),
	_receive_w_response_event(NULL),
	_receive_ar_response_event(NULL),
	_receive_b_request_event(NULL),
	_receive_r_request_event(NULL) {
}

TlmAxi3InitiatorPrimitiveIf::~TlmAxi3InitiatorPrimitiveIf(void) {
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
	if (_receive_aw_response_event) {
		_receive_aw_response_event = NULL;
	}
	if (_receive_w_response_event) {
		_receive_w_response_event = NULL;
	}
	if (_receive_ar_response_event) {
		_receive_ar_response_event = NULL;
	}
	if (_receive_b_request_event) {
		_receive_b_request_event = NULL;
	}
	if (_receive_r_request_event) {
		_receive_r_request_event = NULL;
	}
#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
	axi_aw = 0;
	axi_w = 0;
	axi_b = 0;
	axi_ar = 0;
	axi_r = 0;
#endif
}

tlm::tlm_sync_enum
TlmAxi3InitiatorPrimitiveIf::initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                         tlm::tlm_phase&           phase,
                                                         sc_core::sc_time&         t)
{
	//std::cout << "IN : " << __FILE__ << " / " << __FUNCTION__ << std::endl;

	TlmAxi3Payload *tmp_payload_axi = NULL;
	TlmAxi3Payload *payload_axi = NULL;
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
#if 1 //DEBUG@NOB
#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
		axi_b->record_transport_socket("key", "base", trans);
#endif
#endif
		/* Copy TlmAxi3Payload */
		payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());

		if (_object_b) {
			_object_b->receiveBRequest(payload_axi);
		}
		if (_receive_b_request_event) {
			_receive_b_request_event->notify();
		}

		if (payload_axi) {
			delete payload_axi;
			payload_axi = NULL;
		}
	}

#if 0 //DEBUG@NOB
#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
	axi_b->record_transport_socket("key", "base", trans);
#endif
#endif

	return result;
}

tlm::tlm_sync_enum
TlmAxi3InitiatorPrimitiveIf::initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                         tlm::tlm_phase&           phase,
                                                         sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi = NULL;
  TlmAxi3Payload *payload_axi = NULL;
#if 0 // DEBUG@yama (TBD_IMA_ACCEPTED)
  tlm::tlm_sync_enum result(tlm::TLM_COMPxLETED);
#else
  tlm::tlm_sync_enum result(tlm::TLM_ACCEPTED);
#endif

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
#if 0 //DEBUG@NOB
#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
    axi_r->record_transport_socket("key", "base", trans);
#endif
#endif

    /* Copy TlmAxi3Payload */
    payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());

    if (_object_r) {
      _object_r->receiveRRequest(payload_axi);
    }
    if (_receive_r_request_event) {
      _receive_r_request_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }

#if 1 //DEBUG@NOB
#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
  axi_r->record_transport_socket("key", "base", trans);
#endif
#endif

  return result;
}

tlm::tlm_sync_enum
TlmAxi3InitiatorPrimitiveIf::initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);

#if 0
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
#endif

  /* Check Initialize */
  if (!_object_aw) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    if (tmp_payload_axi) {
      /* Copy TlmAxi3Payload */
      payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
    } else {
      /* Create TlmAxi3Payload */
      payload_axi = new TlmAxi3Payload(tmp_payload_axi->getByteSize());
    }

    if (_object_aw) {
      _object_aw->receiveAwResponse(payload_axi);
    }

    if (_receive_aw_response_event) {
      _receive_aw_response_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
  axi_aw->record_transport_socket();
#endif

  return result;
}

tlm::tlm_sync_enum
TlmAxi3InitiatorPrimitiveIf::initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                         tlm::tlm_phase&           phase,
                                                         sc_core::sc_time&         t) {
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);

#if 0
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
#endif

  /* Check Initialize */
  if (!_object_w) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    if (tmp_payload_axi) {
      /* Copy TlmAxi3Payload */
      payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
    } else {
      /* Create TlmAxi3Payload */
      payload_axi = new TlmAxi3Payload(tmp_payload_axi->getByteSize());
    }

    if (_object_w) {
      _object_w->receiveWResponse(payload_axi);
    }

    if (_receive_w_response_event) {
      _receive_w_response_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
  axi_w->record_transport_socket();
#endif

  return result;
}

tlm::tlm_sync_enum
TlmAxi3InitiatorPrimitiveIf::initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t){
  TlmAxi3Payload *tmp_payload_axi;
  TlmAxi3Payload *payload_axi;
  tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

  /* Get TlmAxi3Payload */
  trans.get_extension(tmp_payload_axi);

#if 0
  /* Check tlm_generic_payload has an TlmAxi3Payload */
  if (!tmp_payload_axi) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }
#endif

  /* Check Initialize */
  if (!_object_ar) {
    trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
  }

  if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
    /* Copy TlmAxi3Payload */
    if (tmp_payload_axi) {
      /* Copy TlmAxi3Payload */
      payload_axi = reinterpret_cast<TlmAxi3Payload*>(tmp_payload_axi->clone());
    } else {
      /* Create TlmAxi3Payload */
      payload_axi = new TlmAxi3Payload(tmp_payload_axi->getByteSize());
    }

    if (_object_ar) {
      _object_ar->receiveArResponse(payload_axi);
    }

    if (_receive_ar_response_event) {
      _receive_ar_response_event->notify();
    }

    if (payload_axi) {
      delete payload_axi;
      payload_axi = NULL;
    }
  }

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
  axi_ar->record_transport_socket();
#endif

  return result;
}

int
TlmAxi3InitiatorPrimitiveIf::initializeAw(TlmAxi3InitiatorPrimitiveIfBase* object_aw) {
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
TlmAxi3InitiatorPrimitiveIf::sendAwRequest(TlmAxi3Payload *payload_aw) {
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

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
    axi_aw->record_transport_socket("key", "base", payload_aw_tlm);
#endif

    /* Send AW request */
    response = initiator_AW->nb_transport_fw(payload_aw_tlm, phase, latency);
    payload_aw_tlm.release_extension(payload_aw_axi);
    payload_aw_axi = NULL;
  }

  return result;  
}

int
TlmAxi3InitiatorPrimitiveIf::registerReceiveAwResponseEvent(sc_event *receive_aw_response_event) {
  int result(0);

  /* Check argument */
  if (!receive_aw_response_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_aw) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_aw_response_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_aw_response_event = receive_aw_response_event;
  }

  return result;
}

int
TlmAxi3InitiatorPrimitiveIf::initializeW(TlmAxi3InitiatorPrimitiveIfBase* object_w) {
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
TlmAxi3InitiatorPrimitiveIf::sendWRequest(TlmAxi3Payload *payload_w) {
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

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
    axi_w->record_transport_socket("key", "base", payload_w_tlm);
#endif

    /* Send W request */
    response = initiator_W->nb_transport_fw(payload_w_tlm, phase, latency);
    payload_w_tlm.release_extension(payload_w_axi);
    payload_w_axi = NULL;
  }

  return result;  
}

int
TlmAxi3InitiatorPrimitiveIf::registerReceiveWResponseEvent(sc_event *receive_w_response_event) {
  int result(0);

  /* Check argument */
  if (!receive_w_response_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_w) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_w_response_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_w_response_event = receive_w_response_event;
  }

  return result;
}

int
TlmAxi3InitiatorPrimitiveIf::initializeAr(TlmAxi3InitiatorPrimitiveIfBase* object_ar) {
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
TlmAxi3InitiatorPrimitiveIf::sendArRequest(TlmAxi3Payload *payload_ar) {
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

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
    axi_ar->record_transport_socket("key", "base", payload_ar_tlm);
#endif

    /* Send AR request */
    response = initiator_AR->nb_transport_fw(payload_ar_tlm, phase, latency);
    payload_ar_tlm.release_extension(payload_ar_axi);
    payload_ar_axi = NULL;
  }

  return result;  
}

int
TlmAxi3InitiatorPrimitiveIf::registerReceiveArResponseEvent(sc_event *receive_ar_response_event) {
  int result(0);

  /* Check argument */
  if (!receive_ar_response_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_ar) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_ar_response_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_ar_response_event = receive_ar_response_event;
  }

  return result;
}

int
TlmAxi3InitiatorPrimitiveIf::initializeB(TlmAxi3InitiatorPrimitiveIfBase* object_b) {
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
TlmAxi3InitiatorPrimitiveIf::sendBResponse(TlmAxi3Payload *payload_b) {
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

    /* Receive B response */
    response = initiator_B->nb_transport_bw(payload_b_tlm, phase, latency);
    payload_b_tlm.release_extension(payload_b_axi);
    payload_b_axi = NULL;

#if 1 //DEBUG@NOB
#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
#if 1 //FIXEDME@NOB
    wait(4.8,SC_NS);
#endif
    axi_b->record_transport_socket();
#endif
#endif
  }

  return result;  
}

int
TlmAxi3InitiatorPrimitiveIf::registerReceiveBRequestEvent(sc_event *receive_b_request_event) {
  int result(0);

  /* Check argument */
  if (!receive_b_request_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_b) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_b_request_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_b_request_event = receive_b_request_event;
  }

  return result;
}

int
TlmAxi3InitiatorPrimitiveIf::initializeR(TlmAxi3InitiatorPrimitiveIfBase* object_r) {
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
TlmAxi3InitiatorPrimitiveIf::sendRResponse(TlmAxi3Payload *payload_r) {
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

    /* Receive R response */
    response = initiator_R->nb_transport_bw(payload_r_tlm, phase, latency);
    payload_r_tlm.release_extension(payload_r_axi);
    payload_r_axi = NULL;

#ifdef TLM_AXI3_INITIATOR_PRIMITIVE_IF_OUTPUT_VCD
    // wait(5,SC_NS);
    axi_r->record_transport_socket();
#endif
  }

  return result;  
}

int
TlmAxi3InitiatorPrimitiveIf::registerReceiveRRequestEvent(sc_event *receive_r_request_event) {
  int result(0);

  /* Check argument */
  if (!receive_r_request_event) {
    result = -1;
  }

  /* Check Initialize */
  if (!_object_r) {
    result = -1;
  }

  /* Check pre-call */
  if (_receive_r_request_event) {
    result = -1;
  }

  if (result == 0) {
    /* Register event(sc_event) */
    _receive_r_request_event = receive_r_request_event;
  }

  return result;
}
