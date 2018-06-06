/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file TlmAxi3TargetBaseIf.h
 * @brief TLM AXI3 base interface class (header)
 */
#include "TlmAxi3TargetBaseIf.h"

namespace {
  unsigned int g_TlmAxi3TargetBaseIf_number;
}

/**
 * �R���X�g���N�^
 *
 * �R���X�g���N�^�B
 **/
TlmAxi3TargetBaseIf::TlmAxi3TargetBaseIf(const char* name) :
  target_AW("target_AW"),
  target_W("target_W"),
  target_B("target_B"),
  target_AR("target_AR"),
  target_R("target_R"),
  _is_print(false) {
  /* nb_transport_fw���\�b�h��target(_AW,_W,_AR)�\�P�b�g�ւ̓o�^ */
  target_AW.register_nb_transport_fw(this, &TlmAxi3TargetBaseIf::relay_target_AW_nb_transport_fw);
  target_W.register_nb_transport_fw(this, &TlmAxi3TargetBaseIf::relay_target_W_nb_transport_fw);
  target_AR.register_nb_transport_fw(this, &TlmAxi3TargetBaseIf::relay_target_AR_nb_transport_fw);
  
  /* nb_transport_bw���\�b�h��target(_B,_R)�\�P�b�g�ւ̓o�^ */
  target_B.register_nb_transport_bw(this, &TlmAxi3TargetBaseIf::relay_target_B_nb_transport_bw);
  target_R.register_nb_transport_bw(this, &TlmAxi3TargetBaseIf::relay_target_R_nb_transport_bw);

  /* b_transport���\�b�h��target(_AW,_W,_AR)�\�P�b�g�ւ̓o�^ */
  target_AW.register_b_transport(this, &TlmAxi3TargetBaseIf::relay_target_AW_b_transport);
  target_W.register_b_transport(this, &TlmAxi3TargetBaseIf::relay_target_W_b_transport);
  target_AR.register_b_transport(this, &TlmAxi3TargetBaseIf::relay_target_AR_b_transport);

  /* get_direct_mem_ptr���\�b�h��target(_AW,_W,_AR)�\�P�b�g�ւ̓o�^ */
  target_AW.register_get_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_AW_get_direct_mem_ptr);
  target_W.register_get_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_W_get_direct_mem_ptr);
  target_AR.register_get_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_AR_get_direct_mem_ptr);

  /* invalidate_direct_mem_ptr���\�b�h��target(_B,_R)�\�P�b�g�ւ̓o�^ */
  target_B.register_invalidate_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_B_invalidate_direct_mem_ptr);
  target_R.register_invalidate_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_R_invalidate_direct_mem_ptr);

  /* transport_dbg���\�b�h��target(_AW,_W,_AR)�\�P�b�g�ւ̓o�^ */
  target_AW.register_transport_dbg(this, &TlmAxi3TargetBaseIf::relay_target_AW_transport_dbg);
  target_W.register_transport_dbg(this, &TlmAxi3TargetBaseIf::relay_target_W_transport_dbg);
  target_AR.register_transport_dbg(this, &TlmAxi3TargetBaseIf::relay_target_AR_transport_dbg);
    
    /* �e�J�E���^�̏����� */
  for (unsigned int i = 0; i < SizeOfInitiatorChannels; i++) {
    _nb_transport_bw_counter[i]           = 0;
    _invalidate_direct_mem_ptr_counter[i] = 0;
  }

  for (unsigned int i = 0; i < SizeOfTargetChannels; i++) {
    _nb_transport_fw_counter[i]    = 0;
    _b_transport_counter[i]        = 0;
    _get_direct_mem_ptr_counter[i] = 0;
    _transport_dbg_counter[i]      = 0;
  }
  
  /* I/F���̏����� */
  if (name) {
    _name = name;
  } else {
    std::stringstream ss;
    ss << "TlmAxi3TargetBaseIf_" << g_TlmAxi3TargetBaseIf_number;
    ss >> _name;
    g_TlmAxi3TargetBaseIf_number++;
  }
}

/**
 * �f�X�g���N�^
 *
 * �f�X�g���N�^�B
 **/
