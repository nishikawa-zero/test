/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  Scenario.h
 * @brief Sample Scenario (header)
 */
#ifndef SCENARIO_H
#define SCENARIO_H

#include <iostream>
#include <systemc>

#include "DummyGraphicsMacroModelScenarioApi.h"
#include "fj_datatype.h"

#define SCENARIO_EVENT_START    0
#define SCENARIO_AXI_IF_ID      0
#define SCENARIO_LOOP          32
#define SCENARIO_BURST_SIZE     8
#define SCENARIO_BURST_LENGTH  16
#define SCENARIO_BUFFER_WIDTH   8
#define SCENARIO_BUFFER_DEPTH  64

#define SCENARIO_BUFFER_STATUS_EMPTY    0
#define SCENARIO_BUFFER_STATUS_USING    1
#define SCENARIO_BUFFER_STATUS_FULL     2

#define SCENARIO_CORE_STATUS_INIT 0
#define SCENARIO_CORE_STATUS_IDLE 1
#define SCENARIO_CORE_STATUS_BUSY 2

#define SENARIO_INPUT_BUFFER_ID  0
#define SENARIO_OUTPUT_BUFFER_ID 1

void ScenarioThread(unsigned int model_id, unsigned int thread_id);
void ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id);

void SubScenarioRchAr(unsigned int model_id);
void SubScenarioRchR(unsigned int model_id);
void SubScenarioWchAw(unsigned int model_id);
void SubScenarioWchW(unsigned int model_id);
void SubScenarioCore(unsigned int model_id);
void SubScenarioInterrupt0(unsigned int model_id);
void SubScenarioInterrupt1(unsigned int model_id);
void SubScenarioInterrupt2(unsigned int model_id);
void SubScenarioInterrupt3(unsigned int model_id);

#endif /* SCENARIO_H */
