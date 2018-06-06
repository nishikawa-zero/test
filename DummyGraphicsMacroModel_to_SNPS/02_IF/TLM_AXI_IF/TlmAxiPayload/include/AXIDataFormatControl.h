/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file  AXIDataFormatControl.h
 * @brief AXI用データ形式操作クラス
 *        AXIのイニシエータ、ターゲット間でデータの形式が
 *        共通になるように操作します。
 *
 * @date $Date: 2009/02/03 00:29:41 $
 * @version $Id: AXIDataFormatControl.h,v 1.6 2009/02/03 00:29:41 shunsaku Exp $
 */

#include "systemc.h"
#include "tlm_config.h"

#ifndef __AXIDataFormatControl_h
#define __AXIDataFormatControl_h


class AXIDataFormatControl {
public:
    AXIDataFormatControl();
    ~AXIDataFormatControl();

    /** データ形式変換（sc_biguint<64> -> バイト列）
     *
     *  @param[in]      biguint64_data      sc_biguint<64>型のデータへのポインタ
     *  @param[in,out]  byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
     */
    void convertDataToByteStream(sc_biguint<64> *biguint64_data, unsigned char *byte);

    /** データ形式変換（sc_biguint<128> -> バイト列）
     *
     *  @param[in]      biguint128_data     sc_biguint<128>型のデータへのポインタ
     *  @oaram[in,out]  byte                unsigned char *型へのポインタ　領域のサイズは、16バイト以上必要。
     */
    void convertDataToByteStream(sc_biguint<128> *biguint128_data, unsigned char *byte);

    /** データ形式変換（sc_biguint<256> -> バイト列）
     *
     *  @param[in]      biguint256_data     sc_biguint<256>型のデータへのポインタ
     *  @param[in,out]  byte                unsigned char *型へのポインタ　領域のサイズは、32バイト以上必要。
     */
    void convertDataToByteStream(sc_biguint<256> *biguint256_data, unsigned char *byte);

    /** AXIデータ形式変換（sc_uint<64> -> バイト列）
     *
     *  @param[in]      uint64_data         sc_uint<64>型のデータへのポインタ
     *  @param[in,out]  byte                unsigned char *型へのポインタ　領域のサイズは、8バイト以上必要。
     */
    void convertDataToByteStream(sc_uint<64> *uint64_data, unsigned char *byte);

    /** データ形式変換（バイト列 -> sc_biguint<64>）
     *
     *  @param[in]      byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
     *  @param[in,out]  biguint64_data      sc_biguint<64>型のデータへのポインタ
     */
    void convertByteStreamToData(unsigned char *byte, sc_biguint<64> *biguint64_data);

    /** データ形式変換（unsigned long long -> バイト列）
     *
     *  unsigned long long形式から、バイトテーブルにデータを変換して設定する。
     *
     *  @param[in]      uint64_data         unsigned long long型のデータへのポインタ
     *  @param[in,out]  byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
     */
    void convertDataToByteStream(unsigned long long *uint64_data, unsigned char *byte);

    /** データ形式変換（バイト列 -> sc_biguint<128>）
     *
     *  @param[in]      byte               unsigned char *型へのポインタ　領域のサイズは、16バイト以上必要。
     *  @param[in,out]  biguint128_data    sc_biguint<128>型のデータへのポインタ
     */
    void convertByteStreamToData( unsigned char *byte, sc_biguint<128> *biguint128_data);

    /** データ形式変換（バイト列 -> sc_biguint<256>）
     *
     *  @param[in]      byte                unsigned char *型へのポインタ　領域のサイズは、32バイト以上必要。
     *  @param[in,out]  biguint256_data     sc_biguint<256>型のデータへのポインタ
     */
    void convertByteStreamToData(unsigned char *byte, sc_biguint<256> *biguint256_data);

    /** AXIデータ形式変換（バイト列 -> sc_uint<64>）
     *
     *  @param[in]      byte           unsigned char *型へのポインタ　領域のサイズは、8バイト以上必要。
     *  @param[in,out]  uint64_data    sc_uint<64>型のデータへのポインタ
     */
    void convertByteStreamToData(unsigned char *byte, sc_uint<64> *uint64_data);

    /** データ形式変換（バイト列 -> unsigned long long）
     *
     *  バイト列からunsigned long long形式に変換する。
     *
     *  @param[in]      byte                unsigned char *型の領域へのポインタ　領域のサイズは、8バイト以上必要。
     *  @param[in,out]  uint64_data         unsigned long long型のデータへのポインタ
     */
    void convertByteStreamToData(unsigned char *byte, unsigned long long *uint64_data);

    /**バーストサイズを転送バイト数に変換します。
     *
     * @param[in] バーストサイズ
     * @return    転送バイト数
     */
    unsigned int convertBurstSize(unsigned size);

    /** バーストバス幅からバーストサイズの変換
     *
     *  バースト時のバス幅からAXI AWSIZE/ARSIZEの変換を行う。
     *  @param[in]  width   転送バス幅
     *  @return     AWSIZE/ARSIZEの指定値
     */
    unsigned int convertBurstWidth2AXIAsize(int width);

    /**
     *  @brief バーストサイズからバス幅への変換
     *
     *  AXI AWSIZE/ARSIZEからバースト時のバス幅の算出を行う。
     *  @param[in]  AWSIZE/ARSIZEの指定値
     *  @return 転送バス幅
     */
    unsigned int convertAXIAsize2BurstWidth(int asize);

    unsigned int convertBurstSize2AXIAsize(int burst_size);
    unsigned int convertAXIAsize2BurstSize(int asize);

};
#endif /* __AXIDataFormatControl_h */
