/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file  tlm_config.h
 * @brief AXI�Ŏg�p��������`���Ă��܂��B
 *
 * @date $Date: 2009/02/03 00:54:40 $
 * @version $Id: tlm_config.h,v 1.7 2009/02/03 00:54:40 shunsaku Exp $
 */

#ifndef __tlm_config_h
#define __tlm_config_h

#include "tlm_axi_target_base_if.h"
#include "axi_payload.h"

#ifdef _MSC_VER
#define VC_PREPROCESSOR             /**<VC �ŃR���p�C�����s�����Ɏg�p���܂��B */
#else
#define GPLUSPLUS_PREPROCESSOR    /**<g++�ŃR���p�C�����s�����Ɏg�p���܂��B */
#endif
#if defined(VC_PREPROCESSOR)
#define FUNCNAME __FUNCSIG__
#endif

#if defined(GPLUSPLUS_PREPROCESSOR)
#define FUNCNAME __PRETTY_FUNCTION__
#endif

#if (BUS_WIDTH==128)
#define MAX_BURST_SIZE       128   /* �o�X���́A128bit 1���16�o�C�g��]��  */
#define MAX_BURST_LENGTH     4     /* �o�[�X�g���́A4 �ő�64�o�C�g�]�� */
#define AXI_DATA_DEF         sc_biguint<MAX_BURST_SIZE>
#define AXI_PAYLOAD_DEF      axi_payload<AXI_DATA_DEF > /* 128bit type AXI payload */
#else
#define MAX_BURST_SIZE       64    /* �o�X���́A 64bit 1���8�o�C�g��]��  */
#define MAX_BURST_LENGTH     8     /* �o�[�X�g���́A8 �ő� 64�o�C�g�]�� */
#define AXI_DATA_DEF         unsigned long long
#define AXI_PAYLOAD_DEF      axi_payload<AXI_DATA_DEF >  /* 64bit type AXI payload */
#endif
/** �o�[�X�g�^�C�v
 *
 * �o�[�X�g�^�C�v���`���Ă��܂��B
 */
enum tlmAXIBURSTTYPE {
    tlmFIXED   = 0, /**< �Œ�A�h���X�o�[�X�g           */
    tlmINCR,        /**< �A�h���X�C���N�������g�o�[�X�g */
    tlmWRAP,        /**< ���b�s���O�o�[�X�g             */
    tlmRESERVE      /**< �\��                           */
};

/** �o�[�X�g�̒���
 *
 * �o�[�X�g�̒����i�]���񐔁j���`���Ă��܂��B
 */
enum tlmAXIBURSTLENGTH {
    tlmLENGTH1   = 0, /**< �]���� 1��*/
    tlmLENGTH2,       /**< �]���� 2��*/
    tlmLENGTH3,       /**< �]���� 3��*/
    tlmLENGTH4,       /**< �]���� 4��*/
    tlmLENGTH5,       /**< �]���� 5��*/
    tlmLENGTH6,       /**< �]���� 6��*/
    tlmLENGTH7,       /**< �]���� 7��*/
    tlmLENGTH8,       /**< �]���� 8��*/
    tlmLENGTH9,       /**< �]���� 9��*/
    tlmLENGTH10,      /**< �]���� 10��*/
    tlmLENGTH11,      /**< �]���� 11��*/
    tlmLENGTH12,      /**< �]���� 12��*/
    tlmLENGTH13,      /**< �]���� 13��*/
    tlmLENGTH14,      /**< �]���� 14��*/
    tlmLENGTH15,      /**< �]���� 15��*/
    tlmLENGTH16       /**< �]���� 16��*/
};


/** �o�[�X�g�T�C�Y
 *
 * �o�[�X�g�T�C�Y�i�]���T�C�Y�j���`���Ă��܂��B
 */
enum tlmAXIBURSTSIZE {
    tlmSIZE1   = 0, /**< �]���o�C�g�� 1byte */
    tlmSIZE2,       /**< �]���o�C�g�� 2byte */
    tlmSIZE4,       /**< �]���o�C�g�� 4byte */
    tlmSIZE8,       /**< �]���o�C�g�� 8byte */
    tlmSIZE16,      /**< �]���o�C�g�� 16byte */
    tlmSIZE32       /**< �]���o�C�g�� 32byte */
};


/**
 *
 *
 */
enum tlmAXICACHE {


};

/** �ی샆�j�b�g
 *
 * �A�N�Z�X�ی���`���܂��B
 */
enum tlmAXISAVEUNIT {


};

/**�A�N�Z�X���
 *
 * �A�N�Z�X��ʂ��`���܂��B
 */
enum tlmAXIACCESS {
    tlmNOMALACCESS   = 0, /**< �ʏ�A�N�Z�X*/
    tlmSEMAPHORE,         /**< �r���A�N�Z�X */
    tlmLOCK,              /**< ���b�N�A�N�Z�X */
    tlmACCESSRESERVE      /**< �\�� */
};

/**����
 *
 * �����̃^�C�v���`���܂��B
 */
enum tlmAXICALL {
    tlmOKAY   = 0, /**< �ʏ�A�N�Z�X���� */
    tlmEXOKAY,     /**< �r���A�N�Z�X���� */
    tlmSLVERR,     /**< �X���[�u�G���[   */
    tlmDECERR      /**< �f�R�[�h�G���[   */
};

#endif /* __tlm_config_h */