TlmAxi3TargetBaseIf::~TlmAxi3TargetBaseIf() {
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
 *
 * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t     �x������
 * @return       �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3TargetBaseIf::target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                  tlm::tlm_phase&           phase,
                                                  sc_core::sc_time&         t) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf :: not support nb_transport_fw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-W�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
 *
 * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t     �x������
 * @return       �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3TargetBaseIf::target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                 tlm::tlm_phase&           phase,
                                                 sc_core::sc_time&         t) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf :: not support nb_transport_fw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-AR�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
 *
 * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t     �x������
 * @return       �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3TargetBaseIf::target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                  tlm::tlm_phase&           phase,
                                                  sc_core::sc_time&         t) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf :: not support nb_transport_fw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-B�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
 *
 * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t     �x������
 * @return       �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3TargetBaseIf::target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                 tlm::tlm_phase&           phase,
                                                 sc_core::sc_time&         t) {
#if defined(TLM_TARGET_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-R�`���l������ target�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
 *
 * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t     �x������
 * @return       �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3TargetBaseIf::target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                 tlm::tlm_phase          & phase,
                                                 sc_core::sc_time        & t) {
#if defined(TLM_TARGET_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �u���b�L���O�]�����z�֐�
 *
 * �u���b�L���O�]�����s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3TargetBaseIf::target_AW_b_transport(tlm::tlm_generic_payload& trans,
                                              sc_core::sc_time        & delay_time) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support b_transport" << endl;
#endif
  return;
}

/**
 * AXI-W�`���l�� target�\�P�b�g �u���b�L���O�]�����z�֐�
 *
 * �u���b�L���O�]�����s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3TargetBaseIf::target_W_b_transport(tlm::tlm_generic_payload& trans,
                                             sc_core::sc_time        & delay_time) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support b_transport" << endl;
#endif
  return;
}

/**
 * AXI-AR�`���l�� target�\�P�b�g �u���b�L���O�]�����z�֐�
 *
 * �u���b�L���O�]�����s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3TargetBaseIf::target_AR_b_transport(tlm::tlm_generic_payload& trans,
                                              sc_core::sc_time        & delay_time) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support b_transport" << endl;
#endif
  return;
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
 *
 * �������|�C���^�̎擾���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3TargetBaseIf::target_AW_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                     tlm::tlm_dmi&             data) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support get_direct_mem_ptr" << endl;
#endif
  return false;
}

/**
 * AXI-W�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
 *
 * �������|�C���^�̎擾���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3TargetBaseIf::target_W_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                    tlm::tlm_dmi&             data) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support get_direct_mem_ptr" << endl;
#endif
  return false;
}

/**
 * AXI-AR�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
 *
 * �������|�C���^�̎擾���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3TargetBaseIf::target_AR_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                     tlm::tlm_dmi&             data) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support get_direct_mem_ptr" << endl;
#endif
  return false;
}

/**
 * AXI-B�`���l������ target�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
 *
 * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
 * @param start_range �J�n�A�h���X
 * @param end_range   �I���A�h���X
 */
void
TlmAxi3TargetBaseIf::target_B_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                           sc_dt::uint64 end_range) {
#if defined(TLM_TARGET_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-R�`���l������target�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
 *
 * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
 * @param start_range �J�n�A�h���X
 * @param end_range   �I���A�h���X
 */
void
TlmAxi3TargetBaseIf::target_R_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                           sc_dt::uint64 end_range) {
#if defined(TLM_TARGET_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �f�o�b�O�p�]�����z�֐�
 *
 * �f�o�b�O�p�]�����s�Ȃ��B
 * @param payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3TargetBaseIf::target_AW_transport_dbg(tlm::tlm_generic_payload& payload) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support transport_dbg" << endl;
#endif
  return 0;
}

