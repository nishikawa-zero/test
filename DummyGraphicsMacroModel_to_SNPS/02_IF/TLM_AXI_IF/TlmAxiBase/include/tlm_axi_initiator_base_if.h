/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file tlm_axi_initiator_base_if.h
 * @brief TLM�C�j�V�G�[�^I/F���N���X(header)
 *
 * @date $Date: 2009/02/03 00:54:40 $
 * @version $Id: tlm_axi_initiator_base_if.h,v 1.3 2009/02/03 00:54:40 shunsaku Exp $
 *
 * @todo axi_payload�e���v���[�g�Ή�(����unsigned long long �̂�)
 */
#if !defined __tlm_axi_initiator_base_if_h
#define __tlm_axi_initiator_base_if_h

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <systemc.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "axi_payload.h"
#include "EndianSwap.h"

#define TLM_AXI_INITIATOR_BASE_DEBUG

/**
 * @brief TLM�C�j�V�G�[�^I/F���N���X
 **/
class tlm_axi_initiator_base_if {
private:
  typedef enum e_EndianConvertModes {
    OFF = 0,
    LITTLE_BIG,
    SizeOfEndianConvertModes
  } e_ENDIAN_CONVERT_MODES;

  typedef enum e_InitiatorChannels {
    AW = 0,
    W,
    AR,
    SizeOfInitiatorChannels
  } e_INITIATOR_CHANNELS;

  typedef enum e_TargetChannels {
    B = 0,
    R,
    SizeOfTargetChannels
  } e_TARGET_CHANNELS;

public:
  tlm_utils::simple_initiator_socket<tlm_axi_initiator_base_if, 64, tlm::tlm_base_protocol_types> initiator_AW; /*< tlm_axi_initiator_AW_socket */
  tlm_utils::simple_initiator_socket<tlm_axi_initiator_base_if, 64, tlm::tlm_base_protocol_types> initiator_W;  /*< tlm_axi_initiator_W_socket */
  tlm_utils::simple_target_socket<tlm_axi_initiator_base_if, 64, tlm::tlm_base_protocol_types>    initiator_B;  /*< tlm_axi_initiator_B_socket */
  tlm_utils::simple_initiator_socket<tlm_axi_initiator_base_if, 64, tlm::tlm_base_protocol_types> initiator_AR; /*< tlm_axi_initiator_AR_socket */
  tlm_utils::simple_target_socket<tlm_axi_initiator_base_if, 64, tlm::tlm_base_protocol_types>    initiator_R;  /*< tlm_axi_initiator_R_socket */

public:
  /**
   * �R���X�g���N�^
   *
   * �R���X�g���N�^�B
   **/
  tlm_axi_initiator_base_if(const char*  name                = NULL,
                            unsigned int endian_convert_mode = OFF);

  /**
   * �f�X�g���N�^
   *
   * �f�X�g���N�^�B
   **/
  virtual ~tlm_axi_initiator_base_if(void);

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase&           phase,
                              sc_core::sc_time&         t);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase&           phase,
                              sc_core::sc_time&         t);

  /**
   * AXI-AW�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                               sc_core::sc_time&         t);

  /**
   * AXI-W�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase& phase,
                              sc_core::sc_time& t);

  /**
   * AXI-AR�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                               sc_core::sc_time&         t);

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �u���b�L���O�]�����z�֐�
   *
   * �u���b�L���O�]�����s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  virtual void
  initiator_B_b_transport(tlm::tlm_generic_payload& payload,
                          sc_core::sc_time&         delay_time);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �u���b�L���O�]�����z�֐�
   *
   * �u���b�L���O�]�����s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  virtual void
  initiator_R_b_transport(tlm::tlm_generic_payload& payload,
                          sc_core::sc_time&         delay_time);

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
   *
   * �������|�C���^�̎擾���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  virtual bool
  initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                 tlm::tlm_dmi&             data);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
   *
   * �������|�C���^�̎擾���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  virtual bool
  initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                 tlm::tlm_dmi&             data);

  /**
   * AXI-AW�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
   *
   * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  virtual void
  initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range);

  /**
   * AXI-W�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
   *
   * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  virtual void
  initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                        sc_dt::uint64 end_range);

  /**
   * AXI-AR�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
   *
   * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
   * @param start_range �J�n�A�h���X
   * @param end_range �I���A�h���X
   */
  virtual void
  initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range);

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����z�֐�
   *
   * �f�o�b�O�p�]�����s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  virtual unsigned int
  initiator_B_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����z�֐�
   *
   * �f�o�b�O�p�]�����s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  virtual unsigned int
  initiator_R_transport_dbg(tlm::tlm_generic_payload& payload);

