/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file DummyGraphicsMacroModelFifo.h
 * @brief Internal buffer for DummyGraphicsMacroModel (source)
 */
#include "DummyGraphicsMacroModelFifo.h"

DummyGraphicsMacroModelFifo::DummyGraphicsMacroModelFifo(const unsigned int width,
                                                         const unsigned int depth,
                                                         const unsigned int write_clock,
                                                         const unsigned int read_clock,
                                                         const unsigned int write_latency,
                                                         const unsigned int read_latency,
                                                         const sc_time_unit time_unit) :
  m_write_clock(write_clock),
  m_read_clock(read_clock),
  m_write_latency(write_latency),
  m_read_latency(read_latency),
  m_time_unit(time_unit),
  m_status(EMPTY) {

  if (width < MIN_WIDTH) {
    m_width = MIN_WIDTH;
    std::cout << "[WARNING] width was modified (" << width << "->" << m_width << ")" << std::endl;
  } else {
    m_width = width;
  }

  if (depth < MIN_DEPTH) {
    m_depth = MIN_DEPTH;
    std::cout << "[WARNING] depth was modified (" << depth << "->" << m_depth << ")" << std::endl;
  } else {
    m_depth = depth;
  }

  m_write_latency_time = sc_time(m_write_latency * m_write_clock, m_time_unit);
  m_read_latency_time = sc_time(m_read_latency * m_read_clock, m_time_unit);
}

DummyGraphicsMacroModelFifo::~DummyGraphicsMacroModelFifo(void){
  while (!m_buffer.empty()) {
    delete m_buffer.front();
    m_buffer.pop_front();
  }
}

int
DummyGraphicsMacroModelFifo::write(const unsigned char *data, const bool is_wait) {
  int result(0);

  if (m_depth != 0) {
    if (m_depth <= m_buffer.size()) {
      if (is_wait) {
        wait(m_e_pop);
      } else {
        result = -1;
      }
    }
  }

  if (result == 0) {
    Record* record = new Record;
    record->data = new unsigned char[m_width];
    for (unsigned int i = 0; i < m_width; ++i){
      record->data[i] = data[i];
    }
    record->time_to_can_read = sc_time_stamp() + m_write_latency_time + m_read_latency_time;
    if (is_wait) {
#if 0
      std::cout << sc_time_stamp() << " m_write_latency=" << m_write_latency << std::endl;
      std::cout << sc_time_stamp() << " m_read_latency=" << m_read_latency << std::endl;
      std::cout << sc_time_stamp() << " m_time_unit=" << m_time_unit << std::endl;
      std::cout << sc_time_stamp() << " record->time_to_can_read=" << record->time_to_can_read << std::endl;
      std::cout << sc_time_stamp() << " m_write_latency_time=" << m_write_latency_time << std::endl;
      std::cout << sc_time_stamp() << " m_read_latency_time=" << m_read_latency_time << std::endl;
#endif
      wait(m_write_latency_time);
      while (m_depth <= m_buffer.size()) {
        wait(m_e_pop);
      }
      m_buffer.push_back(record);
      if (sc_time_stamp() < record->time_to_can_read) {
        m_e_push.notify(record->time_to_can_read - sc_time_stamp());
      } else {
        m_e_push.notify();
      }
    } else {
      m_buffer.push_back(record);
      m_e_push.notify(m_write_latency + m_read_latency, m_time_unit);
    }
  }

  if (full()) {
    setStatus(FULL);
  } else {
    setStatus(USING);    
  }

  return result;
}

int
DummyGraphicsMacroModelFifo::read(unsigned char *data, const bool is_wait) {
  int result(0);
 
  while (m_buffer.empty()) {
    if (is_wait) {
      wait(m_e_push);
    } else {
      result = -1;
      break;
    }
  }
  
  if (!m_buffer.empty()) {
    if (sc_time_stamp() < m_buffer.front()->time_to_can_read) {
      if (is_wait) {
        wait(m_buffer.front()->time_to_can_read - sc_time_stamp());
      } else {
        result = -1;
      }
    }
  } else {
    result = -1;
  }

  if (result == 0) {
    if (sc_time_stamp() < m_pre_read_time + m_read_latency_time) {
      if (is_wait) {
        wait(m_pre_read_time + m_read_latency_time - sc_time_stamp());
      } else {
        result = -1;
      }
    }
  }
  
  if (result == 0) {
    for (unsigned int i = 0; i < m_width; ++i){
      data[i] = m_buffer.front()->data[i];
    }
    delete[] m_buffer.front()->data;
    delete m_buffer.front();
    m_buffer.pop_front();
    m_e_pop.notify();
    m_pre_read_time = sc_time_stamp();
  }

  if (empty()) {
    setStatus(EMPTY);
  } else {
    setStatus(USING);    
  }

  return result;
}  

unsigned int
DummyGraphicsMacroModelFifo::size(void) {
  return m_buffer.size() * m_width;
}

bool
DummyGraphicsMacroModelFifo::empty(void) {
  return m_buffer.empty();
}

bool
DummyGraphicsMacroModelFifo::full(void) {
  if (m_buffer.size() < m_depth) {
    return false;
  } else {
    return true;
  }
}

void
DummyGraphicsMacroModelFifo::setStatus(unsigned char status) {
  if (status < SizeOfStatus) {
    m_status = status;
    m_e_set_status.notify();
#if 0
    std::cout << __FUNCTION__ << " m_status=" << (int)m_status << std::endl;
#endif
  }
}

unsigned char
DummyGraphicsMacroModelFifo::getStatus(void) {
  unsigned char result;

  switch (m_status) {
  case EMPTY:
    result = static_cast<unsigned char>(EMPTY);
    break;
  case FULL:
    result = static_cast<unsigned char>(FULL);
    break;
  default:
    result = static_cast<unsigned char>(USING);
    break;
  }
  return result;
}

void
DummyGraphicsMacroModelFifo::waitStatus(unsigned char status) {
  if (status < SizeOfStatus) {
    while (m_status != status) {
      wait(m_e_set_status);
    }
  }
}

unsigned int
DummyGraphicsMacroModelFifo::getWidth(void) {
  return m_width;
}

unsigned int
DummyGraphicsMacroModelFifo::getDepth(void) {
  return m_depth;
}

unsigned int
DummyGraphicsMacroModelFifo::getWriteClock(void) {
  return m_write_clock;
}

unsigned int
DummyGraphicsMacroModelFifo::getReadClock(void) {
  return m_read_clock;
}

unsigned int
DummyGraphicsMacroModelFifo::getWriteLatency(void) {
  return m_write_latency;
}

unsigned int
DummyGraphicsMacroModelFifo::getReadLatency(void) {
  return m_read_latency;
}

