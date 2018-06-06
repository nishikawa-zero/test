/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModel.cpp
 * @brief DummyGraphicsMacroModel (source)
 */
#include "DummyGraphicsMacroModel.h"

DummyGraphicsMacroModel::DummyGraphicsMacroModel(const sc_module_name name,
                                                           const unsigned int model_id,
                                                           const unsigned int axi_bus_width,
                                                           const unsigned int number_of_axi_if,
                                                           const unsigned int number_of_interrupt,
                                                           const unsigned int number_of_output_signal,
                                                           const unsigned int number_of_thread,
                                                           const unsigned int number_of_read_outstanding,
                                                           const unsigned int number_of_write_outstanding,
                                                           const bool no_r_receive,
                                                           const bool no_b_receive,
                                                           const sc_time_unit time_unit,
                                                           const unsigned int axi_clock,
                                                           const unsigned int core_clock,
                                                           const char *buffer_parameter_file_name,
                                                           const char *fifo_parameter_file_name,
                                                           const char *output_vcd_file_name,
                                                           const char *output_csv_file_name,
                                                           const char *output_summary_file_name):
  sc_module(name),
  AXI(NULL),
  interrupt(NULL),
  output(NULL),
  m_model_id(model_id),
  m_axi_bus_width(axi_bus_width),
  m_number_of_axi_if(number_of_axi_if),
  m_number_of_interrupt(number_of_interrupt),
  m_number_of_output_signal(number_of_output_signal),
  m_number_of_thread(number_of_thread),
  m_number_of_read_outstanding(number_of_read_outstanding),
  m_number_of_write_outstanding(number_of_write_outstanding),
  m_no_r_receive(no_r_receive),
  m_no_b_receive(no_b_receive),
  m_rready_validate(false),
  m_rready_value(false),
  m_time_unit(time_unit),
  m_axi_clock(axi_clock),
  m_core_clock(core_clock),
  m_thread_scenario(NULL),
  m_interrupt_scenario(NULL),
  m_number_of_buffer(0),
  m_buffers(NULL),
  m_number_of_fifo(0),
  m_fifos(NULL),
  m_base_time(sc_time(1,time_unit)),
  m_output(NULL),
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  m_data_out(NULL),
  m_busy_out(NULL),
#endif
  m_is_logging(false),
  m_vcd_maker(NULL),
  m_buffer_vcd_id_count(0),
  m_fifo_vcd_id_count(0),
  m_thread_vcd_id_count(0),
  m_buffer_size_vcd_category('B'),
  m_buffer_status_vcd_category('b'),
  m_fifo_size_vcd_category('F'),
  m_fifo_status_vcd_category('f'),
  m_thread_status_vcd_category('c'),
  m_user_vcd_category('u'),
  m_logging_enable_vcd_category('l') {

  if (buffer_parameter_file_name != NULL) {
    m_buffer_parameter_file_name = buffer_parameter_file_name;
  }
  if (fifo_parameter_file_name != NULL) {
    m_fifo_parameter_file_name = fifo_parameter_file_name;
  }
  if (output_vcd_file_name != NULL) {
    m_output_vcd_file_name = output_vcd_file_name;
  }
  if (output_csv_file_name != NULL) {
    m_output_csv_file_name = output_csv_file_name;
  }
  if (output_summary_file_name != NULL) {
    m_output_summary_file_name = output_summary_file_name;
  }

  AXI = new fj::TlmAxi3FiveChannelInterface_AXI_CX*[m_number_of_axi_if];
  for (unsigned int axi_if_id = 0; axi_if_id < m_number_of_axi_if; ++axi_if_id ) {
    std::string axi_if_name;
    std::stringstream tmp_axi_if_name;
    tmp_axi_if_name << "AXI" << axi_if_id;
    tmp_axi_if_name >> axi_if_name;
    AXI[axi_if_id] = new fj::TlmAxi3FiveChannelInterface_AXI_CX(axi_if_name.c_str(), 8, axi_bus_width, m_no_b_receive, m_no_r_receive, number_of_write_outstanding, number_of_read_outstanding);
  }

  interrupt = new sc_in<bool>[m_number_of_interrupt];
  output = new sc_out<bool>[m_number_of_output_signal]();
  m_output = new bool[m_number_of_output_signal]();

  for (unsigned int i = 0; i < m_number_of_output_signal; ++i) {
    m_output[i] = 0;
  }

#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  data_in  = new sc_in<unsigned int>[2];
  busy_in  = new sc_in<bool>[2];
  data_out = new sc_out<unsigned int> [2];
  busy_out = new sc_out<bool>[2];

  m_data_out = new unsigned int[2];
  m_busy_out = new bool[2];

  for (unsigned int i = 0; i < 2; ++i) {
    m_data_out[i] = 0;
    m_busy_out[i] = 0;
  }

  m_previous_data_in[0] = 0;
  m_previous_data_in[1] = 0;
#endif

  std::string module_name = this->name();
  std::string time_unit_string = "ns";
  if (m_time_unit == SC_FS)       time_unit_string = "fs";
  else if (m_time_unit == SC_PS)  time_unit_string = "ps";
  else if (m_time_unit == SC_NS)  time_unit_string = "ns";
  else if (m_time_unit == SC_US)  time_unit_string = "us";
  else if (m_time_unit == SC_MS)  time_unit_string = "ms";
  else if (m_time_unit == SC_SEC) time_unit_string = "s";

  m_vcd_maker = new VcdMaker(m_output_vcd_file_name.c_str(),
                             module_name.c_str(),
                             time_unit_string.c_str());
  m_vcd_maker->makeValue("logging_enable",
                         m_logging_enable_vcd_category,
                         0,
                         1,
                         0);

  m_status_list[0] = 0;

  SC_THREAD(spawnThreads);
  SC_METHOD(OutputSignalUpdate); sensitive << m_outputsignal_update_event;
}

