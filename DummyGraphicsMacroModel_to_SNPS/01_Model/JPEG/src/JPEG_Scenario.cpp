/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/*
 * @file  JPEG_Scenario.cpp
 * @brief Sample JPEG_Scenario (source)
 */
#include "JPEG_Scenario.h"

namespace {
  	std::vector<JPEG_ScenarioParameter*> g_parameters[JPEG_INSTANCE_MAX][2];
  	bool is_finish_scenario[JPEG_INSTANCE_MAX][2];
	struct JPEG_Parameter	g_param[JPEG_INSTANCE_MAX][JPEG_FRAME_MAX];
}

namespace {
  struct JPEG_ScenarioParameter jpeg_local_parameters[JPEG_INSTANCE_MAX][3];
}

namespace { 
  unsigned int instance_number = 0; 
  std::map<unsigned int, unsigned int> instance_number_map ;
}  

namespace {
  const unsigned int coop_id 	 = 0;
  unsigned int location_value[JPEG_INSTANCE_MAX][JPEG_THREAD_MAX];	// Y/C
}


unsigned int getInstanceNumber(unsigned int model_id) { 
  unsigned int result; 
  std::map<unsigned int, unsigned int>::iterator itr = instance_number_map.find(model_id); 

  if (itr != instance_number_map.end()) { /* already registered */ 
    result = itr->second; 
  } else { /* did not register */ 
    result = instance_number; 
    instance_number_map[model_id] = instance_number; 
    ++instance_number; 
    if (instance_number > JPEG_INSTANCE_MAX-1) {
      std::cout << "JPEG number of instance is over capacity.(MAX_INSTANCE=" << JPEG_INSTANCE_MAX << ")" << std::endl;
      assert(0);
    }
  } 

  return result; 
}

void JPEG_ScenarioThread(unsigned int model_id, unsigned int thread_id) {
  std::cout << __FUNCTION__ << " (thread_id=" << thread_id << ")" << std::endl;
  switch (thread_id) {

  case JPEG_THREAD_ID_AR0:		
  case JPEG_THREAD_ID_AR1:
  case JPEG_THREAD_ID_AR2:
  case JPEG_THREAD_ID_AR3:
    JPEG_SubScenarioAr(model_id, thread_id);
    break;

  case JPEG_THREAD_ID_R0:
  case JPEG_THREAD_ID_R1:
  case JPEG_THREAD_ID_R2:
  case JPEG_THREAD_ID_R3:
    JPEG_SubScenarioR(model_id, thread_id);
    break;

  case JPEG_THREAD_ID_CORE:
    JPEG_SubScenarioCore(model_id, thread_id);
    break;

  case JPEG_THREAD_ID_AW:
    JPEG_SubScenarioAw(model_id, thread_id);
    break;

  case JPEG_THREAD_ID_W:
    JPEG_SubScenarioW(model_id, thread_id);
    break;
    
  default:
    std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << std::endl;
    assert(0);
    break;
  }
}

void JPEG_ScenarioInterrupt(unsigned int model_id, unsigned int interrupt_id) {
  switch (interrupt_id) {

  case 0:
    JPEG_SubScenarioInterrupt0(model_id);
    break;

  case 1:
    JPEG_SubScenarioInterrupt1(model_id);
    break;

  case 2:
    JPEG_SubScenarioInterrupt2(model_id);
    break;

  case 3:
    JPEG_SubScenarioInterrupt3(model_id);
    break;

  default:
    std::cout << "[ERROR] no interrupt scenario (interrupt_id=" << interrupt_id << ")" << std::endl;
    assert(0);
    break;
  }
}
	
void JPEG_SubScenarioAr(unsigned int model_id, unsigned int thread_id) {
	unsigned int ARID = 0;
	unsigned long ARADDR;
	unsigned int ARLEN;
	unsigned int ARSIZE = 0x3; /* 8-Byte*/
	unsigned int ARBURST = 1; /* INCR */
	unsigned int ARLOCK = 0;
	unsigned int ARCACHE = 0;
	unsigned int ARPROT = 0;
	unsigned int ARUSER = 0;

	unsigned int location;
	unsigned int leflg;
	unsigned int reflg;
	unsigned int feflg;
	unsigned int count;
	unsigned int max_count;

	unsigned int axi_if_id;
	unsigned int input_buffer_id;
	unsigned int core_id; // 転送対象(Y or C)

	unsigned int transfer_size;
	AddressGenerator *input_address_generator;

	unsigned int input_buffer_size;
	unsigned int remain_buffer_size;
	unsigned int processed_data_size = 0;
	
	unsigned int h_mesh_count = 0;

	unsigned int scenario_id = 0;
	bool is_finish_one_frame;
	bool is_finish_all_frame = false;

	char coop_flag = 0;
	char already_coop_flag = 0;
	unsigned int coop_value = 0; // マクロ間連携先の座標値
	unsigned int co_posX, co_posY;
	unsigned int my_posX = 0;
	unsigned int my_posY = 0;
	unsigned int instance_id;
	instance_id  = getInstanceNumber(model_id);

  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " start" << std::endl;

  	/* Make each channel parameters */
  	switch (thread_id) {
  		case JPEG_THREAD_ID_AR0:
    	makeVcdValue(model_id, "scenario_id", 0, 8, 0);
    	ARID = 0;
    	axi_if_id = 0;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFY;
    	core_id = 0;
    	break;
  		case JPEG_THREAD_ID_AR1:
    	makeVcdValue(model_id, "scenario_id", 1, 8, 0);
    	ARID = 1;
    	axi_if_id = 1;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFC;
    	core_id = 1;
    	break;
  		case JPEG_THREAD_ID_AR2:
    	makeVcdValue(model_id, "scenario_id", 2, 8, 0);
    	ARID = 0;
    	axi_if_id = 2;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFY;
    	core_id = 0;
    	break;
  		case JPEG_THREAD_ID_AR3:
 	   	makeVcdValue(model_id, "scenario_id", 3, 8, 0);
    	ARID = 1;
    	axi_if_id = 3;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFC;
    	core_id = 1;
    	break;

  		default:
		std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
    	assert(0);    
    	break;
	}
  	
	enableLogging(model_id);    
  
	/* For all frame */
  	while (!is_finish_all_frame) {
    	/* Wait startup event &  Make each channel parameters */
    	switch (thread_id) {
    		case JPEG_THREAD_ID_AR0:
//			printf("[AR][%d] waitEvent JPEG_EVENT_START start\n", thread_id);
      		waitEvent(model_id, JPEG_EVENT_START);
//			printf("[AR][%d] waitEvent JPEG_EVENT_START end\n", thread_id);
      		setVcdValue(model_id, 0, scenario_id);
   	 		break;
    		case JPEG_THREAD_ID_AR1:
      		waitEvent(model_id, JPEG_EVENT_START);
      		setVcdValue(model_id, 1, scenario_id);
      		break;
    		case JPEG_THREAD_ID_AR2:
      		waitEvent(model_id, JPEG_EVENT_START);
      		setVcdValue(model_id, 2, scenario_id);
    		break;
    		case JPEG_THREAD_ID_AR3:
      		waitEvent(model_id, JPEG_EVENT_START);
      		setVcdValue(model_id, 3, scenario_id);
      		break;
    		default:
      		std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
      		assert(0);    
      		break;
    	}
		
		/* 非対象スレッド */
		if( (thread_id == JPEG_THREAD_ID_AR0) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_y == 1) ){
			break;
		}
		else if( (thread_id == JPEG_THREAD_ID_AR1) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_c == 1) ){
			break;
		}
		else if( (thread_id == JPEG_THREAD_ID_AR2) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_y == 0) ){
			break;
		}
		else if( (thread_id == JPEG_THREAD_ID_AR3) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_c == 0) ){
			break;
		}
		
