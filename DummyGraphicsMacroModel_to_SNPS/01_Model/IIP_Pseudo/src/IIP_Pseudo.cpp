/*
*    Class implementation of the SoC Designer component <IIP_Pseudo>
*
*    This code has been generated by the SoC Designer Component Wizard.
*    Copyright (c)  2008-2010 Carbon Design Systems Inc.
*
* THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF CARBON
* DESIGN SYSTEMS, INC.  PERMISSION IS HEREBY GRANTED TO USE, MODIFY, AND/OR COPY
* THIS SOFTWARE FOR INTERNAL USE ONLY PROVIDED THAT THE ABOVE COPYRIGHT NOTICE
* APPEARS IN ALL COPIES OF THIS SOFTWARE.
*/

#include "IIP_Pseudo.h"

#include <iostream>
#include <cstdio>

#include "ProtocolUtils.h"

#include "DummyGraphicsMacroModel_AXI_Master_Port.h"
#include "DummyGraphicsMacroModel_interrupt_SS.h"
#include "DummyGraphicsMacroModel_reset_x_SS.h"
#include "DummyGraphicsMacroModel_data_in_SS.h"
#include "DummyGraphicsMacroModel_busy_in_SS.h"

IIP_Pseudo::IIP_Pseudo(CASIModuleIF* c, const string &s) : CASIModule(c, s)
{
	uint32_t i;
	char strBuffer[1000];

  for (unsigned int i = 0; i < 1; ++i) {
    std::stringstream ss;
    std::string port_name;

    ss << "AXIv2_master_" << i;
    ss >> port_name;
    AXIv2_master_TMaster[i] = new DummyGraphicsMacroModel_AXI_Master_Port<IIP_Pseudo>( this, port_name );
    initAXIv2TransactionPort((CASITransactionMasterIF*)AXIv2_master_TMaster[i]);
    registerPort( AXIv2_master_TMaster[i], port_name.c_str() );
  }

	// interrupt x 4
	for ( i = 0; i < 4; i++ )
	{
		sprintf ( strBuffer, "interrupt%d", i );
		DummyGraphicsMacroModel_interrupt_SSlave[i] = new DummyGraphicsMacroModel_interrupt_SS<IIP_Pseudo>( this, i );
		registerPort( DummyGraphicsMacroModel_interrupt_SSlave[i], strBuffer );
	}

	// output x 4
	for ( i = 0; i < 4; i++ )
	{
		sprintf ( strBuffer, "output%d", i );
		output_SMaster[i] = new sc_port<CASISignalIF>(this, strBuffer );
		sprintf ( strBuffer, "output%d", i );
		initSignalPort((CASISignalMasterIF*)output_SMaster[i]);
		registerPort( output_SMaster[i], strBuffer );
	}

  for ( i = 0; i < 2; i++ )
  {
    // input
    sprintf ( strBuffer, "data_in%d", i );
    DummyGraphicsMacroModel_data_in_SSlave[i] = new DummyGraphicsMacroModel_data_in_SS<IIP_Pseudo>( this, i );
    registerPort( DummyGraphicsMacroModel_data_in_SSlave[i], strBuffer );
    
    sprintf ( strBuffer, "busy_in%d", i );
    DummyGraphicsMacroModel_busy_in_SSlave[i] = new DummyGraphicsMacroModel_busy_in_SS<IIP_Pseudo>( this, i );
    registerPort( DummyGraphicsMacroModel_busy_in_SSlave[i], strBuffer );
    
    // output
    sprintf ( strBuffer, "data_out%d", i );
    data_out_SMaster[i] = new sc_port<CASISignalIF>(this, strBuffer );
    initSignalPort((CASISignalMasterIF*)data_out_SMaster[i]);
    registerPort( data_out_SMaster[i], strBuffer );
    
    sprintf ( strBuffer, "busy_out%d", i );
    busy_out_SMaster[i] = new sc_port<CASISignalIF>(this, strBuffer );
    initSignalPort((CASISignalMasterIF*)busy_out_SMaster[i]);
    registerPort( busy_out_SMaster[i], strBuffer );
  }
  
	DummyGraphicsMacroModel_reset_x_SSlave = new DummyGraphicsMacroModel_reset_x_SS<IIP_Pseudo>( this );
	registerPort( DummyGraphicsMacroModel_reset_x_SSlave, "reset_x" );

	// Clocking the components
	SC_MX_CLOCKED();
	// Register ourself as a clock slave port.
	registerPort( dynamic_cast< CASIClockSlaveIF* >( this ), "clk-in");

	// Place parameter definitions here:
  defineParameter( "Enable Debug Messages",                     "false", eslapi::CASI_PARAM_BOOL);
	defineParameter( "model_id",                                      "0", eslapi::CASI_PARAM_VALUE,  0);
	defineParameter( "number_of_thread",                              "1", eslapi::CASI_PARAM_VALUE,  0);
	defineParameter( "number_of_read_outstanding",                    "4", eslapi::CASI_PARAM_VALUE,  0);
	defineParameter( "number_of_write_outstanding",                   "4", eslapi::CASI_PARAM_VALUE,  0);
	defineParameter( "no_r_receive",                              "false", eslapi::CASI_PARAM_BOOL,   0);
	defineParameter( "no_b_receive",                              "false", eslapi::CASI_PARAM_BOOL,   0);
	defineParameter( "time_unit",                                 "SC_PS", eslapi::CASI_PARAM_STRING, 0);
	defineParameter( "axi_clock",                                  "5000", eslapi::CASI_PARAM_VALUE,  0);
	defineParameter( "core_clock",                                 "4250", eslapi::CASI_PARAM_VALUE,  0);
	defineParameter( "buffer_parameter_file_name",                     "", eslapi::CASI_PARAM_STRING, 0);
	defineParameter( "fifo_parameter_file_name",                       "", eslapi::CASI_PARAM_STRING, 0);
	defineParameter( "output_vcd_file_name",                           "", eslapi::CASI_PARAM_STRING, 0);
	defineParameter( "output_csv_file_name",                           "", eslapi::CASI_PARAM_STRING, 0);
	defineParameter( "output_summary_file_name",                       "", eslapi::CASI_PARAM_STRING, 0);
	defineParameter( "Data Width",                                   "64", eslapi::CASI_PARAM_VALUE,  0);
	defineParameter( "Address Width",                                "32", eslapi::CASI_PARAM_VALUE,  0);
}

