/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  IIP_Pseudo_Scenario.h
 * @brief Sample IIP_Pseudo_Scenario (header)
 */
#ifndef IIP_Pseudo_SCENARIO_H
#define IIP_Pseudo_SCENARIO_H

#include <iostream>
#include <systemc>
#include <math.h>

#include "DummyGraphicsMacroModelScenarioApi.h"
#include "AddressGenerator.h"
#include "fj_datatype.h"

#define IIP_Pseudo_AXI_BUS_WIDTH 8
#define IIP_Pseudo_MAX_AXLEN 32

void IIP_Pseudo_ScenarioThread(unsigned int model_id, unsigned int thread_id);
void IIP_Pseudo_ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id);

void IIP_Pseudo_ScenarioMain(unsigned int model_id, unsigned int thread_id);

void IIP_Pseudo_SubScenarioInterrupt0(unsigned int model_id);
void IIP_Pseudo_SubScenarioInterrupt1(unsigned int model_id);
void IIP_Pseudo_SubScenarioInterrupt2(unsigned int model_id);
void IIP_Pseudo_SubScenarioInterrupt3(unsigned int model_id);

#endif /* SCENARIO_H */
