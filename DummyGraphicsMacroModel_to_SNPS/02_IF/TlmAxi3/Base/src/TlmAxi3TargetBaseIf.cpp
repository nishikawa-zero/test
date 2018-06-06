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
 * コンストラクタ
 *
 * コンストラクタ。
 **/
TlmAxi3TargetBaseIf::TlmAxi3TargetBaseIf(const char* name) :
  target_AW("target_AW"),
  target_W("target_W"),
  target_B("target_B"),
  target_AR("target_AR"),
  target_R("target_R"),
  _is_print(false) {
  /* nb_transport_fwメソッドのtarget(_AW,_W,_AR)ソケットへの登録 */
  target_AW.register_nb_transport_fw(this, &TlmAxi3TargetBaseIf::relay_target_AW_nb_transport_fw);
  target_W.register_nb_transport_fw(this, &TlmAxi3TargetBaseIf::relay_target_W_nb_transport_fw);
  target_AR.register_nb_transport_fw(this, &TlmAxi3TargetBaseIf::relay_target_AR_nb_transport_fw);
  
  /* nb_transport_bwメソッドのtarget(_B,_R)ソケットへの登録 */
  target_B.register_nb_transport_bw(this, &TlmAxi3TargetBaseIf::relay_target_B_nb_transport_bw);
  target_R.register_nb_transport_bw(this, &TlmAxi3TargetBaseIf::relay_target_R_nb_transport_bw);

  /* b_transportメソッドのtarget(_AW,_W,_AR)ソケットへの登録 */
  target_AW.register_b_transport(this, &TlmAxi3TargetBaseIf::relay_target_AW_b_transport);
  target_W.register_b_transport(this, &TlmAxi3TargetBaseIf::relay_target_W_b_transport);
  target_AR.register_b_transport(this, &TlmAxi3TargetBaseIf::relay_target_AR_b_transport);

  /* get_direct_mem_ptrメソッドのtarget(_AW,_W,_AR)ソケットへの登録 */
  target_AW.register_get_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_AW_get_direct_mem_ptr);
  target_W.register_get_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_W_get_direct_mem_ptr);
  target_AR.register_get_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_AR_get_direct_mem_ptr);

  /* invalidate_direct_mem_ptrメソッドのtarget(_B,_R)ソケットへの登録 */
  target_B.register_invalidate_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_B_invalidate_direct_mem_ptr);
  target_R.register_invalidate_direct_mem_ptr(this, &TlmAxi3TargetBaseIf::relay_target_R_invalidate_direct_mem_ptr);

  /* transport_dbgメソッドのtarget(_AW,_W,_AR)ソケットへの登録 */
  target_AW.register_transport_dbg(this, &TlmAxi3TargetBaseIf::relay_target_AW_transport_dbg);
  target_W.register_transport_dbg(this, &TlmAxi3TargetBaseIf::relay_target_W_transport_dbg);
  target_AR.register_transport_dbg(this, &TlmAxi3TargetBaseIf::relay_target_AR_transport_dbg);
    
    /* 各カウンタの初期化 */
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
  
  /* I/F名の初期化 */
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
 * デストラクタ
 *
 * デストラクタ。
 **/
TlmAxi3TargetBaseIf::~TlmAxi3TargetBaseIf() {
}

/**
 * AXI-AWチャネル向け targetソケット ノンブロッキング転送(Forward Path)仮想関数
 *
 * Forward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-Wチャネル向け targetソケット ノンブロッキング転送(Forward Path)仮想関数
 *
 * Forward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-ARチャネル向け targetソケット ノンブロッキング転送(Forward Path)仮想関数
 *
 * Forward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-Bチャネル向け targetソケット ノンブロッキング転送(Backward Path)仮想関数
 *
 * Backward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-Rチャネル向け targetソケット ノンブロッキング転送(Backward Path)仮想関数
 *
 * Backward Pathを用いたノンブロッキング転送を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-AWチャネル向け targetソケット ブロッキング転送仮想関数
 *
 * ブロッキング転送を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
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
 * AXI-Wチャネル targetソケット ブロッキング転送仮想関数
 *
 * ブロッキング転送を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
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
 * AXI-ARチャネル targetソケット ブロッキング転送仮想関数
 *
 * ブロッキング転送を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
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
 * AXI-AWチャネル向け targetソケット ダイレクトメモリポインタ取得仮想関数
 *
 * メモリポインタの取得を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
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
 * AXI-Wチャネル向け targetソケット ダイレクトメモリポインタ取得仮想関数
 *
 * メモリポインタの取得を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
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
 * AXI-ARチャネル向け targetソケット ダイレクトメモリポインタ取得仮想関数
 *
 * メモリポインタの取得を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
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
 * AXI-Bチャネル向け targetソケット メモリポインタ使用負荷通知仮想関数
 *
 * イニシエータにメモリポインタの使用負荷を通知する。
 * @param start_range 開始アドレス
 * @param end_range   終了アドレス
 */
