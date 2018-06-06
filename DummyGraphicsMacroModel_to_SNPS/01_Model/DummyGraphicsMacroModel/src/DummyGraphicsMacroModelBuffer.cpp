/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModelBuffer.cpp
 * @brief DummyGraphicsMacroModelBuffer (source)
 */
#include "DummyGraphicsMacroModelBuffer.h"

DummyGraphicsMacroModelBuffer::DummyGraphicsMacroModelBuffer(const unsigned int number_of_internal_buffer,
                                                             const unsigned int width,
                                                             const unsigned int depth,
                                                             const unsigned int write_clock,
                                                             const unsigned int read_clock,
                                                             const unsigned int write_latency,
                                                             const unsigned int read_latency,
                                                             const sc_time_unit time_unit):
  m_number_of_internal_buffer(number_of_internal_buffer),
  m_width(width),
  m_depth(depth),
  m_write_clock(write_clock),
  m_read_clock(read_clock),
  m_write_latency(write_latency),
  m_read_latency(read_latency),
  m_time_unit(time_unit),
  m_current_write_buffer_id(0),
  m_current_read_buffer_id(0),
  m_next_write_buffer_id(1),
  m_next_read_buffer_id(1),
  m_internal_buffers(NULL) {

  if (number_of_internal_buffer < MIN_BUFFER_NUMBER) {
    m_number_of_internal_buffer = MIN_BUFFER_NUMBER;
    std::cout << "[WARNING] number_of_internal_buffer  was modified (" << number_of_internal_buffer  << "->" << m_number_of_internal_buffer << ")" << std::endl;;
  } else {
    m_number_of_internal_buffer = number_of_internal_buffer;
  }

#if 0
  std::cout << __FUNCTION__ << "m_number_of_internal_buffer=" << m_number_of_internal_buffer << std::endl;
#endif

  m_internal_buffers = new InternalBuffer[m_number_of_internal_buffer];

  for (unsigned int i = 0U; i < m_number_of_internal_buffer; ++i) {
    m_internal_buffers[i].data = new DummyGraphicsMacroModelFifo(m_width,
                                                                 m_depth,
                                                                 m_write_clock,
                                                                 m_read_clock,
                                                                 m_write_latency,
                                                                 m_read_latency,
                                                                 m_time_unit);
    m_internal_buffers[i].is_writable = true;
    m_internal_buffers[i].is_readable = false;
  }

  m_current_write_buffer_id = 0;
  m_current_read_buffer_id = 0;
  m_next_write_buffer_id = 0;
  m_next_read_buffer_id = 0;

  incrementNextWriteBufferId();
  incrementNextReadBufferId();
}

DummyGraphicsMacroModelBuffer::~DummyGraphicsMacroModelBuffer(void) {
  delete[] m_internal_buffers;
}


int
DummyGraphicsMacroModelBuffer::write(const unsigned char *data,
                                     const bool is_wait) {
  int result = 0;

#if 0
  std::cout << __FUNCTION__ << " m_current_write_buffer_id=" << m_current_write_buffer_id << ",is_writable=" << m_internal_buffers[m_current_write_buffer_id].is_writable << std::endl;
#endif

  if (is_wait) {
    while (!m_internal_buffers[m_current_write_buffer_id].is_writable) {
      wait(m_e_switch_read_buffer);
    }
  } else {
    if (!m_internal_buffers[m_current_write_buffer_id].is_writable) {
      result = -1;
    }
  }

  if (result == 0) {
    result = m_internal_buffers[m_current_write_buffer_id].data->write(data, is_wait);
    m_e_write.notify();
    checkWriteBufferStatus();
  }

  return result;
}

