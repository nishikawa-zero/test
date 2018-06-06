/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2010
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file BusTransactionInitiatorInterfacePrimitiveBase.h
 * @brief Bus transaction initiator pirimitive interface for AXI-TLM interface(header)
 *
 * @date $Date: 2010/09/02 00:00:00 $
 * @version $Id: BusTransactionInitiatorInterfacePrimitiveBase.h,v 1.1 2010/09/02 00:00:00 imaizumi Exp $
 */
#ifndef BusTransactionInitiatorInterfacePrimitiveBase_h
#define BusTransactionInitiatorInterfacePrimitiveBase_h

#include "axi_payload.h"

template<class DATA_TYPE = unsigned int>
class BusTransactionInitiatorInterfacePrimitiveBase {
public:
  /**
   * Receive AW transaction response function
   *
   * Receive AW transaction response function
   * @param payload_aw AW payload for AXI-TLM interface
   */
  virtual void receiveAwResponse(axi_payload<DATA_TYPE>* payload_aw) {}

  /**
   * Receive W transaction response function
   *
   * Receive W transaction response function
   * @param payload_aw W payload for AXI-TLM interface
   */
  virtual void receiveWResponse(axi_payload<DATA_TYPE>* payload_w) {}

  /**
   * Receive AR transaction response function
   *
   * Receive AR transaction response function
   * @param payload_aw AR payload for AXI-TLM interface
   */
  virtual void receiveArResponse(axi_payload<DATA_TYPE>* payload_ar) {}

  /**
   * Receive B transaction request function
   *
   * Receive B transaction request function
   * @param payload_b B payload for AXI-TLM interface
   */
  virtual void receiveBRequest(axi_payload<DATA_TYPE>* payload_b) {}

  /**
   * Receive R transaction request function
   *
   * Receive R transaction request function
   * @param payload_r R payload for AXI-TLM interface
   */
  virtual void receiveRRequest(axi_payload<DATA_TYPE>* payload_r) {}
};
#endif /* BusTransactionInitiatorInterfacePrimitiveBase_h */
