/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 */
/**
 * @file OutputSignalReceiver.h
 * @brief receive signal from kernel (header)
 */
#if !defined OUTPUT_SIGNAL_RECEIVER_H
#define OUTPUT_SIGNAL_RECEIVER_H

#include <systemc.h>

template<class DataType>
class OutputSignalReceiver: public sc_module {
public:
  SC_HAS_PROCESS(OutputSignalReceiver);
  
  /**
   * @brief Constructor
   **/
  OutputSignalReceiver(sc_module_name name, unsigned int number_of_signal, bool is_input);

  /**
   * @brief Destructor
   **/
  ~OutputSignalReceiver(void);

  void set(unsigned int signal_number, DataType value);
  DataType get(unsigned int signal_number);

private:
  void spawnThreads(void);
  void SignalThread(unsigned int signal_number);

public:
  sc_signal<DataType>* signals;

private:
  unsigned int m_number_of_signal;
  DataType *m_signal_values;
  bool m_is_input;
};
#endif /* OUTPUT_SIGNAL_RECEIVER_H */