DummyGraphicsMacroModel::~DummyGraphicsMacroModel(void) {
  delete[] interrupt;
  delete[] output;
  delete[] m_output;
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  delete[] data_in;
  delete[] busy_in; 
  delete[] data_out;
  delete[] busy_out;
  delete[] m_data_out;
  delete[] m_busy_out;
#endif

  for (unsigned int axi_if_id = 0; axi_if_id < m_number_of_axi_if; ++axi_if_id ) {
    delete AXI[axi_if_id];
  }
  delete[] AXI;
  
  delete m_vcd_maker;
}

int
DummyGraphicsMacroModel::registerThreadScenario(void (* scenario)(unsigned int, unsigned int)) {
  int result = 0;

  if (scenario && (m_thread_scenario == NULL)) {
    m_thread_scenario = scenario;
  } else {
    result = -1;
  }

  return result;
}

int
DummyGraphicsMacroModel::registerInterruptScenario(void (* scenario)(unsigned int, unsigned int)) {
  int result = 0;

  if (scenario && (m_interrupt_scenario == NULL)) {
    m_interrupt_scenario = scenario;
  } else {
    result = -1;
  }

  return result;
}

int
DummyGraphicsMacroModel::setNumberOfBuffer(const unsigned int number_of_buffer) {
  int result = -1;

  return result;
}

int
DummyGraphicsMacroModel::setNumberOfInternalBuffer(const unsigned int buffer_id,
                                                             const unsigned int number_of_internal_buffer) {
  int result = -1;
  
  return result;
}


void
DummyGraphicsMacroModel::spawnThreads(void) {
  for (unsigned int interrupt_id = 0; interrupt_id < m_number_of_interrupt; ++interrupt_id ) {
    sc_spawn_options option;
    std::string interrupt_thread_name;
    std::stringstream tmp_interrupt_thread_name;
    tmp_interrupt_thread_name << "Interrupt" << interrupt_id;
    tmp_interrupt_thread_name >> interrupt_thread_name;
    sc_spawn(sc_bind(&DummyGraphicsMacroModel::Interrupt, this, interrupt_id), interrupt_thread_name.c_str(), &option);
  }

  for (unsigned int thread_id = 0; thread_id < m_number_of_thread; ++thread_id ) {
    sc_spawn_options option;
    std::string thread_name;
    std::stringstream tmp_thread_name;
    tmp_thread_name << "Thread" << thread_id;
    tmp_thread_name >> thread_name;
    sc_spawn(sc_bind(&DummyGraphicsMacroModel::Thread, this, thread_id), thread_name.c_str(), &option);

    LoggingParameters *tmp_parameters = new LoggingParameters;

    tmp_parameters->vcd_id = m_thread_vcd_id_count;
    m_thread_status.push_back(0);
    m_thread_logging_parameters.push_back(tmp_parameters);

    std::string signal_name;
    std::stringstream ss;
    ss << "thread_" << thread_id << "_status";
    ss >> signal_name;
    m_vcd_maker->makeValue(signal_name.c_str(),
                           m_thread_status_vcd_category,
                           tmp_parameters->vcd_id,
                           8,
                           0);
    
    ++m_thread_vcd_id_count;
  }
}

void
DummyGraphicsMacroModel::OutputSignalUpdate(void) {
  for(unsigned int i = 0; i < m_number_of_output_signal; i++) {
    output[i] = m_output[i];
  }
#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
  for(unsigned int i = 0; i < 2; i++) {
    data_out[i] = m_data_out[i];
    busy_out[i] = m_busy_out[i];
  }
#endif
}


void
DummyGraphicsMacroModel::Thread(const unsigned int thread_id) {
  if (m_thread_scenario) {
    m_thread_scenario(m_model_id, thread_id);
  }
}

void
DummyGraphicsMacroModel::Interrupt(const unsigned int interrupt_id) {
  if (m_interrupt_scenario) {
    while(1) {
      wait(interrupt[interrupt_id].value_changed_event());
      m_interrupt_scenario(m_model_id, interrupt_id);
    }
  }
}


void
DummyGraphicsMacroModel::checkAxiIfId(const unsigned int axi_if_id) {
  if (m_number_of_axi_if <= axi_if_id) {
    std::cout << "[ERROR] " << this->name() << " does not have axi_if_id:" << axi_if_id << std::endl; 
    assert(0);
  }
}

void
DummyGraphicsMacroModel::checkInterruptId(const unsigned int interrupt_id) {
  if (m_number_of_interrupt <= interrupt_id) {
    std::cout << "[ERROR] " << this->name() << " does not have interrupt_id:" << interrupt_id << std::endl; 
    assert(0);
  }
}

void
DummyGraphicsMacroModel::checkOutputSignalId(const unsigned int output_signal_id) {
  if (m_number_of_output_signal <= output_signal_id) {
    std::cout << "[ERROR] " << this->name() << " does not have output_signal_id:" << output_signal_id << std::endl; 
    assert(0);
  }
}

void
DummyGraphicsMacroModel::checkBufferId(const unsigned int buffer_id) {
  if (m_number_of_buffer <= buffer_id) {
    std::cout << "[ERROR] " << this->name() << " does not have buffer_id:" << buffer_id << std::endl; 
    assert(0);
  }
}

void
DummyGraphicsMacroModel::checkInternalBufferId(const unsigned int buffer_id,
                                                         const unsigned int internal_buffer_id) {
  checkBufferId(buffer_id);
  if (m_buffers.at(buffer_id)->getNumberOfInternalBuffer() <= internal_buffer_id) {
    std::cout << "[ERROR] " << this->name() << " does not have buffer_id:" << buffer_id << ", internal_buffer_id:" << internal_buffer_id << std::endl; 
    assert(0);
  }
}

void
DummyGraphicsMacroModel::checkFifoId(const unsigned int fifo_id) {
  if (m_number_of_fifo <= fifo_id) {
    std::cout << "[ERROR] " << this->name() << " does not have fifo_id:" << fifo_id << std::endl; 
    assert(0);
  }
}

void
DummyGraphicsMacroModel::checkThreadId(const unsigned int thread_id) {
  if (m_number_of_thread <= thread_id) {
    std::cout << "[ERROR] " << this->name() << " does not have thread_id:" << thread_id << std::endl; 
    assert(0);
  }
}

