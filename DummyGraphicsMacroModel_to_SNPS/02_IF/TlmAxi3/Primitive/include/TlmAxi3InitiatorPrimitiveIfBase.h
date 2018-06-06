/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3InitiatorPrimitiveIfBase.h
 * @brief Base class for primitive interface class of TLM AXI initiator (header)
 */
#ifndef TLM_AXI2_INITIATOR_PRIMITIVE_IF_BASE_H
#define TLM_AXI2_INITIATOR_PRIMITIVE_IF_BASE_H

#include "TlmAxi3Payload.h"

class TlmAxi3InitiatorPrimitiveIfBase {
public:
  /**
   * Receive AW transaction response function
   *
   * Receive AW transaction response function
   * @param payload_aw AW payload for AXI-TLM interface
   */
  virtual void receiveAwResponse(TlmAxi3Payload *payload_aw) {}

  /**
   * Receive W transaction response function
   *
   * Receive W transaction response function
   * @param payload_aw W payload for AXI-TLM interface
   */
  virtual void receiveWResponse(TlmAxi3Payload *payload_w) {}

  /**
   * Receive AR transaction response function
   *
   * Receive AR transaction response function
   * @param payload_aw AR payload for AXI-TLM interface
   */
  virtual void receiveArResponse(TlmAxi3Payload *payload_ar) {}

  /**
   * Receive B transaction request function
   *
   * Receive B transaction request function
   * @param payload_b B payload for AXI-TLM interface
   */
  virtual void receiveBRequest(TlmAxi3Payload *payload_b) {}

  /**
   * Receive R transaction request function
   *
   * Receive R transaction request function
   * @param payload_r R payload for AXI-TLM interface
   */
  virtual void receiveRRequest(TlmAxi3Payload *payload_r) {}
};
#endif /* TLM_AXI2_INITIATOR_PRIMITIVE_IF_BASE_H */