//		printf("[AR][%d] scenario_id = %d\n", thread_id, scenario_id);
//		printf("[AR][%d] g_parameters[core_id].size() = %d\n", thread_id, g_parameters[core_id].size());
		
		if (scenario_id < g_parameters[instance_id][core_id].size()) {
//			//printf("\n1a\n\n");
			//printf("[AR][%d] 195 core_id = %d\n", thread_id, core_id);
			//printf("[AR][%d] 195 scenario_id = %d\n", thread_id, scenario_id);
      		input_address_generator = g_parameters[instance_id][core_id].at(scenario_id)->input_address_generator;
      		max_count = input_address_generator->size(); // size()はリクエスト回数
//		        //printf("[AR][%d] max_count = %d\n", thread_id, max_count);
//			//printf("scenario_id = %d\n",scenario_id);
    	} 
		else {
      		is_finish_all_frame = true;
      		break;
    	}
    	count = 0;
    	is_finish_one_frame = false;
		
	bool isBusy_opp = false;		
  
    	/* For 1 frame */
    	while (!is_finish_one_frame) {

	  if(jpeg_local_parameters[instance_id][scenario_id].coop == true){
	    // Wait Busy signal from COOP-model
	    //	    std::cout << __FUNCTION__ << " core_id=" << core_id << " waitBusySignal at " << sc_time_stamp() << std::endl;
	    //	    while(!isBusy_opp) {
	    //	      isBusy_opp = getBusyInSignal(model_id,coop_id);
	    //	      waitAxiCycle(model_id, 1);
	    //	    }
	    //	    std::cout << __FUNCTION__ << " core_id=" << core_id << " BusySignal assert at " << sc_time_stamp() << std::endl;
}

	  
      		/* Wait buffer status EMPTY */
//			dumpSimulationTime(model_id);
//      		std::cout << __FUNCTION__ << " waitWriteBufferStatus(" << input_buffer_id << "," << JPEG_BUFFER_STATUS_EMPTY <<")" << std::endl;
      		waitWriteBufferStatus(model_id, input_buffer_id, JPEG_BUFFER_STATUS_EMPTY);
//			dumpSimulationTime(model_id);
//      		std::cout << __FUNCTION__ << " end waitWriteBufferStatus(" << input_buffer_id << "," << JPEG_BUFFER_STATUS_EMPTY <<")" << std::endl;

			
			//			//printf("\n1\n\n");
      		/* Get buffer size */
	  		input_buffer_size = getBufferWidth(model_id, input_buffer_id) * getBufferDepth(model_id, input_buffer_id);
      		remain_buffer_size = input_buffer_size;
//			debug = getBufferWidth(model_id, input_buffer_id);
//			//printf("getBufferWidth = %d\n",debug);
//			debug = getBufferDepth(model_id, input_buffer_id);
//			//printf("getBufferDepth = %d\n",debug);
			
//		printf("[AR][%d] remain_buffer_size = %d\n",thread_id, remain_buffer_size);

      		/* While buffer is not FULL or buffer is not enough to write RDATAs */
      		while (remain_buffer_size != 0) {
        		/* Get ARADDR */
        		input_address_generator->getParameterChannel(&ARADDR, &ARLEN, &location, &leflg, &reflg, &feflg, count);

			//			printf("***\n");
			//			printf("[AR][%d] ARADDR = 0x%x\n", thread_id, ARADDR);
			//			printf("[AR][%d] location = 0x%08x\n", thread_id, location);
			//			printf("[AR][%d] count = %d\n", thread_id, count);
			//			printf("[AR][%d] reflg = %x\n", thread_id, reflg);
			//			printf("[AR][%d] ARLEN = %d\n", thread_id, ARLEN);
			//			printf("\n2\n\n");

        		/* Culcurate RDATAs size */
        		transfer_size = (JPEG_BUS_WIDTH * (ARLEN + 1));
			//	printf("\n3\n\n");
			//	printf("input_buffer_size = %d\n",input_buffer_size);
			//	printf("remain_buffer_size = %d\n",remain_buffer_size);
			//	printf("transfer_size = %d\n",transfer_size);
			//	printf("ARLEN = %d\n",ARLEN);
        		/* Check buffer is enough to write RDATAs or not */
        		if (remain_buffer_size < transfer_size) {
          			break;
        		}
			//	printf("\n4\n\n");
			/* マクロ間連携処理 */
			if(jpeg_local_parameters[instance_id][scenario_id].coop == JPEG_ENABLE){
			  my_posX = ((location >> 16) & 0xFFFF) + transfer_size - 1;
			  my_posY =  (location      ) & 0xFFFF;
			  coop_flag = 0;
			  /* 転送座標に到達するまでループ */
			  while(coop_flag != 1){
			    getDataInSignal(model_id, coop_id, &coop_value);
			    co_posX = (coop_value >> 16) & 0xFFFF;
			    co_posY = (coop_value      ) & 0xFFFF;
			    
			    /* Y座標を比較 */
			    if ( co_posY == my_posY ){	// IIP Y == JPEG Y
			      /* X座標を比較 */
			      if( co_posX >= my_posX ){
				coop_flag = 1;
			      }
			    } else if ( co_posY > my_posY ){	// IIP Y > JPEG Y
			      if ( (co_posY / 8) == (my_posY / 8 )) {
				if ( co_posX >= my_posX ){
				  coop_flag = 1;
				}
			      } else {
				coop_flag = 1;
			      }
			    } else {	// IIP Y < JPEG Y
			      if (((co_posY / 8) == (my_posY / 8))&&( co_posX > my_posX )){
				coop_flag = 1;
			      }
			    }
			    if (coop_flag != 1) {
			      if (already_coop_flag == 0) {
				//std::cout << __FUNCTION__ ;
				//printf(" wait next posX/Y : JPEG[%8x] COOP[%8x] at ",location,coop_value);
				//std::cout << sc_time_stamp() << std::endl;
				already_coop_flag = 1;
			      }
			      waitAxiCycle(model_id, 1);
			    }
			  }
			}
			if (already_coop_flag == 1) {
			  //std::cout << __FUNCTION__ ;
			  //printf(" get posX/Y : COOP[%8x] continue at ",coop_value);
			  //std::cout << sc_time_stamp() << std::endl;
			  already_coop_flag = 0;
			}
			//				//printf("\n5\n\n");
        		/* Make AR transaction */
			//        		dumpSimulationTime(model_id);
//				printf("[AR] count = %d\n", count);
//				std::cout << __FUNCTION__ << " sendAr(" << axi_if_id << ")" << " [" << thread_id << "]" << " [" << count << "]" << std::endl;
			sendAr(model_id, axi_if_id, ARID, ARADDR, ARLEN, ARSIZE, ARBURST, ARLOCK, ARCACHE, ARPROT, ARUSER);

        		/* Culcurate remain buffer size */
        		remain_buffer_size -= transfer_size;
				//printf("[AR][%d] remain_buffer_size = %d\n",thread_id, remain_buffer_size);
        		/* Culcurate processed data size */
        		processed_data_size += transfer_size;
        		++count;
				
//				printf("[AR][%d] count = %d\n",thread_id, count);
        		/* Check all transfer is finish or not */
        		if (max_count <= count) {
          			is_finish_one_frame = true;
				//	printf("[AR][%d] remain_buffer_size = %d\n",thread_id, remain_buffer_size);
          			break;
        		}
			//printf("[AR][%d] reflg = %d\n",thread_id, reflg);
			//printf("[AR][%d] jpeg_local_parameters[instance_id][scenario_id].input_length = %d\n",thread_id, jpeg_local_parameters[instance_id][scenario_id].input_length);
        		/* Check assuming buffer full */
//        		if ((reflg == 1) && (ARLEN != jpeg_local_parameters[instance_id][scenario_id].input_length)) {
//          			break;
//        		}
				if(reflg == 1){
					h_mesh_count++;
					if(h_mesh_count == g_param[instance_id][scenario_id].h_mesh){
						h_mesh_count = 0;
						//フレーム右端メッシュの最後は面切り替え
						break;
					}
				}
			}
      		//printf("[AR][%d] input_buffer_id = %d\n",thread_id, input_buffer_id);
			/* Wait buffer switching */
      		//dumpSimulationTime(model_id);
//      		std::cout << __FUNCTION__ << " waitWriteBufferStatus(" << input_buffer_id << "," << JPEG_BUFFER_STATUS_FULL <<")" << std::endl;
      		waitWriteBufferStatus(model_id, input_buffer_id, JPEG_BUFFER_STATUS_FULL);
    	}
    	++scenario_id;
	if (g_parameters[instance_id][core_id].size() <= scenario_id) {
	  is_finish_all_frame = true;
	}
	}
  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " finish " << "thread_id(" << thread_id << ")" << std::endl;
}

void JPEG_SubScenarioR(unsigned int model_id, unsigned int thread_id) {
	unsigned int RID = 0;
	unsigned int RLAST;
	unsigned int RRESP;
	unsigned char rdata[JPEG_BUS_WIDTH];  

	unsigned long ARADDR;
	unsigned int ARLEN;

	unsigned int location;
	unsigned int leflg;
	unsigned int reflg;
	unsigned int feflg;
	unsigned int count;
	unsigned int max_count;

	unsigned int axi_if_id;
	unsigned int input_buffer_id;
	unsigned int core_id;

	unsigned int transfer_size;
	AddressGenerator *input_address_generator;

	unsigned int input_buffer_size;
	unsigned int remain_buffer_size;
	unsigned int processed_data_size = 0;

	unsigned int scenario_id = 0;
	bool is_finish_one_frame;
	bool is_finish_all_frame = false;
	
	unsigned int h_mesh_count = 0;

	unsigned int posX = 0;
	unsigned int posY = 0;

	unsigned int instance_id;
	instance_id  = getInstanceNumber(model_id);

  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " start" << std::endl;

  	/* Wait startup event &  Make each channel parameters */
  	switch (thread_id) {
  		case JPEG_THREAD_ID_R0:
    	RID = 0;
    	axi_if_id = 0;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFY;
    	core_id = 0;
    	break;
  		case JPEG_THREAD_ID_R1:
    	RID = 1;
    	axi_if_id = 1;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFC;
    	core_id = 1;
    	break;
  		case JPEG_THREAD_ID_R2:
    	RID = 0;
    	axi_if_id = 2;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFY;
    	core_id = 0;
    	break;
  		case JPEG_THREAD_ID_R3:
    	RID = 1;
    	axi_if_id = 3;
    	input_buffer_id = JPEG_BUFFER_ID_IBUFC;
    	core_id = 1;
    	break;
  		default:
    	std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
    	assert(0);    
    	break;
	}
  	input_buffer_size = getBufferWidth(model_id, input_buffer_id) * getBufferDepth(model_id, input_buffer_id);

  	/* For all frame */
  	while (!is_finish_all_frame) {
    	/* Wait startup event &  Make each channel parameters */
    	switch (thread_id) {
    		case JPEG_THREAD_ID_R0:
      		waitEvent(model_id, JPEG_EVENT_START);
      		break;
    		case JPEG_THREAD_ID_R1:
      		waitEvent(model_id, JPEG_EVENT_START);
      		break;
			case JPEG_THREAD_ID_R2:
      		waitEvent(model_id, JPEG_EVENT_START);
      		break;
    		case JPEG_THREAD_ID_R3:
      		waitEvent(model_id, JPEG_EVENT_START);
      		break;
    		default:
      		std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
      		assert(0);    
      		break;
    	}

    	if (scenario_id < g_parameters[instance_id][core_id].size()) {
			input_address_generator = g_parameters[instance_id][core_id].at(scenario_id)->input_address_generator;
      		max_count = input_address_generator->size();
    	} 
		else {
      		is_finish_all_frame = true;
      		break;
    	}
    	count = 0;
    	is_finish_one_frame = false;
		
		/* 非対象スレッド */
		if( (thread_id == JPEG_THREAD_ID_R0) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_y == 1) ){
			break;
		}
		else if( (thread_id == JPEG_THREAD_ID_R1) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_c == 1) ){
			break;
		}
		else if( (thread_id == JPEG_THREAD_ID_R2) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_y == 0) ){
			break;
		}
		else if( (thread_id == JPEG_THREAD_ID_R3) && (jpeg_local_parameters[instance_id][scenario_id].axi_if_c == 0) ){
			break;
		}
		
