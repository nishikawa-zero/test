/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file  AXIDataFormatControl.cpp
 * @brief AXI�p�f�[�^�`������N���X
 *        AXI�̃C�j�V�G�[�^�A�^�[�Q�b�g�ԂŃf�[�^�̌`����
 *        ���ʂɂȂ�悤�ɑ��삵�܂��B
 *
 * @date $Date: 2009/02/03 00:29:41 $
 * @version $Id: AXIDataFormatControl.cpp,v 1.10 2009/02/03 00:29:41 shunsaku Exp $
 */

#include "AXIDataFormatControl.h"
#include <iostream>


AXIDataFormatControl::AXIDataFormatControl() {


}

AXIDataFormatControl::~AXIDataFormatControl() {

}

/** �f�[�^�`���ϊ��isc_biguint<64> -> �o�C�g��j
 *
 *  sc_biguint<64>�`������A�o�C�g�e�[�u���Ƀf�[�^��ϊ����Đݒ肷��B
 *
 *  @param[in]      biguint64_data      sc_biguint<64>�^�̃f�[�^�ւ̃|�C���^
 *  @param[in,out]  byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 */
void
AXIDataFormatControl::convertDataToByteStream(sc_biguint<64> *biguint64_data, unsigned char *byte)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */
    sc_uint<8> byte_data;

    for (int i=0; i < 8; i++) {
        byte_data = (sc_uint<8>)biguint64_data->range((i*8)+7, (i*8));
        *byte = (unsigned char)byte_data;
        byte++;
    }
}

/** �f�[�^�`���ϊ��isc_biguint<128> -> �o�C�g��j
 *
 *  sc_biguint<64>�`������A�o�C�g�e�[�u���Ƀf�[�^��ϊ����Đݒ肷��B
 *
 *  @param[in]      biguint128_data     sc_biguint<128>�^�̃f�[�^�ւ̃|�C���^
 *  @param[in,out]  byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 */
void
AXIDataFormatControl::convertDataToByteStream(sc_biguint<128> *biguint128_data, unsigned char *byte)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */
    sc_uint<8> byte_data;

    for (int i=0; i < 16; i++) {
        byte_data = (sc_uint<8>)biguint128_data->range((i*8)+7, (i*8));
        *byte = (unsigned char)byte_data;
        byte++;
    }

}

/** �f�[�^�`���ϊ��isc_biguint<256> -> �o�C�g��j
 *
 *  sc_biguint<64>�`������A�o�C�g�e�[�u���Ƀf�[�^��ϊ����Đݒ肷��B
 *
 *  @param[in]      biguint256_data     sc_biguint<256>�^�̃f�[�^�ւ̃|�C���^
 *  @param[in,out]  byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 */
void
AXIDataFormatControl::convertDataToByteStream(sc_biguint<256> *biguint256_data, unsigned char *byte)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    sc_uint<8> byte_data;

    for (int i = 0; i < 32; i++) {
        byte_data = (sc_uint<8>)biguint256_data->range((i*8)+7, (i*8));
        *byte = (unsigned char)byte_data;
        byte++;
    }

}

/** �f�[�^�`���ϊ��isc_uint<64> -> �o�C�g��j
 *
 *  sc_uint<64>�`������A�o�C�g�e�[�u���Ƀf�[�^��ϊ����Đݒ肷��B
 *
 *  @param[in]      uint64_data         sc_uint<64>�^�̃f�[�^�ւ̃|�C���^
 *  @param[in,out]  byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 */
void
AXIDataFormatControl::convertDataToByteStream(sc_uint<64> *uint64_data, unsigned char *byte)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    unsigned char *byte_data;

    byte_data = (unsigned char *)uint64_data;

    for (int i = 0; i < 8; i++) {
        *byte = *byte_data;
        byte++;
        byte_data++;
    }

}
/** �f�[�^�`���ϊ��iunsigned long long -> �o�C�g��j
 *
 *  unsigned long long�`������A�o�C�g�e�[�u���Ƀf�[�^��ϊ����Đݒ肷��B
 *
 *  @param[in]      uint64_data         unsigned long long�^�̃f�[�^�ւ̃|�C���^
 *  @param[in,out]  byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 */