/**
 * AXI-W�`���l������ target�\�P�b�g �f�o�b�O�p�]�����z�֐�
 *
 * �f�o�b�O�p�]�����s�Ȃ��B
 * @param payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3TargetBaseIf::target_W_transport_dbg(tlm::tlm_generic_payload& payload) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support transport_dbg" << endl;
#endif
  return 0;
}

/**
 * AXI-AR�`���l������ target�\�P�b�g �f�o�b�O�p�]�����z�֐�
 *
 * �f�o�b�O�p�]�����s�Ȃ��B
 * @param payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3TargetBaseIf::target_AR_transport_dbg(tlm::tlm_generic_payload& payload) {
#if defined(TLM_AXI_TARGET_BASE_DEBUG)
  cout << " TlmAxi3TargetBaseIf not support transport_dbg" << endl;
#endif
  return 0;
}

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
TlmAxi3TargetBaseIf::relay_target_AW_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                        tlm::tlm_phase&           phase,
                                                        sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
    printForwardAxiPayload(AW, trans);
  }

  result = target_AW_nb_transport_fw(trans, phase, t);

  _nb_transport_fw_counter[AW]++;

  return result;
}

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
TlmAxi3TargetBaseIf::relay_target_W_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                       tlm::tlm_phase&           phase,
                                                       sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
    printForwardAxiPayload(W, trans);
  }

  result = target_W_nb_transport_fw(trans, phase, t);

  _nb_transport_fw_counter[W]++;

  return result;
}

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
TlmAxi3TargetBaseIf::relay_target_AR_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                        tlm::tlm_phase&           phase,
                                                        sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
    printForwardAxiPayload(AR, trans);
  }

  result = target_AR_nb_transport_fw(trans, phase, t);

  _nb_transport_fw_counter[AR]++;

  return result;
}

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
TlmAxi3TargetBaseIf::relay_target_B_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                                                       sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = target_B_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[B]++;

  return result;
}

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
TlmAxi3TargetBaseIf::relay_target_R_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                                                       sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = target_R_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[R]++;

  return result;
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �u���b�L���O�]�����p�֐�
 *
 * �u���b�L���O�]���̒��p���s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3TargetBaseIf::relay_target_AW_b_transport(tlm::tlm_generic_payload& payload,
                                                    sc_core::sc_time&         delay_time) {
  if (_is_print) {
  }

  target_AW_b_transport(payload, delay_time);

  _b_transport_counter[AW]++;
}

/**
 * AXI-W�`���l������ target�\�P�b�g �u���b�L���O�]�����p�֐�
 *
 * �u���b�L���O�]�����s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3TargetBaseIf::relay_target_W_b_transport(tlm::tlm_generic_payload& payload,
                                                   sc_core::sc_time&         delay_time) {
  if (_is_print) {
  }

  target_W_b_transport(payload, delay_time);

  _b_transport_counter[W]++;
}

/**
 * AXI-AR�`���l������ target�\�P�b�g �u���b�L���O�]�����p�֐�
 *
 * �u���b�L���O�]���̒��p���s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3TargetBaseIf::relay_target_AR_b_transport(tlm::tlm_generic_payload& payload,
                                                    sc_core::sc_time&         delay_time) {
  if (_is_print) {
  }

  target_AR_b_transport(payload, delay_time);

  _b_transport_counter[AR]++;
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
 *
 * �������|�C���^�擾�̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3TargetBaseIf::relay_target_AW_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                           tlm::tlm_dmi&             data) {
  bool result;

  if (_is_print) {
  }

  result = target_AW_get_direct_mem_ptr(payload, data);

  _get_direct_mem_ptr_counter[AW]++;

  return result;
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
 *
 * �������|�C���^�擾�̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3TargetBaseIf::relay_target_W_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                          tlm::tlm_dmi&             data) {
  bool result;

  if (_is_print) {
  }

  result = target_W_get_direct_mem_ptr(payload, data);

  _get_direct_mem_ptr_counter[W]++;

  return result;
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
 *
 * �������|�C���^�擾�̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3TargetBaseIf::relay_target_AR_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                           tlm::tlm_dmi&             data) {
  bool result;

  if (_is_print) {
  }

  result = target_AR_get_direct_mem_ptr(payload, data);

  _get_direct_mem_ptr_counter[AR]++;

  return result;
}

/**
 * AXI-B�`���l������ target�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
 *
 * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
 * @param start_range �J�n�A�h���X
 * @param end_range   �I���A�h���X
 */
void
TlmAxi3TargetBaseIf::relay_target_B_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                 sc_dt::uint64 end_range) {
  if (_is_print) {
  }

  target_B_invalidate_direct_mem_ptr(start_range, end_range);

  _invalidate_direct_mem_ptr_counter[B]++;
}

/**
 * AXI-R�`���l������ target�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
 *
 * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
 * @param start_range �J�n�A�h���X
 * @param end_range   �I���A�h���X
 */
void
TlmAxi3TargetBaseIf::relay_target_R_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                 sc_dt::uint64 end_range) {
  if (_is_print) {
  }
  
  target_R_invalidate_direct_mem_ptr(start_range, end_range);
  
  _invalidate_direct_mem_ptr_counter[R]++;
}