#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
void
DummyGraphicsMacroModel::checkCoopSignalId(unsigned int coop_signal_id) {
  if (2 <= coop_signal_id) {
    std::cout << "[ERROR] " << this->name() << " does not have coop_signal_id:" << coop_signal_id << std::endl; 
    assert(0);
  }
}
#endif

void
DummyGraphicsMacroModel::readBufferParameterFile(void) {
  if (!m_buffer_parameter_file_name.empty()) {
    CsvParser csv;
    unsigned int buffer_id = 0;
    
    csv.initialize(m_buffer_parameter_file_name.c_str());
    
#if 0
    for (unsigned int row = 0; row < csv.getRowSize(); ++row) {
      for (unsigned int column = 0; column < csv.getColumnSize(row); ++column) {
        if (column != 0) {
          std::cout << ",";
        }
        std::cout << csv.getString(row, column);
      }
      std::cout << std::endl;
    }
#endif
    
    for (unsigned int row = 0; row < csv.getRowSize(); ++row) {
      if (SizeOfBufferParameterFileFormat <= csv.getColumnSize(row)) {
#if 0
        std::cout << "NUMBER_OF_INTERNAL_BUFFER=" << csv.getUint32(row, NUMBER_OF_INTERNAL_BUFFER) << std::endl;
        std::cout << "BUFFER_WIDTH=" << csv.getUint32(row, BUFFER_WIDTH) << std::endl;
        std::cout << "BUFFER_DEPTH=" << csv.getUint32(row, BUFFER_DEPTH) << std::endl;
        std::cout << "BUFFER_WRITE_CLOCK=" << csv.getUint32(row, BUFFER_WRITE_CLOCK) << std::endl;
        std::cout << "BUFFER_READ_CLOCK=" << csv.getUint32(row, BUFFER_READ_CLOCK) << std::endl;
        std::cout << "BUFFER_WRITE_LATENCY=" << csv.getUint32(row, BUFFER_WRITE_LATENCY) << std::endl;
        std::cout << "BUFFER_READ_LATENCY=" << csv.getUint32(row, BUFFER_READ_LATENCY) << std::endl;
        
#endif
        DummyGraphicsMacroModelBuffer* tmp_buffer = new DummyGraphicsMacroModelBuffer(csv.getUint32(row, NUMBER_OF_INTERNAL_BUFFER),
                                                                                      csv.getUint32(row, BUFFER_WIDTH),
                                                                                      csv.getUint32(row, BUFFER_DEPTH),
                                                                                      csv.getUint32(row, BUFFER_WRITE_CLOCK),
                                                                                      csv.getUint32(row, BUFFER_READ_CLOCK),
                                                                                      csv.getUint32(row, BUFFER_WRITE_LATENCY),
                                                                                      csv.getUint32(row, BUFFER_READ_LATENCY),
                                                                                      m_time_unit);
        
        std::vector<LoggingParameters*> tmp_vector;
        m_buffer_logging_parameters.push_back(tmp_vector);
        
        for (unsigned int internal_buffer_id = 0; internal_buffer_id < tmp_buffer->getNumberOfInternalBuffer(); ++internal_buffer_id) {
          LoggingParameters *tmp_parameters = new LoggingParameters;
          
          if (m_vcd_maker != NULL) {
            unsigned int signal_width = 0;
            unsigned int signal_max_value = tmp_buffer->getWidth() * tmp_buffer->getDepth();
            std::string signal_name;
            std::stringstream ss;
            
            tmp_parameters->vcd_id = m_buffer_vcd_id_count;
            ++m_buffer_vcd_id_count;
            
            while (0 < signal_max_value) {
              ++signal_width;
              signal_max_value >>= 1;
            }
            
            ss << "buffer_" << buffer_id << "_" << internal_buffer_id << "_size";
            ss >> signal_name;
            m_vcd_maker->makeValue(signal_name.c_str(),
                                   m_buffer_size_vcd_category,
                                   tmp_parameters->vcd_id,
                                   signal_width,
                                   0);
            ss.clear();
            ss << "buffer_" << buffer_id << "_" << internal_buffer_id << "_status";
            ss >> signal_name;
            m_vcd_maker->makeValue(signal_name.c_str(),
                                   m_buffer_status_vcd_category,
                                   tmp_parameters->vcd_id,
                                   8,
                                   0);
          }
          m_buffer_logging_parameters.back().push_back(tmp_parameters);
        }
        m_buffers.push_back(tmp_buffer);
      }
      ++buffer_id;
    }
    m_number_of_buffer = m_buffers.size();
  }
}

void
DummyGraphicsMacroModel::readFifoParameterFile(void) {
  if (!m_fifo_parameter_file_name.empty()) {
    CsvParser csv;
    unsigned int fifo_id = 0;
    
    csv.initialize(m_fifo_parameter_file_name.c_str());

#if 0
    for (unsigned int row = 0; row < csv.getRowSize(); ++row) {
      for (unsigned int column = 0; column < csv.getColumnSize(row); ++column) {
        if (column != 0) {
          std::cout << ",";
        }
        std::cout << csv.getString(row, column);
      }
      std::cout << std::endl;
    }
#endif

    for (unsigned int row = 0; row < csv.getRowSize(); ++row) {
      if (SizeOfFifoParameterFileFormat <= csv.getColumnSize(row)) {
        DummyGraphicsMacroModelFifo* tmp_fifo = new DummyGraphicsMacroModelFifo(csv.getUint32(row, FIFO_WIDTH),
                                                                                csv.getUint32(row, FIFO_DEPTH),
                                                                                csv.getUint32(row, FIFO_WRITE_CLOCK),
                                                                                csv.getUint32(row, FIFO_READ_CLOCK),
                                                                                csv.getUint32(row, FIFO_WRITE_LATENCY),
                                                                                csv.getUint32(row, FIFO_READ_LATENCY),
                                                                                m_time_unit);
      
        {
          LoggingParameters *tmp_parameters = new LoggingParameters;
        
          if (m_vcd_maker != NULL) {
            unsigned int signal_width = 0;
            unsigned int signal_max_value = tmp_fifo->getWidth() * tmp_fifo->getDepth();
            std::string signal_name;
            std::stringstream ss;

            tmp_parameters->vcd_id = m_fifo_vcd_id_count;
            ++m_fifo_vcd_id_count;

            while (0 < signal_max_value) {
              ++signal_width;
              signal_max_value >>= 1;
            }

            ss << "fifo_" << fifo_id << "_size";
            ss >> signal_name;
            m_vcd_maker->makeValue(signal_name.c_str(),
                                   m_fifo_size_vcd_category,
                                   tmp_parameters->vcd_id,
                                   signal_width,
                                   0);
            ss.clear();
            ss << "fifo_" << fifo_id << "_status";
            ss >> signal_name;
            m_vcd_maker->makeValue(signal_name.c_str(),
                                   m_fifo_status_vcd_category,
                                   tmp_parameters->vcd_id,
                                   8,
                                   0);
          }
          m_fifo_logging_parameters.push_back(tmp_parameters);
        }
        m_fifos.push_back(tmp_fifo);
      }
      ++fifo_id;
    }
    m_number_of_fifo = m_fifos.size();
  }
}

