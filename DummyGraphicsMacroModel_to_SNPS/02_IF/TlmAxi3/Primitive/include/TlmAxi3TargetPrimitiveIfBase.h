/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3TargetPrimitiveIfBase.h
 * @brief Base class for primitive intarface class of TLM AXI target (header)
 */
#ifndef TLM_AXI2_TARGET_PRIMITIVE_IF_BASE_H
#define TLM_AXI2_TARGET_PRIMITIVE_IF_BASE_H

#include "TlmAxi3Payload.h"

class TlmAxi3TargetPrimitiveIfBase {
public:
  /**
   * Receive AW transaction request function
   *
   * Receive AW transaction request function
   * @param payload_aw AW payload for AXI-TLM interface
   */
  virtual void receiveAwRequest(TlmAxi3Payload *payload_aw) {}

  /**
   * Receive W transaction request function
   *
   * Receive W transaction request function
   * @param payload_aw W payload for AXI-TLM interface
   */
  virtual void receiveWRequest(TlmAxi3Payload *payload_w) {}

  /**
   * Receive AR transaction request function
   *
   * Receive AR transaction request function
   * @param payload_aw AR payload for AXI-TLM interface
   */
  virtual void receiveArRequest(TlmAxi3Payload *payload_ar) {}

  /**
   * Receive B transaction response function
   *
   * Receive B transaction response function
   * @param payload_b B payload for AXI-TLM interface
   */
  virtual void receiveBResponse(TlmAxi3Payload *payload_b) {}

  /**
   * Receive R transaction response function
   *
   * Receive R transaction response function
   * @param payload_r R payload for AXI-TLM interface
   */
  virtual void receiveRResponse(TlmAxi3Payload *payload_r) {}
};
#endif /* TLM_AXI2_TARGET_PRIMITIVE_IF_BASE_H */
