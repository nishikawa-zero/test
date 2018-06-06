/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file  tlm_config.h
 * @brief AXIで使用する情報を定義しています。
 *
 * @date $Date: 2009/02/03 00:54:40 $
 * @version $Id: tlm_config.h,v 1.7 2009/02/03 00:54:40 shunsaku Exp $
 */

#ifndef __tlm_config_h
#define __tlm_config_h

#include "tlm_axi_target_base_if.h"
#include "axi_payload.h"

#ifdef _MSC_VER
#define VC_PREPROCESSOR             /**<VC でコンパイルを行う時に使用します。 */
#else
#define GPLUSPLUS_PREPROCESSOR    /**<g++でコンパイルを行う時に使用します。 */
#endif
#if defined(VC_PREPROCESSOR)
#define FUNCNAME __FUNCSIG__
#endif

#if defined(GPLUSPLUS_PREPROCESSOR)
#define FUNCNAME __PRETTY_FUNCTION__
#endif

#if (BUS_WIDTH==128)
#define MAX_BURST_SIZE       128   /* バス幅は、128bit 1回に16バイトを転送  */
#define MAX_BURST_LENGTH     4     /* バースト長は、4 最大64バイト転送 */
#define AXI_DATA_DEF         sc_biguint<MAX_BURST_SIZE>
#define AXI_PAYLOAD_DEF      axi_payload<AXI_DATA_DEF > /* 128bit type AXI payload */
#else
#define MAX_BURST_SIZE       64    /* バス幅は、 64bit 1回に8バイトを転送  */
#define MAX_BURST_LENGTH     8     /* バースト長は、8 最大 64バイト転送 */
#define AXI_DATA_DEF         unsigned long long
#define AXI_PAYLOAD_DEF      axi_payload<AXI_DATA_DEF >  /* 64bit type AXI payload */
#endif
/** バーストタイプ
 *
 * バーストタイプを定義しています。
 */
enum tlmAXIBURSTTYPE {
    tlmFIXED   = 0, /**< 固定アドレスバースト           */
    tlmINCR,        /**< アドレスインクリメントバースト */
    tlmWRAP,        /**< ラッピングバースト             */
    tlmRESERVE      /**< 予約                           */
};

/** バーストの長さ
 *
 * バーストの長さ（転送回数）を定義しています。
 */
enum tlmAXIBURSTLENGTH {
    tlmLENGTH1   = 0, /**< 転送回数 1回*/
    tlmLENGTH2,       /**< 転送回数 2回*/
    tlmLENGTH3,       /**< 転送回数 3回*/
    tlmLENGTH4,       /**< 転送回数 4回*/
    tlmLENGTH5,       /**< 転送回数 5回*/
    tlmLENGTH6,       /**< 転送回数 6回*/
    tlmLENGTH7,       /**< 転送回数 7回*/
    tlmLENGTH8,       /**< 転送回数 8回*/
    tlmLENGTH9,       /**< 転送回数 9回*/
    tlmLENGTH10,      /**< 転送回数 10回*/
    tlmLENGTH11,      /**< 転送回数 11回*/
    tlmLENGTH12,      /**< 転送回数 12回*/
    tlmLENGTH13,      /**< 転送回数 13回*/
    tlmLENGTH14,      /**< 転送回数 14回*/
    tlmLENGTH15,      /**< 転送回数 15回*/
    tlmLENGTH16       /**< 転送回数 16回*/
};


/** バーストサイズ
 *
 * バーストサイズ（転送サイズ）を定義しています。
 */
enum tlmAXIBURSTSIZE {
    tlmSIZE1   = 0, /**< 転送バイト数 1byte */
    tlmSIZE2,       /**< 転送バイト数 2byte */
    tlmSIZE4,       /**< 転送バイト数 4byte */
    tlmSIZE8,       /**< 転送バイト数 8byte */
    tlmSIZE16,      /**< 転送バイト数 16byte */
    tlmSIZE32       /**< 転送バイト数 32byte */
};


/**
 *
 *
 */
enum tlmAXICACHE {


};

/** 保護ユニット
 *
 * アクセス保護を定義します。
 */
enum tlmAXISAVEUNIT {


};

/**アクセス種別
 *
 * アクセス種別を定義します。
 */
enum tlmAXIACCESS {
    tlmNOMALACCESS   = 0, /**< 通常アクセス*/
    tlmSEMAPHORE,         /**< 排他アクセス */
    tlmLOCK,              /**< ロックアクセス */
    tlmACCESSRESERVE      /**< 予約 */
};

/**応答
 *
 * 応答のタイプを定義します。
 */
enum tlmAXICALL {
    tlmOKAY   = 0, /**< 通常アクセス成功 */
    tlmEXOKAY,     /**< 排他アクセス成功 */
    tlmSLVERR,     /**< スレーブエラー   */
    tlmDECERR      /**< デコードエラー   */
};

#endif /* __tlm_config_h */