void
DummyGraphicsMacroModel::openCsvFile(void) {
  if (!m_output_csv_file_name.empty()) {
    m_ofs_csv.open(m_output_csv_file_name.c_str());
    
    if (!m_ofs_csv) {
      std::cout << "[ERROR] can not open " << m_output_csv_file_name << std::endl;
      assert(0);
    }
    
    m_ofs_csv << "time";
    for (unsigned int thread_id = 0; thread_id < m_number_of_thread; ++thread_id) {
      m_ofs_csv << ",thread_" << thread_id << "_status";  
    }
    for (unsigned int buffer_id = 0; buffer_id < m_number_of_buffer; ++buffer_id) {
      for (unsigned int internal_buffer_id = 0; internal_buffer_id < m_buffers.at(buffer_id)->getNumberOfInternalBuffer(); ++internal_buffer_id) {
        m_ofs_csv << ",buf_"<< buffer_id << "_" << internal_buffer_id << "_size"
                  << ",buf_"<< buffer_id << "_" << internal_buffer_id << "_status";
      }
    }
    for (unsigned int fifo_id = 0; fifo_id < m_number_of_fifo; ++fifo_id) {
      m_ofs_csv << ",fifo_"<< fifo_id << "_size"
                << ",fifo_"<< fifo_id << "_status";
    }
    m_ofs_csv << std::endl;
  }
}

void
DummyGraphicsMacroModel::dumpCsv(void) {
  if (!m_output_csv_file_name.empty()) {
    if (m_pre_dump_csv_time != sc_time_stamp()) {
      flushCsv();
    } else {
      m_tmp_csv_log.str("");
      m_tmp_csv_log.clear();
    }
    
    m_pre_dump_csv_time = sc_time_stamp();
    m_tmp_csv_log << sc_time_stamp().to_default_time_units();
    for (unsigned int thread_id = 0; thread_id < m_number_of_thread; ++thread_id) {
      unsigned int status = m_thread_status.at(thread_id);
      
      m_tmp_csv_log << "," << status;
    }
    
    for (unsigned int buffer_id = 0; buffer_id < m_number_of_buffer; ++buffer_id) {
      for (unsigned int internal_buffer_id = 0; internal_buffer_id < m_buffers.at(buffer_id)->getNumberOfInternalBuffer(); ++internal_buffer_id) {
        m_tmp_csv_log << "," << m_buffers.at(buffer_id)->getBufferSize(internal_buffer_id)
                      << "," << static_cast<unsigned int>(m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id));
      }
    }    

    for (unsigned int fifo_id = 0; fifo_id < m_number_of_fifo; ++fifo_id) {
      m_tmp_csv_log << "," << m_fifos.at(fifo_id)->size()
                    << "," << static_cast<unsigned int>(m_fifos.at(fifo_id)->getStatus());
    }    
    
    m_tmp_csv_log << std::endl;
  }
}

void
DummyGraphicsMacroModel::flushCsv(void) {
  if (!m_output_csv_file_name.empty()) {
    m_ofs_csv << m_tmp_csv_log.str();
    m_tmp_csv_log.str("");
    m_tmp_csv_log.clear();
  }
}

void
DummyGraphicsMacroModel::openSummaryFile(void) {
  if (!m_output_summary_file_name.empty()) {
    m_ofs_summary.open(m_output_summary_file_name.c_str());
    
    if (!m_ofs_summary) {
      std::cout << "[ERROR] can not open " << m_output_summary_file_name << std::endl;
      assert(0);
    }
    
    m_ofs_summary << "status";

    for (unsigned int thread_id = 0; thread_id < m_number_of_thread; ++thread_id) {
      m_ofs_summary << ",thread_" << thread_id;
    }
    for (unsigned int buffer_id = 0; buffer_id < m_number_of_buffer; ++buffer_id) {
      for (unsigned int internal_buffer_id = 0; internal_buffer_id < m_buffers.at(buffer_id)->getNumberOfInternalBuffer(); ++internal_buffer_id) {
        m_ofs_summary << ",buf_"<< buffer_id << "_" << internal_buffer_id;
      }
    }
    for (unsigned int fifo_id = 0; fifo_id < m_number_of_fifo; ++fifo_id) {
      m_ofs_summary << ",fifo_"<< fifo_id;
    }
    m_ofs_summary << std::endl;
  }
}

