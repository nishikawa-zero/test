/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  BufferlessModel_Scenario.h
 * @brief Sample BufferlessModel_Scenario (header)
 */
#ifndef BufferlessModel_SCENARIO_H
#define BufferlessModel_SCENARIO_H

#include <iostream>
#include <systemc>

#include "DummyGraphicsMacroModelScenarioApi.h"
#include "fj_datatype.h"
#include "AddressGenerator.h"
#include "CsvParser.h"

#define BufferlessModel_THREAD_ID_AR     0
#define BufferlessModel_THREAD_ID_R      1
#define BufferlessModel_THREAD_ID_AW_W   2

#define BufferlessModel_FIFO_ID_0        0
#define BufferlessModel_AXI_IF_ID_0      0
#define BufferlessModel_EVENT_ID_0       0
#define BufferlessModel_IN_PORT_ID_0     0

#define BufferlessModel_REQUEST_LIMIT   10
#define BufferlessModel_BUSWIDTH_BYTE   16


void BufferlessModel_ScenarioThread(unsigned int model_id, unsigned int thread_id);
void BufferlessModel_ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id);

void BufferlessModel_SubScenarioAr(unsigned int model_id, unsigned int thread_id);
void BufferlessModel_SubScenarioR(unsigned int model_id, unsigned int thread_id);
void BufferlessModel_SubScenarioAw_W(unsigned int model_id, unsigned int thread_id);
void BufferlessModel_SubScenarioInterrupt0(unsigned int model_id);
void BufferlessModel_SubScenarioInterrupt1(unsigned int model_id);
void BufferlessModel_SubScenarioInterrupt2(unsigned int model_id);
void BufferlessModel_SubScenarioInterrupt3(unsigned int model_id);


#endif /* SCENARIO_H */
