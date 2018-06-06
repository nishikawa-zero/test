/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file  AXIDataFormatControl.cpp
 * @brief AXI用データ形式操作クラス
 *        AXIのイニシエータ、ターゲット間でデータの形式が
 *        共通になるように操作します。
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

/** データ形式変換（sc_biguint<64> -> バイト列）
 *
 *  sc_biguint<64>形式から、バイトテーブルにデータを変換して設定する。
 *
 *  @param[in]      biguint64_data      sc_biguint<64>型のデータへのポインタ
 *  @param[in,out]  byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
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

/** データ形式変換（sc_biguint<128> -> バイト列）
 *
 *  sc_biguint<64>形式から、バイトテーブルにデータを変換して設定する。
 *
 *  @param[in]      biguint128_data     sc_biguint<128>型のデータへのポインタ
 *  @param[in,out]  byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
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

/** データ形式変換（sc_biguint<256> -> バイト列）
 *
 *  sc_biguint<64>形式から、バイトテーブルにデータを変換して設定する。
 *
 *  @param[in]      biguint256_data     sc_biguint<256>型のデータへのポインタ
 *  @param[in,out]  byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
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

/** データ形式変換（sc_uint<64> -> バイト列）
 *
 *  sc_uint<64>形式から、バイトテーブルにデータを変換して設定する。
 *
 *  @param[in]      uint64_data         sc_uint<64>型のデータへのポインタ
 *  @param[in,out]  byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
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
/** データ形式変換（unsigned long long -> バイト列）
 *
 *  unsigned long long形式から、バイトテーブルにデータを変換して設定する。
 *
 *  @param[in]      uint64_data         unsigned long long型のデータへのポインタ
 *  @param[in,out]  byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
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

/** データ形式変換（バイト列 -> sc_biguint<64>）
 *
 *  バイト列からsc_biguint<64>形式に変換する。
 *
 *  @param[in]      byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
 *  @param[in,out]  biguint64_data      sc_biguint<64>型のデータへのポインタ
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

/** データ形式変換（バイト列 -> sc_biguint<128>）
 *
 *  バイト列からsc_biguint<128>形式に変換する。
 *
 *  @param[in]      byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
 *  @param[in,out]  biguint128_data     sc_biguint<128>型のデータへのポインタ
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

/** データ形式変換（バイト列 -> sc_biguint<256>）
 *
 *  バイト列からsc_biguint<256>形式に変換する。
 *
 *  @param[in]      byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
 *  @param[in,out]  biguint256_data     sc_biguint<256>型のデータへのポインタ
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

/** データ形式変換（バイト列 -> sc_uint<64>）
 *
 *  バイト列からsc_uint<64>形式に変換する。
 *
 *  @param[in]      byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
 *  @param[in,out]  uint64_data         sc_uint<64>型のデータへのポインタ
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
/** データ形式変換（バイト列 -> unsigned long long）
 *
 *  バイト列からunsigned long long形式に変換する。
 *
 *  @param[in]      byte                    unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
 *  @param[in,out]  uint64_data             unsigned long long型のデータへのポインタ
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


/**バーストサイズを転送バイト数に変換します。
 *
 * @param[in] バーストサイズ
 * @return    転送バイト数
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
 *  @brief バーストバス幅からバーストサイズの変換
 *
 *  バースト時のバス幅からAXI AWSIZE/ARSIZEの変換を行う。
 *  @param[in]  width   転送バス幅
 *  @return     AWSIZE/ARSIZEの指定値
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
 *  @brief バーストサイズからバス幅への変換
 *
 *  AXI AWSIZE/ARSIZEからバースト時のバス幅の算出を行う。
 *  @param[in]  AWSIZE/ARSIZEの指定値
 *  @return 転送バス幅
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