void
DummyGraphicsMacroModel::dumpSummary(void) {
  if (!m_output_summary_file_name.empty()) {
    std::map<unsigned char, unsigned char>::iterator status_list_itr = m_status_list.begin();

    while (status_list_itr != m_status_list.end()) {
      unsigned char status = status_list_itr->first;  
      StatusTimerMapItr itr;
      m_ofs_summary << static_cast<unsigned int>(status);
      
      for (unsigned int thread_id = 0; thread_id < m_number_of_thread; ++thread_id) {
        m_ofs_summary << ",";
        itr = m_thread_logging_parameters.at(thread_id)->status_timer_map.find(status);
        if (itr == m_thread_logging_parameters.at(thread_id)->status_timer_map.end()) {
          m_ofs_summary << "-(0%)";
        } else {
          m_ofs_summary << (itr->second / m_base_time) << "(" << ((itr->second / m_total_logging_time) * 100)  << "%)";
        }
      }    
      
      for (unsigned int buffer_id = 0; buffer_id < m_number_of_buffer; ++buffer_id) {
        for (unsigned int internal_buffer_id = 0; internal_buffer_id < m_buffers.at(buffer_id)->getNumberOfInternalBuffer(); ++internal_buffer_id) {
          m_ofs_summary << ",";
          itr = m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->status_timer_map.find(status);
          if (itr == m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->status_timer_map.end()) {
            m_ofs_summary << "-(0%)";
          } else {
            m_ofs_summary << (itr->second / m_base_time) << "(" << ((itr->second / m_total_logging_time) * 100)  << "%)";
          }
        }
      }
      
      for (unsigned int fifo_id = 0; fifo_id < m_number_of_fifo; ++fifo_id) {
        m_ofs_summary << ",";
        itr = m_fifo_logging_parameters.at(fifo_id)->status_timer_map.find(status);
        if (itr == m_fifo_logging_parameters.at(fifo_id)->status_timer_map.end()) {
          m_ofs_summary << "-(0%)";
        } else {
          m_ofs_summary << (itr->second / m_base_time) << "(" << ((itr->second / m_total_logging_time) * 100)  << "%)";
        }
      }

      m_ofs_summary << std::endl;
     
      ++status_list_itr;
    }
  }
}

void
DummyGraphicsMacroModel::end_of_elaboration(void) {
  setDummyGraphicsMacroModelBasePointer(m_model_id, this);
  readBufferParameterFile();
  readFifoParameterFile();
  openCsvFile();
  openSummaryFile();
}

void
DummyGraphicsMacroModel::end_of_simulation(void) {
  flushCsv();
  dumpSummary();
  m_vcd_maker->finish(sc_time_stamp()/m_base_time);
}

int
DummyGraphicsMacroModel::sendAw(const unsigned int axi_if_id,
                                          const unsigned int AWID,
                                          const unsigned int AWADDR,
                                          const unsigned int AWLEN,
                                          const unsigned int AWSIZE,
                                          const unsigned int AWBURST,
                                          const unsigned int AWLOCK,
                                          const unsigned int AWCACHE,
                                          const unsigned int AWPROT,
                                          const unsigned int AWUSER) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->sendAw(AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
}

int
DummyGraphicsMacroModel::sendAwWithNoWait(const unsigned int axi_if_id,
                                                    const unsigned int AWID,
                                                    const unsigned int AWADDR,
                                                    const unsigned int AWLEN,
                                                    const unsigned int AWSIZE,
                                                    const unsigned int AWBURST,
                                                    const unsigned int AWLOCK,
                                                    const unsigned int AWCACHE,
                                                    const unsigned int AWPROT,
                                                    const unsigned int AWUSER) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->sendAwWithNoWait(AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
}

int
DummyGraphicsMacroModel::sendW(const unsigned int axi_if_id,
                                         const unsigned int WID,
                                         const unsigned int WLAST,
                                         const unsigned char* wdata,
                                         const unsigned char* wstrb) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->sendW(WID, WLAST, wdata, wstrb);
}

int
DummyGraphicsMacroModel::sendWWithNoWait(const unsigned int axi_if_id,
                                                   const unsigned int WID,
                                                   const unsigned int WLAST,
                                                   const unsigned char* wdata,
                                                   const unsigned char* wstrb) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->sendWWithNoWait(WID, WLAST, wdata, wstrb);
}

int
DummyGraphicsMacroModel::receiveB(const unsigned int axi_if_id,
                                            unsigned int *BID,
                                            unsigned int *BRESP) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveB(BID, BRESP);
}

int
DummyGraphicsMacroModel::receiveBWithNoWait(const unsigned int axi_if_id,
                                                      unsigned int *BID,
                                                      unsigned int *BRESP) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveBWithNoWait(BID, BRESP);
}

int
DummyGraphicsMacroModel::receiveBById(const unsigned int axi_if_id,
                                                const unsigned int BID,
                                                unsigned int *BRESP) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveBById(BID, BRESP);
}

int
DummyGraphicsMacroModel::receiveBByIdWithNoWait(const unsigned int axi_if_id,
                                                          const unsigned int BID,
                                                          unsigned int *BRESP) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveBByIdWithNoWait(BID, BRESP);
}

int
DummyGraphicsMacroModel::sendAr(const unsigned int axi_if_id,
                                          const unsigned int ARID,
                                          const unsigned int ARADDR,
                                          const unsigned int ARLEN,
                                          const unsigned int ARSIZE,
                                          const unsigned int ARBURST,
                                          const unsigned int ARLOCK,
                                          const unsigned int ARCACHE,
                                          const unsigned int ARPROT,
                                          const unsigned int ARUSER) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->sendAr(ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
}

int
DummyGraphicsMacroModel::sendArWithNoWait(const unsigned int axi_if_id,
                                                    const unsigned int ARID,
                                                    const unsigned int ARADDR,
                                                    const unsigned int ARLEN,
                                                    const unsigned int ARSIZE,
                                                    const unsigned int ARBURST,
                                                    const unsigned int ARLOCK,
                                                    const unsigned int ARCACHE,
                                                    const unsigned int ARPROT,
                                                    const unsigned int ARUSER) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->sendArWithNoWait(ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);
}

int
DummyGraphicsMacroModel::receiveR(const unsigned int axi_if_id,
                                            unsigned int *RID,
                                            unsigned int *RLAST,
                                            unsigned int *RRESP,
                                            unsigned char *rdata) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveR(RID, RLAST, RRESP, rdata);
}

int
DummyGraphicsMacroModel::receiveRWithNoWait(const unsigned int axi_if_id,
                                                      unsigned int *RID,
                                                      unsigned int *RLAST,
                                                      unsigned int *RRESP,
                                                      unsigned char *rdata) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveRWithNoWait(RID, RLAST, RRESP, rdata);
}

int
DummyGraphicsMacroModel::receiveRById(const unsigned int axi_if_id,
                                                const unsigned int RID,
                                                unsigned int *RLAST,
                                                unsigned int *RRESP,
                                                unsigned char *rdata) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveRById(RID, RLAST, RRESP, rdata);
}

