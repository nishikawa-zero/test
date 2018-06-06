/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file TlmAxi3InitiatorBaseIf.h
 * @brief TLM AXI3 base interface class (source)
 */
#include "TlmAxi3InitiatorBaseIf.h"

namespace {
  unsigned int g_TlmAxi3InitiatorBaseIf_number;
}

/**
 * �R���X�g���N�^
 *
 * �R���X�g���N�^�B
 **/
TlmAxi3InitiatorBaseIf::TlmAxi3InitiatorBaseIf(const char* name) :
  initiator_AW("initiator_AW"),
  initiator_W("initiator_W"),
  initiator_B("initiator_B"),
  initiator_AR("initiator_AR"),
  initiator_R("initiator_R"),
  _is_print(false)
{
	//std::cout << "IN : " << __FILE__ << " / " << __FUNCTION__ << std::endl;

  /* nb_transport_fw���\�b�h��Initiator(_B,_R)�\�P�b�g�ւ̓o�^ */
  initiator_B.register_nb_transport_fw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_nb_transport_fw);
  initiator_R.register_nb_transport_fw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_nb_transport_fw);

  /* nb_transport_bw���\�b�h��initiator(_AW,_W,_AR)�\�P�b�g�ւ̓o�^ */
  initiator_AW.register_nb_transport_bw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AW_nb_transport_bw);
  initiator_W.register_nb_transport_bw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_W_nb_transport_bw);
  initiator_AR.register_nb_transport_bw(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AR_nb_transport_bw);

  /* b_transport���\�b�h��initiator(_B,_R)�\�P�b�g�ւ̓o�^ */
  initiator_B.register_b_transport(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_b_transport);
  initiator_R.register_b_transport(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_b_transport);

  /* get_direct_mem_ptr���\�b�h��initiator(_B,_R)�\�P�b�g�ւ̓o�^ */
  initiator_B.register_get_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_get_direct_mem_ptr);
  initiator_R.register_get_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_get_direct_mem_ptr);

  /* invalidate_direct_mem_ptr���\�b�h��initiator(_AW,_W,_AR)�\�P�b�g�ւ̓o�^ */
  initiator_AW.register_invalidate_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AW_invalidate_direct_mem_ptr);
  initiator_W.register_invalidate_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_W_invalidate_direct_mem_ptr);
  initiator_AR.register_invalidate_direct_mem_ptr(this, &TlmAxi3InitiatorBaseIf::relay_initiator_AR_invalidate_direct_mem_ptr);

  /* transport_dbg���\�b�h��initiator(_B,_R)�\�P�b�g�ւ̓o�^ */
  initiator_B.register_transport_dbg(this, &TlmAxi3InitiatorBaseIf::relay_initiator_B_transport_dbg);
  initiator_R.register_transport_dbg(this, &TlmAxi3InitiatorBaseIf::relay_initiator_R_transport_dbg);

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
    ss << "TlmAxi3InitiatorBaseIf_" << g_TlmAxi3InitiatorBaseIf_number;
    ss >> _name;
    g_TlmAxi3InitiatorBaseIf_number++;
  }
}


/**
 * �f�X�g���N�^
 *
 * �f�X�g���N�^�B
 **/
TlmAxi3InitiatorBaseIf::~TlmAxi3InitiatorBaseIf(void) {
}

/**
 * AXI-B�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
 *
 * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t     �x������
 * @return       �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf :: not support nb_transport_fw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-W�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Forward Path)���z�֐�
 *
 * Forward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t     �x������
 * @return       �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf :: not support nb_transport_fw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AWI-AW�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
 *
 * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t �x������
 * @return �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase&           phase,
                                                     sc_core::sc_time&         t)
{
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AWI-W�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
 *
 * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t �x������
 * @return �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                    tlm::tlm_phase&           phase,
                                                    sc_core::sc_time&         t)
{
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AWI-AR�`���l������ initiator�\�P�b�g �m���u���b�L���O�]��(Backward Path)���z�֐�
 *
 * Backward Path��p�����m���u���b�L���O�]�����s�Ȃ��B
 * @param  trans tlm_generic_payload
 * @param  phase TLM�t�F�[�Y
 * @param  t �x������
 * @return �����X�e�[�^�X
 **/