//		printf("[R][%d] max_count = %d\n",thread_id, max_count);
		processed_data_size = 0;
    	/* For 1 frame */
    	while (!is_finish_one_frame) {
      		/* Wait buffer empty */ 
      		//dumpSimulationTime(model_id);
//      		std::cout << __FUNCTION__ << " waitWriteBufferStatus(" << input_buffer_id << "," << JPEG_BUFFER_STATUS_EMPTY <<")" << std::endl;
      		waitWriteBufferStatus(model_id, input_buffer_id, JPEG_BUFFER_STATUS_EMPTY);
      
      		/* Get buffer size */
      		remain_buffer_size = input_buffer_size;
      		//printf("[R][%d] remain_buffer_size = %d\n", thread_id, remain_buffer_size);
      		/* While buffer is not full or buffer is not enough to write RDATAs */
      		while (remain_buffer_size != 0) {
//				//printf("[R] 432 thread_id = %d\n",thread_id);
//				//printf("[R] RID = %d\n",RID);
				
        		/* Get ARLEN */
        		input_address_generator->getParameterChannel(&ARADDR, &ARLEN, &location, &leflg, &reflg, &feflg, count);
 //       		//printf("[R] 437 thread_id = %d\n",thread_id);
//				//printf("[R] RID = %d\n",RID);
				/* Culcurate RDATAs size */
        		transfer_size = (JPEG_BUS_WIDTH * (ARLEN + 1));
 //       		//printf("[R] 441 thread_id = %d\n",thread_id);
//				//printf("[R] RID = %d\n",RID);
				/* Check buffer is enough to write RDATAs or not */ 
        		if (remain_buffer_size < transfer_size) {
          			break;
        		}
				        
        		/* Make R transaction */ 
        		for (unsigned int i = 0; i < ARLEN + 1; ++i) { 
          			receiveRById(model_id, axi_if_id, RID, &RLAST, &RRESP, rdata);
//					//printf("[R] 451 thread_id = %d\n",thread_id);
//					//printf("[R] RID = %d\n",RID);
          			writeBuffer(model_id, input_buffer_id, rdata);
					processed_data_size += JPEG_BUS_WIDTH;
        		}
//			printf("[R][%d] processed_data_size = %d\n", thread_id, processed_data_size);
//			printf("[R] 455 thread_id = %d\n",thread_id);
//			printf("[R] RID = %d\n",RID);
			
			/* マクロ間連携処理 */
			if((jpeg_local_parameters[instance_id][scenario_id].coop == JPEG_ENABLE)&&(leflg==1)){
			  posX = ((location >> 16) & 0xFFFF) + transfer_size - 1;
			  posY =  (location      ) & 0xFFFF;
			  location_value[instance_id][thread_id] = (posX << 16) | posY;
			  
			  /* 転送座標値を送信する */
			  //printf("send posX,posY = [%4d,%4d] thread_id=%d\n",posX,posY,thread_id);
			  if (location_value[instance_id][JPEG_THREAD_ID_R0] < location_value[instance_id][JPEG_THREAD_ID_R1]) {
			    location = location_value[instance_id][JPEG_THREAD_ID_R0];
			  } else {
			    location = location_value[instance_id][JPEG_THREAD_ID_R1];
			  }
			  setDataOutSignal(model_id, coop_id, location);
			}
//				//printf("[R] 462 thread_id = %d\n",thread_id);
//				//printf("[R] RID = %d\n",RID);
			

        		/* Culcurate remain buffer size */
        		remain_buffer_size -= transfer_size;
//        		printf("[R][%d] remain_buffer_size = %d\n",thread_id, remain_buffer_size);
//				printf("[R][%d] count = %d\n",thread_id, count);
        		/* Culcurate processed data size */
//        		processed_data_size += transfer_size;
        		++count;
//        		//printf("[R] 472 thread_id = %d\n",thread_id);
//				//printf("[R] RID = %d\n",RID);
//				printf("[R][%d] count = %d\n",thread_id, count);
        		/* Check all transfer is finish or not */
        		if (max_count <= count) {
					is_finish_one_frame = true;
//					printf("[R][%d] remain_buffer_size = %d\n",thread_id, remain_buffer_size);
          			break;
       			}
//      			//printf("[R] 480 thread_id = %d\n",thread_id);
//				//printf("[R] RID = %d\n",RID);
				
        		/* Check assuming buffer full */
//        		if ((reflg == 1) && (ARLEN != jpeg_local_parameters[instance_id][scenario_id].input_length)) {
//          			break;
//        		}
				
				if(reflg == 1){
					h_mesh_count++;
					if(h_mesh_count == g_param[instance_id][scenario_id].h_mesh){
						h_mesh_count = 0;
						//フレーム右端メッシュの最後は面切り替え
						break;
					}
				}
							
//				//printf("[R] 487 thread_id = %d\n",thread_id);
//				//printf("[R] RID = %d\n",RID);
				
			}
      		
      	    /* Buffer switch latency (for test) */
      		waitAxiCycle(model_id, 1);
//      		printf("[R][%d] is_finish_one_frame = %d\n",thread_id, is_finish_one_frame);
      		/* Switch buffer */
      		//dumpSimulationTime(model_id);
 //     		std::cout << __FUNCTION__ << " switchWriteBuffer(" << thread_id << "," << input_buffer_id << ")" << std::endl;
      		switchWriteBuffer(model_id, input_buffer_id);
//			printf("[R][%d] switchWriteBuffer end\n");
    	}
    	++scenario_id;
    	if (g_parameters[instance_id][core_id].size() <= scenario_id) {
      		is_finish_all_frame = true;
    	}
//		printf("[R][%d] is_finish_all_frame = %d\n",is_finish_all_frame, count);
  	}
  
  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " finish " << "thread_id(" << thread_id << ")" << std::endl;
}