int
DummyGraphicsMacroModel::receiveRByIdWithNoWait(const unsigned int axi_if_id,
                                                          const unsigned int RID,
                                                          unsigned int *RLAST,
                                                          unsigned int *RRESP,
                                                          unsigned char *rdata) {
  checkAxiIfId(axi_if_id);
  return AXI[axi_if_id]->receiveRByIdWithNoWait(RID, RLAST, RRESP, rdata);
}

void
DummyGraphicsMacroModel::waitAxiCycle(const unsigned int cycle) {
  wait(m_axi_clock * cycle, m_time_unit);
}

void
DummyGraphicsMacroModel::waitCoreCycle(const unsigned int cycle) {
  wait(m_core_clock * cycle, m_time_unit);
}

void
DummyGraphicsMacroModel::setOutputSignal(const unsigned int output_signal_id,
                                                   bool value) {
  checkOutputSignalId(output_signal_id);
  //output[output_signal_id] = value;
  m_output[output_signal_id] = value;
  m_outputsignal_update_event.notify();
}

bool
DummyGraphicsMacroModel::getOutputSignal(const unsigned int output_signal_id) {
  checkOutputSignalId(output_signal_id);
  return output[output_signal_id];
}

bool
DummyGraphicsMacroModel::getInterruptSignal(const unsigned int interrupt_id) {
  checkInterruptId(interrupt_id);
  return interrupt[interrupt_id];
}

void
DummyGraphicsMacroModel::setRreadyValue(const bool value) {
  m_rready_value    = value;
  m_rready_validate = true;
}

void
DummyGraphicsMacroModel::releaseRreadyControl(void) {
  m_rready_validate = false;
}

bool
DummyGraphicsMacroModel::getRreadyValue(void) {
  return m_rready_value;
}

bool
DummyGraphicsMacroModel::isValidateRreadyControl(void) {
  return m_rready_validate;
}

void
DummyGraphicsMacroModel::waitEvent(const unsigned int event_id) {
  std::map<unsigned int, sc_event>::iterator itr = m_event_map.find(event_id);

  if (itr == m_event_map.end()) {
    sc_event tmp_event;
    m_event_map.insert(std::make_pair(event_id, tmp_event));
    itr = m_event_map.find(event_id);
  }
  wait(itr->second);
}

void
DummyGraphicsMacroModel::notifyEvent(const unsigned int event_id) {
  std::map<unsigned int, sc_event>::iterator itr = m_event_map.find(event_id);

  if (itr != m_event_map.end()) {
    itr->second.notify();
  }

}

void
DummyGraphicsMacroModel::setThreadStatus(const unsigned int thread_id,
                                                   const unsigned int status) {
  unsigned int pre_status = m_thread_status.at(thread_id);

  checkThreadId(thread_id);
  m_thread_status.at(thread_id) = status;

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_thread_status_vcd_category,
                            m_thread_logging_parameters.at(thread_id)->vcd_id,
                            status);
    }
    m_thread_logging_parameters.at(thread_id)->status_timer_map[pre_status] += sc_time_stamp() - m_thread_logging_parameters.at(thread_id)->status_start_time;
    m_thread_logging_parameters.at(thread_id)->status_start_time = sc_time_stamp();
    m_status_list[status] = status;
    dumpCsv();
  }
}

unsigned int
DummyGraphicsMacroModel::getThreadStatus(const unsigned int thread_id) {
  checkThreadId(thread_id);
  return m_thread_status.at(thread_id);
}


void
DummyGraphicsMacroModel::enableLogging(void) {
  m_is_logging = true;
  m_logging_start_time = sc_time_stamp();

  for (unsigned int thread_id = 0; thread_id < m_number_of_thread; ++thread_id) {
    m_thread_logging_parameters.at(thread_id)->status_start_time = sc_time_stamp();
  }
  
  for (unsigned int buffer_id = 0; buffer_id < m_number_of_buffer; ++buffer_id) {
    for (unsigned int internal_buffer_id = 0; internal_buffer_id < m_buffers.at(buffer_id)->getNumberOfInternalBuffer(); ++internal_buffer_id) {
      m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->status_start_time = sc_time_stamp();
      if (m_vcd_maker != NULL) {
        m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                              m_buffer_status_vcd_category,
                              m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                              m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id));
        m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                              m_buffer_size_vcd_category,
                              m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                              m_buffers.at(buffer_id)->getBufferSize(internal_buffer_id));
      }
    }
  }
  
  if (m_vcd_maker != NULL) {
    m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                          m_logging_enable_vcd_category,
                          0,
                          1);
  }
}

void
DummyGraphicsMacroModel::disableLogging(void) {
  m_is_logging = false;
  m_total_logging_time += sc_time_stamp() - m_logging_start_time;

  for (unsigned int thread_id = 0; thread_id < m_number_of_thread; ++thread_id) {
    m_thread_logging_parameters.at(thread_id)->status_timer_map[getThreadStatus(thread_id)] += sc_time_stamp() - m_thread_logging_parameters.at(thread_id)->status_start_time;
  }
  
  for (unsigned int buffer_id = 0; buffer_id < m_number_of_buffer; ++buffer_id) {
    for (unsigned int internal_buffer_id = 0; internal_buffer_id < m_buffers.at(buffer_id)->getNumberOfInternalBuffer(); ++internal_buffer_id) {
      m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->status_timer_map[m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id)] += sc_time_stamp()
        - m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->status_start_time;
      m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->status_start_time = sc_time_stamp();
    }
  }  

  if (m_vcd_maker != NULL) {
    m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                          m_logging_enable_vcd_category,
                          0,
                          0);
  }
}

int
DummyGraphicsMacroModel::writeBuffer(const unsigned int buffer_id,
                                               const unsigned char *data) {
  int result;

  checkBufferId(buffer_id);
  result = m_buffers.at(buffer_id)->write(data, true);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      unsigned int internal_buffer_id = m_buffers.at(buffer_id)->getInternalWriteBufferId();
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_size_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferSize(internal_buffer_id));
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_status_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id));
    }
    dumpCsv();
  }

  return result;
}