IIP_Pseudo::~IIP_Pseudo()
{
	uint32_t i;

	// Release all resources.
	for ( i = 0; i < 1; i++ )
    delete AXIv2_master_TMaster[i];
	for ( i = 0; i < 4; i++ )
		delete DummyGraphicsMacroModel_interrupt_SSlave[i];
	for ( i = 0; i < 4; i++ )
		delete output_SMaster[i];
	delete DummyGraphicsMacroModel_reset_x_SSlave;
	for ( i = 0; i < 2; i++ ) {
		delete DummyGraphicsMacroModel_data_in_SSlave[i];
		delete DummyGraphicsMacroModel_busy_in_SSlave[i];
  }
}

void IIP_Pseudo::communicate()
{
	// the following message will be printed only in the debug version of MxExplorer
	if (p_enableDbgMsg == true)
	{
		message(eslapi::CASI_MSG_INFO,"Executing communicate function");
	}

	// TODO:  Add your communicate code here.
	// ...

  for (unsigned int i = 0; i < 1; ++i) {
    AXIv2_master_TMaster[i]->sendDrive();
  }

	/* FSL code begin */
	doneSendAW();
	doneSendW();
	doneSendAR();

	getsendB();
	getsendR();
	/* FSL code end */
}

void IIP_Pseudo::update()
{
	// the following message will be printed only in the debug version of MxExplorer
	if (p_enableDbgMsg == true)
	{
		message(eslapi::CASI_MSG_INFO,"Executing update function");
	}

	// TODO:  Add your update code here.
	// ...

	/* FSL code begin */
	getsendAW();
	getsendW();
	getsendAR();

	controlOutput();
	controlCoopOutput();
	/* FSL code end */
}