void JPEG_SubScenarioCore(unsigned int model_id, unsigned int thread_id) {
	unsigned long ARADDR;
	unsigned int ARLEN;
	unsigned long AWADDR;
  	unsigned int AWLEN;
  	unsigned int location;
  	unsigned int leflg;
  	unsigned int reflg;
  	unsigned int feflg;
  	unsigned int count;
  	unsigned int max_count;

  	unsigned int input_buffer_id;
  	unsigned int output_buffer_id;
  	unsigned int core_id;
  	unsigned char data[JPEG_BUS_WIDTH];

  	unsigned int input_buffer_width;
  	unsigned int output_buffer_width;
  	unsigned int input_buffer_depth;
  	unsigned int output_buffer_depth;
  	unsigned int input_buffer_size;
  	unsigned int output_buffer_size;

  	unsigned int remain_input_y_buffer_size = 0;
	unsigned int remain_input_c_buffer_size = 0;
  	unsigned int remain_output_buffer_size = 0;
  	unsigned int processed_data_size = 0;
  	unsigned int burst_count = 0;
	
  	unsigned int transfer_size = 0;
  	AddressGenerator *output_address_generator;
	AddressGenerator *input_address_generator;

  	unsigned int scenario_id = 0;
  	bool is_finish_one_frame;
  	bool is_finish_all_frame = false;
	
	unsigned int hdr_size = 0;
	unsigned int encode_size = 0;
	unsigned int ftr_size = 0;
	unsigned int remain_hdr_size = 0;
	unsigned int remain_encode_size = 0;
	unsigned int remain_ftr_size = 0;
	
	unsigned int write_buffer_size = 0;
	unsigned int write_exe_size = 0;
	unsigned int read_exe_size = 0;
	
	unsigned int write_data_size = 0;
	
	unsigned int count_y = 0;
	unsigned int count_c = 0;
	
	unsigned int burst_y_count = 0;
	unsigned int burst_c_count = 0;
	
	unsigned int input_total_y_data = 0;
	unsigned int input_total_c_data = 0;
	
	unsigned int total_out_data_size = 0;
	
	unsigned int instance_id;
	instance_id  = getInstanceNumber(model_id);

	bool isBusy_opp = false;		
  
  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " start" << std::endl;

  	/* Make each channel parameters */
  	switch (thread_id) {
 	 	case JPEG_THREAD_ID_CORE:
    	input_buffer_id = JPEG_BUFFER_ID_IBUFY;
    	output_buffer_id = JPEG_BUFFER_ID_OBUF;
    	core_id = 0;
    	break;
  		default:
    	std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
    	assert(0);    
    	break;
  	}
  	input_buffer_width = getBufferWidth(model_id, input_buffer_id);
  	output_buffer_width = getBufferWidth(model_id, output_buffer_id);
  	input_buffer_depth = getBufferDepth(model_id, input_buffer_id);
  	output_buffer_depth = getBufferDepth(model_id, output_buffer_id);
  	input_buffer_size = input_buffer_width * input_buffer_depth;
  	output_buffer_size = output_buffer_width * output_buffer_depth;
	//printf("[CORE] input_buffer_width = %d\n", input_buffer_width);
	//printf("[CORE] output_buffer_width = %d\n", output_buffer_width);
	//printf("[CORE] input_buffer_depth = %d\n", input_buffer_depth);
	//printf("[CORE] output_buffer_depth = %d\n", output_buffer_depth);
	//printf("[CORE] input_buffer_size = %d\n", input_buffer_size);
	//printf("[CORE] output_buffer_size = %d\n", output_buffer_size);

  	/* For all frame */
  	while (!is_finish_all_frame) {
    	switch (thread_id) {
    		case JPEG_THREAD_ID_CORE:
//			printf("[CORE] waitEvent JPEG_EVENT_START\n");
      		waitEvent(model_id, JPEG_EVENT_START);
      		break;
    		default:
      		std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
      		assert(0);    
     		break;
    	}
		total_out_data_size = 0;
//		scenario_id = 1;
		
    	if (scenario_id < g_parameters[instance_id][core_id].size()) {
			input_address_generator = g_parameters[instance_id][core_id].at(scenario_id)->input_address_generator;
      		output_address_generator = g_parameters[instance_id][core_id].at(scenario_id)->output_address_generator;
      		max_count = output_address_generator->size();
    	} else {
      		is_finish_all_frame = true;
      		break;
    	}
    	count = 0;
    	is_finish_one_frame = false;
		
//		printf("[CORE] max_count = %d\n", max_count);
		
//		waitCoreCycle(model_id, 10000);
//		waitEvent(model_id, JPEG_EVENT_START);
		
		/* 総転送量計算 */
		hdr_size = jpeg_local_parameters[instance_id][scenario_id].hdr_size;
		ftr_size = jpeg_local_parameters[instance_id][scenario_id].ftr_size;
		encode_size = jpeg_local_parameters[instance_id][scenario_id].output_total_size - hdr_size - ftr_size;
		remain_hdr_size = hdr_size;
		remain_ftr_size = ftr_size;
		remain_encode_size = encode_size;
//		printf("[CORE] remain_hdr_size = %d\n", remain_hdr_size);
//		printf("[CORE] remain_ftr_size = %d\n", remain_ftr_size);
//		printf("[CORE] remain_encode_size = %d\n", remain_encode_size);
    	/* Set core status BUSY */
      	//dumpSimulationTime(model_id);
//      	std::cout << __FUNCTION__ << " setThreadStatus(" << model_id << "," << thread_id << ","  << JPEG_CORE_STATUS_BUSY << ")" << std::endl;

		// set coop signal busy_out0
		if(jpeg_local_parameters[instance_id][scenario_id].coop == true){
		  
		  setBusyOutSignalWithInit(model_id,coop_id,1);
		  
		  std::cout << __FUNCTION__ << " core_id=" << core_id << " waitBusySignal at " << sc_time_stamp() << std::endl;
		  
		  // Wait Busy signal from COOP-model
		  while(!isBusy_opp) {
		    isBusy_opp = getBusyInSignal(model_id,coop_id);
		    waitAxiCycle(model_id, 1);
		  }
		  std::cout << __FUNCTION__ << " core_id=" << core_id << " BusySignal assert at " << sc_time_stamp() << ", loop exit." << std::endl;
		}

      	setThreadStatus(model_id, thread_id, JPEG_CORE_STATUS_BUSY);
      
		/* ヘッダ処理 */
		while(remain_hdr_size > 0){
			/* Write data into output buffer */
			waitCoreCycle(model_id, 1);
      		writeBuffer(model_id, output_buffer_id, data);
			total_out_data_size += JPEG_BUS_WIDTH;
			/* Get AXI write tansfers parameter */
        	output_address_generator->getParameterChannel(&AWADDR, &AWLEN, &location, &leflg, &reflg, &feflg, count);
//        	printf("[CORE] AWLEN = %d\n", AWLEN);
//		printf("[CORE] burst_count = %d\n", burst_count);
//		printf("[CORE] count = %d\n", count);
			burst_count += output_buffer_width / JPEG_BUS_WIDTH;
      		if (AWLEN < burst_count) {
       			++count;
        		burst_count = 0;
        	}
			
			/* 残りデータ量算出 */
			remain_hdr_size = remain_hdr_size - output_buffer_width;
//			printf("[CORE] remain_hdr_size = %d\n", remain_hdr_size);
			write_buffer_size = getWriteBufferSize(model_id, output_buffer_id);
//			printf("[CORE] write_buffer_size = %d\n", write_buffer_size);
			/* 空き容量チェック */
			if(write_buffer_size == (output_buffer_width * output_buffer_depth)){
//				printf("[CORE] switchWriteBuffer\n");
				switchWriteBuffer(model_id, output_buffer_id);
			}
			
			/* 出力左端補正ON */
			if(jpeg_local_parameters[instance_id][scenario_id].out_left_align == 1){
				transfer_size = JPEG_BUS_WIDTH * (AWLEN + 1);
				/* バースト転送サイズが残りバッファ容量を超える場合はみなしFull */
				if ( ((output_buffer_size - write_buffer_size) < transfer_size) && (burst_count == 0)) {
//          			printf("[CORE] switchWriteBuffer\n");
					switchWriteBuffer(model_id, output_buffer_id);
        		}
			}
			
		}
//		//printf("[CORE] 651\n");
		output_buffer_width = getBufferWidth(model_id, output_buffer_id);
  		output_buffer_depth = getBufferDepth(model_id, output_buffer_id);
  		output_buffer_size = output_buffer_width * output_buffer_depth;
		//printf("[CORE] output_buffer_width = %d\n", output_buffer_width);
		//printf("[CORE] output_buffer_depth = %d\n", output_buffer_depth);
		//printf("[CORE] output_buffer_size = %d\n", output_buffer_size);
    	if (scenario_id != 0) {
      		//dumpSimulationTime(model_id);
//      		std::cout << __FUNCTION__ << " switchReadBuffer(" << input_buffer_id << ")" << std::endl;
//			printf("[CORE] switchReadBuffer\n");
      		switchReadBuffer(model_id, JPEG_BUFFER_ID_IBUFY);
			switchReadBuffer(model_id, JPEG_BUFFER_ID_IBUFC);
    	}
    	
    	/* loop [全データ転送（フッター除く）] */
    	while (remain_encode_size != 0) {
			//printf("[CORE] 674\n");
      		bool is_switch_read_buffer = false;
      		bool is_switch_write_buffer = false;
      
#if 0
      std::cout << sc_time_stamp() << " remain_input_buffer_size= " << remain_input_buffer_size << std::endl;
      std::cout << sc_time_stamp() << " remain_output_buffer_size= " << remain_output_buffer_size << std::endl;
#endif
//			//printf("[CORE] 681\n");
      		/* Wait input buffer status FULL */
    		//dumpSimulationTime(model_id);
//    		std::cout << __FUNCTION__ << " waitReadBufferStatus(" << input_buffer_id << "," << JPEG_BUFFER_STATUS_FULL << ")" << std::endl;
//    		printf("[CORE] waitReadBufferStatus JPEG_BUFFER_STATUS_FULL start\n");
//			printf("[CORE] waitReadBufferStatus Y\n");
			waitReadBufferStatus(model_id, JPEG_BUFFER_ID_IBUFY, JPEG_BUFFER_STATUS_FULL);
//			printf("[CORE] waitReadBufferStatus JPEG_BUFFER_STATUS_FULL end\n");
 //   		//printf("[CORE] 686\n");
			/* データ量確認 */
			remain_input_y_buffer_size = getReadBufferSize(model_id, JPEG_BUFFER_ID_IBUFY);
			//printf("[CORE] remain_input_y_buffer_size = %d\n", remain_input_y_buffer_size);
			/* Wait input buffer status FULL */
    		//dumpSimulationTime(model_id);
 //   		std::cout << __FUNCTION__ << " waitReadBufferStatus(" << input_buffer_id << "," << JPEG_BUFFER_STATUS_FULL << ")" << std::endl;
//    		printf("[CORE] waitReadBufferStatus C\n");
			waitReadBufferStatus(model_id, JPEG_BUFFER_ID_IBUFC, JPEG_BUFFER_STATUS_FULL);
    		
			/* データ量確認 */
			remain_input_c_buffer_size = getReadBufferSize(model_id, JPEG_BUFFER_ID_IBUFC);
			//printf("[CORE] remain_input_c_buffer_size = %d\n", remain_input_c_buffer_size);
			
			/* 出力データ量計算 */
			write_data_size = (remain_input_y_buffer_size + remain_input_c_buffer_size) * jpeg_local_parameters[instance_id][scenario_id].comp_rate / 100;
			
			/* 空き容量チェック */
			write_buffer_size = getWriteBufferSize(model_id, output_buffer_id);
			//printf("[CORE] write_buffer_size = %d\n", write_buffer_size);
			
			/* loop [リードバッファ !=0] */
			while( (remain_input_y_buffer_size != 0) && (remain_input_c_buffer_size != 0) ){
				//printf("[CORE] 717 Get Y location\n");
				/* Get location */
        		input_address_generator->getParameterChannel(&ARADDR, &ARLEN, &location, &leflg, &reflg, &feflg, count_y);
//				//printf("[CORE] 697\n");
				/* バッファリード */
				readBuffer(model_id, JPEG_BUFFER_ID_IBUFY, data);
				read_exe_size = input_buffer_width;
				remain_input_y_buffer_size = remain_input_y_buffer_size - input_buffer_width;
				input_total_y_data += input_buffer_width;
//				printf("[CORE] remain_input_y_buffer_size = %d\n", remain_input_y_buffer_size);
//				printf("[CORE] input_total_y_data = %d\n", input_total_y_data);
				burst_y_count += input_buffer_width / JPEG_BUS_WIDTH;
      			if (ARLEN < burst_y_count) {
       				++count_y;
        			burst_y_count = 0;
        		}
				//printf("[CORE] count_y = %d\n", count_y);
				
//				//printf("[CORE] 709\n");
				//printf("[CORE] 735 Get C location\n");
				input_address_generator->getParameterChannel(&ARADDR, &ARLEN, &location, &leflg, &reflg, &feflg, count_c);
				
				/* バッファリード */
				if( (jpeg_local_parameters[instance_id][scenario_id].ifmt == 1) && (((location & 0x00FF) % 2) == 1) ){
					readBuffer(model_id, JPEG_BUFFER_ID_IBUFC, data);
					read_exe_size += input_buffer_width;
					
					burst_c_count += input_buffer_width / JPEG_BUS_WIDTH;
      				if (ARLEN < burst_c_count) {
       					++count_c;
        				burst_c_count = 0;
        			}
					
					remain_input_c_buffer_size = remain_input_c_buffer_size - input_buffer_width;
//					printf("[CORE] remain_input_c_buffer_size = %d\n", remain_input_c_buffer_size);
					input_total_c_data += input_buffer_width;
//					printf("[CORE] input_total_c_data = %d\n", input_total_c_data);
				}
				else if( (jpeg_local_parameters[instance_id][scenario_id].ifmt == 1) && (((location & 0x00FF) % 2) == 0) ){
					/* 偶数行はバッファリードしない */
				}
				else{
					readBuffer(model_id, JPEG_BUFFER_ID_IBUFC, data);
					read_exe_size += input_buffer_width;
					
					burst_c_count += input_buffer_width / JPEG_BUS_WIDTH;
      				if (ARLEN < burst_c_count) {
       					++count_c;
        				burst_c_count = 0;
        			}
					
					remain_input_c_buffer_size = remain_input_c_buffer_size - input_buffer_width;
//					printf("[CORE] remain_input_c_buffer_size = %d\n", remain_input_c_buffer_size);
					input_total_c_data += input_buffer_width;
//					printf("[CORE] input_total_c_data = %d\n", input_total_c_data);
				}
				//printf("[CORE] count_c = %d\n", count_c);
				
				//printf("[CORE] read_exe_size = %d\n", read_exe_size);
				//printf("[CORE] write_exe_size = %d\n", write_exe_size);
				/* 出力データ量加算 */
				write_exe_size += read_exe_size * jpeg_local_parameters[instance_id][scenario_id].comp_rate / 100;
				
				//printf("[CORE] jpeg_local_parameters[instance_id][scenario_id].core_pix = %d\n", jpeg_local_parameters[instance_id][scenario_id].core_pix);
				/* 処理性能分Wait */
				waitCoreCycle(model_id, 8/jpeg_local_parameters[instance_id][scenario_id].core_pix);
//				waitCoreCycle(model_id, jpeg_local_parameters[instance_id][scenario_id].core_pix);
				//printf("[CORE] wait end\n");
				/* opt [出力データ量＞バッファ幅] */
				if(write_exe_size >= output_buffer_width){
//					//printf("[CORE] 752\n");
					/* バッファ書き込み */
					writeBuffer(model_id, output_buffer_id, data);
					total_out_data_size += JPEG_BUS_WIDTH;
//					//printf("[CORE] 755\n");
					/* 出力データ量をバス幅分減算 */
					write_data_size -= output_buffer_width;
					write_exe_size -= output_buffer_width;
					remain_encode_size -= output_buffer_width;
					++count;
					//printf("[CORE] count = %d\n", count);
				}
//				//printf("[CORE] 697\n");
				/* 出力側端数チェック */
				write_buffer_size = getWriteBufferSize(model_id, output_buffer_id);
				//printf("[CORE] write_buffer_size = %d\n", write_buffer_size);
//				printf("[CORE] remain_encode_size = %d\n", remain_encode_size);
				if(remain_encode_size < 256){
//					printf("[CORE] remain_encode_size = %d\n", remain_encode_size);
//					printf("[CORE] input_total_y_data = %d\n", input_total_y_data);
//					printf("[CORE] input_total_c_data = %d\n", input_total_c_data);
//					printf("[CORE] write_buffer_size = %d\n", write_buffer_size);
//					printf("[CORE] total_out_data_size = %d\n", total_out_data_size);
				}
				if(write_buffer_size > (output_buffer_size - output_buffer_width)){
					//printf("[CORE] write_buffer_size = %d\n", write_buffer_size);
					//printf("[CORE] switchWriteBuffer start\n");
//					printf("[CORE] input_total_y_data = %d\n", input_total_y_data);
//					printf("[CORE] input_total_c_data = %d\n", input_total_c_data);
//					printf("[CORE] total_out_data_size = %d\n", total_out_data_size);
//					printf("[CORE] count = %d\n", count);
					/* 面切り替えを行う */
//					printf("[CORE] switchWriteBuffer\n");
					switchWriteBuffer(model_id, output_buffer_id);
					
					//printf("[CORE] switchWriteBuffer end\n");
				}
				/*
				if(remain_encode_size < 8){
					remain_encode_size = 0;
					break;
				}
				*/
			}
			
			/* リードバッファ面切り替え */
			/*
			if(remain_input_y_buffer_size == 0){
				switchReadBuffer(model_id, JPEG_BUFFER_ID_IBUFY);
			}
			if(remain_input_c_buffer_size == 0){
				switchReadBuffer(model_id, JPEG_BUFFER_ID_IBUFC);
			}
			*/
			if(remain_input_y_buffer_size == 0){
				if(input_total_y_data >= (jpeg_local_parameters[instance_id][scenario_id].jimgsh * jpeg_local_parameters[instance_id][scenario_id].jimgsv)){
					/* 入力データは全て使用したのでスイッチしない */
				}
				else{
//					printf("[CORE] switchReadBuffer C\n");
					switchReadBuffer(model_id, JPEG_BUFFER_ID_IBUFY);
				}
			}
			if(remain_input_c_buffer_size == 0){
				if(input_total_c_data >= (jpeg_local_parameters[instance_id][scenario_id].jimgsh * jpeg_local_parameters[instance_id][scenario_id].jimgsv)){
				}
				else{
//					printf("[CORE] switchReadBuffer C\n");
					switchReadBuffer(model_id, JPEG_BUFFER_ID_IBUFC);
				}
			}
			
//			printf("[CORE] input_total_y_data = %d\n", input_total_y_data);
//			printf("[CORE] input_total_c_data = %d\n", input_total_c_data);
//			printf("[CORE] total_out_data_size = %d\n", total_out_data_size);
//			printf("[CORE] count = %d\n", count);
		}
		
		input_total_y_data = 0;
		input_total_c_data = 0;
//		printf("[CORE] goto ftr\n");
		
//		waitAxiCycle(model_id, 10000);
//		sc_stop();
		
		/* loop [フッターデータ残り ＞ 0] */
		while(remain_ftr_size > 0){
			/* Write data into output buffer */
			waitCoreCycle(model_id, 1);
      		writeBuffer(model_id, output_buffer_id, data);
			total_out_data_size += JPEG_BUS_WIDTH;
//			printf("[CORE] total_out_data_size = %d\n", total_out_data_size);
			/* Get AXI write tansfers parameter */
        	output_address_generator->getParameterChannel(&AWADDR, &AWLEN, &location, &leflg, &reflg, &feflg, count);
        	
			burst_count += output_buffer_width / JPEG_BUS_WIDTH;
      		if (AWLEN < burst_count) {
       			++count;
        		burst_count = 0;
        	}
			
			/* 残りデータ量算出 */
			remain_ftr_size = remain_ftr_size - output_buffer_width;
			
			write_buffer_size = getWriteBufferSize(model_id, output_buffer_id);
			
			/* 空き容量チェック */
			if(write_buffer_size == output_buffer_size){
				switchWriteBuffer(model_id, output_buffer_id);
			}
		}
		
		//printf("[CORE] Flash final data\n");
		/* Flash final data */
    	if(write_buffer_size == output_buffer_size){
		}
		else{
			switchWriteBuffer(model_id, output_buffer_id);
    	}
    	++scenario_id;
    	if (g_parameters[instance_id][core_id].size() <= scenario_id) {
      		is_finish_all_frame = true;
    	}
  	}

  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " finish" << std::endl;
}