int
DummyGraphicsMacroModel::writeBufferWithNoWait(const unsigned int buffer_id,
                                                         const unsigned char *data) {
  int result;

  checkBufferId(buffer_id);
  result = m_buffers.at(buffer_id)->write(data, false);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      unsigned int internal_buffer_id = m_buffers.at(buffer_id)->getInternalWriteBufferId();
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_size_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferSize(internal_buffer_id));
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_status_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id));
    }
    dumpCsv();
  }

  return result;
}

int
DummyGraphicsMacroModel::readBuffer(const unsigned int buffer_id,
                                              unsigned char *data) {
  int result;

  checkBufferId(buffer_id);
  result = m_buffers.at(buffer_id)->read(data, true);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      unsigned int internal_buffer_id = m_buffers.at(buffer_id)->getInternalReadBufferId();
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_size_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferSize(internal_buffer_id));
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_status_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id));
    }
    dumpCsv();
  }

  return result;
}

int
DummyGraphicsMacroModel::readBufferWithNoWait(const unsigned int buffer_id,
                                                        unsigned char *data) {
  int result;

  checkBufferId(buffer_id);
  result = m_buffers.at(buffer_id)->read(data, false);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      unsigned int internal_buffer_id = m_buffers.at(buffer_id)->getInternalReadBufferId();
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_size_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferSize(internal_buffer_id));
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_status_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id));
    }
    dumpCsv();
  }

  return result;
}

unsigned int
DummyGraphicsMacroModel::getWriteBufferSize(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getWriteBufferSize();
}

unsigned int
DummyGraphicsMacroModel::getReadBufferSize(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getReadBufferSize();
}

void
DummyGraphicsMacroModel::waitWriteBufferStatus(const unsigned int buffer_id,
                                                         const unsigned char status) {

  checkBufferId(buffer_id);
  m_buffers.at(buffer_id)->waitWriteBufferStatus(status);
}

void
DummyGraphicsMacroModel::waitReadBufferStatus(const unsigned int buffer_id,
                                                        const unsigned char status) {
  checkBufferId(buffer_id);
  m_buffers.at(buffer_id)->waitReadBufferStatus(status);
}

void
DummyGraphicsMacroModel::switchWriteBuffer(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  m_buffers.at(buffer_id)->switchWriteBuffer();
  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      unsigned int internal_buffer_id = m_buffers.at(buffer_id)->getInternalReadBufferId();
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_size_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferSize(internal_buffer_id));
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_buffer_status_vcd_category,
                            m_buffer_logging_parameters.at(buffer_id).at(internal_buffer_id)->vcd_id,
                            m_buffers.at(buffer_id)->getBufferStatus(internal_buffer_id));
    }
    dumpCsv();
  }
}

void
DummyGraphicsMacroModel::switchReadBuffer(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  m_buffers.at(buffer_id)->switchReadBuffer();
}

bool
DummyGraphicsMacroModel::isPossibleToSwitchWriteBuffer(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->isPossibleToSwitchWriteBuffer();
}

bool
DummyGraphicsMacroModel::isPossibleToSwitchReadBuffer(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->isPossibleToSwitchReadBuffer();
}

int
DummyGraphicsMacroModel::writeFifo(const unsigned int fifo_id,
                                             const unsigned char *data) {
  int result;

  checkFifoId(fifo_id);
  result = m_fifos.at(fifo_id)->write(data, true);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_size_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->size());
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_status_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->getStatus());
    }
    dumpCsv();
  }

  return result;
}

int
DummyGraphicsMacroModel::writeFifoWithNoWait(const unsigned int fifo_id,
                                                       const unsigned char *data) {
  int result;

  checkFifoId(fifo_id);
  result = m_fifos.at(fifo_id)->write(data, false);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_size_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->size());
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_status_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->getStatus());
    }
    dumpCsv();
  }

  return result;
}

int
DummyGraphicsMacroModel::readFifo(const unsigned int fifo_id,
                                            unsigned char *data) {
  int result;

  checkFifoId(fifo_id);
  result = m_fifos.at(fifo_id)->read(data, true);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_size_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->size());
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_status_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->getStatus());
    }
    dumpCsv();
  }

  return result;
}

int
DummyGraphicsMacroModel::readFifoWithNoWait(const unsigned int fifo_id,
                                                      unsigned char *data) {
  int result;

  checkFifoId(fifo_id);
  result = m_fifos.at(fifo_id)->read(data, false);

  if (m_is_logging) {
    if (m_vcd_maker != NULL) {
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_size_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->size());
      m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                            m_fifo_status_vcd_category,
                            m_fifo_logging_parameters.at(fifo_id)->vcd_id,
                            m_fifos.at(fifo_id)->getStatus());
    }
    dumpCsv();
  }

  return result;
}

unsigned int
DummyGraphicsMacroModel::getFifoSize(const unsigned int fifo_id) {
  checkFifoId(fifo_id);
  return m_fifos.at(fifo_id)->size();
}

void
DummyGraphicsMacroModel::waitFifoStatus(const unsigned int fifo_id,
                                                  const unsigned char status) {
  checkFifoId(fifo_id);
  m_fifos.at(fifo_id)->waitStatus(status);
}

int
DummyGraphicsMacroModel::makeVcdValue(const char *name,
                                                const unsigned int vcd_id,
                                                const unsigned int width,
                                                const unsigned long long initial_value) {
  int result = -1;

  if (m_vcd_maker != NULL) {
    result = m_vcd_maker->makeValue(name,
                                    m_user_vcd_category,
                                    vcd_id,
                                    width,
                                    initial_value);
  }
  
  return result;
}

int
DummyGraphicsMacroModel::setVcdValue(const unsigned int vcd_id,
                                               const unsigned long long value) {
  int result = -1;

  if (m_vcd_maker != NULL) {
    result = m_vcd_maker->setValue(sc_time_stamp()/m_base_time,
                                   m_user_vcd_category,
                                   vcd_id,
                                   value);
  }

  return result;
}

