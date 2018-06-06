/*
* ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2010
* LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
*
*/
/**
* @file BusTransactionInitiatorInterfacePrimitive.cpp
* @brief Bus transaction initiator pirimitive interface for AXI-TLM interface(source)
*
* @date $Date: 2010/09/02 00:00:00 $
* @version $Id: BusTransactionInitiatorInterfacePrimitive.cpp,v 1.3 2010/09/02 00:00:00 imaizumi Exp $
*/
#include "BusTransactionInitiatorInterfacePrimitive.h"
#if INFO
#include <iostream>
#endif

template<class DATA_TYPE>
BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>:: BusTransactionInitiatorInterfacePrimitive(void) :
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
#ifdef VCD_OUTPUT_FUNC_ON
#if 1 //DEBUG@NOB
		string basename = sc_get_curr_simcontext()->hierarchy_curr()->name();
		axi_aw = new tb_tr_tlm2(basename.c_str(), ".AW", true);
		axi_w  = new tb_tr_tlm2(basename.c_str(), ".W",  true);
		axi_b  = new tb_tr_tlm2(basename.c_str(), ".B",  true);
		axi_ar = new tb_tr_tlm2(basename.c_str(), ".AR", true);
		axi_r  = new tb_tr_tlm2(basename.c_str(), ".R",  true);
#else
		axi_aw = new tb_tr_tlm2("AXI_M", ".AW", true);
		axi_w  = new tb_tr_tlm2("AXI_M", ".W",  true);
		axi_b  = new tb_tr_tlm2("AXI_M", ".B",  true);
		axi_ar = new tb_tr_tlm2("AXI_M", ".AR", true);
		axi_r  = new tb_tr_tlm2("AXI_M", ".R",  true);
#endif
#endif
}

template<class DATA_TYPE>
BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::~BusTransactionInitiatorInterfacePrimitive(void) {
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
#ifdef VCD_OUTPUT_FUNC_ON
	axi_aw = 0;
	axi_w = 0;
	axi_b = 0;
	axi_ar = 0;
	axi_r = 0;
#endif
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
	tlm::tlm_phase&           phase,
	sc_core::sc_time&         t)
{
	//std::cout << "IN : " << __FILE__ << " / " << __FUNCTION__ << std::endl;

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
#if 1 //DEBUG@NOB
#ifdef VCD_OUTPUT_FUNC_ON
		axi_b->record_transport_socket("key", "base", trans);
#endif
#endif
		/* Copy axi_payload */
		payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());

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
#ifdef VCD_OUTPUT_FUNC_ON
	axi_b->record_transport_socket("key", "base", trans);
#endif
#endif

	return result;
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
	tlm::tlm_phase&           phase,
	sc_core::sc_time&         t) {
		axi_payload<DATA_TYPE>* tmp_payload_axi;
		axi_payload<DATA_TYPE>* payload_axi;
#if 0 // DEBUG@yama (TBD_IMA_ACCEPTED)
		tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);
#else
		tlm::tlm_sync_enum result(tlm::TLM_ACCEPTED);
#endif

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
#if 0 //DEBUG@NOB
#ifdef VCD_OUTPUT_FUNC_ON
			axi_r->record_transport_socket("key", "base", trans);
#endif
#endif
			/* Copy axi_payload */
			payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());

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
#ifdef VCD_OUTPUT_FUNC_ON
		axi_r->record_transport_socket("key", "base", trans);
#endif
#endif

		return result;
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
	tlm::tlm_phase&           phase,
	sc_core::sc_time&         t) {
		axi_payload<DATA_TYPE>* tmp_payload_axi;
		axi_payload<DATA_TYPE>* payload_axi;
		tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

		/* Get axi_payload */
		trans.get_extension(tmp_payload_axi);

#if 0
		/* Check tlm_generic_payload has an axi_payload */
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
				/* Copy axi_payload */
				payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());
			} else {
				/* Create axi_payload */
				payload_axi = new axi_payload<DATA_TYPE>;
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

#ifdef VCD_OUTPUT_FUNC_ON
		axi_aw->record_transport_socket();
#endif

		return result;
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
	tlm::tlm_phase&           phase,
	sc_core::sc_time&         t) {
		axi_payload<DATA_TYPE>* tmp_payload_axi;
		axi_payload<DATA_TYPE>* payload_axi;
		tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

		/* Get axi_payload */
		trans.get_extension(tmp_payload_axi);

#if 0
		/* Check tlm_generic_payload has an axi_payload */
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
				/* Copy axi_payload */
				payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());
			} else {
				/* Create axi_payload */
				payload_axi = new axi_payload<DATA_TYPE>;
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

#ifdef VCD_OUTPUT_FUNC_ON
		axi_w->record_transport_socket();
#endif

		return result;
}

