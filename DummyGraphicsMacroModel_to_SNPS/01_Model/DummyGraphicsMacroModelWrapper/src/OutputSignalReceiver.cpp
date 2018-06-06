/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file OutputSignalReceiver.cpp
 * @brief receive signal from kernel (source)
 */
#include "OutputSignalReceiver.h"
#include <iostream>

template <class DataType>
OutputSignalReceiver<DataType>::OutputSignalReceiver(sc_module_name name, unsigned int number_of_signal, bool is_input) :
  sc_module(name),
  signals(NULL),
  m_number_of_signal(number_of_signal),
  m_signal_values(NULL),
  m_is_input(is_input) {
  signals = new sc_signal<DataType>[m_number_of_signal];
  m_signal_values = new DataType[m_number_of_signal];

  for (unsigned int i = 0; i < m_number_of_signal; ++i) {
    m_signal_values[i] = 0;
  }
  
  SC_THREAD(spawnThreads);
}

template <class DataType>
OutputSignalReceiver<DataType>::~OutputSignalReceiver(void) {
  delete[] signals;
  delete[] m_signal_values;
}


template<class DataType>
void
OutputSignalReceiver<DataType>::spawnThreads(void) {
  for (unsigned int i = 0; i < m_number_of_signal; ++i) {
    sc_spawn_options option;
    std::string thread_name;
    std::stringstream tmp_thread_name;
    tmp_thread_name << "Thread" << i;
    tmp_thread_name >> thread_name;
    sc_spawn(sc_bind(&OutputSignalReceiver<DataType>::SignalThread, this, i), thread_name.c_str(), &option);
  }
}

template<class DataType>
void
OutputSignalReceiver<DataType>::SignalThread(unsigned int signal_number) {
  while (m_is_input == false) {
    wait(signals[signal_number].value_changed_event());
    m_signal_values[signal_number] = signals[signal_number];
  }
}

template <class DataType>
void
OutputSignalReceiver<DataType>::set(unsigned int signal_number, DataType value) {
  m_signal_values[signal_number] = value;
}

template <class DataType>
DataType
OutputSignalReceiver<DataType>::get(unsigned int signal_number) {
  return m_signal_values[signal_number];
}

template class OutputSignalReceiver<bool>;
template class OutputSignalReceiver<unsigned int>;
