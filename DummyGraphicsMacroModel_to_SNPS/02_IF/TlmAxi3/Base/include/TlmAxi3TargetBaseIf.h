/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file TlmAxi3TargetBaseIf.h
 * @brief TLM AXI3 base interface class (header)
 */
#ifndef TLM_AXI3_TARGET_BASE_IF_H
#define TLM_AXI3_TARGET_BASE_IF_H

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>
#include <systemc.h>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "TlmAxi3Payload.h"

#define TLM_AXI_TARGET_BASE_DEBUG

/**
 * @brief TLM AXI�^�[�Q�b�gI/F���N���X
 **/
class TlmAxi3TargetBaseIf {
private:
  typedef enum e_InitiatorChannels {
    B = 0,
    R,
    SizeOfInitiatorChannels
  } e_INITIATOR_CHANNELS;

  typedef enum e_TargetChannels {
    AW = 0,
    W,
    AR,
    SizeOfTargetChannels
  } e_TARGET_CHANNELS;

public:
  tlm_utils::simple_target_socket<TlmAxi3TargetBaseIf, 64, tlm::tlm_base_protocol_types>    target_AW; /*< tlm_axi_target_AW_socket */
  tlm_utils::simple_target_socket<TlmAxi3TargetBaseIf, 64, tlm::tlm_base_protocol_types>    target_W;  /*< tlm_axi_target_W_socket */
  tlm_utils::simple_initiator_socket<TlmAxi3TargetBaseIf, 64, tlm::tlm_base_protocol_types> target_B;  /*< tlm_axi_target_B_socket */
  tlm_utils::simple_target_socket<TlmAxi3TargetBaseIf, 64, tlm::tlm_base_protocol_types>    target_AR; /*< tlm_axi_target_AR_socket */
  tlm_utils::simple_initiator_socket<TlmAxi3TargetBaseIf, 64, tlm::tlm_base_protocol_types> target_R;  /*< tlm_axi_target_R_socket */

public:
  /**
   * �R���X�g���N�^
   *
   * �R���X�g���N�^�B
   **/
  TlmAxi3TargetBaseIf(const char* name = NULL);