/* FSL code begin */
void
	IIP_Pseudo::doneSendAW(void)
{
  for (unsigned int i = 0; i < 1; ++i) {
    if(AXIv2_master_TMaster[i]->getSig(AW_VALID) && AXIv2_master_TMaster[i]->getSig(AW_READY))
    {
#ifdef ABSTFR_TIMESTAMP
      cout << "[abstFR] AW send :: model_id = " << p_model_id << " , sc_time = " << sc_time_stamp() << endl;
#endif
      /* AW_VALID,AW_READYともに1であれば、AW送信できたと判断する */
      /* フラグを上げてBREADY=1にする */
      AXIv2_master_TMaster[i]->m_aw_done_flag = 1;
      m_b_count[0]++;
      switch(p_Data_Bit_Width){
      case 64:
      case 128:
        core->m_arbiter[i]->popAWTransaction();
        break;
      default:
        message(eslapi::CASI_MSG_WARNING,
                "IIP_Pseudo::doneSendAW: p_Data_Bit_Width <%d> is not supported.",
                p_Data_Bit_Width);
        break;
      }
    }
  }
}

void
	IIP_Pseudo::doneSendW(void)
{
  for (unsigned int i = 0; i < 1; ++i) {
    if(AXIv2_master_TMaster[i]->getSig(W_VALID) && AXIv2_master_TMaster[i]->getSig(W_READY))
    {
      /*#ifdef ABSTFR_TIMESTAMP
        cout << "[abstFR] W send :: model_id = " << p_model_id << " , sc_time = " << sc_time_stamp() << endl;
        #endif*/
      if(AXIv2_master_TMaster[i]->getSig(W_LAST))
      {
        /* W_VALID,W_READYともに1であれば、W送信できたと判断する */
        /* W_LAST == 1によりW転送完了を判断し、フラグを上げてBREADY=1にする */
        AXIv2_master_TMaster[i]->m_w_done_flag = 1;
      }
      switch(p_Data_Bit_Width){
      case 64:
      case 128:
        core->m_arbiter[i]->popWTransaction();
        break;
      default:
        message(eslapi::CASI_MSG_WARNING,
                "IIP_Pseudo::doneSendW: p_Data_Bit_Width <%d> is not supported.",
                p_Data_Bit_Width);
        break;
      }
    }
  }
}

void
	IIP_Pseudo::doneSendAR(void)
{
  for (unsigned int i = 0; i < 1; ++i) {
    if(AXIv2_master_TMaster[i]->getSig(AR_VALID) && AXIv2_master_TMaster[i]->getSig(AR_READY))
    {
#if 0
      std::cout << sc_time_stamp() << " doneSendAR" << std::endl;
#endif

#ifdef ABSTFR_TIMESTAMP
      cout << "[abstFR] AR send :: model_id = " << p_model_id << " , sc_time = " << sc_time_stamp() << endl;
#endif
      /* AR_VALID,AR_READYともに1であれば、AR送信できたと判断する */
      /* フラグを上げてRREADY=1にする */
      AXIv2_master_TMaster[i]->m_ar_done_flag = 1;
      m_r_count[i] += AXIv2_master_TMaster[i]->getSig(AR_LEN) + 1;
      
      switch(p_Data_Bit_Width){
      case 64:
      case 128:
        core->m_arbiter[i]->popARTransaction();
        break;
      default:
        message(eslapi::CASI_MSG_WARNING,
                "IIP_Pseudo::doneSendAR: p_Data_Bit_Width <%d> is not supported.",
                p_Data_Bit_Width);
        break;
      }
    }
  }
}

void
	IIP_Pseudo::getsendAW(void)
{
  for (unsigned int i = 0; i < 1; ++i) {
    switch(p_Data_Bit_Width){
    case 64:
    case 128:
    {
      TlmAxi3Payload* aw_transaction = NULL;
      aw_transaction = core->m_arbiter[i]->frontAWTransaction();
      if(aw_transaction)
      {
				/* AWキューにトランザクションがあればAWをセットする */
				AXIv2_master_TMaster[i]->setAW(1, // AWVALID
                                       aw_transaction->getAWID(),
                                       (uint64_t)aw_transaction->getAWADDR(),
                                       aw_transaction->getAWLEN(),
                                       aw_transaction->getAWSIZE(),
                                       aw_transaction->getAWBURST(),
                                       (bool)aw_transaction->getAWLOCK(),
                                       aw_transaction->getAWCACHE(),
                                       aw_transaction->getAWPROT(),
                                       aw_transaction->getAWUSER()); // user /* AXI仕様にないシグナルを使いたい場合に用いる */
				AXIv2_master_TMaster[i]->setSig(AW_LOCK, (fj::uint64)aw_transaction->getAWLOCK());
			}
			else
      {
        /* AWキューにトランザクションがなければAWVALIDを0にする */
				AXIv2_master_TMaster[i]->setSig(AW_VALID, 0);
			}
		}
		break;
	default:
		message(eslapi::CASI_MSG_WARNING,
            "IIP_Pseudo::getsendAW: p_Data_Bit_Width <%d> is not supported.",
            p_Data_Bit_Width);
		break;
    }
  }
}

