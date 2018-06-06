/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  JPEG_Scenario.h
 * @brief Sample JPEG_Scenario (header)
 */
#ifndef JPEG_SCENARIO_H
#define JPEG_SCENARIO_H

#include <iostream>
#include <systemc>

#include "DummyGraphicsMacroModelScenarioApi.h"
#include "fj_datatype.h"
#include "AddressGenerator.h"
#include "CsvParser.h"

#define JPEG_FRAME_MAX  128

#define JPEG_THREAD_MAX 11
#define JPEG_THREAD_ID_AR0   	0
#define JPEG_THREAD_ID_R0    	1
#define JPEG_THREAD_ID_AR1   	2
#define JPEG_THREAD_ID_R1    	3
#define JPEG_THREAD_ID_AR2   	4
#define JPEG_THREAD_ID_R2    	5
#define JPEG_THREAD_ID_AR3   	6
#define JPEG_THREAD_ID_R3    	7
#define JPEG_THREAD_ID_CORE  	8
#define JPEG_THREAD_ID_AW    	9
#define JPEG_THREAD_ID_W    	10

#define JPEG_BUFFER_ID_IBUFY 	0
#define JPEG_BUFFER_ID_IBUFC 	1
#define JPEG_BUFFER_ID_OBUF  	2

#define JPEG_BUS_WIDTH 			8	// 64bit-bus

#define JPEG_BUFFER_STATUS_EMPTY	0
#define JPEG_BUFFER_STATUS_USING 	1
#define JPEG_BUFFER_STATUS_FULL  	2

#define JPEG_EVENT_START	 	0
#define JPEG_EVENT_KICK_WCH	 	1

#define JPEG_ENABLE			 	1

#define JPEG_INPUT_DIMENSION 	4
#define JPEG_OUTPUT_DIMENSION 	1

#define JPEG_BASE_HSIZE			256
#define JPEG_BASE_VSIZE			8

#define JPEG_BUS_SIZE		 	3 // 8byte

#define JPEG_OUTPUT_SIGNAL 		0

#define JPEG_CORE_STATUS_IDLE 1
#define JPEG_CORE_STATUS_BUSY 2

#define SizeOfJPEGScenarioParameterFormat	18 // ÉpÉâÉÅÅ[É^êî

#define JPEG_INSTANCE_MAX 3

enum JPEG_ScenarioParameterFormat {
	IFMT,
	RBSIZE,
	WBSIZE,
	JIMGSH,
	JIMGSV,
	JIMGAY,
	JIMGACB,
	JCODA,
	JIMGYGH,
	JIMGCGH,
	HDR_SIZE,
	FTR_SIZE,
	COOP,
	CORE_PIX,
	AXI_IF_Y,
	AXI_IF_C,
	OUT_LEFT_ALIGN,
	COMP_RATE,
	SRAM_MODE,
	SRAM_SADDR,
	SRAM_SIZE
};

struct JPEG_ScenarioParameter {
  unsigned int ifmt;
  unsigned int rbsize;
  unsigned int wbsize;
  unsigned int jimgsh;
  unsigned int jimgsv;
  unsigned int jimgay;
  unsigned int jimgacb;
  unsigned int jcoda;
  unsigned int jimgygh;
  unsigned int jimgcgh;
  unsigned int hdr_size;
  unsigned int ftr_size;
  unsigned int coop;
  unsigned int core_pix;
  unsigned int axi_if_y;
  unsigned int axi_if_c;
  unsigned int out_left_align;
  unsigned int comp_rate;
  unsigned int sram_mode;
  unsigned int sram_saddr;
  unsigned int sram_size;
  
  unsigned int base_hsize;
  unsigned int base_vsize;
  unsigned int input_addr;
  unsigned int input_gsize;
  unsigned int input_length;
  unsigned int output_length;
  unsigned int input_total_size;
  unsigned int output_total_size;
  
  AddressGenerator *input_address_generator;
  AddressGenerator *output_address_generator;
  
JPEG_ScenarioParameter(void):
  input_address_generator(NULL),
    output_address_generator(NULL) {
  }
};

struct JPEG_Parameter
{
	unsigned long h_mesh;
};

void JPEG_ScenarioThread(unsigned int model_id, unsigned int thread_id);
void JPEG_ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id);

void JPEG_SubScenarioAr(unsigned int model_id, unsigned int thread_id);
void JPEG_SubScenarioR(unsigned int model_id, unsigned int thread_id);
void JPEG_SubScenarioAw(unsigned int model_id, unsigned int thread_id);
void JPEG_SubScenarioW(unsigned int model_id, unsigned int thread_id);
void JPEG_SubScenarioCore(unsigned int model_id, unsigned int thread_id);
void JPEG_SubScenarioInterrupt0(unsigned int model_id);
void JPEG_SubScenarioInterrupt1(unsigned int model_id);
void JPEG_SubScenarioInterrupt2(unsigned int model_id);
void JPEG_SubScenarioInterrupt3(unsigned int model_id);

void JPEG_readScenarioParameterFile(unsigned int core_id, const char *file_name);

#endif /* SCENARIO_H */