private:
  /*
   * ���p�֐�
   */

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Forward Path)���p�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_phase&           phase,
                                    sc_core::sc_time&         t);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Forward Path)���p�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_phase&           phase,
                                    sc_core::sc_time&         t);

  /**
   * AXI-AW�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���p�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase&           phase,
                                     sc_core::sc_time&         t);

  /**
   * AXI-W�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���p�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_phase&           phase,
                                    sc_core::sc_time&         t);

  /**
   * AXI-AR�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���p�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase&           phase,
                                     sc_core::sc_time&         t);

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �u���b�L���O�]�����p�֐�
   *
   * �u���b�L���O�]���̒��p���s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  void
  relay_initiator_B_b_transport(tlm::tlm_generic_payload& payload,
                                sc_core::sc_time&         delay_time);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �u���b�L���O�]�����p�֐�
   *
   * �u���b�L���O�]���̒��p���s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  void
  relay_initiator_R_b_transport(tlm::tlm_generic_payload& payload,
                                sc_core::sc_time&         delay_time);

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
   *
   * �������|�C���^�擾�̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  bool
  relay_initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                       tlm::tlm_dmi&             data);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
   *
   * �������|�C���^�擾�̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  bool
  relay_initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                       tlm::tlm_dmi&             data);

  /**
   * AXI-AW�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
   *
   * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  void
  relay_initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range);

  /**
   * AXI-W�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
   *
   * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  void
  relay_initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                        sc_dt::uint64 end_range);

  /**
   * AXI-AR�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
   *
   * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  void
  relay_initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                               sc_dt::uint64 end_range);

  /**
   * AXI-B�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����p�֐�
   *
   * �f�o�b�O�p�]���̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  unsigned int
  relay_initiator_B_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-R�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����p�֐�
   *
   * �f�o�b�O�p�]���̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  unsigned int
  relay_initiator_R_transport_dbg(tlm::tlm_generic_payload& payload);

private:
  /*
   * ���[�e�B���e�B�֐�
   */
  
  /**
   * AXI payload�G���f�B�A���ϊ��֐�
   *
   * AXI payload�̃G���f�B�A����ϊ�����
   * @param payload tlm_generic_payload
   **/
  void
  convertEndian(tlm::tlm_generic_payload& payload);

public:
  /*
   * �f�o�b�O�����֐�
   */

  /**
   * ���MAXI payload�o�͊J�n�֐�
   *
   * �C�j�V�G�[�^���瑗�M�����AXI payload�̏o�͂��J�n����
   */
  void
  startPrintForwardAxiPayload(void);

  /**
   * ���MAXI payload�o�͒�~�֐�
   *
   * �C�j�V�G�[�^���瑗�M�����AXI payload�̏o�͂��~����
   */
  void
  finishPrintForwardAxiPayload(void);

private:
  /*
   * �f�o�b�O�����֐�
   */

  /**
   * ���MAXI payload�o�͊֐�
   *
   * �C�j�V�G�[�^���瑗�M�����AXI payload�̓��e���o�͂���
   * @param initiator_channel ���M�`���l��
   * @param payload           tlm_generic_payload
   **/
  void
  printForwardAxiPayload(unsigned int              initiator_channel,
                         tlm::tlm_generic_payload& payload);

private:
  unsigned long long _nb_transport_fw_counter[SizeOfTargetChannels];
  unsigned long long _nb_transport_bw_counter[SizeOfInitiatorChannels];
  unsigned long long _b_transport_counter[SizeOfTargetChannels];
  unsigned long long _get_direct_mem_ptr_counter[SizeOfTargetChannels];
  unsigned long long _invalidate_direct_mem_ptr_counter[SizeOfInitiatorChannels];
  unsigned long long _transport_dbg_counter[SizeOfTargetChannels];

  std::string _name;
  unsigned int _endian_convert_mode;

  bool _is_print;

  EndianSwap<unsigned long long, unsigned char> _endian_swapper;
};
#endif /* __tlm_axi_initiator_base_if_h */