void
	IIP_Pseudo::getsendW(void)
{

  for (unsigned int i = 0; i < 1; ++i) {
    switch(p_Data_Bit_Width){
    case 64:
    case 128:
      {
        TlmAxi3Payload* w_transaction = NULL;
        w_transaction = core->m_arbiter[i]->frontWTransaction();
        if(w_transaction)
        {
          unsigned int tmp_wdata = 0;
          uint32_t tmp_wstrb = 0;
          unsigned int byte_index = 0;
          unsigned int set_count = 0;

          /* WキューにトランザクションがあればWをセットする */
          for (int j = 0; j < p_Data_Bit_Width / 8; ++j) {
            tmp_wdata |= (*(w_transaction->getWDATA() + j) << (byte_index * 8));
            ++byte_index;

            if (4 <= byte_index) {
              AXIv2_master_TMaster[i]->setWData(tmp_wdata, set_count);
              tmp_wdata = 0;
              byte_index = 0;
              ++set_count;
            }
          }

          for (int j = 0; j < p_Data_Bit_Width / 8; ++j) {
            tmp_wstrb |= (*(w_transaction->getWSTRB() + j) << j);
          }

          AXIv2_master_TMaster[i]->setW(1, // WVALID
                                        w_transaction->getWID(),
                                        tmp_wstrb,
                                        w_transaction->getWLAST(),
                                        0); // user /* AXI仕様にないシグナルを使いたい場合に用いる */
        }
        else
        {
          /* WキューにトランザクションがなければWVALIDを0にする */
          AXIv2_master_TMaster[i]->setSig(W_VALID, 0);
        }
      }
      break;
    default:
      message(eslapi::CASI_MSG_WARNING,
              "IIP_Pseudo::getsendW: p_Data_Bit_Width <%d> is not supported.",
              p_Data_Bit_Width);
      break;
    }
  }
}

void
	IIP_Pseudo::getsendB(void)
{
  for (unsigned int i = 0; i < 1; ++i) {
    //uint8_t tmp_bid   = 0x0;
    //uint8_t tmp_bresp = 0x0;
    
    unsigned int tmp_bid   = 0x0;
    unsigned int tmp_bresp = 0x0;
    
    
    if(AXIv2_master_TMaster[i]->getSig(B_VALID) && AXIv2_master_TMaster[i]->getSig(B_READY))
    {
      /* B_VALID,B_READYともに1であれば、Bを受信する */
      tmp_bid   = static_cast< unsigned int >( AXIv2_master_TMaster[i]->getSig(B_ID) );
      tmp_bresp = static_cast< unsigned int >( AXIv2_master_TMaster[i]->getSig(B_RESP) );
      
#ifdef ABSTFR_TIMESTAMP
      cout << "[abstFR] B get :: model_id = " << p_model_id << " , sc_time = " << sc_time_stamp() << endl;
#endif
      
      switch(p_Data_Bit_Width){
      case 64:
      case 128:
        {
          TlmAxi3Payload* b_transaction = NULL;
          b_transaction = new TlmAxi3Payload(p_Data_Bit_Width / 8);
          b_transaction->setBID(tmp_bid);
          b_transaction->setBRESP(tmp_bresp);
          core->m_arbiter[i]->pushBTransaction(b_transaction);
        }
        break;
      default:
        message(eslapi::CASI_MSG_WARNING,
                "IIP_Pseudo::getsendB: p_Data_Bit_Width <%d> is not supported.",
                p_Data_Bit_Width);
        break;
      }
      
      m_b_count[0]--;
      if(m_b_count[0] == 0)
      {
        /* m_b_count[0] == 0によりライト転送完了を判断し、フラグを下げてBREADY=0にする */
        AXIv2_master_TMaster[i]->m_aw_done_flag = 0;
        AXIv2_master_TMaster[i]->m_w_done_flag = 0;
      }
    }
  }
}