  /**
   * �f�X�g���N�^
   *
   * �f�X�g���N�^�B
   **/
  virtual ~TlmAxi3TargetBaseIf(void);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                            tlm::tlm_phase&           phase,
                            sc_core::sc_time&         t);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);

  /**
   * AXI-AR�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                            tlm::tlm_phase&           phase,
                            sc_core::sc_time&         t);

  /**
   * AXI-B�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);

  /**
   * AXI-B�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  virtual tlm::tlm_sync_enum
  target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                           tlm::tlm_phase&           phase,
                           sc_core::sc_time&         t);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �u���b�L���O�]�����z�֐�
   *
   * �u���b�L���O�]�����s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  virtual void
  target_AW_b_transport(tlm::tlm_generic_payload& payload,
                        sc_core::sc_time&         delay_time);

  /**
   * AXI-W�`���l������ target�\�P�b�g �u���b�L���O�]�����z�֐�
   *
   * �u���b�L���O�]�����s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  virtual void
  target_W_b_transport(tlm::tlm_generic_payload& payload,
                       sc_core::sc_time&         delay_time);

  /**
   * AXI-AR�`���l������ target�\�P�b�g �u���b�L���O�]�����z�֐�
   *
   * �u���b�L���O�]�����s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  virtual void
  target_AR_b_transport(tlm::tlm_generic_payload& payload,
                        sc_core::sc_time&         delay_time);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
   *
   * �������|�C���^�̎擾���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  virtual bool
  target_AW_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                               tlm::tlm_dmi&             data);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
   *
   * �������|�C���^�̎擾���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  virtual bool
  target_W_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                              tlm::tlm_dmi&             data);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
   *
   * �������|�C���^�̎擾���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  virtual bool
  target_AR_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                               tlm::tlm_dmi&             data);

  /**
   * AXI-B�`���l������ target�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
   *
   * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  virtual void
  target_B_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                     sc_dt::uint64 end_range);

  /**
   * AXI-R�`���l������ target�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
   *
   * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  virtual void
  target_R_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                     sc_dt::uint64 end_range);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �f�o�b�O�p�]�����z�֐�
   *
   * �f�o�b�O�p�]�����s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  virtual unsigned int
  target_AW_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-W�`���l������ target�\�P�b�g �f�o�b�O�p�]�����z�֐�
   *
   * �f�o�b�O�p�]�����s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  virtual unsigned int
  target_W_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-AR�`���l������ target�\�P�b�g �f�o�b�O�p�]�����z�֐�
   *
   * �f�o�b�O�p�]�����s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  virtual unsigned int
  target_AR_transport_dbg(tlm::tlm_generic_payload& payload);

private:
  /*
   * ���p�֐�
   */

  /**
   * AXI-AW�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���p�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_phase&           phase,
                                  sc_core::sc_time&         t);

  /**
   * AXI-W�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���p�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                 tlm::tlm_phase&           phase,
                                 sc_core::sc_time&         t);

  /**
   * AXI-AR�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���p�֐�
   *
   * Forward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                  tlm::tlm_phase&           phase,
                                  sc_core::sc_time&         t);

  /**
   * AXI-B�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Backward Path)���p�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                 tlm::tlm_phase&           phase,
                                 sc_core::sc_time&         t);

  /**
   * AXI-R�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Backward Path)���p�֐�
   *
   * Backward Path��p�����m���u���b�L���O�]���̒��p���s�Ȃ��B
   * @param  trans tlm_generic_payload
   * @param  phase TLM�t�F�[�Y
   * @param  t     �x������
   * @return       �����X�e�[�^�X
   **/
  tlm::tlm_sync_enum
  relay_target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                 tlm::tlm_phase&           phase,
                                 sc_core::sc_time&         t);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �u���b�L���O�]�����p�֐�
   *
   * �u���b�L���O�]���̒��p���s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  void
  relay_target_AW_b_transport(tlm::tlm_generic_payload& payload,
                              sc_core::sc_time&         delay_time);

  /**
   * AXI-W�`���l������ target�\�P�b�g �u���b�L���O�]�����p�֐�
   *
   * �u���b�L���O�]�����s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  void
  relay_target_W_b_transport(tlm::tlm_generic_payload& payload,
                             sc_core::sc_time&         delay_time);

  /**
   * AXI-AR�`���l������ target�\�P�b�g �u���b�L���O�]�����p�֐�
   *
   * �u���b�L���O�]���̒��p���s�Ȃ��B
   * @param trans tlm_generic_payload
   * @param t     �x������
   **/
  void
  relay_target_AR_b_transport(tlm::tlm_generic_payload& payload,
                              sc_core::sc_time&         delay_time);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
   *
   * �������|�C���^�擾�̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  bool
  relay_target_AW_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                     tlm::tlm_dmi&             data);

  /**
   * AXI-W�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
   *
   * �������|�C���^�擾�̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  bool
  relay_target_W_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                    tlm::tlm_dmi&             data);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
   *
   * �������|�C���^�擾�̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmi�N���X�C���X�^���X
   * @return xxx
   **/
  bool
  relay_target_AR_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                     tlm::tlm_dmi&             data);

  /**
   * AXI-B�`���l������ target�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
   *
   * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  void
  relay_target_B_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                           sc_dt::uint64 end_range);

  /**
   * AXI-R�`���l������ target�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
   *
   * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
   * @param start_range �J�n�A�h���X
   * @param end_range   �I���A�h���X
   */
  void
  relay_target_R_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                           sc_dt::uint64 end_range);

  /**
   * AXI-AW�`���l������ target�\�P�b�g �f�o�b�O�p�]�����p�֐�
   *
   * �f�o�b�O�p�]���̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  unsigned int
  relay_target_AW_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-W�`���l������ target�\�P�b�g �f�o�b�O�p�]�����p�֐�
   *
   * �f�o�b�O�p�]���̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  unsigned int
  relay_target_W_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-AR�`���l������ target�\�P�b�g �f�o�b�O�p�]�����p�֐�
   *
   * �f�o�b�O�p�]���̒��p���s�Ȃ��B
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  unsigned int
  relay_target_AR_transport_dbg(tlm::tlm_generic_payload& payload);

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
  printForwardAxiPayload(unsigned int initiator_channel,
                         tlm::tlm_generic_payload& payload);
  
private:
  unsigned long long _nb_transport_fw_counter[SizeOfTargetChannels];
  unsigned long long _nb_transport_bw_counter[SizeOfInitiatorChannels];
  unsigned long long _b_transport_counter[SizeOfTargetChannels];
  unsigned long long _get_direct_mem_ptr_counter[SizeOfTargetChannels];
  unsigned long long _invalidate_direct_mem_ptr_counter[SizeOfInitiatorChannels];
  unsigned long long _transport_dbg_counter[SizeOfTargetChannels];

  std::string  _name;
  bool _is_print;
};
#endif /* TLM_AXI3_TARGET_BASE_IF_H */