int
DummyGraphicsMacroModelBuffer::read(unsigned char *data,
                                    const bool is_wait) {
  int result = 0;

  if (is_wait) {
    while (!m_internal_buffers[m_current_read_buffer_id].is_readable) {
      wait(m_e_switch_write_buffer);
    }
  } else {
    if (!m_internal_buffers[m_current_read_buffer_id].is_readable) {
      result = -1;
    }
  }

  if (result == 0) {
    result = m_internal_buffers[m_current_read_buffer_id].data->read(data, is_wait);
    m_e_read.notify();
    checkReadBufferStatus();
  }

  return result;
}

unsigned int
DummyGraphicsMacroModelBuffer::getWriteBufferSize(void) {
  return m_internal_buffers[m_current_write_buffer_id].data->size();
}

unsigned int
DummyGraphicsMacroModelBuffer::getReadBufferSize(void) {
  return m_internal_buffers[m_current_read_buffer_id].data->size();
}

unsigned int
DummyGraphicsMacroModelBuffer::getBufferSize(unsigned int internal_buffer_id) {
  if (internal_buffer_id < m_number_of_internal_buffer) {
    return m_internal_buffers[internal_buffer_id].data->size();
  } else {
    return 0;
  }
}

unsigned char
DummyGraphicsMacroModelBuffer::getWriteBufferStatus(void) {
  return m_internal_buffers[m_current_write_buffer_id].data->getStatus();
}

unsigned char
DummyGraphicsMacroModelBuffer::getReadBufferStatus(void) {
  return m_internal_buffers[m_current_read_buffer_id].data->getStatus();
}

unsigned char
DummyGraphicsMacroModelBuffer::getBufferStatus(unsigned int internal_buffer_id) {
  if (internal_buffer_id < m_number_of_internal_buffer) {
    return m_internal_buffers[internal_buffer_id].data->getStatus();
  } else {
    return 0;
  }
}

void
DummyGraphicsMacroModelBuffer::waitWriteBufferStatus(unsigned char status) {
  if (status < DummyGraphicsMacroModelFifo::SizeOfStatus) {
#if 0
    std::cout << sc_time_stamp() << " status=" << (int)status << "m_internal_buffers[" << m_current_write_buffer_id << "].data->getStatus()" << (int)m_internal_buffers[m_current_write_buffer_id].data->getStatus() << std::endl;
#endif
    if (status != m_internal_buffers[m_current_write_buffer_id].data->getStatus()) {
      wait(m_e_set_write_buffer_status[status]);
    }
  }
}

void
DummyGraphicsMacroModelBuffer::waitReadBufferStatus(unsigned char status) {
  if (status < DummyGraphicsMacroModelFifo::SizeOfStatus) {
    if (status != m_internal_buffers[m_current_read_buffer_id].data->getStatus()) {
      wait(m_e_set_read_buffer_status[status]);
    }
  }
}

void
DummyGraphicsMacroModelBuffer::switchWriteBuffer(void) {
  m_internal_buffers[m_current_write_buffer_id].is_writable = false;
  m_internal_buffers[m_current_write_buffer_id].is_readable = true;

  m_internal_buffers[m_current_write_buffer_id].data->setStatus(DummyGraphicsMacroModelFifo::FULL);
  checkWriteBufferStatus();

  m_e_switch_write_buffer.notify();

  while (!isPossibleToSwitchWriteBuffer()) {
    wait(m_e_switch_read_buffer);
  }
  
  m_current_write_buffer_id = m_next_write_buffer_id;
  incrementNextWriteBufferId();
  checkWriteBufferStatus();
  checkReadBufferStatus();

  m_internal_buffers[m_current_write_buffer_id].is_writable = true;
  m_internal_buffers[m_current_write_buffer_id].is_readable = false;

#if 0
  std::cout << sc_time_stamp() << " m_current_write_buffer_id=" << m_current_write_buffer_id << std::endl;
#endif
}