void
	IIP_Pseudo::getsendAR(void)
{
  for (unsigned int i = 0; i < 1; ++i) {
    switch(p_Data_Bit_Width){
    case 64:
    case 128:
      {
        TlmAxi3Payload* ar_transaction = NULL;
        ar_transaction = core->m_arbiter[i]->frontARTransaction();
        if(ar_transaction)
        {
#if 0
          std::cout << sc_time_stamp() << " getsendAR" << std::endl;
#endif

          /* ARキューにトランザクションがあればARをセットする */
          AXIv2_master_TMaster[i]->setAR(1, // ARVALID
                                         ar_transaction->getARID(),
                                         (uint64_t)ar_transaction->getARADDR(),
                                         ar_transaction->getARLEN(),
                                         ar_transaction->getARSIZE(),
                                         ar_transaction->getARBURST(),
                                         (bool)ar_transaction->getARLOCK(),
                                         ar_transaction->getARCACHE(),
                                         ar_transaction->getARPROT(),
                                         ar_transaction->getARUSER()); // user /* AXI仕様にないシグナルを使いたい場合に用いる */
          AXIv2_master_TMaster[i]->setSig(AR_LOCK, (fj::uint64)ar_transaction->getARLOCK());
        }
        else
        {
          /* ARキューにトランザクションがなければARVALIDを0にする */
          AXIv2_master_TMaster[i]->setSig(AR_VALID, 0);
        }
      }
      break;
    default:
      message(eslapi::CASI_MSG_WARNING,
              "IIP_Pseudo::getsendAR: p_Data_Bit_Width <%d> is not supported.",
              p_Data_Bit_Width);
      break;
    }
  }
}

void
	IIP_Pseudo::getsendR(void)
{
  for (unsigned int i = 0; i < 1; ++i) {
    //uint8_t  tmp_rid      = 0x0;
    //uint8_t  tmp_rresp    = 0x0;
    //bool     tmp_rlast    = 0x0;
    
    unsigned int tmp_rid	= 0x0;
    unsigned int tmp_rresp	= 0x0;
    unsigned int tmp_rlast	= 0x0;
    
    uint32_t tmp_rdata[4]; //[0]:31-0,[1]:63-32,[2]:95-64,[3]:127:96
    
    if(AXIv2_master_TMaster[i]->getSig(R_VALID) && AXIv2_master_TMaster[i]->getSig(R_READY))
    {
      /* R_VALID,R_READYともに1であれば、Rを受信する */
      tmp_rid   = static_cast< unsigned int >( AXIv2_master_TMaster[i]->getSig(R_ID)		);
      tmp_rresp = static_cast< unsigned int >( AXIv2_master_TMaster[i]->getSig(R_RESP)	);
      tmp_rlast = static_cast< unsigned int >( AXIv2_master_TMaster[i]->getSig(R_LAST)	);
#ifdef ABSTFR_TIMESTAMP
      if(tmp_rlast)
      {
        cout << "[abstFR] R get :: model_id = " << p_model_id << " , sc_time = " << sc_time_stamp() << endl;
      }
#endif
      
      switch(p_Data_Bit_Width){
      case 64:
      case 128:
        {
          TlmAxi3Payload* r_transaction = NULL;
          r_transaction = new TlmAxi3Payload(p_Data_Bit_Width/8);
          for (int j = 0; j < p_Data_Bit_Width / (8 * 4); ++j) {
            tmp_rdata[j] = AXIv2_master_TMaster[i]->getRData(j);
          }
          r_transaction->setRID(tmp_rid);
          r_transaction->setRLAST(tmp_rlast);
          r_transaction->setRRESP(tmp_rresp);
          r_transaction->setRDATA((unsigned char*)tmp_rdata);
          core->m_arbiter[i]->pushRTransaction(r_transaction);
        }
        break;
      default:
        message(eslapi::CASI_MSG_WARNING,
                "IIP_Pseudo::getsendR: p_Data_Bit_Width <%d> is not supported.",
                p_Data_Bit_Width);
        break;
      }
      
      m_r_count[i]--;
      if(m_r_count[i] == 0)
      {
        /* m_r_count == 0によりリード転送完了を判断し、フラグを下げてRREADY=0にする */
        AXIv2_master_TMaster[i]->m_ar_done_flag = 0;
      }
    }
	}
}

