/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file InternalBuffer.h
 * @brief Internal buffer for DummyGraphicsMacroModel (header)
 */
#ifndef INTERNAL_BUFFER_H
#define INTERNAL_BUFFER_H

#include <list>
#include <systemc.h>

class InternalBuffer {
private:
  enum DefaultPrameters {
    DEFAULT_WIDTH = 1,
    DEFAULT_DEPTH = 1,
    DEFAULT_WRITE_LATENCY = 10,
    DEFAULT_READ_LATENCY = 10
  };

  struct Record {
    unsigned char *data;
    sc_time time_to_can_read;
  };
  
public:
  InternalBuffer(void);  
  ~InternalBuffer(void);

  void initialize(const unsigned int width = 1, /* byte */
                  const unsigned int depth = 1,
                  const unsigned int write_latency = 10,
                  const unsigned int read_latency = 10,
                  const sc_time_unit time_unit = SC_NS);
  
  int write(const unsigned char *data, bool is_wait = false);
  int read(unsigned char *data, bool is_wait = false);
  unsigned int size(void);
  bool empty(void);

  unsigned int getWidth(void);
  unsigned int getDepth(void);
  unsigned int getWriteLatency(void);
  unsigned int getReadLatency(void);

  void setStatus(const unsigned int status);
  unsigned int getStatus(void);
  void waitStatus(const unsigned int status);
 
private:
  unsigned int m_width;
  unsigned int m_depth;
  unsigned int m_write_latency;
  unsigned int m_read_latency;
  sc_time_unit m_time_unit;

  unsigned int m_status;
  sc_time_unit m_pre_read_time;

  sc_event m_e_push;
  sc_event m_e_pop;
  sc_event m_e_set_status;

  std::list<Record*> m_buffer;
};
#endif /* INTERNAL_BUFFER_H */
  