void
DummyGraphicsMacroModel::dumpSimulationTime(void) {
  std::cout << sc_time_stamp() << " " << std::flush;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfAxiIf(void) {
  return m_number_of_axi_if;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfInterrupt(void) {
  return m_number_of_interrupt;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfOutputSignal(void) {
  return m_number_of_output_signal;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfBuffer(void) {
  return m_number_of_buffer;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfFifo(void) {
  return m_number_of_fifo;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfThread(void) {
  return m_number_of_thread;
}
unsigned int
DummyGraphicsMacroModel::getNumberOfReadOutStanding(void) {
  return m_number_of_read_outstanding;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfWriteOutStanding(void) {
  return m_number_of_write_outstanding;
}

bool
DummyGraphicsMacroModel::getNoRReceive(void) {
  return m_no_r_receive;
}

bool
DummyGraphicsMacroModel::getNoBReceive(void) {
  return m_no_b_receive;
}

const char*
DummyGraphicsMacroModel::getBufferParameterFileName(void) {
  return m_buffer_parameter_file_name.c_str();
}

const char*
DummyGraphicsMacroModel::getFifoParameterFileName(void) {
  return m_fifo_parameter_file_name.c_str();
}

const char*
DummyGraphicsMacroModel::getOutputVcdFileName(void) {
  return m_output_vcd_file_name.c_str();
}

const char*
DummyGraphicsMacroModel::getOutputCsvFileName(void) {
  return m_output_csv_file_name.c_str();
}

const char*
DummyGraphicsMacroModel::getOutputSummaryFileName(void) {
  return m_output_summary_file_name.c_str();
}

sc_time_unit
DummyGraphicsMacroModel::getTimeUnit(void) {
  return m_time_unit;
}

unsigned int
DummyGraphicsMacroModel::getAxiClock(void) {
  return m_axi_clock;
}

unsigned int
DummyGraphicsMacroModel::getCoreClock(void) {
  return m_core_clock;
}

unsigned int
DummyGraphicsMacroModel::getNumberOfInternalBuffer(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getNumberOfInternalBuffer();
}

unsigned int
DummyGraphicsMacroModel::getBufferWidth(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getWidth();
}

unsigned int
DummyGraphicsMacroModel::getBufferDepth(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getDepth();
}

unsigned int
DummyGraphicsMacroModel::getBufferWriteClock(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getWriteClock();
}

unsigned int
DummyGraphicsMacroModel::getBufferReadClock(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getReadClock();
}

unsigned int
DummyGraphicsMacroModel::getBufferWriteLatency(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getWriteLatency();
}

unsigned int
DummyGraphicsMacroModel::getBufferReadLatency(const unsigned int buffer_id) {
  checkBufferId(buffer_id);
  return m_buffers.at(buffer_id)->getReadLatency();
}

unsigned int
DummyGraphicsMacroModel::getFifoWidth(const unsigned int fifo_id) {
  checkFifoId(fifo_id);
  return m_fifos.at(fifo_id)->getWidth();
}

unsigned int
DummyGraphicsMacroModel::getFifoDepth(const unsigned int fifo_id) {
  checkFifoId(fifo_id);
  return m_fifos.at(fifo_id)->getDepth();
}

unsigned int
DummyGraphicsMacroModel::getFifoWriteClock(const unsigned int fifo_id) {
  checkFifoId(fifo_id);
  return m_fifos.at(fifo_id)->getWriteClock();
}

unsigned int
DummyGraphicsMacroModel::getFifoReadClock(const unsigned int fifo_id) {
  checkFifoId(fifo_id);
  return m_fifos.at(fifo_id)->getReadClock();
}

unsigned int
DummyGraphicsMacroModel::getFifoWriteLatency(const unsigned int fifo_id) {
  checkFifoId(fifo_id);
  return m_fifos.at(fifo_id)->getWriteLatency();
}

unsigned int
DummyGraphicsMacroModel::getFifoReadLatency(const unsigned int fifo_id) {
  checkFifoId(fifo_id);
  return m_fifos.at(fifo_id)->getReadLatency();
}

#ifdef DUMMY_GRAPHICS_MACRO_MODEL_WITH_COOPERATION_IF
bool
DummyGraphicsMacroModel::getDataInSignal(unsigned int coop_signal_id, 
                                                   unsigned int *value) {
  checkCoopSignalId(coop_signal_id);

  *value =data_in[coop_signal_id];

  if (*value == m_previous_data_in[coop_signal_id]) {
    return false;
  } else {
    m_previous_data_in[coop_signal_id] = *value;
    return (*value!=0);
  }
}

void 
DummyGraphicsMacroModel::setDataOutSignal(unsigned int coop_signal_id, 
                                                    unsigned int value) {
  checkCoopSignalId(coop_signal_id);
  //data_out[coop_signal_id] = value;
  m_data_out[coop_signal_id] = value;
  m_outputsignal_update_event.notify();
}

unsigned int 
DummyGraphicsMacroModel::getDataOutSignal(unsigned int coop_signal_id) {
  checkCoopSignalId(coop_signal_id);
  return data_out[coop_signal_id];
}

bool 
DummyGraphicsMacroModel::getBusyInSignal(unsigned int coop_signal_id) {
  checkCoopSignalId(coop_signal_id);
  return busy_in[coop_signal_id];
}

void 
DummyGraphicsMacroModel::setBusyOutSignalWithInit(unsigned int coop_signal_id, 
                                                            unsigned int value) {

  std::cout << "[INFO: Kernel]setBusyOutSignalWithInit: coop_signal_id=" << coop_signal_id 
            << ", busy_out[" << coop_signal_id << "]="  << busy_out[coop_signal_id] 
            << ", value " << value  << " @ " << sc_time_stamp() << std::endl;

  checkCoopSignalId(coop_signal_id);
  //busy_out[coop_signal_id] = value;
  m_busy_out[coop_signal_id] = value;
  if (value) {
    //data_out[coop_signal_id] = 0;
    m_data_out[coop_signal_id] = 0;
  }
  m_outputsignal_update_event.notify();

}

bool 
DummyGraphicsMacroModel::getBusyOutSignal(unsigned int coop_signal_id) {
  checkCoopSignalId(coop_signal_id);
  return busy_out[coop_signal_id];
}
#endif