int
	IIP_Pseudo::getDataWidth(void)
{
	return p_Data_Bit_Width;
}

void
	IIP_Pseudo::controlInterrupt(void)
{
	for(fj::uint32 interrupt_number = 0; interrupt_number < 4; interrupt_number ++)
	{
    m_signal_interrupt[interrupt_number].write(m_interrupt_1bit[interrupt_number]);
	}
	//std::cout << "[INFO]IIP_Pseudo::controlInterrupt interrupt = " << (fj::uint32)interrupt_value 
	//          << " at " << sc_time_stamp() << std::endl;
}

void 
	IIP_Pseudo::controlOutput(void)
{
	fj::uint32   tmp_array[4];

 	for(fj::uint32 output_number = 0; output_number < 4; output_number ++)
	{
		if(core->m_output_receiver->get(output_number) != m_previous_output_value[output_number]) {
      output_SMaster[output_number]->driveSignal(core->m_output_receiver->get(output_number), tmp_array);
      m_previous_output_value[output_number] = core->m_output_receiver->get(output_number);
		}
  }
}

void
	IIP_Pseudo::controlCoopInput(void)
{
	for(fj::uint32 input_number = 0; input_number < 2; input_number ++)
	{
    m_signal_data_in[input_number].write(m_data_in_32bit[input_number]);
    m_signal_busy_in[input_number].write(m_busy_in_1bit[input_number]);
	}
}

void 
	IIP_Pseudo::controlCoopOutput(void)
{
	fj::uint32   tmp_array[4];

 	for(fj::uint32 output_number = 0; output_number < 2; output_number ++)
	{
		if(core->m_data_out_receiver->get(output_number) != m_previous_data_out_value[output_number]) {
      data_out_SMaster[output_number]->driveSignal(core->m_data_out_receiver->get(output_number), tmp_array);
      m_previous_data_out_value[output_number] = core->m_data_out_receiver->get(output_number);
		}
		if(core->m_busy_out_receiver->get(output_number) != m_previous_busy_out_value[output_number]) {
      busy_out_SMaster[output_number]->driveSignal(core->m_busy_out_receiver->get(output_number), tmp_array);
      m_previous_busy_out_value[output_number] = core->m_busy_out_receiver->get(output_number);
		}
  }
}

/* FSL code begin */

void IIP_Pseudo::init()
{

	// Initialize ourself for save/restore.
	initStream( this );

  for (unsigned int i = 0; i < 1; ++i) {
    AXIv2_master_TMaster[i]->init(p_Address_Bit_Width, p_Data_Bit_Width);
  }

	// Allocate memory and initialize data here:
	// ...
  
	/* FSL code begin */
        for (unsigned int i = 0; i < 1; i++) {
	  m_b_count[i] = 0x0;
	  m_r_count[i] = 0x0;
        }

	core = NULL;

	m_signal_reset_x = 0x1;

	for(fj::uint32 i = 0; i < 4; i ++)
	{
    m_signal_interrupt[i]  = 0x0;
    m_signal_output[i] = 0x0;
		m_interrupt_1bit[i] = false;
    m_previous_output_value[i] = 0x0;
	}

  for(fj::uint32 i = 0; i < 2; i ++)
  {
    m_signal_data_in[i]  = 0x0;
    m_signal_busy_in[i]  = 0x0;
    m_signal_data_out[i] = 0x0;
    m_signal_busy_out[i] = 0x0;
    m_data_in_32bit[i] = 0;
    m_busy_in_1bit[i] = false;
    m_previous_data_out_value[i] = 0x0;
    m_previous_busy_out_value[i] = false;
  }
  
	sc_time_unit time_unit; // sc_time_unit for IIP_Pseudo

	if     (p_time_unit == "SC_FS")  {time_unit = SC_FS;}
	else if(p_time_unit == "SC_PS")  {time_unit = SC_PS;}
	else if(p_time_unit == "SC_NS")  {time_unit = SC_NS;}
	else if(p_time_unit == "SC_US")  {time_unit = SC_US;}
	else if(p_time_unit == "SC_MS")  {time_unit = SC_MS;}
	else if(p_time_unit == "SC_SEC") {time_unit = SC_SEC;}
	else                             {time_unit = SC_NS;}

	switch(p_Data_Bit_Width){
	case 64:
	case 128:
		core = new IIP_Pseudo_wrapperbase(p_model_id,
                               p_Data_Bit_Width,
                               p_number_of_thread,
                               p_number_of_read_outstanding,
                               p_number_of_write_outstanding,
                               p_no_r_receive,
                               p_no_b_receive,
                               time_unit,
                               p_axi_clock,
                               p_core_clock,
                               p_buffer_parameter_file_name.c_str(),
                               p_fifo_parameter_file_name.c_str(),
                               p_output_vcd_file_name.c_str(),
                               p_output_csv_file_name.c_str(),
                               p_output_summary_file_name.c_str()
                               );
		//core->reset_x(m_signal_reset_x);
    for (unsigned int i = 0; i < 1; ++i) {
      core->m_arbiter[i]->m_clk( *(getMxSCClock()) );
    }
		break;
	default:
		message(eslapi::CASI_MSG_WARNING,
			"FRBMx2::init: p_Data_Bit_Width <%d> is not supported.",
			p_Data_Bit_Width);
		break;
	}
	/* FSL code end */

	// Call the base class after this has been initialized.
	CASIModule::init();
}