void
AXIDataFormatControl::convertDataToByteStream(unsigned long long *uint64_data, unsigned char *byte)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    unsigned char *byte_data;

    byte_data = (unsigned char *)uint64_data;

    for (int i = 0; i < 8; i++) {
        *byte = *byte_data;
        byte++;
        byte_data++;
    }

}

/** �f�[�^�`���ϊ��i�o�C�g�� -> sc_biguint<64>�j
 *
 *  �o�C�g�񂩂�sc_biguint<64>�`���ɕϊ�����B
 *
 *  @param[in]      byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 *  @param[in,out]  biguint64_data      sc_biguint<64>�^�̃f�[�^�ւ̃|�C���^
 */
void
AXIDataFormatControl::convertByteStreamToData(unsigned char *byte, sc_biguint<64> *biguint64_data)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    sc_uint<8> byte_data;

    for (int i = 0; i < 8; i++) {
        byte_data = *byte;
        biguint64_data->range((i*8)+7, (i*8)) = byte_data;
        byte++;
    }

}

/** �f�[�^�`���ϊ��i�o�C�g�� -> sc_biguint<128>�j
 *
 *  �o�C�g�񂩂�sc_biguint<128>�`���ɕϊ�����B
 *
 *  @param[in]      byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 *  @param[in,out]  biguint128_data     sc_biguint<128>�^�̃f�[�^�ւ̃|�C���^
 */
void
AXIDataFormatControl::convertByteStreamToData(unsigned char *byte, sc_biguint<128> *biguint128_data)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    sc_uint<8> byte_data;

    for (int i = 0; i < 16; i++) {
        byte_data = *byte;
        biguint128_data->range((i*8)+7, (i*8)) = byte_data;
        byte++;
    }

}

/** �f�[�^�`���ϊ��i�o�C�g�� -> sc_biguint<256>�j
 *
 *  �o�C�g�񂩂�sc_biguint<256>�`���ɕϊ�����B
 *
 *  @param[in]      byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 *  @param[in,out]  biguint256_data     sc_biguint<256>�^�̃f�[�^�ւ̃|�C���^
 */
void
AXIDataFormatControl::convertByteStreamToData(unsigned char *byte, sc_biguint<256> *biguint256_data)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    sc_uint<8> byte_data;

    for (int i = 0; i < 32; i++) {
        byte_data = *byte;
        biguint256_data->range((i*8)+7, (i*8)) = byte_data;
        byte++;
    }

}

/** �f�[�^�`���ϊ��i�o�C�g�� -> sc_uint<64>�j
 *
 *  �o�C�g�񂩂�sc_uint<64>�`���ɕϊ�����B
 *
 *  @param[in]      byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 *  @param[in,out]  uint64_data         sc_uint<64>�^�̃f�[�^�ւ̃|�C���^
 */
void
AXIDataFormatControl::convertByteStreamToData(unsigned char *byte, sc_uint<64> *uint64_data)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    unsigned char *byte_data;

    byte_data = (unsigned char *)uint64_data;

    for (int i = 0; i < 8; i++) {
        *byte_data = *byte;
        byte++;
        byte_data++;
    }

}
/** �f�[�^�`���ϊ��i�o�C�g�� -> unsigned long long�j
 *
 *  �o�C�g�񂩂�unsigned long long�`���ɕϊ�����B
 *
 *  @param[in]      byte                    unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
 *  @param[in,out]  uint64_data             unsigned long long�^�̃f�[�^�ւ̃|�C���^
 */
void
AXIDataFormatControl::convertByteStreamToData(unsigned char *byte, unsigned long long *uint64_data)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    unsigned char *byte_data;

    byte_data = (unsigned char *)uint64_data;

    for (int i = 0; i < 8; i++) {
        *byte_data = *byte;
        byte++;
        byte_data++;
    }

}