/**
 * AXI-AW�`���l������ target�\�P�b�g �f�o�b�O�p�]�����p�֐�
 *
 * �f�o�b�O�p�]���̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3TargetBaseIf::relay_target_AW_transport_dbg(tlm::tlm_generic_payload& payload) {
  unsigned int result;

  if (_is_print) {
  }

  result = target_AW_transport_dbg(payload);

  _transport_dbg_counter[AW]++;

  return result;
}

/**
 * AXI-W�`���l������ target�\�P�b�g �f�o�b�O�p�]�����p�֐�
 *
 * �f�o�b�O�p�]���̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3TargetBaseIf::relay_target_W_transport_dbg(tlm::tlm_generic_payload& payload) {
  unsigned int result;

  if (_is_print) {
  }

  result = target_W_transport_dbg(payload);

  _transport_dbg_counter[W]++;

  return result;
}

/**
 * AXI-AR�`���l������ target�\�P�b�g �f�o�b�O�p�]�����p�֐�
 *
 * �f�o�b�O�p�]���̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3TargetBaseIf::relay_target_AR_transport_dbg(tlm::tlm_generic_payload& payload) {
  unsigned int result;

  if (_is_print) {
  }

  result = target_AR_transport_dbg(payload);

  _transport_dbg_counter[AR]++;

  return result;
}

/*
 * �f�o�b�O�����֐�
 */

/**
 * ���MAXI payload�o�͊J�n�֐�
 *
 * �C�j�V�G�[�^���瑗�M�����AXI payload�̏o�͂��J�n����
 */
void
TlmAxi3TargetBaseIf::startPrintForwardAxiPayload(void) {
  _is_print = true;
}

/**
 * ���MAXI payload�o�͒�~�֐�
 *
 * �C�j�V�G�[�^���瑗�M�����AXI payload�̏o�͂��~����
 */
void
TlmAxi3TargetBaseIf::finishPrintForwardAxiPayload(void) {
  _is_print = false;
}

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
TlmAxi3TargetBaseIf::printForwardAxiPayload(unsigned int initiator_channel,
                                            tlm::tlm_generic_payload& payload) {
  TlmAxi3Payload* axi(NULL);
  
  payload.get_extension(axi);

  if (axi) {
    std::cout << "[TlmAxi3TargetBaseIf] "
              << sc_time_stamp()
              << " @"
              << _name
              << ":";

    switch (initiator_channel) {
    case AW:
      std::cout << std::dec
                << " AW = {count="
                << _nb_transport_fw_counter[AW];
      std::cout << std::hex
                << std::showbase
                << ",ADDR="
                << axi->getAWADDR()
                << std::dec
                << ",LEN="
                << static_cast<unsigned int>(axi->getAWLEN())
                << ",SIZE="
                << static_cast<unsigned int>(axi->getAWSIZE())
                << ",BURST="
                << static_cast<unsigned int>(axi->getAWBURST())
                << ",LOCK="
                << static_cast<unsigned int>(axi->getAWLOCK())
                << ",CACHE="
                << static_cast<unsigned int>(axi->getAWCACHE())
                << ",PROT="
                << static_cast<unsigned int>(axi->getAWPROT())
                << ",ID="
                << static_cast<unsigned int>(axi->getAWID());
      std::cout << "}";
    case W:
      std::cout << std::dec
                << "  W = {count="
                << _nb_transport_fw_counter[W];
      std::cout << std::hex
                << ",LAST="
                << axi->getWLAST();
      for (unsigned int i = 0; i < axi->getByteSize(); ++i) {
        std::cout << ",DATA[" << i << "]="
                  << std::hex
                  << std::showbase
                  << (axi->getWDATA())[i]
                  << std::dec;
      }
      for (unsigned int i = 0; i < axi->getByteSize(); ++i) {
        std::cout << ",STRB[" << i << "]="
                  << std::hex
                  << std::showbase
                  << (axi->getWSTRB())[i]
                  << std::dec;
      }
      std::cout << ",ID="
                << static_cast<unsigned int>(axi->getWID());
      std::cout << "}";
      break;
    case AR:
      std::cout << std::dec
                << " AR = {count="
                << _nb_transport_fw_counter[AR];
      std::cout << std::hex
                << ",ADDR="
                << axi->getARADDR()
                << ",LEN="
                << static_cast<unsigned int>(axi->getARLEN())
                << ",SIZE="
                << static_cast<unsigned int>(axi->getARSIZE())
                << ",BURST="
                << static_cast<unsigned int>(axi->getARBURST())
                << ",LOCK="
                << static_cast<unsigned int>(axi->getARLOCK())
                << ",CACHE="
                << static_cast<unsigned int>(axi->getARCACHE())
                << ",PROT="
                << static_cast<unsigned int>(axi->getARPROT())
                << ",ID="
                << static_cast<unsigned int>(axi->getARID());
      std::cout << "}";
      break;
    default:
      break;
    }
  }
  
  std::cout << std::endl;
}

