/*
 *    Class definition of AXIv2_master port for component <SD_AXIv2_DummyGraphicsMacroModel>
 *
 *    This code has been generated by the SoC Designer Component Wizard.
 *    Copyright (c)  2008 Carbon Design Systems Inc.
 *
 * THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF CARBON
 * DESIGN SYSTEMS, INC.  PERMISSION IS HEREBY GRANTED TO USE, MODIFY, AND/OR COPY
 * THIS SOFTWARE FOR INTERNAL USE ONLY PROVIDED THAT THE ABOVE COPYRIGHT NOTICE
 * APPEARS IN ALL COPIES OF THIS SOFTWARE.
 */

#include "BufferlessModel_AXI_Master_Port.h"
#ifdef USE_BufferlessModel
#include "BufferlessModel.h"
#endif
#ifdef USE_TM
#include "TM.h"
#endif
#ifdef USE_FD
#include "FD.h"
#endif
#ifdef USE_SFLT
#include "SFLT.h"
#endif
#ifdef USE_RAW
#include "RAW.h"
#endif
#ifdef USE_MVD
#include "MVD.h"
#endif

template<class WrapperClass>
BufferlessModel_AXI_Master_Port<WrapperClass>::BufferlessModel_AXI_Master_Port(WrapperClass* _owner, std::string name) 
  : AXI_Master_Port(_owner, name), owner_master(_owner)
{
  // TODO: Add constructor code here.

  /* add FSL begin */
  m_aw_done_flag = 0;
  m_w_done_flag  = 0;
  m_ar_done_flag = 0;
  m_getsendr_done_flag = false;
  m_drive_transaction_cb_r_done_flag = false;
  /* add FSL end */

}