/**�o�[�X�g�T�C�Y��]���o�C�g���ɕϊ����܂��B
 *
 * @param[in] �o�[�X�g�T�C�Y
 * @return    �]���o�C�g��
 */
unsigned int
AXIDataFormatControl::convertBurstSize(unsigned size)
{
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    unsigned int burstSize;

    switch(size){
    case tlmSIZE1:
        burstSize = 1;
        break;
    case tlmSIZE2:
        burstSize = 2;
        break;
    case tlmSIZE4:
        burstSize = 4;
        break;
    case tlmSIZE8:
        burstSize = 8;
        break;
    case tlmSIZE16:
        burstSize = 16;
        break;
    case tlmSIZE32:
        burstSize = 32;
        break;
    default:
        cout << "size is uncertainty" << endl;
        break;
    }

    return burstSize;
}

/**
 *  @brief �o�[�X�g�o�X������o�[�X�g�T�C�Y�̕ϊ�
 *
 *  �o�[�X�g���̃o�X������AXI AWSIZE/ARSIZE�̕ϊ����s���B
 *  @param[in]  width   �]���o�X��
 *  @return     AWSIZE/ARSIZE�̎w��l
 */
unsigned int
AXIDataFormatControl::convertBurstWidth2AXIAsize(int width) {
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    unsigned int asize = 0;
    switch ((width>>3)) {
    case 1:
        asize = 0;
        break;
    case 2:
        asize = 1;
        break;
    case 4:
        asize = 2;
        break;
    case 8:
        asize = 3;
        break;
    case 16:
        asize = 4;
        break;
    case 32:
        asize = 5;
        break;
    case 64:
        asize = 6;
        break;
    case 128:
        asize = 7;
        break;
    default:
        break;

    }
    return asize;
}
/**
 *  @brief �o�[�X�g�T�C�Y����o�X���ւ̕ϊ�
 *
 *  AXI AWSIZE/ARSIZE����o�[�X�g���̃o�X���̎Z�o���s���B
 *  @param[in]  AWSIZE/ARSIZE�̎w��l
 *  @return �]���o�X��
 */
unsigned int
AXIDataFormatControl::convertAXIAsize2BurstWidth(int asize) {
#ifdef SDRAMC_DBG_FUNC_TRACE
    cout << FUNCNAME << endl;
#endif /* .SDRAMC_DBG_FUNC_TRACE */

    unsigned int width = 0;
    switch (asize) {
    case 0:
        width = 8;
        break;
    case 1:
        width = 16;
        break;
    case 2:
        width = 32;
        break;
    case 3:
        width = 64;
        break;
    case 4:
        width = 128;
        break;
    case 5:
        width = 256;
        break;
    case 6:
        width = 512;
        break;
    case 7:
        width = 1024;
        break;
    default:
        break;

    }
    return width;
}


unsigned int 
AXIDataFormatControl::convertBurstSize2AXIAsize(int burst_size){
  unsigned int asize = 0;
  switch(burst_size){
  case 1   : asize = 0; break;
  case 2   : asize = 1; break;
  case 4   : asize = 2; break;
  case 8   : asize = 3; break;
  case 16  : asize = 4; break;
  case 32  : asize = 5; break;
  case 64  : asize = 6; break;
  case 128 : asize = 7;
  default  : break;
  }
  return asize;
}

unsigned int 
AXIDataFormatControl::convertAXIAsize2BurstSize(int asize){
  unsigned int burst_size = 0;
  switch(asize){
  case 0 : burst_size = 1; break;
  case 1 : burst_size = 2; break;
  case 2 : burst_size = 4; break;
  case 3 : burst_size = 8; break;
  case 4 : burst_size = 16; break;
  case 5 : burst_size = 32; break;
  case 6 : burst_size = 64; break;
  case 7 : burst_size = 128; break;
  default : break;
  }
  return burst_size;
}
