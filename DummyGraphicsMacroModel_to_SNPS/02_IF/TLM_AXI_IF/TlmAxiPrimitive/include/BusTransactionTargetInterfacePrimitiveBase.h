/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2010
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file BusTransactionTargetInterfacePrimitiveBase.h
 * @brief Bus transaction target pirimitive interface for AXI-TLM interface(header)
 *
 * @date $Date: 2010/09/02 00:00:00 $
 * @version $Id: BusTransactionTargetInterfacePrimitiveBase.h,v 1.1 2010/09/02 00:00:00 imaizumi Exp $
 */
#ifndef BusTransactionTargetInterfacePrimitiveBase_h
#define BusTransactionTargetInterfacePrimitiveBase_h

#include "axi_payload.h"

template<class DATA_TYPE = unsigned int>
class BusTransactionTargetInterfacePrimitiveBase {
public:
  /**
   * Receive AW transaction request function
   *
   * Receive AW transaction request function
   * @param payload_aw AW payload for AXI-TLM interface
   */
  virtual void receiveAwRequest(axi_payload<DATA_TYPE>* payload_aw) {}

  /**
   * Receive W transaction request function
   *
   * Receive W transaction request function
   * @param payload_aw W payload for AXI-TLM interface
   */
  virtual void receiveWRequest(axi_payload<DATA_TYPE>* payload_w) {}

  /**
   * Receive AR transaction request function
   *
   * Receive AR transaction request function
   * @param payload_aw AR payload for AXI-TLM interface
   */
  virtual void receiveArRequest(axi_payload<DATA_TYPE>* payload_ar) {}

  /**
   * Receive B transaction response function
   *
   * Receive B transaction response function
   * @param payload_b B payload for AXI-TLM interface
   */
  virtual void receiveBResponse(axi_payload<DATA_TYPE>* payload_b) {}

  /**
   * Receive R transaction response function
   *
   * Receive R transaction response function
   * @param payload_r R payload for AXI-TLM interface
   */
  virtual void receiveRResponse(axi_payload<DATA_TYPE>* payload_r) {}
};
#endif /* BusTransactionTargetInterfacePrimitiveBase_h */