template<class WrapperClass>
void BufferlessModel_AXI_Master_Port<WrapperClass>::driveTransactionCB_R()
{
  /*
  TODO: Add R combinatorial code  here
  
  //EXAMPLE:
  
  if (getSig(R_VALID))
    this->setRReady(1);
    
  */

/* add FSL begin */
#ifndef DISABLE_RREADY_SYNC_WITH_WREADY
#if defined(USE_TM) || defined(USE_FD) || defined(USE_SFLT) || defined(USE_RAW) || defined(USE_MVD)
  unsigned int buffer_num      = 0;
  unsigned int full_buffer_num = 0;
  unsigned int buffer_size     = 0; // width * current_depth
  unsigned int buffer_width    = 0;

#ifndef DISABLE_COMMUNICATE_SIGNAL_REFERENCE
  /* add miyakawa */
  /* communicate()での信号値参照をupdate()で実行するため、呼出の順序制御は不要 */
  if (m_getsendr_done_flag)
  {
#endif
    if (getSig(W_READY) == 0)
    {
      /* count full_buffer(buffer_size == 1) */
      buffer_num = owner_master->core->m_kernel->getNumberOfBuffer();

      for (unsigned int i = 0; i < buffer_num; i++)
      {
        buffer_size  = owner_master->core->m_kernel->getWriteBufferSize(i);
        buffer_width = owner_master->core->m_kernel->getBufferWidth(i);

        if      (buffer_size / buffer_width == 1) { full_buffer_num++; }
        else if (buffer_size / buffer_width == 0) { /* do nothing */ }
        else
        {
          std::cout << "[ERROR] " << this->name << " does not have buffer depth > 2" << std::endl;
          std::cout << "[ERROR] " << this->name << " buffer size  "                  << buffer_size  << std::endl;
          std::cout << "[ERROR] " << this->name << " buffer width "                  << buffer_width << std::endl;
          assert(0);
        }
      }

      if (full_buffer_num == buffer_num)
      {
        this->setRReady(0);
      }
      else if(m_ar_done_flag) { this->setRReady(1); }
      else                    { this->setRReady(0); }
#ifdef DISABLE_COMMUNICATE_SIGNAL_REFERENCE // 定義されていたら実行
      /* add miyakawa */
      /* シナリオからのRREADY制御が行われるならば、そちらで上書き */
      /* バッファFULLで0にすべきところを、シナリオから強制的に1にしたままの場合、 */
      /* シナリオとして破綻しているためエラー */
      if (owner_master->core->m_kernel->isValidateRreadyControl() == true)
      {
        if (owner_master->core->m_kernel->getRreadyValue() == true)
        {
          if (full_buffer_num == buffer_num) { assert(0); }
          else
          {
            this->setRReady(1);
          }
        }
        else
        {
          this->setRReady(0);
        }
      }
      // debug
      else {

      }
#endif
    }  // wready == 1
    else
    {
      if (m_ar_done_flag) { this->setRReady(1); } /* AR送信できたらRREADYを1にする */
      else                { this->setRReady(0); } /* 全てのR受信終わったらRREADYを0にする */
#ifdef DISABLE_COMMUNICATE_SIGNAL_REFERENCE // 定義されていたら実行
      /* シナリオからのRREADY制御が行われるならば、そちらで上書き */
      if (owner_master->core->m_kernel->isValidateRreadyControl() == true)
      {
        this->setRReady(owner_master->core->m_kernel->getRreadyValue());
      }
      // debug
      else {
      }
#endif
    }

#ifndef DISABLE_COMMUNICATE_SIGNAL_REFERENCE  // 定義されて"いなかったら"実行
    m_getsendr_done_flag = 0;
  }
  else
  {
    m_drive_transaction_cb_r_done_flag = 1;
  }
#endif

#else  // not defined(USE_TM) || defined(USE_FD) || defined(USE_SFLT) || defined(USE_RAW)
  unsigned int fifo_num      = 0;
  unsigned int full_fifo_num = 0;
  unsigned int fifo_size     = 0; // width * current_depth
  unsigned int fifo_width    = 0;

  if (m_getsendr_done_flag)
  {
    if(getSig(W_READY) == 0)
    {
      /* count full_fifo(fifo_size == 1) */
      fifo_num = owner_master->core->m_kernel->getNumberOfFifo();

      for (unsigned int i = 0; i < fifo_num; i++)
      {
        fifo_size  = owner_master->core->m_kernel->getFifoSize(i);
        fifo_width = owner_master->core->m_kernel->getFifoWidth(i);

        if      (fifo_size / fifo_width == 1) { full_fifo_num++; }
        else if (fifo_size / fifo_width == 0) { /* do nothing */ }
        else
        {
          std::cout << "[ERROR] " << this->name << " does not have fifo depth > 2" << std::endl;
          std::cout << "[ERROR] " << this->name << " fifo size  "                  << fifo_size  << std::endl;
          std::cout << "[ERROR] " << this->name << " fifo width "                  << fifo_width << std::endl;
          assert(0);
        }
      }

      if      (full_fifo_num == fifo_num) { this->setRReady(0); }
      else if (m_ar_done_flag)            { this->setRReady(1); }
      else                                { this->setRReady(0); }
    }
    else
    {
      if (m_ar_done_flag) { this->setRReady(1); } /* AR送信できたらRREADYを1にする */
      else                { this->setRReady(0); } /* 全てのR受信終わったらRREADYを0にする */
    }

    m_getsendr_done_flag = 0;
  }
  else
  {
    m_drive_transaction_cb_r_done_flag = true;
  }
#endif
#else /* DISABLE_RREADY_SYNC_WITH_WREADY */
  if (m_ar_done_flag) { this->setRReady(1); } /* AR送信できたらRREADYを1にする */
  else                { this->setRReady(0); } /* 全てのR受信終わったらRREADYを0にする */
#endif
/* add FSL end */
}

template<class WrapperClass>
void BufferlessModel_AXI_Master_Port<WrapperClass>::driveTransactionCB_B()
{
  /*
  TODO: Add B combinatorial code  here
  
  //EXAMPLE:
  
  if (getSig(B_VALID))
    this->setBReady(1);
    
  */

  /* add FSL begin */
  if(m_aw_done_flag && m_w_done_flag)
  {
    /* AWと、全てのW送信できたらBREADYを1にする */
    this->setBReady(1);
  }
  else
  {
    /* 全てのB受信終わったらBREADYを0にする */
    this->setBReady(0);
  }
  /* add FSL end */

}

#ifdef USE_BufferlessModel
template class BufferlessModel_AXI_Master_Port<BufferlessModel>;
#endif
#ifdef USE_TM
template class BufferlessModel_AXI_Master_Port<TM>;
#endif
#ifdef USE_FD
template class BufferlessModel_AXI_Master_Port<FD>;
#endif
#ifdef USE_SFLT
template class BufferlessModel_AXI_Master_Port<SFLT>;
#endif
#ifdef USE_RAW
template class BufferlessModel_AXI_Master_Port<RAW>;
#endif
#ifdef USE_MVD
template class BufferlessModel_AXI_Master_Port<MVD>;
#endif