void JPEG_SubScenarioAw(unsigned int model_id, unsigned int thread_id) {
  	unsigned int AWID = 0;
  	unsigned long AWADDR;
  	unsigned int AWLEN;
  	unsigned int AWSIZE = 0x3; /* 8-Byte*/
  	unsigned int AWBURST = 1; /* INCR */
  	unsigned int AWLOCK = 0;
  	unsigned int AWCACHE = 0;
  	unsigned int AWPROT = 0;
  	unsigned int AWUSER = 0;

  	unsigned int location;
  	unsigned int leflg;
  	unsigned int reflg;
  	unsigned int feflg;
  	unsigned int count;
  	unsigned int max_count;

  	unsigned int axi_if_id;
  	unsigned int output_buffer_id;
  	unsigned int core_id;

  	unsigned int transfer_size;
  	AddressGenerator *output_address_generator;

  	unsigned int output_buffer_size;
  	unsigned int remain_output_buffer_size ;
  	unsigned int processed_data_size = 0;

  	unsigned int scenario_id = 0;
  	bool is_finish_one_frame;
  	bool is_finish_all_frame = false;

	unsigned int instance_id;
	instance_id  = getInstanceNumber(model_id);

  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " start" << std::endl;
//	//printf("0\n");
  	/* Make each channel parameters */
  	switch (thread_id) {
  		case JPEG_THREAD_ID_AW:
    	AWID = 0;
    	axi_if_id = 0;
    	output_buffer_id = JPEG_BUFFER_ID_OBUF;
    	core_id = 0;
    	break;
  		default:
    	std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
   	 	assert(0);    
    	break;
  	}
	
//	printf("[AW] g_parameters[core_id].size() == %d\n", g_parameters[core_id].size());
	
//  	//printf("002\n");
  	/* For all frame */
  	while (!is_finish_all_frame) {
   		/* Wait startup event &  Make each channel parameters */
    	switch (thread_id) {
    		case JPEG_THREAD_ID_AW:
      		waitEvent(model_id, JPEG_EVENT_START);
      		break;
    		default:
      		std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
      		assert(0);    
      		break;
    	}
//		//printf("01\n");
		/* 出力バッファFULL待ち */
		//dumpSimulationTime(model_id);
//		std::cout << __FUNCTION__ << " waitReadBufferStatus(" << output_buffer_id << "," << JPEG_BUFFER_STATUS_FULL << ")" << std::endl;
		waitReadBufferStatus(model_id, output_buffer_id, JPEG_BUFFER_STATUS_FULL);
//		//printf("2\n");
    	if (scenario_id < g_parameters[instance_id][core_id].size()) {
      		output_address_generator = g_parameters[instance_id][core_id].at(scenario_id)->output_address_generator;
      		max_count = output_address_generator->size();
    	} else {
			is_finish_all_frame = true;
      		break;
    	}
//		printf("[AW] max_count = %d\n", max_count);
    	count = 0;
    	is_finish_one_frame = false;
//		//printf("3\n");
    	/* For 1 frame */
    	while (!is_finish_one_frame) {
      		/* Get data size */
      		remain_output_buffer_size = getReadBufferSize(model_id, output_buffer_id);
//			printf("[AW] 920 remain_output_buffer_size = %d\n", remain_output_buffer_size);
		notifyEvent(model_id, JPEG_EVENT_KICK_WCH);
//     		//printf("4\n");
      		/* While buffer is not EMPTY */
      		while (remain_output_buffer_size != 0) {
       			/* Get AWADDR */
        		output_address_generator->getParameterChannel(&AWADDR, &AWLEN, &location, &leflg, &reflg, &feflg, count);
        		//printf("5\n");
			//printf("[AW] AWADDR = 0x%08x\n", AWADDR);
			//printf("[AW] AWLEN = %d\n", AWLEN);
        		/* Culcurate WDATAs size */
        		transfer_size = JPEG_BUS_WIDTH * (AWLEN + 1);
 //       		printf("[AW] remain_output_buffer_size = %d\n", remain_output_buffer_size);
//				printf("[AW] transfer_size = %d\n", transfer_size);
        		/* Check buffer size to make AXI write transaction */
        		if (remain_output_buffer_size < transfer_size) {
          			break;
        		}
#if 0
        std::cout << __FUNCTION__ << " remain_output_buffer_size= " << remain_output_buffer_size << std::endl;
#endif
//        		//printf("6\n");
        		/* Make AW transaction */
        		//dumpSimulationTime(model_id);
//        		std::cout << __FUNCTION__ << " sendAw(" << axi_if_id << ")" << std::endl;
        		sendAw(model_id, axi_if_id, AWID, AWADDR, AWLEN, AWSIZE, AWBURST, AWLOCK, AWCACHE, AWPROT, AWUSER);
        
        		/* Culcurate remain buffer size */
        		remain_output_buffer_size -= transfer_size;
//        		printf("[AW] count = %d\n", count);
				
        		/* Culcurate processed data size */
        		processed_data_size += transfer_size;
        		++count;
        		//printf("[AW] max_count = %d\n", max_count);
//				printf("[AW] AWADDR = 0x%08x\n", AWADDR);
//				printf("[AW] processed_data_size = %d\n", processed_data_size);
        		/* Check all transfer is finish or not */
//				printf("[AW] max_count == %d\n", max_count);
//				printf("[AW] count == %d\n", count);
//				printf("[AW] remain_output_buffer_size == %d\n", remain_output_buffer_size);
        		if (max_count <= count) {
          			is_finish_one_frame = true;
//					remain_output_buffer_size = 0;
          			break;
        		}
#if 0
        std::cout << __FUNCTION__ << " leflg=" << leflg << std::endl;
#endif
        		//printf("[AW] reflg = %d\n", reflg);
        		/* Check line end flag */
				if (reflg == 1) {
          			break;
        		}
      		}
      		
			if(is_finish_one_frame == true){
				break;
			}
      		/* Wait buffer switching */
			//printf("[AW] waitReadBufferStatus\n");
      		//dumpSimulationTime(model_id);
//      		std::cout << __FUNCTION__ << " waitReadBufferStatus(" << output_buffer_id << "," << JPEG_BUFFER_STATUS_EMPTY << ")" << std::endl;
      		waitReadBufferStatus(model_id, output_buffer_id, JPEG_BUFFER_STATUS_FULL);
			//printf("[AW] waitReadBufferStatus END\n");
			
    	}
		
    	++scenario_id;
//		printf("[AW] g_parameters[core_id].size() == %d\n", g_parameters[core_id].size());
//		printf("[AW] scenario_id == %d\n", scenario_id);
//		printf("[AW] is_finish_all_frame == %d\n", is_finish_all_frame);
    	if (g_parameters[instance_id][core_id].size() <= scenario_id) {
      		is_finish_all_frame = true;
    	}
  	}
	
	//printf("[AW] processed_data_size == %d\n", processed_data_size);
	
  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " finish" << std::endl;
}

