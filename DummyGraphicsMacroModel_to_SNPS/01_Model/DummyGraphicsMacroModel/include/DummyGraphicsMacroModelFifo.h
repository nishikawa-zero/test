/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file DummyGraphicsMacroModelFifo.h
 * @brief Fifo for DummyGraphicsMacroModel (header)
 */
#ifndef FIFO_H
#define FIFO_H

#include <list>
#include <systemc.h>

class DummyGraphicsMacroModelFifo {
public:
  enum Status {
    EMPTY = 0,
    USING = 1,
    FULL = 2,
    SizeOfStatus
  };

private:
  enum Prameters {
    MIN_WIDTH = 1,
    MIN_DEPTH = 1
  };

  struct Record {
    unsigned char *data;
    sc_time time_to_can_read;
  };
  
public:
  DummyGraphicsMacroModelFifo(const unsigned int width,
                              const unsigned int depth,
                              const unsigned int write_clock,
                              const unsigned int read_clock,
                              const unsigned int write_latency,
                              const unsigned int read_latencysc_time_unit,
                              const sc_time_unit time_unit);  
  ~DummyGraphicsMacroModelFifo(void);

  int write(const unsigned char *data,
            const bool is_wait = false);
  int read(unsigned char *data,
           const bool is_wait = false);
  unsigned int size(void);
  bool empty(void);
  bool full(void);

  void setStatus(unsigned char);
  unsigned char getStatus(void);
  void waitStatus(unsigned char);

  unsigned int getWidth(void);
  unsigned int getDepth(void);
  unsigned int getWriteClock(void);
  unsigned int getReadClock(void);
  unsigned int getWriteLatency(void);
  unsigned int getReadLatency(void);

private:
  unsigned int m_width;
  unsigned int m_depth;
  unsigned int m_write_clock;
  unsigned int m_read_clock;
  unsigned int m_write_latency;
  unsigned int m_read_latency;
  sc_time_unit m_time_unit;

  sc_time m_write_latency_time;
  sc_time m_read_latency_time;
  sc_time m_pre_read_time;
  
  unsigned char m_status;

  sc_event m_e_push;
  sc_event m_e_pop;
  sc_event m_e_set_status;

  std::list<Record*> m_buffer;
};
#endif /* INTERNAL_BUFFER_H */
  