void
TlmAxi3TargetBaseIf::target_B_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                           sc_dt::uint64 end_range) {
#if defined(TLM_TARGET_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-Rチャネル向けtargetソケット メモリポインタ使用負荷通知仮想関数
 *
 * イニシエータにメモリポインタの使用負荷を通知する。
 * @param start_range 開始アドレス
 * @param end_range   終了アドレス
 */
void
TlmAxi3TargetBaseIf::target_R_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                                           sc_dt::uint64 end_range) {
#if defined(TLM_TARGET_BASE_DEBUG)
  cout << this->name() << " not support invalidate_direct_mem_ptr" << endl;
#endif
}

/**
 * AXI-AWチャネル向け targetソケット デバッグ用転送仮想関数
 *
 * デバッグ用転送を行なう。
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
 * AXI-Wチャネル向け targetソケット デバッグ用転送仮想関数
 *
 * デバッグ用転送を行なう。
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
 * AXI-ARチャネル向け targetソケット デバッグ用転送仮想関数
 *
 * デバッグ用転送を行なう。
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
 * 中継関数
 */

/**
 * AXI-AWチャネル向け targetソケット ノンブロッキング転送(Forward Path)中継関数
 *
 * Forward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-AWチャネル向け targetソケット ノンブロッキング転送(Forward Path)中継関数
 *
 * Forward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-ARチャネル向け targetソケット ノンブロッキング転送(Forward Path)中継関数
 *
 * Forward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-Bチャネル向け targetソケット ノンブロッキング転送(Backward Path)中継関数
 *
 * Backward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-Rチャネル向け targetソケット ノンブロッキング転送(Backward Path)中継関数
 *
 * Backward Pathを用いたノンブロッキング転送の中継を行なう。
 * @param  trans tlm_generic_payload
 * @param  phase TLMフェーズ
 * @param  t     遅延時間
 * @return       応答ステータス
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
 * AXI-AWチャネル向け targetソケット ブロッキング転送中継関数
 *
 * ブロッキング転送の中継を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
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
 * AXI-Wチャネル向け targetソケット ブロッキング転送中継関数
 *
 * ブロッキング転送を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
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
 * AXI-ARチャネル向け targetソケット ブロッキング転送中継関数
 *
 * ブロッキング転送の中継を行なう。
 * @param trans tlm_generic_payload
 * @param t     遅延時間
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
 * AXI-AWチャネル向け targetソケット ダイレクトメモリポインタ取得中継関数
 *
 * メモリポインタ取得の中継を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
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
 * AXI-AWチャネル向け targetソケット ダイレクトメモリポインタ取得中継関数
 *
 * メモリポインタ取得の中継を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
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
 * AXI-AWチャネル向け targetソケット ダイレクトメモリポインタ取得中継関数
 *
 * メモリポインタ取得の中継を行なう。
 * @param  payload tlm_generic_payload
 * @param  data    tlm_dmiクラスインスタンス
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
 * AXI-Bチャネル向け targetソケット メモリポインタ使用負荷通知中継関数
 *
 * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
 * @param start_range 開始アドレス
 * @param end_range   終了アドレス
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
 * AXI-Rチャネル向け targetソケット メモリポインタ使用負荷通知中継関数
 *
 * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
 * @param start_range 開始アドレス
 * @param end_range   終了アドレス
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
 * AXI-AWチャネル向け targetソケット デバッグ用転送中継関数
 *
 * デバッグ用転送の中継を行なう。
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
 * AXI-Wチャネル向け targetソケット デバッグ用転送中継関数
 *
 * デバッグ用転送の中継を行なう。
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
 * AXI-ARチャネル向け targetソケット デバッグ用転送中継関数
 *
 * デバッグ用転送の中継を行なう。
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
 * デバッグ向け関数
 */

/**
 * 送信AXI payload出力開始関数
 *
 * イニシエータから送信されるAXI payloadの出力を開始する
 */
void
TlmAxi3TargetBaseIf::startPrintForwardAxiPayload(void) {
  _is_print = true;
}

/**
 * 送信AXI payload出力停止関数
 *
 * イニシエータから送信されるAXI payloadの出力を停止する
 */
void
TlmAxi3TargetBaseIf::finishPrintForwardAxiPayload(void) {
  _is_print = false;
}

/*
 * デバッグ向け関数
 */

/**
 * 送信AXI payload出力関数
 *
 * イニシエータから送信されるAXI payloadの内容を出力する
 * @param initiator_channel 送信チャネル
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

