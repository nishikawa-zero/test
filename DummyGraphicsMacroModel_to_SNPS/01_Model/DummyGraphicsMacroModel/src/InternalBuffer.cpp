/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file InternalBuffer.h
 * @brief Internal buffer for DummyGraphicsMacroModel (source)
 */
#include "InternalBuffer.h"

InternalBuffer::InternalBuffer(void) :
  m_width(DEFAULT_WIDTH),
  m_depth(DEFAULT_DEPTH),
  m_write_latency(DEFAULT_WRITE_LATENCY),
  m_read_latency(DEFAULT_READ_LATENCY),
  m_time_unit(SC_NS),
  m_status(0) {
}

InternalBuffer::~InternalBuffer(void){
  while (!m_buffer.empty()) {
    delete m_buffer.front();
    m_buffer.pop_front();
  }
}

void
InternalBuffer::initialize(const unsigned int width,
                           const unsigned int depth,
                           const unsigned int write_latency,
                           const unsigned int read_latency,
                           const sc_time_unit time_unit) {
  if (width != 0) {
    m_width = width;
  }
  if (depth != 0) {
    m_depth = depth;
  }
  m_write_latency = write_latency;
  m_read_latency = read_latency;
  m_time_unit = time_unit;
}


int
InternalBuffer::write(const unsigned char *data, const bool is_wait) {
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
    sc_time latency(m_write_latency + m_read_latency, m_time_unit);
    for (unsigned int i = 0; i < m_width; ++i){
      record->data[i] = data[i];
    }
    record->time_to_can_read = sc_time_stamp() + latency;
    m_buffer.push_back(record);
    m_e_push.notify(m_write_latency + m_read_latency, m_time_unit);
    if (is_wait) {
#if 0
      std::cout << sc_time_stamp() << " m_write_latency=" << m_write_latency << std::endl;
      std::cout << sc_time_stamp() << " m_read_latency=" << m_read_latency << std::endl;
      std::cout << sc_time_stamp() << " m_time_unit=" << m_time_unit << std::endl;
      std::cout << sc_time_stamp() << " latency=" << latency << std::endl;
      std::cout << sc_time_stamp() << " record->time_to_can_read=" << record->time_to_can_read << std::endl;
#endif
      wait(m_write_latency, m_time_unit);
    }
  }

  return result;
}

int
InternalBuffer::read(unsigned char *data, const bool is_wait) {
  int result(0);
 
  if (m_buffer.empty()) {
    if (is_wait) {
      wait(m_e_push);
    } else {
      result = -1;
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
    for (unsigned int i = 0; i < m_width; ++i){
      data[i] = m_buffer.front()->data[i];
    }
    delete[] m_buffer.front()->data;
    delete m_buffer.front();
    m_buffer.pop_front();
    m_e_pop.notify();
  }

  return result;
}  

unsigned int
InternalBuffer::size(void) {
  return m_buffer.size() * m_width;
}

bool
InternalBuffer::empty(void) {
  return m_buffer.empty();
}

unsigned int
InternalBuffer::getWidth(void) {
  return m_width;
}

unsigned int
InternalBuffer::getDepth(void) {
  return m_depth;
}

unsigned int
InternalBuffer::getWriteLatency(void) {
  return m_write_latency;
}

unsigned int
InternalBuffer::getReadLatency(void) {
  return m_read_latency;
}

void
InternalBuffer::setStatus(const unsigned int status) {
  m_status = status;
  m_e_set_status.notify();
}

unsigned int
InternalBuffer::getStatus(void) {
  return m_status;
}

void
InternalBuffer::waitStatus(const unsigned int status) {

  while (m_status != status) {
    wait(m_e_set_status);
  }
}