tlm::tlm_sync_enum
TlmAxi3InitiatorBaseIf::initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                     tlm::tlm_phase&           phase,
                                                     sc_core::sc_time&         t)
{
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support nb_transport_bw" << endl;
#endif
  return tlm::TLM_COMPLETED;
}

/**
 * AXI-B�`���l�� initiator�\�P�b�g �u���b�L���O�]�����z�֐�
 *
 * �u���b�L���O�]�����s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3InitiatorBaseIf::initiator_B_b_transport(tlm::tlm_generic_payload& trans,
                                                sc_core::sc_time&         delay_time) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support b_transport" << endl;
#endif
  return;
}

/**
 * AXI-R�`���l�� initiator�\�P�b�g �u���b�L���O�]�����z�֐�
 *
 * �u���b�L���O�]�����s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3InitiatorBaseIf::initiator_R_b_transport(tlm::tlm_generic_payload& trans,
                                                sc_core::sc_time&         delay_time) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support b_transport" << endl;
#endif
  return;
}

/**
 * AXI-B�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
 *
 * �������|�C���^�̎擾���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                       tlm::tlm_dmi&             data) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support get_direct_mem_ptr" << endl;
#endif
  return false;
}

/**
 * AXI-R�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���z�֐�
 *
 * �������|�C���^�̎擾���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                       tlm::tlm_dmi&             data) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support get_direct_mem_ptr" << endl;
#endif
  return false;
}

/**
 * AXI-AW�`���l������ initiator�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
 *
 * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
 * @param start_range �J�n�A�h���X
 * @param end_range �I���A�h���X
 */
void
TlmAxi3InitiatorBaseIf::initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                               sc_dt::uint64 end_range) {
#if defined(TLM_Initiator_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-W�`���l������ initiator�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
 *
 * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
 * @param start_range �J�n�A�h���X
 * @param end_range �I���A�h���X
 */
void
TlmAxi3InitiatorBaseIf::initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                              sc_dt::uint64 end_range) {
#if defined(TLM_INITIATOR_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-AR�`���l������ initiator�\�P�b�g �������|�C���^�g�p���גʒm���z�֐�
 *
 * �C�j�V�G�[�^�Ƀ������|�C���^�̎g�p���ׂ�ʒm����B
 * @param start_range �J�n�A�h���X
 * @param end_range �I���A�h���X
 */
void
TlmAxi3InitiatorBaseIf::initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                               sc_dt::uint64 end_range) {
#if defined(TLM_INITIATOR_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-B�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����z�֐�
 *
 * �f�o�b�O�p�]�����s�Ȃ��B
 * @param payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::initiator_B_transport_dbg(tlm::tlm_generic_payload& payload) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support transport_dbg" << endl;
#endif
  return 0;
}