void IIP_Pseudo::reset(eslapi::CASIResetLevel level, const CASIFileMapIF *filelist)
{
	// Add your reset behavior here:
	// ...

  for (unsigned int i = 0; i < 1; ++i) {
    AXIv2_master_TMaster[i]->reset();
  }

	// Call the base class after this has been reset.
	CASIModule::reset(level, filelist);
}

void IIP_Pseudo::terminate()
{
	// Call the base class first.
	CASIModule::terminate();


	// Free memory which has been allocated in init stage
	// ...

	/* FSL code start */
  delete core;
	/* FSL code end */
}

void IIP_Pseudo::setParameter( const string &name, const string &value )
{
	CASIConvertErrorCodes status = CASIConvert_SUCCESS;

  if (name == "Enable Debug Messages")
  {
    status = CASIConvertStringToValue( value, &p_enableDbgMsg  );
  }
  else if (name == "model_id")
  {
		status = CASIConvertStringToValue( value, &p_model_id );
	}
	else if (name == "number_of_thread")
	{
		status = CASIConvertStringToValue( value, &p_number_of_thread );
	}
	else if (name == "number_of_read_outstanding")
	{
		status = CASIConvertStringToValue( value, &p_number_of_read_outstanding );
	}
	else if (name == "number_of_write_outstanding")
	{
		status = CASIConvertStringToValue( value, &p_number_of_write_outstanding );
	}
	else if (name == "no_r_receive")
	{
		status = CASIConvertStringToValue( value, &p_no_r_receive );
	}
	else if (name == "no_b_receive")
	{
		status = CASIConvertStringToValue( value, &p_no_b_receive );
	}
	else if (name == "time_unit")
	{
		p_time_unit = value;
	}
	else if (name == "axi_clock")
	{
		status = CASIConvertStringToValue( value, &p_axi_clock );
	}
	else if (name == "core_clock")
	{
		status = CASIConvertStringToValue( value, &p_core_clock );
	}
	else if (name == "buffer_parameter_file_name")
	{
		p_buffer_parameter_file_name =  value;
	}
	else if (name == "fifo_parameter_file_name")
	{
		p_fifo_parameter_file_name =  value;
	}
	else if (name == "output_vcd_file_name")
	{
		p_output_vcd_file_name =  value;
	}
	else if (name == "output_csv_file_name")
	{
		p_output_csv_file_name =  value;
	}
	else if (name == "output_summary_file_name")
	{
		p_output_summary_file_name =  value;
	}
	else if (name == "Data Width")
	{
		status = CASIConvertStringToValue( value, &p_Data_Bit_Width );
	}
	else if (name == "Address Width")
	{
		status = CASIConvertStringToValue( value, &p_Address_Bit_Width );
	}

	if ( status == CASIConvert_SUCCESS )
	{
		CASIModule::setParameter(name, value);
	}
	else
	{
		message( eslapi::CASI_MSG_WARNING, "IIP_Pseudo::setParameter: Illegal value <%s> passed for parameter <%s>. Assignment ignored.", value.c_str(), name.c_str() );
	}
}

