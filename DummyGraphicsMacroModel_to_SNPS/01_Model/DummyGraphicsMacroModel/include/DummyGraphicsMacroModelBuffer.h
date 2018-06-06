/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModelBuffer.h
 * @brief DummyGraphicsMacroModelBuffer (header)
 */
#include <systemc.h>
#include <string>
#include <queue>

#include "DummyGraphicsMacroModelFifo.h"

#ifndef DUMMY_GRAPHICS_MACRO_MODEL_BUFFER_H
#define DUMMY_GRAPHICS_MACRO_MODEL_BUFFER_H

class DummyGraphicsMacroModelBuffer {
private:
  enum Parameters {
    MIN_BUFFER_NUMBER = 1
  };

private:
  struct InternalBuffer {
    bool is_writable;
    bool is_readable;
    DummyGraphicsMacroModelFifo* data;
  };

public:
  DummyGraphicsMacroModelBuffer(const unsigned int number_of_internal_buffer,
                                const unsigned int width,
                                const unsigned int depth,
                                const unsigned int write_clock,
                                const unsigned int read_clock,
                                const unsigned int write_latency,
                                const unsigned int read_latency,
                                const sc_time_unit time_unit = SC_NS);
  ~DummyGraphicsMacroModelBuffer(void);

  int write(const unsigned char *data,
            const bool is_wait = false);
  int read(unsigned char *data,
           const bool is_wait = false);
  unsigned int getWriteBufferSize(void);
  unsigned int getReadBufferSize(void);
  unsigned int getBufferSize(const unsigned int internal_buffer_id);
  unsigned char getWriteBufferStatus(void);
  unsigned char getReadBufferStatus(void);
  unsigned char getBufferStatus(const unsigned int internal_buffer_id);
  void waitWriteBufferStatus(unsigned char status);
  void waitReadBufferStatus(unsigned char status);
  void switchWriteBuffer(void);
  void switchReadBuffer(void);
  bool isPossibleToSwitchWriteBuffer(void);
  bool isPossibleToSwitchReadBuffer(void);

  unsigned int getInternalWriteBufferId(void);
  unsigned int getInternalReadBufferId(void);

public:
  unsigned int getNumberOfInternalBuffer(void);
  unsigned int getWidth(void);
  unsigned int getDepth(void);
  unsigned int getWriteClock(void);
  unsigned int getReadClock(void);
  unsigned int getWriteLatency(void);
  unsigned int getReadLatency(void);
  sc_time_unit getIimeUnit(void);

private:
  void checkWriteBufferStatus(void);
  void checkReadBufferStatus(void);
  void waitCurrentWriteBufferWriteEnable(void);
  void waitCurrentReadBufferReadEnable(void);
  void incrementNextWriteBufferId(void);
  void incrementNextReadBufferId(void);

private:
  unsigned int m_number_of_internal_buffer;
  unsigned int m_width;
  unsigned int m_depth;
  unsigned int m_write_clock;
  unsigned int m_read_clock;
  unsigned int m_write_latency;
  unsigned int m_read_latency;
  sc_time_unit m_time_unit;

  unsigned int m_current_write_buffer_id;
  unsigned int m_current_read_buffer_id;
  unsigned int m_next_write_buffer_id;
  unsigned int m_next_read_buffer_id;

  sc_event m_e_write;
  sc_event m_e_read;
  sc_event m_e_set_write_buffer_status[DummyGraphicsMacroModelFifo::SizeOfStatus];
  sc_event m_e_set_read_buffer_status[DummyGraphicsMacroModelFifo::SizeOfStatus];
  sc_event m_e_switch_write_buffer;
  sc_event m_e_switch_read_buffer;
  
  InternalBuffer *m_internal_buffers;
};
#endif /* DUMMY_GRAPHICS_MACRO_MODEL_BUFFER_H */