template<class DATA_TYPE>
tlm::tlm_sync_enum
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
	tlm::tlm_phase&           phase,
	sc_core::sc_time&         t){
		axi_payload<DATA_TYPE>* tmp_payload_axi;
		axi_payload<DATA_TYPE>* payload_axi;
		tlm::tlm_sync_enum result(tlm::TLM_COMPLETED);

		/* Get axi_payload */
		trans.get_extension(tmp_payload_axi);

#if 0
		/* Check tlm_generic_payload has an axi_payload */
		if (!tmp_payload_axi) {
			trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
		}
#endif

		/* Check Initialize */
		if (!_object_ar) {
			trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
		}

		if (trans.get_response_status() != tlm::TLM_GENERIC_ERROR_RESPONSE) {
			/* Copy axi_payload */
			if (tmp_payload_axi) {
				/* Copy axi_payload */
				payload_axi = reinterpret_cast<axi_payload<DATA_TYPE>*>(tmp_payload_axi->clone());
			} else {
				/* Create axi_payload */
				payload_axi = new axi_payload<DATA_TYPE>;
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

#ifdef VCD_OUTPUT_FUNC_ON
		axi_ar->record_transport_socket();
#endif

		return result;
}

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initializeAw(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_aw) {
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
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::sendAwRequest(axi_payload<DATA_TYPE>* payload_aw) {
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

#ifdef VCD_OUTPUT_FUNC_ON
			axi_aw->record_transport_socket("key", "base", payload_aw_tlm);
#endif

			/* Send AW request */
			response = initiator_AW->nb_transport_fw(payload_aw_tlm, phase, latency);
			payload_aw_tlm.release_extension(payload_aw_axi);
			payload_aw_axi = NULL;
		}

		return result;  
}

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::registerReceiveAwResponseEvent(sc_event* receive_aw_response_event) {
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

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initializeW(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_w) {
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
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::sendWRequest(axi_payload<DATA_TYPE>* payload_w) {
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

#ifdef VCD_OUTPUT_FUNC_ON
			axi_w->record_transport_socket("key", "base", payload_w_tlm);
#endif

			/* Send W request */
			response = initiator_W->nb_transport_fw(payload_w_tlm, phase, latency);
			payload_w_tlm.release_extension(payload_w_axi);
			payload_w_axi = NULL;
		}

		return result;  
}

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::registerReceiveWResponseEvent(sc_event* receive_w_response_event) {
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

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initializeAr(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_ar) {
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
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::sendArRequest(axi_payload<DATA_TYPE>* payload_ar) {
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

#ifdef VCD_OUTPUT_FUNC_ON
			axi_ar->record_transport_socket("key", "base", payload_ar_tlm);
#endif

			/* Send AR request */
			response = initiator_AR->nb_transport_fw(payload_ar_tlm, phase, latency);
			payload_ar_tlm.release_extension(payload_ar_axi);
			payload_ar_axi = NULL;
		}

		return result;  
}

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::registerReceiveArResponseEvent(sc_event* receive_ar_response_event) {
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

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initializeB(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_b) {
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
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::sendBResponse(axi_payload<DATA_TYPE>* payload_b) {
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

			/* Receive B response */
			response = initiator_B->nb_transport_bw(payload_b_tlm, phase, latency);
			payload_b_tlm.release_extension(payload_b_axi);
			payload_b_axi = NULL;

#if 1 //DEBUG@NOB
#ifdef VCD_OUTPUT_FUNC_ON
#if 1 //FIXEDME@NOB
			wait(4.8,SC_NS);
#endif
			axi_b->record_transport_socket();
#endif
#endif
		}

		return result;  
}

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::registerReceiveBRequestEvent(sc_event* receive_b_request_event) {
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

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::initializeR(BusTransactionInitiatorInterfacePrimitiveBase<DATA_TYPE>* object_r) {
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
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::sendRResponse(axi_payload<DATA_TYPE>* payload_r) {
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

			/* Receive R response */
			response = initiator_R->nb_transport_bw(payload_r_tlm, phase, latency);
			payload_r_tlm.release_extension(payload_r_axi);
			payload_r_axi = NULL;

#ifdef VCD_OUTPUT_FUNC_ON
			// wait(5,SC_NS);
			axi_r->record_transport_socket();
#endif
		}

		return result;  
}

template<class DATA_TYPE>
int
	BusTransactionInitiatorInterfacePrimitive<DATA_TYPE>::registerReceiveRRequestEvent(sc_event* receive_r_request_event) {
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

template class BusTransactionInitiatorInterfacePrimitive<sc_biguint<128> >;
template class BusTransactionInitiatorInterfacePrimitive<unsigned long long>;
template class BusTransactionInitiatorInterfacePrimitive<unsigned int>;