string IIP_Pseudo::getProperty( eslapi::CASIPropertyType property )
{
	string description; 
	switch ( property ) 
	{    
	case eslapi::CASI_PROP_LOADFILE_EXTENSION:
		return "";
	case eslapi::CASI_PROP_REPORT_FILE_EXT:
		return "yes";
	case eslapi::CASI_PROP_COMPONENT_TYPE:
		return "Core"; 
	case eslapi::CASI_PROP_COMPONENT_VERSION:
		return "0.1";
	case eslapi::CASI_PROP_MSG_PREPEND_NAME:
		return "yes"; 
	case eslapi::CASI_PROP_DESCRIPTION:
		description = "IIP_Pseudo";
		return description + " Compiled on " + __DATE__ + ", " + __TIME__; 
	case eslapi::CASI_PROP_CADI_SUPPORT:
		return "no";
	case eslapi::CASI_PROP_SAVE_RESTORE:
		return "yes";
	default:
		return "";
	}
}

string IIP_Pseudo::getName(void)
{
	return "IIP_Pseudo";
}

bool
	IIP_Pseudo::saveData( CASIODataStream &data )
{
	// TODO:  Add your save code here.
	// This shows how the example state variable is saved.
	// data << exampleStateVariable;

	// TODO:  Add verification if applicable.
	// return save was successful
	return true;
}

bool
	IIP_Pseudo::restoreData( CASIIDataStream &data )
{
	// TODO:  Add your restore code here.
	// This shows how the example state variable is restored.
	// data >> exampleStateVariable;

	// TODO:  Add verification if applicable.
	// return restore was successful
	return true;
}

void
	IIP_Pseudo::initSignalPort(CASISignalMasterIF* signalIf)
{
	CASISignalProperties prop_sm1;
	memset(&prop_sm1, 0, sizeof(prop_sm1));
	prop_sm1.isOptional = false;
	prop_sm1.bitwidth = 32;
	signalIf->setProperties(&prop_sm1);
}

// This initAXIv2TransactionPort() is only called for AXIv2 Transaction Master Ports.
// Do not call this function for any port which has its own initialization code.
void
	IIP_Pseudo::initAXIv2TransactionPort(CASITransactionMasterIF* transIf)
{
	CASITransactionProperties prop;
	memset(&prop, 0, sizeof(prop));
	prop.casiVersion = eslapi::CASI_VERSION_1_1;     //the transaction version used for this transaction
	prop.useMultiCycleInterface = false;    // using read/write interface methods
	prop.addressBitwidth = 32;      // address bitwidth used for addressing of resources 
	prop.mauBitwidth = 8;           // minimal addressable unit 
	prop.dataBitwidth = 32;         // maximum data bitwidth transferred in a single cycle 
	prop.isLittleEndian = true;     // alignment of MAUs 
	prop.isOptional = false;        // if true this port can be disabled 
	prop.supportsAddressRegions = true;  // M/S can negotiate address mapping
	prop.numCtrlFields = 1;         // # of ctrl elements used / entry is used for transfer size


  // prop.protocolID = 0x0002A3E1;           // magic number for the AXIv2 protocol 
  prop.protocolID = AXI2_PROTOCOL_ID;           // magic number for the AXIv2 protocol 


  sprintf(prop.protocolName,"AXIv2");         // The name of the  protocol being used
	// CASI : slave port address regions forwarding 
	prop.isAddrRegionForwarded = false; //true if addr region for this slave port is actually 
	//forwarded to a master port, false otherwise
	prop.forwardAddrRegionToMasterPort = NULL; //master port of the  same component to which this slave port's addr region is forwarded
	transIf->setProperties(&prop);
}

/************************
* IIP_Pseudo Factory class
***********************/
class IIP_PseudoFactory : public CASIFactory
{
public:
	IIP_PseudoFactory() : CASIFactory ( "IIP_Pseudo" ) {}
	CASIModuleIF *createInstance(CASIModuleIF *c, const string &id)
	{ 
		return new IIP_Pseudo(c, id); 
	}
};

/**
*  Entry point into the memory components (from SoC Designer)
*/
extern "C" void 
	CASIInit(void)
{
	new IIP_PseudoFactory();
}