void JPEG_SubScenarioW(unsigned int model_id, unsigned int thread_id) {
  	unsigned int WID = 0;
  	unsigned int WLAST;
  	unsigned char wdata[JPEG_BUS_WIDTH];  
  	unsigned char wstrb[JPEG_BUS_WIDTH];  

  	unsigned long AWADDR;
  	unsigned int AWLEN;

  	unsigned int location;
  	unsigned int leflg;
  	unsigned int reflg;
  	unsigned int feflg;
  	unsigned int count;
  	unsigned int max_count;

  	unsigned int axi_if_id;
  	unsigned int output_buffer_id;
  	unsigned int core_id;
  	unsigned int output_signal_id;

  	unsigned int transfer_size;
  	AddressGenerator *output_address_generator;

  	unsigned int output_buffer_size;
  	unsigned int remain_output_buffer_size ;
  	unsigned int processed_data_size = 0;
	
  	unsigned int scenario_id = 0;
  	bool is_finish_one_frame;
  	bool is_finish_all_frame = false;

	unsigned int instance_id;
	instance_id  = getInstanceNumber(model_id);

	// initialize variables
	for (int i = 0; i < JPEG_BUS_WIDTH; i++) {
	  wstrb[i] = 0xFF;
	  wdata[i] = 0x00;
	}
	for (int i = 0; i < JPEG_INSTANCE_MAX; i++) {
	  is_finish_scenario[i][0] = false;
	  is_finish_scenario[i][1] = false;

	}
  	//dumpSimulationTime(model_id);
  	std::cout << __FUNCTION__ << " start" << std::endl;

  	/* Wait startup event &  Make each channel parameters */
  	switch (thread_id) {
  		case JPEG_THREAD_ID_W:
    	WID = 0;
    	axi_if_id = 0;
    	output_buffer_id = JPEG_BUFFER_ID_OBUF;
    	core_id = 0;
    	output_signal_id = JPEG_OUTPUT_SIGNAL;
    	break;
  		default:
    	std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
    	assert(0);    
    	break;
  	}

  	/* For all frame */
  	while (!is_finish_all_frame) {
    	/* Wait startup event &  Make each channel parameters */
    	switch (thread_id) {
    		case JPEG_THREAD_ID_W:
      		waitEvent(model_id, JPEG_EVENT_START);
      		break;
    		default:
//      		std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
      		assert(0);    
      		break;
    	}

    	if (scenario_id < g_parameters[instance_id][core_id].size()) {
      		output_address_generator = g_parameters[instance_id][core_id].at(scenario_id)->output_address_generator;
      		max_count = output_address_generator->size();
    	} 
		else {
      		is_finish_all_frame = true;
      		break;
    	}
    	count = 0;
    	is_finish_one_frame = false;
	//		printf("[W] max_count = %d\n", max_count);

    	if (scenario_id != 0) {
      		//dumpSimulationTime(model_id);
      		std::cout << __FUNCTION__ << " switchReadBuffer(" << output_buffer_id << ")" << std::endl;
      		switchReadBuffer(model_id, output_buffer_id);
    	}

    	/* For all transfer */
    	while (!is_finish_one_frame) {
	  //printf("[W] waitEvent JPEG_EVENT_KICK_WCH\n");
	  waitEvent(model_id, JPEG_EVENT_KICK_WCH);
	  //printf("[W] waitReadBufferStatus Start\n");
	  /* Wait buffer status FULL */
	  //dumpSimulationTime(model_id);
	  //std::cout << __FUNCTION__ << " waitReadBufferStatus(" << output_buffer_id << "," << JPEG_BUFFER_STATUS_FULL << ")" << std::endl;
	  waitReadBufferStatus(model_id, output_buffer_id, JPEG_BUFFER_STATUS_FULL);
	  //printf("[W] waitReadBufferStatus End\n");
	  
	  /* Get data size */
	  remain_output_buffer_size = getReadBufferSize(model_id, output_buffer_id);
	  //printf("[W] remain_output_buffer_size = %d\n", remain_output_buffer_size);
#if 0
	  std::cout << sc_time_stamp() << " remain_output_buffer_size= " << remain_output_buffer_size << std::endl;
#endif
	  
	  /* While buffer is not EMPTY */
	  while (remain_output_buffer_size != 0) {
	    /* Get AWLEN */
	    output_address_generator->getParameterChannel(&AWADDR, &AWLEN, &location, &leflg, &reflg, &feflg, count);
	    
	    /* Culcurate WDATAs size */ 
	    transfer_size = JPEG_BUS_WIDTH * (AWLEN + 1);
	    //printf("[W] remain_output_buffer_size = %d\n", remain_output_buffer_size);
	    //printf("[W] transfer_size = %d\n", transfer_size);
	    //printf("[W] AWLEN = %d\n", AWLEN);
	    /* Check buffer size to make AXI write transaction */
	    if (remain_output_buffer_size < transfer_size) {
	      break;
	    }
	    //printf("[W] AWLEN = %d\n", AWLEN);
	    /* Make W transaction */
	    for (unsigned int i = 0; i < AWLEN + 1; ++i) { 
	      readBuffer(model_id, output_buffer_id, wdata);
	      if (i == AWLEN) {
		WLAST = 1;
	      } 
	      else {
		WLAST = 0;
	      }
#if 0
	      std::cout << __FUNCTION__ << " remain_output_buffer_size= " << remain_output_buffer_size << std::endl;
#endif
	      //dumpSimulationTime(model_id);
	      //std::cout << __FUNCTION__ << " sendW(" << axi_if_id << "," << WID << "," << WLAST << ")" << std::endl;
	      sendW(model_id, axi_if_id, WID, WLAST, wdata, wstrb);
	    }
	    
	    /* Culcurate remain buffer size */ 
	    remain_output_buffer_size -= transfer_size;
	    
	    /* Culcurate processed data size */
	    processed_data_size += transfer_size;
	    ++count;
	    //printf("[W] processed_data_size = %d\n", processed_data_size);
	    //printf("[W] count = %d\n", count);
	    
	    /* Check all transfer is finish or not */
	    if (max_count <= count) {
	      is_finish_one_frame = true;
	      break;
	    }
	    
	    /* Check line end flag */
	    if (leflg == 1) {
	      break;
	    }
	  }    
	  
	  /* Buffer switch latency (for test) */
	  waitAxiCycle(model_id, 1);
	  
	  /* Switch output buffer */                                                                                             
	  if (!is_finish_one_frame) {
	    //dumpSimulationTime(model_id);
	    //        		std::cout << __FUNCTION__ << " switchReadBuffer(" << output_buffer_id << ")" << std::endl;
	    switchReadBuffer(model_id, output_buffer_id);
	  }
    	}
	
    	/* Assert finish signal */
    	waitAxiCycle(model_id, 200);
	
    	//dumpSimulationTime(model_id);
    	std::cout << __FUNCTION__ << " setOutputSignal(" << output_signal_id << ", 1)" << std::endl;
    	setOutputSignal(model_id, output_signal_id, 1);
    
    	waitAxiCycle(model_id, 1);
    
    	//dumpSimulationTime(model_id);
    	std::cout << __FUNCTION__ << " setOutputSignal(" << output_signal_id << ", 0)" << std::endl;
    	setOutputSignal(model_id, output_signal_id, 0);

    	waitAxiCycle(model_id, 1);

    	++scenario_id;
    	if (g_parameters[instance_id][core_id].size() <= scenario_id) {
      		is_finish_all_frame = true;
    	}
	//	printf("[W] scenario_id = %d\n", scenario_id);
	//	printf("[W] g_parameters[core_id].size() = %d\n", g_parameters[instance_id][core_id].size());
	//	printf("[W] is_finish_all_frame = %d\n", is_finish_all_frame);

  	}
	
//	printf("[W] 1184\n");
  	switch (thread_id) {
	case JPEG_THREAD_ID_W:
	  is_finish_scenario[instance_id][0] = true;
	  is_finish_scenario[instance_id][1] = true;
	  break;
	default:
	  std::cout << "[ERROR] no thread scenario (thread_id=" << thread_id << ")" << endl;
	  assert(0);    
	  break;
  	}
	
  	bool is_finish_all_scenario = true;
  	for (unsigned int i = 0; i < 2; ++i) {
	  if (is_finish_scenario[instance_id][i] == false) {
	    is_finish_all_scenario = false;
	  }
  	}
	
	std::cout << __FUNCTION__ << " finish" << std::endl;
	
  	if (is_finish_all_scenario) {
	  dumpSimulationTime(model_id);
	  
	  //dumpSimulationTime(model_id);
	  std::cout << __FUNCTION__ << " disableLogging()" << std::endl;
	  disableLogging(model_id);
	  
	  //dumpSimulationTime(model_id);
	  std::cout << __FUNCTION__ << " finish all scenario" << std::endl;
	}
}

