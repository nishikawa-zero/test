/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file  AXIDataFormatControl.h
 * @brief AXI�p�f�[�^�`������N���X
 *        AXI�̃C�j�V�G�[�^�A�^�[�Q�b�g�ԂŃf�[�^�̌`����
 *        ���ʂɂȂ�悤�ɑ��삵�܂��B
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

    /** �f�[�^�`���ϊ��isc_biguint<64> -> �o�C�g��j
     *
     *  @param[in]      biguint64_data      sc_biguint<64>�^�̃f�[�^�ւ̃|�C���^
     *  @param[in,out]  byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
     */
    void convertDataToByteStream(sc_biguint<64> *biguint64_data, unsigned char *byte);

    /** �f�[�^�`���ϊ��isc_biguint<128> -> �o�C�g��j
     *
     *  @param[in]      biguint128_data     sc_biguint<128>�^�̃f�[�^�ւ̃|�C���^
     *  @oaram[in,out]  byte                unsigned char *�^�ւ̃|�C���^�@�̈�̃T�C�Y�́A16�o�C�g�ȏ�K�v�B
     */
    void convertDataToByteStream(sc_biguint<128> *biguint128_data, unsigned char *byte);

    /** �f�[�^�`���ϊ��isc_biguint<256> -> �o�C�g��j
     *
     *  @param[in]      biguint256_data     sc_biguint<256>�^�̃f�[�^�ւ̃|�C���^
     *  @param[in,out]  byte                unsigned char *�^�ւ̃|�C���^�@�̈�̃T�C�Y�́A32�o�C�g�ȏ�K�v�B
     */
    void convertDataToByteStream(sc_biguint<256> *biguint256_data, unsigned char *byte);

    /** AXI�f�[�^�`���ϊ��isc_uint<64> -> �o�C�g��j
     *
     *  @param[in]      uint64_data         sc_uint<64>�^�̃f�[�^�ւ̃|�C���^
     *  @param[in,out]  byte                unsigned char *�^�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
     */
    void convertDataToByteStream(sc_uint<64> *uint64_data, unsigned char *byte);

    /** �f�[�^�`���ϊ��i�o�C�g�� -> sc_biguint<64>�j
     *
     *  @param[in]      byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
     *  @param[in,out]  biguint64_data      sc_biguint<64>�^�̃f�[�^�ւ̃|�C���^
     */
    void convertByteStreamToData(unsigned char *byte, sc_biguint<64> *biguint64_data);

    /** �f�[�^�`���ϊ��iunsigned long long -> �o�C�g��j
     *
     *  unsigned long long�`������A�o�C�g�e�[�u���Ƀf�[�^��ϊ����Đݒ肷��B
     *
     *  @param[in]      uint64_data         unsigned long long�^�̃f�[�^�ւ̃|�C���^
     *  @param[in,out]  byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
     */
    void convertDataToByteStream(unsigned long long *uint64_data, unsigned char *byte);

    /** �f�[�^�`���ϊ��i�o�C�g�� -> sc_biguint<128>�j
     *
     *  @param[in]      byte               unsigned char *�^�ւ̃|�C���^�@�̈�̃T�C�Y�́A16�o�C�g�ȏ�K�v�B
     *  @param[in,out]  biguint128_data    sc_biguint<128>�^�̃f�[�^�ւ̃|�C���^
     */
    void convertByteStreamToData( unsigned char *byte, sc_biguint<128> *biguint128_data);

    /** �f�[�^�`���ϊ��i�o�C�g�� -> sc_biguint<256>�j
     *
     *  @param[in]      byte                unsigned char *�^�ւ̃|�C���^�@�̈�̃T�C�Y�́A32�o�C�g�ȏ�K�v�B
     *  @param[in,out]  biguint256_data     sc_biguint<256>�^�̃f�[�^�ւ̃|�C���^
     */
    void convertByteStreamToData(unsigned char *byte, sc_biguint<256> *biguint256_data);

    /** AXI�f�[�^�`���ϊ��i�o�C�g�� -> sc_uint<64>�j
     *
     *  @param[in]      byte           unsigned char *�^�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
     *  @param[in,out]  uint64_data    sc_uint<64>�^�̃f�[�^�ւ̃|�C���^
     */
    void convertByteStreamToData(unsigned char *byte, sc_uint<64> *uint64_data);

    /** �f�[�^�`���ϊ��i�o�C�g�� -> unsigned long long�j
     *
     *  �o�C�g�񂩂�unsigned long long�`���ɕϊ�����B
     *
     *  @param[in]      byte                unsigned char *�^�̗̈�ւ̃|�C���^�@�̈�̃T�C�Y�́A8�o�C�g�ȏ�K�v�B
     *  @param[in,out]  uint64_data         unsigned long long�^�̃f�[�^�ւ̃|�C���^
     */
    void convertByteStreamToData(unsigned char *byte, unsigned long long *uint64_data);

    /**�o�[�X�g�T�C�Y��]���o�C�g���ɕϊ����܂��B
     *
     * @param[in] �o�[�X�g�T�C�Y
     * @return    �]���o�C�g��
     */
    unsigned int convertBurstSize(unsigned size);

    /** �o�[�X�g�o�X������o�[�X�g�T�C�Y�̕ϊ�
     *
     *  �o�[�X�g���̃o�X������AXI AWSIZE/ARSIZE�̕ϊ����s���B
     *  @param[in]  width   �]���o�X��
     *  @return     AWSIZE/ARSIZE�̎w��l
     */
    unsigned int convertBurstWidth2AXIAsize(int width);

    /**
     *  @brief �o�[�X�g�T�C�Y����o�X���ւ̕ϊ�
     *
     *  AXI AWSIZE/ARSIZE����o�[�X�g���̃o�X���̎Z�o���s���B
     *  @param[in]  AWSIZE/ARSIZE�̎w��l
     *  @return �]���o�X��
     */
    unsigned int convertAXIAsize2BurstWidth(int asize);

    unsigned int convertBurstSize2AXIAsize(int burst_size);
    unsigned int convertAXIAsize2BurstSize(int asize);

};
#endif /* __AXIDataFormatControl_h */