/**
 * AXI-R�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����z�֐�
 *
 * �f�o�b�O�p�]�����s�Ȃ��B
 * @param payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::initiator_R_transport_dbg(tlm::tlm_generic_payload& payload) {
#if defined(TLM_AXI_INITIATOR_BASE_DEBUG)
  cout << " TlmAxi3InitiatorBaseIf not support transport_dbg" << endl;
#endif
  return 0;
}

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
TlmAxi3InitiatorBaseIf::relay_initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t)
{
	//std::cout << "IN : " << __FILE__ << " / " << __FUNCTION__ << std::endl;

  tlm::tlm_sync_enum result;

  if (_is_print) {
    printForwardAxiPayload(B, trans);
  }

  result = initiator_B_nb_transport_fw(trans, phase, t);

  _nb_transport_fw_counter[B]++;

  return result;
}

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
TlmAxi3InitiatorBaseIf::relay_initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
    printForwardAxiPayload(R, trans);
  }

  result = initiator_R_nb_transport_fw(trans, phase, t);

  _nb_transport_fw_counter[R]++;

  return result;
}

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
TlmAxi3InitiatorBaseIf::relay_initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                           tlm::tlm_phase&           phase,
                                                           sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = initiator_AW_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[AW]++;

  return result;
}

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
TlmAxi3InitiatorBaseIf::relay_initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                          tlm::tlm_phase&           phase,
                                                          sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = initiator_W_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[W]++;

  return result;
}

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
TlmAxi3InitiatorBaseIf::relay_initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                                           tlm::tlm_phase&           phase,
                                                           sc_core::sc_time&         t) {
  tlm::tlm_sync_enum result;

  if (_is_print) {
  }

  result = initiator_AR_nb_transport_bw(trans, phase, t);

  _nb_transport_bw_counter[AR]++;

  return result;
}

/**
 * AXI-B�`���l������ initiator�\�P�b�g �u���b�L���O�]�����p�֐�
 *
 * �u���b�L���O�]���̒��p���s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3InitiatorBaseIf::relay_initiator_B_b_transport(tlm::tlm_generic_payload& payload,
                                                      sc_core::sc_time&         delay_time) {
  if (_is_print) {
  }

  initiator_B_b_transport(payload, delay_time);

  _b_transport_counter[B]++;
}

/**
 * AXI-R�`���l������ initiator�\�P�b�g �u���b�L���O�]�����p�֐�
 *
 * �u���b�L���O�]���̒��p���s�Ȃ��B
 * @param trans tlm_generic_payload
 * @param t     �x������
 **/
void
TlmAxi3InitiatorBaseIf::relay_initiator_R_b_transport(tlm::tlm_generic_payload& payload,
                                                      sc_core::sc_time&         delay_time) {
  if (_is_print) {
  }

  initiator_R_b_transport(payload, delay_time);

  _b_transport_counter[R]++;
}

/**
 * AXI-B�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
 *
 * �������|�C���^�擾�̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::relay_initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                             tlm::tlm_dmi&             data) {
  bool result;

  if (_is_print) {
  }

  result = initiator_B_get_direct_mem_ptr(payload, data);

  _get_direct_mem_ptr_counter[B]++;

  return result;
}

/**
 * AXI-R�`���l������ initiator�\�P�b�g �_�C���N�g�������|�C���^�擾���p�֐�
 *
 * �������|�C���^�擾�̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmi�N���X�C���X�^���X
 * @return xxx
 **/
bool
TlmAxi3InitiatorBaseIf::relay_initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                                             tlm::tlm_dmi&             data) {
  bool result;

  if (_is_print) {
  }

  result = initiator_R_get_direct_mem_ptr(payload, data);

  _get_direct_mem_ptr_counter[R]++;

  return result;
}

/**
 * AXI-AW�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
 *
 * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
 * @param start_range �J�n�A�h���X
 * @param end_range   �I���A�h���X
 */
void
TlmAxi3InitiatorBaseIf::relay_initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                     sc_dt::uint64 end_range) {
  if (_is_print) {
  }

  initiator_AW_invalidate_direct_mem_ptr(start_range, end_range);

  _invalidate_direct_mem_ptr_counter[AW]++;
}

/**
 * AXI-W�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
 *
 * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
 * @param start_range �J�n�A�h���X
 * @param end_range   �I���A�h���X
 */
void
TlmAxi3InitiatorBaseIf::relay_initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                    sc_dt::uint64 end_range) {
  if (_is_print) {
  }
  
  initiator_W_invalidate_direct_mem_ptr(start_range, end_range);
  
  _invalidate_direct_mem_ptr_counter[W]++;
}