void
DummyGraphicsMacroModelBuffer::switchReadBuffer(void) {
  m_internal_buffers[m_current_read_buffer_id].is_writable = true;
  m_internal_buffers[m_current_read_buffer_id].is_readable = false;

  m_e_switch_read_buffer.notify();

  while (!isPossibleToSwitchReadBuffer()) {
    wait(m_e_switch_write_buffer);
  }

  m_current_read_buffer_id = m_next_read_buffer_id;
  incrementNextReadBufferId();
  checkWriteBufferStatus();
  checkReadBufferStatus();

  m_internal_buffers[m_current_read_buffer_id].is_writable = false;
  m_internal_buffers[m_current_read_buffer_id].is_readable = true;
}

bool
DummyGraphicsMacroModelBuffer::isPossibleToSwitchWriteBuffer(void) {
  if ((m_internal_buffers[m_next_write_buffer_id].is_writable)
      && m_internal_buffers[m_next_write_buffer_id].data->empty()) {
    return true;
  }
  return false;
}

bool
DummyGraphicsMacroModelBuffer::isPossibleToSwitchReadBuffer(void) {
  if ((m_internal_buffers[m_next_read_buffer_id].is_readable)
      && (!m_internal_buffers[m_next_read_buffer_id].data->empty())){
    return true;
  }
  return false;
}

void
DummyGraphicsMacroModelBuffer::checkWriteBufferStatus(void) {
#if 0
  std::cout << __FUNCTION__ << " m_e_set_write_buffer_status[" << (int)m_internal_buffers[m_current_write_buffer_id].data->getStatus() << "].notify()" << std::endl;
#endif
  m_e_set_write_buffer_status[m_internal_buffers[m_current_write_buffer_id].data->getStatus()].notify();
}

void
DummyGraphicsMacroModelBuffer::checkReadBufferStatus(void) {
  m_e_set_read_buffer_status[m_internal_buffers[m_current_read_buffer_id].data->getStatus()].notify();
}

void
DummyGraphicsMacroModelBuffer::waitCurrentWriteBufferWriteEnable(void) {
  while (!m_internal_buffers[m_current_write_buffer_id].is_writable) {
    wait(m_e_switch_read_buffer);
  }
}

void
DummyGraphicsMacroModelBuffer::waitCurrentReadBufferReadEnable(void) {
  while (!m_internal_buffers[m_current_read_buffer_id].is_readable) {
    wait(m_e_switch_write_buffer);
  }
}

void
DummyGraphicsMacroModelBuffer::incrementNextWriteBufferId(void) {
  ++m_next_write_buffer_id;
  if (m_number_of_internal_buffer <= m_next_write_buffer_id) {
    m_next_write_buffer_id = 0;
  }
}

void
DummyGraphicsMacroModelBuffer::incrementNextReadBufferId(void) {
  ++m_next_read_buffer_id;
  if (m_number_of_internal_buffer <= m_next_read_buffer_id) {
    m_next_read_buffer_id = 0;
  }
}

unsigned int
DummyGraphicsMacroModelBuffer::getInternalWriteBufferId(void) {
  return m_current_write_buffer_id;
}

unsigned int
DummyGraphicsMacroModelBuffer::getInternalReadBufferId(void) {
  return m_current_read_buffer_id;
}

unsigned int
DummyGraphicsMacroModelBuffer::getNumberOfInternalBuffer(void) {
  return m_number_of_internal_buffer;
}

unsigned int
DummyGraphicsMacroModelBuffer::getWidth(void) {
  return m_width;
}

unsigned int
DummyGraphicsMacroModelBuffer::getDepth(void) {
  return m_depth;
}

unsigned int
DummyGraphicsMacroModelBuffer::getWriteClock(void) {
  return m_write_clock;
}

unsigned int
DummyGraphicsMacroModelBuffer::getReadClock(void) {
  return m_read_clock;
}

unsigned int
DummyGraphicsMacroModelBuffer::getWriteLatency(void) {
  return m_write_latency;
}

unsigned int
DummyGraphicsMacroModelBuffer::getReadLatency(void) {
  return m_read_latency;
}

sc_time_unit
DummyGraphicsMacroModelBuffer::getIimeUnit(void) {
  return m_time_unit;
}
