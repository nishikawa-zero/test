/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  IIP_Pseudo_Scenario.cpp
 * @brief Sample IIP_Pseudo_Scenario (source)
 */
#include "IIP_Pseudo_Scenario.h"

void
IIP_Pseudo_ScenarioThread(unsigned int model_id, unsigned int thread_id) {
  std::cout << __FUNCTION__ << " (thread_id=" << thread_id << ")" << std::endl;
  switch (thread_id) {
  case 0:
    IIP_Pseudo_ScenarioMain(model_id, thread_id);
    break;
  default:
    std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
    assert(0);
    break;
  }
}

void
IIP_Pseudo_ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id) {
  switch (interrupt_id) {
  case 0:
    IIP_Pseudo_SubScenarioInterrupt0(model_id);
    break;
  case 1:
    IIP_Pseudo_SubScenarioInterrupt1(model_id);
    break;
  case 2:
    IIP_Pseudo_SubScenarioInterrupt2(model_id);
    break;
  case 3:
    IIP_Pseudo_SubScenarioInterrupt3(model_id);
    break;
  default:
    std::cout << "[ERROR] no interrupt scenario (interrupt_id=" << interrupt_id << ")" << endl;
    assert(0);
    break;
  }
}

void
IIP_Pseudo_ScenarioMain(unsigned int model_id, unsigned int thread_id) {
  bool busy_in = false;
  unsigned int data_in[10] = {};
  unsigned int x = 0;
  unsigned int y = 0;

  unsigned int hsize = 5632;
  unsigned int vsize = 3728;
  unsigned int location;

  unsigned int wait_cycle[2] = {10, 1000};
  unsigned int wait_pattern = 0;

  AddressGenerator Ydata(4, // dimension
                         0x0, // start address
                         5632, // globalsize
                         5632, // hsize
                         3728, // vsize
                         256, // base_hsize
                         8, // base_vsize
                         0, // hmargin
                         3, // base_axi_size(64bit bus)
                         31, // base_axi_length(32beat)
                         false // left align
                         );
  
  setBusyOutSignalWithInit(model_id, 0, true);

  for (unsigned int count = 0; count < Ydata.size(); ++count) {
    unsigned long ARADDR;
    unsigned int ARLEN;
    unsigned int location;
    unsigned int leflg;
    unsigned int reflg;
    unsigned int feflg;
    
    unsigned int data_size;
    unsigned int jpg_x_coordinate;
    unsigned int jpg_y_coordinate;
    unsigned int jpg_location;
    
    unsigned int base_axi_size = 3;
    unsigned int base_axi_length = 31;

    Ydata.getParameterChannel(&ARADDR, &ARLEN, &location, &leflg, &reflg, &feflg, count);

#if 0
    std::cout << "ARADDR=" << ARADDR << ",ARLEN=" << ARLEN << ",location=" << location << ",leflg=" << leflg << ",reflg=" << reflg << ",feflg=" << feflg << ",count=" << count << std::endl;
#endif

    data_size = pow(2, base_axi_size) * (ARLEN + 1);
    jpg_y_coordinate = location & 0xFFFF;
    jpg_x_coordinate = ((location >> 16) & 0xFFFF) + data_size - 1;
    jpg_location = (jpg_x_coordinate << 16) | jpg_y_coordinate;

#if 0
    std::cout << "jpg_location=" << std::hex << std::showbase << jpg_location << std::dec << ",processed_data_size=" << processed_data_size << std::endl;
#endif

    setDataOutSignal(model_id, 0, jpg_location);
    
    waitAxiCycle(model_id, wait_cycle[wait_pattern]);

    if (((count + 1) % 10) == 0) {
      wait_pattern = (wait_pattern + 1) & 0x1;
    }
  }
}

void
IIP_Pseudo_SubScenarioInterrupt0(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << std::endl;
}

void
IIP_Pseudo_SubScenarioInterrupt1(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << std::endl;
}

void
IIP_Pseudo_SubScenarioInterrupt2(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << std::endl;
}

void
IIP_Pseudo_SubScenarioInterrupt3(unsigned int model_id) {
  dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << std::endl;
}

