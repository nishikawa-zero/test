/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file tlm_axi_initiator_base_if.h
 * @brief TLMイニシエータI/F基底クラス(header)
 *
 * @date $Date: 2009/02/03 00:54:40 $
 * @version $Id: tlm_axi_initiator_base_if.h,v 1.3 2009/02/03 00:54:40 shunsaku Exp $
 *
 * @todo axi_payloadテンプレート対応(現状unsigned long long のみ)
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
 * @brief TLMイニシエータI/F基底クラス
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
   * コンストラクタ
   *
   * コンストラクタ。
   **/
  tlm_axi_initiator_base_if(const char*  name                = NULL,
                            unsigned int endian_convert_mode = OFF);

  /**
   * デストラクタ
   *
   * デストラクタ。
   **/
  virtual ~tlm_axi_initiator_base_if(void);

  /**
   * AXI-Bチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)仮想関数
   *
   * Forward Pathを用いたノンブロッキング転送を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  virtual tlm::tlm_sync_enum
  initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase&           phase,
                              sc_core::sc_time&         t);

  /**
   * AXI-Rチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)仮想関数
   *
   * Forward Pathを用いたノンブロッキング転送を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  virtual tlm::tlm_sync_enum
  initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase&           phase,
                              sc_core::sc_time&         t);

  /**
   * AXI-AWチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)仮想関数
   *
   * Backward Pathを用いたノンブロッキング転送を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  virtual tlm::tlm_sync_enum
  initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                               sc_core::sc_time&         t);

  /**
   * AXI-Wチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)仮想関数
   *
   * Backward Pathを用いたノンブロッキング転送を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  virtual tlm::tlm_sync_enum
  initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                              tlm::tlm_phase& phase,
                              sc_core::sc_time& t);

  /**
   * AXI-ARチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)仮想関数
   *
   * Backward Pathを用いたノンブロッキング転送を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  virtual tlm::tlm_sync_enum
  initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                               tlm::tlm_phase&           phase,
                               sc_core::sc_time&         t);

  /**
   * AXI-Bチャネル向け initiatorソケット ブロッキング転送仮想関数
   *
   * ブロッキング転送を行なう。
   * @param trans tlm_generic_payload
   * @param t     遅延時間
   **/
  virtual void
  initiator_B_b_transport(tlm::tlm_generic_payload& payload,
                          sc_core::sc_time&         delay_time);

  /**
   * AXI-Rチャネル向け initiatorソケット ブロッキング転送仮想関数
   *
   * ブロッキング転送を行なう。
   * @param trans tlm_generic_payload
   * @param t     遅延時間
   **/
  virtual void
  initiator_R_b_transport(tlm::tlm_generic_payload& payload,
                          sc_core::sc_time&         delay_time);

  /**
   * AXI-Bチャネル向け initiatorソケット ダイレクトメモリポインタ取得仮想関数
   *
   * メモリポインタの取得を行なう。
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmiクラスインスタンス
   * @return xxx
   **/
  virtual bool
  initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                 tlm::tlm_dmi&             data);

  /**
   * AXI-Rチャネル向け initiatorソケット ダイレクトメモリポインタ取得仮想関数
   *
   * メモリポインタの取得を行なう。
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmiクラスインスタンス
   * @return xxx
   **/
  virtual bool
  initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                 tlm::tlm_dmi&             data);

  /**
   * AXI-AWチャネル向けinitiatorソケット メモリポインタ使用負荷通知仮想関数
   *
   * イニシエータにメモリポインタの使用負荷を通知する。
   * @param start_range 開始アドレス
   * @param end_range   終了アドレス
   */
  virtual void
  initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range);

  /**
   * AXI-Wチャネル向けinitiatorソケット メモリポインタ使用負荷通知仮想関数
   *
   * イニシエータにメモリポインタの使用負荷を通知する。
   * @param start_range 開始アドレス
   * @param end_range   終了アドレス
   */
  virtual void
  initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                        sc_dt::uint64 end_range);

  /**
   * AXI-ARチャネル向けinitiatorソケット メモリポインタ使用負荷通知仮想関数
   *
   * イニシエータにメモリポインタの使用負荷を通知する。
   * @param start_range 開始アドレス
   * @param end_range 終了アドレス
   */
  virtual void
  initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range);

  /**
   * AXI-Bチャネル向け initiatorソケット デバッグ用転送仮想関数
   *
   * デバッグ用転送を行なう。
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  virtual unsigned int
  initiator_B_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-Rチャネル向け initiatorソケット デバッグ用転送仮想関数
   *
   * デバッグ用転送を行なう。
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  virtual unsigned int
  initiator_R_transport_dbg(tlm::tlm_generic_payload& payload);

private:
  /*
   * 中継関数
   */

  /**
   * AXI-Bチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)中継関数
   *
   * Forward Pathを用いたノンブロッキング転送の中継を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  tlm::tlm_sync_enum
  relay_initiator_B_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_phase&           phase,
                                    sc_core::sc_time&         t);

  /**
   * AXI-Rチャネル向け initiatorソケット ノンブロッキング転送(Forward Path)中継関数
   *
   * Forward Pathを用いたノンブロッキング転送の中継を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  tlm::tlm_sync_enum
  relay_initiator_R_nb_transport_fw(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_phase&           phase,
                                    sc_core::sc_time&         t);

  /**
   * AXI-AWチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)中継関数
   *
   * Backward Pathを用いたノンブロッキング転送の中継を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  tlm::tlm_sync_enum
  relay_initiator_AW_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase&           phase,
                                     sc_core::sc_time&         t);

  /**
   * AXI-Wチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)中継関数
   *
   * Backward Pathを用いたノンブロッキング転送の中継を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  tlm::tlm_sync_enum
  relay_initiator_W_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_phase&           phase,
                                    sc_core::sc_time&         t);

  /**
   * AXI-ARチャネル向け initiatorソケット ノンブロッキング転送(Backward Path)中継関数
   *
   * Backward Pathを用いたノンブロッキング転送の中継を行なう。
   * @param  trans tlm_generic_payload
   * @param  phase TLMフェーズ
   * @param  t     遅延時間
   * @return       応答ステータス
   **/
  tlm::tlm_sync_enum
  relay_initiator_AR_nb_transport_bw(tlm::tlm_generic_payload& trans,
                                     tlm::tlm_phase&           phase,
                                     sc_core::sc_time&         t);

  /**
   * AXI-Bチャネル向け initiatorソケット ブロッキング転送中継関数
   *
   * ブロッキング転送の中継を行なう。
   * @param trans tlm_generic_payload
   * @param t     遅延時間
   **/
  void
  relay_initiator_B_b_transport(tlm::tlm_generic_payload& payload,
                                sc_core::sc_time&         delay_time);

  /**
   * AXI-Rチャネル向け initiatorソケット ブロッキング転送中継関数
   *
   * ブロッキング転送の中継を行なう。
   * @param trans tlm_generic_payload
   * @param t     遅延時間
   **/
  void
  relay_initiator_R_b_transport(tlm::tlm_generic_payload& payload,
                                sc_core::sc_time&         delay_time);

  /**
   * AXI-Bチャネル向け initiatorソケット ダイレクトメモリポインタ取得中継関数
   *
   * メモリポインタ取得の中継を行なう。
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmiクラスインスタンス
   * @return xxx
   **/
  bool
  relay_initiator_B_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                       tlm::tlm_dmi&             data);

  /**
   * AXI-Rチャネル向け initiatorソケット ダイレクトメモリポインタ取得中継関数
   *
   * メモリポインタ取得の中継を行なう。
   * @param  payload tlm_generic_payload
   * @param  data    tlm_dmiクラスインスタンス
   * @return xxx
   **/
  bool
  relay_initiator_R_get_direct_mem_ptr(tlm::tlm_generic_payload& payload,
                                       tlm::tlm_dmi&             data);

  /**
   * AXI-AWチャネル向けinitiatorソケット メモリポインタ使用負荷通知中継関数
   *
   * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
   * @param start_range 開始アドレス
   * @param end_range   終了アドレス
   */
  void
  relay_initiator_AW_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                         sc_dt::uint64 end_range);

  /**
   * AXI-Wチャネル向けinitiatorソケット メモリポインタ使用負荷通知中継関数
   *
   * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
   * @param start_range 開始アドレス
   * @param end_range   終了アドレス
   */
  void
  relay_initiator_W_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                        sc_dt::uint64 end_range);

  /**
   * AXI-ARチャネル向けinitiatorソケット メモリポインタ使用負荷通知中継関数
   *
   * イニシエータへのメモリポインタ使用負荷通知の中継を行う。
   * @param start_range 開始アドレス
   * @param end_range   終了アドレス
   */
  void
  relay_initiator_AR_invalidate_direct_mem_ptr(sc_dt::uint64 start_range,
                                               sc_dt::uint64 end_range);

  /**
   * AXI-Bチャネル向け initiatorソケット デバッグ用転送中継関数
   *
   * デバッグ用転送の中継を行なう。
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  unsigned int
  relay_initiator_B_transport_dbg(tlm::tlm_generic_payload& payload);

  /**
   * AXI-Rチャネル向け initiatorソケット デバッグ用転送中継関数
   *
   * デバッグ用転送の中継を行なう。
   * @param  payload tlm_generic_payload
   * @return xxx
   **/
  unsigned int
  relay_initiator_R_transport_dbg(tlm::tlm_generic_payload& payload);

private:
  /*
   * ユーティリティ関数
   */
  
  /**
   * AXI payloadエンディアン変換関数
   *
   * AXI payloadのエンディアンを変換する
   * @param payload tlm_generic_payload
   **/
  void
  convertEndian(tlm::tlm_generic_payload& payload);

public:
  /*
   * デバッグ向け関数
   */

  /**
   * 送信AXI payload出力開始関数
   *
   * イニシエータから送信されるAXI payloadの出力を開始する
   */
  void
  startPrintForwardAxiPayload(void);

  /**
   * 送信AXI payload出力停止関数
   *
   * イニシエータから送信されるAXI payloadの出力を停止する
   */
  void
  finishPrintForwardAxiPayload(void);

private:
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