/**
 * AXI-AR�`���l������initiator�\�P�b�g �������|�C���^�g�p���גʒm���p�֐�
 *
 * �C�j�V�G�[�^�ւ̃������|�C���^�g�p���גʒm�̒��p���s���B
 * @param start_range �J�n�A�h���X
 * @param end_range   �I���A�h���X
 */
void
TlmAxi3InitiatorBaseIf::relay_initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                                     sc_dt::uint64 end_range) {
  if (_is_print) {
  }

  initiator_AR_invalidate_direct_mem_ptr(start_range, end_range);

  _invalidate_direct_mem_ptr_counter[AR]++;
}

/**
 * AXI-B�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����p�֐�
 *
 * �f�o�b�O�p�]���̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::relay_initiator_B_transport_dbg(tlm::tlm_generic_payload& payload) {
  unsigned int result;

  if (_is_print) {
  }

  result = initiator_B_transport_dbg(payload);

  _transport_dbg_counter[B]++;

  return result;
}

/**
 * AXI-R�`���l������ initiator�\�P�b�g �f�o�b�O�p�]�����p�֐�
 *
 * �f�o�b�O�p�]���̒��p���s�Ȃ��B
 * @param  payload tlm_generic_payload
 * @return xxx
 **/
unsigned int
TlmAxi3InitiatorBaseIf::relay_initiator_R_transport_dbg(tlm::tlm_generic_payload& payload) {
  unsigned int result;

  if (_is_print) {
  }

  result = initiator_R_transport_dbg(payload);

  _transport_dbg_counter[R]++;

  return result;
}

/**
 * ���MAXI payload�o�͊J�n�֐�
 *
 * �C�j�V�G�[�^���瑗�M�����AXI payload�̏o�͂��J�n����
 */
void
TlmAxi3InitiatorBaseIf::startPrintForwardAxiPayload(void) {
  _is_print = true;
}

/**
 * ���MAXI payload�o�͒�~�֐�
 *
 * �C�j�V�G�[�^���瑗�M�����AXI payload�̏o�͂��~����
 */
void
TlmAxi3InitiatorBaseIf::finishPrintForwardAxiPayload(void) {
  _is_print = false;
}

/**
 * ���MAXI payload�o�͊֐�
 *
 * �C�j�V�G�[�^���瑗�M�����AXI payload�̓��e���o�͂���
 * @param initiator_channel ���M�`���l��
 * @param payload           tlm_generic_payload
 **/
void
TlmAxi3InitiatorBaseIf::printForwardAxiPayload(unsigned int              initiator_channel,
                                               tlm::tlm_generic_payload& payload) {
  TlmAxi3Payload* axi(NULL);
  
  payload.get_extension(axi);
  
  if (axi) {
    std::cout << "[TlmAxi3InitiatorBaseIf] "
              << sc_time_stamp()
              << " @"
              << _name
              << ":";

    switch (initiator_channel) {
    case B:
      std::cout << std::dec
                << "  B = {count="
                << _nb_transport_fw_counter[B];
      std::cout << std::hex
                << ",RESP="
                << static_cast<unsigned int>(axi->getBRESP())
                << ",ID="
                << static_cast<unsigned int>(axi->getBID());
      std::cout << "}";
    case R:
      std::cout << std::dec
                << "  R = {count="
                << _nb_transport_fw_counter[R];
      std::cout << std::hex
                << ",LAST="
                << axi->getRLAST();
      for (unsigned int i = 0; i < axi->getByteSize(); ++i) {
        std::cout << ",DATA[" << i << "]="
                  << std::hex
                  << std::showbase
                  << (axi->getRDATA())[i]
                  << std::dec;
      }
      std::cout << ",RESP="
                << static_cast<unsigned int>(axi->getRRESP())
                << ",ID="
                << static_cast<unsigned int>(axi->getRID());
      std::cout << "}";
      break;
    default:
      break;
    }
  }
  
  std::cout << std::endl;
}