void JPEG_SubScenarioInterrupt0(unsigned int model_id) {
  char file_name[255];
  sprintf(file_name, "JPEG_scenario_parameter_%d.csv", model_id);
  //dumpSimulationTime(model_id);
  std::cout << "SubScenarioInterrupt0" << std::endl;
  
  /* Read parameter file */
  if (getInterruptSignal(model_id, 0) == 1) {
    /* Read scenario parameter file (only once) */
    //    std::cout << __FUNCTION__ << " read ParameterFile" << std::endl;
    JPEG_readScenarioParameterFile(model_id, file_name);
  }
  /* Notify startup event */
  //  std::cout << __FUNCTION__ << "model_id = " << model_id << " notifyEvent" << std::endl;
  notifyEvent(model_id, JPEG_EVENT_START);
  
}

void
JPEG_SubScenarioInterrupt1(unsigned int model_id) {
  //dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << std::endl;
}

void
JPEG_SubScenarioInterrupt2(unsigned int model_id) {
  //dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << std::endl;
}

void
JPEG_SubScenarioInterrupt3(unsigned int model_id) {
  //dumpSimulationTime(model_id);
  std::cout << __FUNCTION__ << std::endl;
}

void
JPEG_readScenarioParameterFile(unsigned int model_id, const char *file_name) {
  unsigned int core_id = 0;
  unsigned int instance_id;
  instance_id  = getInstanceNumber(model_id);

  	if (g_parameters[instance_id][core_id].empty()) {
	    JPEG_ScenarioParameter *parameter;
    	CsvParser csv;
		    
		csv.initialize(file_name);    
    	
		printf("csv.getRowSize() = %d\n", csv.getRowSize());
		
    	for (unsigned int row = 0; row < csv.getRowSize(); ++row) {
      		if (SizeOfJPEGScenarioParameterFormat <= csv.getColumnSize(row)) {
      			bool left_align;
				
				/* Y成分とC成分用に分けてaddress_generatorへセットする */
				while(core_id < 2){
        			parameter = new JPEG_ScenarioParameter;

					/* パラメータ読み取り */
        			parameter->ifmt = csv.getUint32(row, IFMT);
					parameter->rbsize = csv.getUint32(row, RBSIZE);
					parameter->wbsize = csv.getUint32(row, WBSIZE);
					parameter->jimgsh = csv.getUint32(row, JIMGSH);
					parameter->jimgsv = csv.getUint32(row, JIMGSV);
					parameter->jimgay = csv.getUint32(row, JIMGAY);
					parameter->jimgacb = csv.getUint32(row, JIMGACB);
					parameter->jcoda = csv.getUint32(row, JCODA);
					parameter->jimgygh = csv.getUint32(row, JIMGYGH);
					parameter->jimgcgh = csv.getUint32(row, JIMGCGH);
					parameter->hdr_size = csv.getUint32(row, HDR_SIZE);
					parameter->ftr_size = csv.getUint32(row, FTR_SIZE);
					parameter->coop = csv.getUint32(row, COOP);
					parameter->core_pix = csv.getUint32(row, CORE_PIX);
					parameter->axi_if_y = csv.getUint32(row, AXI_IF_Y);
					parameter->axi_if_c = csv.getUint32(row, AXI_IF_C);
					parameter->out_left_align = csv.getUint32(row, OUT_LEFT_ALIGN);
					parameter->comp_rate = csv.getUint32(row, COMP_RATE);
					if (csv.getColumnSize(row) > SizeOfJPEGScenarioParameterFormat) {
					  parameter->sram_mode = csv.getUint32(row, SRAM_MODE);
					  parameter->sram_saddr = csv.getUint32(row, SRAM_SADDR);
					  parameter->sram_size = csv.getUint32(row, SRAM_SIZE);
					} else {
					  parameter->sram_mode = 0;
					  parameter->sram_saddr = 0;
					  parameter->sram_size = 0;
					}
				
					/* 入力水平サイズを8倍数に補正 */
					if( (parameter->jimgsh % 8) != 0 ){
						parameter->jimgsh = parameter->jimgsh / 8;
						parameter->jimgsh = parameter->jimgsh * 8;
						parameter->jimgsh = parameter->jimgsh + 8;
					}
				
					parameter->base_hsize = JPEG_BASE_HSIZE;
					parameter->base_vsize = JPEG_BASE_VSIZE;
				
//					printf("row = %d\n", row);
//					printf("parameter->jimgsv = %d\n", parameter->jimgsv);
								
					if( (core_id == 0) && (parameter->ifmt == 1) ){
						/* YCbCr420 Y成分 */
						parameter->base_vsize = JPEG_BASE_VSIZE * 2;
					}
					if(core_id == 0){
						/* Y成分 */
						parameter->input_addr = parameter->jimgay;
						parameter->input_gsize = parameter->jimgygh;
					}
					else{
						/* C成分 */
						parameter->input_addr = parameter->jimgacb;
						parameter->input_gsize = parameter->jimgcgh;
					}
					if(parameter->rbsize == 0){
						parameter->input_length = 15;
					}
					else if(parameter->rbsize == 1){
						parameter->input_length = 31;
					}
					if(parameter->wbsize == 0){
						parameter->output_length = 15;
					}
					else if(parameter->wbsize == 1){
						parameter->output_length = 31;
					}
					
					if(parameter->ifmt == 0){
						parameter->input_total_size = parameter->jimgsh * parameter->jimgsv * 2;
					}
					else if(parameter->ifmt == 1){
						parameter->input_total_size = parameter->jimgsh * parameter->jimgsv * 3 / 2;
					}
				
					//parameter->output_total_size = (parameter->input_total_size * parameter->comp_rate) / 100;
					parameter->output_total_size = ((parameter->input_total_size * parameter->comp_rate) / 100) + parameter->hdr_size + parameter->ftr_size;
					
					/* 圧縮量を8の倍数で切り上げ */
					parameter->output_total_size = parameter->output_total_size / 8;
					parameter->output_total_size = parameter->output_total_size * 8;
//					parameter->output_total_size = parameter->output_total_size + 8;
				
//        		if (csv.getUint32(row, IN_LEFT_ALIGN) == 0) {
//          			left_align = false;
//        		}
//			 	else {
//          			left_align = true;
//       		}
					//printf("parameter->input_addr = %x\n", parameter->input_addr);
        			parameter->input_address_generator =  new AddressGenerator(4,
											   parameter->input_addr,
											   parameter->input_gsize,
											   parameter->jimgsh,
											   parameter->jimgsv,
											   parameter->base_hsize,
											   parameter->base_vsize,
											   0,
											   JPEG_BUS_SIZE,
											   parameter->input_length,
											   false,
											   ALIGN_4K,
											   parameter->sram_mode,
											   parameter->sram_saddr,
											   parameter->sram_size
											   );
				printf("sram_mode[%d] sram addr[%08x]size[%08x]\n",parameter->sram_mode,parameter->sram_saddr,parameter->sram_size);
        			if (csv.getUint32(row, OUT_LEFT_ALIGN) == 0) {
            			left_align = false;
        			} 
					else {
          				left_align = true;
        			}
					//printf("left_align = %d\n", left_align);
					parameter->output_address_generator =  new AddressGenerator(1,
                                                                    parameter->jcoda,
                                                                    0,
                                                                    parameter->output_total_size,
                                                                    0,
                                                                    0,
                                                                    0,
                                                                    0,
                                                                    JPEG_BUS_SIZE,
                                                                    parameter->output_length,
                                                                    left_align);
        			g_parameters[instance_id][core_id].push_back(parameter);
					//printf("1251 parameter->input_addr = %x\n", parameter->input_addr);
					//printf("1251 core_id = %d\n", core_id);
					
					core_id++;
					
					/* グローバル変数 */
					jpeg_local_parameters[instance_id][row].ifmt = parameter->ifmt;
					jpeg_local_parameters[instance_id][row].rbsize = parameter->rbsize;
					jpeg_local_parameters[instance_id][row].wbsize = parameter->wbsize;
					jpeg_local_parameters[instance_id][row].jimgsh = parameter->jimgsh;
					jpeg_local_parameters[instance_id][row].jimgsv = parameter->jimgsv;
					jpeg_local_parameters[instance_id][row].jimgay = parameter->jimgay;
					jpeg_local_parameters[instance_id][row].jimgacb = parameter->jimgacb;
					jpeg_local_parameters[instance_id][row].jcoda = parameter->jcoda;
					jpeg_local_parameters[instance_id][row].jimgygh = parameter->jimgygh;
					jpeg_local_parameters[instance_id][row].jimgcgh = parameter->jimgcgh;
					jpeg_local_parameters[instance_id][row].hdr_size = parameter->hdr_size;
					jpeg_local_parameters[instance_id][row].ftr_size = parameter->ftr_size;
					jpeg_local_parameters[instance_id][row].coop = parameter->coop;
					jpeg_local_parameters[instance_id][row].core_pix = parameter->core_pix;
					jpeg_local_parameters[instance_id][row].axi_if_y = parameter->axi_if_y;
					jpeg_local_parameters[instance_id][row].axi_if_c = parameter->axi_if_c;
					jpeg_local_parameters[instance_id][row].out_left_align = parameter->out_left_align;
					jpeg_local_parameters[instance_id][row].comp_rate = parameter->comp_rate;
					jpeg_local_parameters[instance_id][row].base_hsize = parameter->base_hsize;
					jpeg_local_parameters[instance_id][row].base_vsize = parameter->base_vsize;
					jpeg_local_parameters[instance_id][row].input_addr = parameter->input_addr;
					jpeg_local_parameters[instance_id][row].input_gsize = parameter->input_gsize;
					jpeg_local_parameters[instance_id][row].input_length = parameter->input_length;
					jpeg_local_parameters[instance_id][row].output_length = parameter->output_length;
					jpeg_local_parameters[instance_id][row].input_total_size = parameter->input_total_size;
					jpeg_local_parameters[instance_id][row].output_total_size = parameter->output_total_size;
					
				}
				g_param[instance_id][row].h_mesh = (parameter->jimgsh + parameter->base_hsize - 1)/(parameter->base_hsize);
				printf("hmesh (%d)\n", g_param[instance_id][row].h_mesh);
				
				core_id = 0;
				
				printf("jpeg_local_parameters.ifmt (%d)\n", jpeg_local_parameters[instance_id][row].ifmt);
				printf("jpeg_local_parameters.rbsize (%d)\n", jpeg_local_parameters[instance_id][row].rbsize);
				printf("jpeg_local_parameters.wbsize (%d)\n", jpeg_local_parameters[instance_id][row].wbsize);
				printf("jpeg_local_parameters.jimgsh (%d)\n", jpeg_local_parameters[instance_id][row].jimgsh);
				printf("jpeg_local_parameters.jimgsv (%d)\n", jpeg_local_parameters[instance_id][row].jimgsv);
				printf("jpeg_local_parameters.jimgay (0x%x)\n", jpeg_local_parameters[instance_id][row].jimgay);
				printf("jpeg_local_parameters.jimgacb (0x%x)\n", jpeg_local_parameters[instance_id][row].jimgacb);
				printf("jpeg_local_parameters.jcoda (0x%x)\n", jpeg_local_parameters[instance_id][row].jcoda);
				printf("jpeg_local_parameters.jimgygh (%d)\n", jpeg_local_parameters[instance_id][row].jimgygh);
				printf("jpeg_local_parameters.jimgcgh (%d)\n", jpeg_local_parameters[instance_id][row].jimgcgh);
				printf("jpeg_local_parameters.hdr_size (%d)\n", jpeg_local_parameters[instance_id][row].hdr_size);
				printf("jpeg_local_parameters.ftr_size (%d)\n", jpeg_local_parameters[instance_id][row].ftr_size);
				printf("jpeg_local_parameters.coop (%d)\n", jpeg_local_parameters[instance_id][row].coop);
				printf("jpeg_local_parameters.core_pix (%d)\n", jpeg_local_parameters[instance_id][row].core_pix);
				printf("jpeg_local_parameters.axi_if_y (%d)\n", jpeg_local_parameters[instance_id][row].axi_if_y);
				printf("jpeg_local_parameters.axi_if_c (%d)\n", jpeg_local_parameters[instance_id][row].axi_if_c);
				printf("jpeg_local_parameters.out_left_align (%d)\n", jpeg_local_parameters[instance_id][row].out_left_align);
				printf("jpeg_local_parameters.comp_rate (%d)\n", jpeg_local_parameters[instance_id][row].comp_rate);
				printf("jpeg_local_parameters.base_hsize (%d)\n", jpeg_local_parameters[instance_id][row].base_hsize);
				printf("jpeg_local_parameters.base_vsize (%d)\n", jpeg_local_parameters[instance_id][row].base_vsize);
				printf("jpeg_local_parameters.input_addr (0x%x)\n", jpeg_local_parameters[instance_id][row].input_addr);
				printf("jpeg_local_parameters.input_gsize (%d)\n", jpeg_local_parameters[instance_id][row].input_gsize);
				printf("jpeg_local_parameters.input_length (%d)\n", jpeg_local_parameters[instance_id][row].input_length);
				printf("jpeg_local_parameters.output_length (%d)\n", jpeg_local_parameters[instance_id][row].output_length);
				printf("jpeg_local_parameters.input_total_size (%d)\n", jpeg_local_parameters[instance_id][row].input_total_size);
				printf("jpeg_local_parameters.output_total_size (%d)\n\n", jpeg_local_parameters[instance_id][row].output_total_size);
			}
    	}
  	}
	//printf("\n");
	
	
#if 0
  std::cout << "g_parameters[" << core_id << "].size() = " << g_parameters[instance_id][core_id].size() << std::endl;
#endif
}
