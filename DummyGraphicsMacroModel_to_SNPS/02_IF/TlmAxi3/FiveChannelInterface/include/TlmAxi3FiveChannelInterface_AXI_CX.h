/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2011
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */

#include <queue>
#include <list>
#include <systemc.h>
#include <tlm.h>
#include <boost/shared_ptr.hpp>

#include "fj_datatype.h"
#include "TlmAxi3Payload.h"
#include "TlmAxi3InitiatorPrimitiveIf.h"

#ifndef TLM_AXI_5CHANNEL_INTERFACE_AXI_CX_H
#define TLM_AXI_5CHANNEL_INTERFACE_AXI_CX_H

namespace fj
{

/** 汎用バスマスタ向けAXI I/Fクラス
 *
 * 汎用バスマスタ向けのAXI I/Fクラスを表現する。
 */
class TlmAxi3FiveChannelInterface_AXI_CX: public sc_module,
                                          public TlmAxi3InitiatorPrimitiveIfBase
{
private:
  typedef boost::shared_ptr<TlmAxi3Payload> AxiPayloadPtr;
  
public:
  SC_HAS_PROCESS(TlmAxi3FiveChannelInterface_AXI_CX);
  
  /** コンストラクタ
   *
   * コンストラクタ
   *
   * param[in] id_width                AXI ID幅
   * param[in] no_response             レスポンス破棄フラグ
   * param[in] write_outstanding_limit ライトアウトスタンディング制限数
   * param[in] read_outstanding_limit  リードアウトスタンディング制限数
   **/
  TlmAxi3FiveChannelInterface_AXI_CX(const sc_module_name name,
                                     const fj::uint32 id_width = 8,
                                     const fj::uint32 bus_width = 64,
                                     const bool no_receive_b = false,
                                     const bool no_receive_r = false,
                                     const fj::uint32 write_outstanding_limit = 0,
                                     const fj::uint32 read_outstanding_limit = 0);
  
  
  /** AXI-AWチャネルトランザクション送信サービス
   *
   * 引数で指定されたパラメータのAXI-AWチャネルトランザクションを送信し、
   * 送信完了を待ち合わせる。
   *
   * @param[in] AWID    AXI ID
   * @param[in] AWADDR  ライトアドレス
   * @param[in] AWLEN   バースト長
   * @param[in] AWSIZE  バーストサイズ
   * @param[in] AWBURST バーストタイプ (0:FIXED 1:INCR 2:WRAP 3:RESERVED)
   * @param[in] AWLOCK  ロックタイプ (0:NORMAL 1:EXCLLUSIVE 2:LOCKED 3:RESERVED)
   * @param[in] AWCACHE キャッシュタイプ
   * @param[in] AWPROT  プロテクションタイプ
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int sendAw(const unsigned int AWID,
             const unsigned int AWADDR,
             const unsigned int AWLEN,
             const unsigned int AWSIZE,
             const unsigned int AWBURST,
             const unsigned int AWLOCK,
             const unsigned int AWCACHE,
             const unsigned int AWPROT,
             const unsigned int AWUSER);
  
  /** AXI-AWチャネルトランザクション送信サービス
   *
   * 引数で指定されたパラメータのAXI-AWチャネルトランザクションを送信する。
   * 送信完了は待ち合わせない。
   *
   * @param[in] AWID    AXI ID
   * @param[in] AWADDR  ライトアドレス
   * @param[in] AWLEN   バースト長
   * @param[in] AWSIZE  バーストサイズ
   * @param[in] AWBURST バーストタイプ (0:FIXED 1:INCR 2:WRAP 3:RESERVED)
   * @param[in] AWLOCK  ロックタイプ (0:NORMAL 1:EXCLLUSIVE 2:LOCKED 3:RESERVED)
   * @param[in] AWCACHE キャッシュタイプ
   * @param[in] AWPROT  プロテクションタイプ
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int sendAwWithNoWait(const unsigned int AWID,
                       const unsigned int AWADDR,
                       const unsigned int AWLEN,
                       const unsigned int AWSIZE,
                       const unsigned int AWBURST,
                       const unsigned int AWLOCK,
                       const unsigned int AWCACHE,
                       const unsigned int AWPROT,
                       const unsigned int AWUSER);
  
  /** AXI-Wチャネルトランザクション送信サービス
   *
   * 引数で指定されたパラメータのAXI-Wチャネルトランザクションを送信し、
   * 送信完了を待ち合わせる。
   *
   * @param[in] WID   AXI ID
   * @param[in] WLAST ラストライトデータ
   * @param[in] wdata ライトデータ
   * @param[in] wstrb ライトストローブ (0:disable, 1:enable)
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int sendW(const unsigned int WID,
            const unsigned int WLAST,
            const unsigned char* wdata,
            const unsigned char* wstrb);

  /** AXI-Wチャネルトランザクション送信サービス
   *
   * 引数で指定されたパラメータのAXI-Wチャネルトランザクションを送信する。
   * 送信完了は待ち合わせない。
   *
   * @param[in] WID   AXI ID
   * @param[in] WLAST ラストライトデータ
   * @param[in] wdata ライトデータ
   * @param[in] wstrb ライトストローブ (0:disable, 1:enable)
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int sendWWithNoWait(const unsigned int WID,
                      const unsigned int WLAST,
                      const unsigned char* wdata,
                      const unsigned char* wstrb);
  

  /** AXI-Bチャネルトランザクション受信サービス
   *
   * AXI-Bチャネルトランザクション受信完了を待ち合わせる
   *
   * @param[out] BID   AXI ID
   * @param[out] BRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveB(unsigned int *BID,
               unsigned int *BRESP);

  /** AXI-Bチャネルトランザクション受信サービス
   *
   * AXI-Bチャネルトランザクション受信完了を問い合わせる。
   * 未受信の場合はエラーを返す。
   *
   * @param[out] BID   AXI ID
   * @param[out] BRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveBWithNoWait(unsigned int *BID,
                         unsigned int *BRESP);

  /** AXI-Bチャネルトランザクション受信サービス
   *
   * 指定されたAXI IDのAXI-Bチャネルトランザクション受信完了を待ち合わせる
   *
   * @param[in]  BID   AXI ID
   * @param[out] BRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveBById(const unsigned int BID,
                   unsigned int *BRESP);
  
  /** AXI-Bチャネルトランザクション受信サービス
   *
   * 指定されたAXI IDのAXI-Bチャネルトランザクション受信完了を問い合わせる。
   * 未受信の場合はエラーを返す。
   *
   * @param[in]  BID   AXI ID
   * @param[out] BRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveBByIdWithNoWait(const unsigned int BID,
                             unsigned int *BRESP);

  /** AXI-ARチャネルトランザクション送信サービス
   *
   * 引数で指定されたパラメータのAXI-ARチャネルトランザクションを送信し、
   * 送信完了を待ち合わせる。
   *
   * @param[in] ARID    AXI ID
   * @param[in] ARADDR  ライトアドレス
   * @param[in] ARLEN   バースト長
   * @param[in] ARSIZE  バーストサイズ
   * @param[in] ARBURST バーストタイプ (0:FIXED 1:INCR 2:WRAP 3:RESERVED)
   * @param[in] ARLOCK  ロックタイプ (0:NORMAL 1:EXCLLUSIVE 2:LOCKED 3:RESERVED)
   * @param[in] ARCACHE キャッシュタイプ
   * @param[in] ARPROT  プロテクションタイプ
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int sendAr(const unsigned int ARID,
             const unsigned int ARADDR,
             const unsigned int ARLEN,
             const unsigned int ARSIZE,
             const unsigned int ARBURST,
             const unsigned int ARLOCK,
             const unsigned int ARCACHE,
             const unsigned int ARPROT,
             const unsigned int ARUSER);
  
  /** AXI-ARチャネルトランザクション送信サービス
   *
   * 引数で指定されたパラメータのAXI-ARチャネルトランザクションを送信する。
   * 送信完了は待ち合わせない。
   *
   * @param[in] ARID    AXI ID
   * @param[in] ARADDR  ライトアドレス
   * @param[in] ARLEN   バースト長
   * @param[in] ARSIZE  バーストサイズ
   * @param[in] ARBURST バーストタイプ (0:FIXED 1:INCR 2:WRAP 3:RESERVED)
   * @param[in] ARLOCK  ロックタイプ (0:NORMAL 1:EXCLLUSIVE 2:LOCKED 3:RESERVED)
   * @param[in] ARCACHE キャッシュタイプ
   * @param[in] ARPROT  プロテクションタイプ
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int sendArWithNoWait(const unsigned int ARID,
                       const unsigned int ARADDR,
                       const unsigned int ARLEN,
                       const unsigned int ARSIZE,
                       const unsigned int ARBURST,
                       const unsigned int ARLOCK,
                       const unsigned int ARCACHE,
                       const unsigned int ARPROT,
                       const unsigned int ARUSER);

  /** AXI-Rチャネルトランザクション受信サービス
   *
   * AXI-Rチャネルトランザクション受信完了を待ち合わせる
   *
   * @param[out] RID   AXI ID
   * @param[out] RRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveR(unsigned int *RID,
               unsigned int *RLAST,
               unsigned int *RRESP,
               unsigned char *rdata);

  /** AXI-Rチャネルトランザクション受信サービス
   *
   * AXI-Rチャネルトランザクション受信完了を問い合わせる。
   * 未受信の場合はエラーを返す。
   *
   * @param[in]  RID   AXI ID
   * @param[out] RRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveRWithNoWait(unsigned int *RID,
                         unsigned int *RLAST,
                         unsigned int *RESP,
                         unsigned char *rdata);

  /** AXI-Rチャネルトランザクション受信サービス
   *
   * 指定されたAXI IDのAXI-Rチャネルトランザクション受信完了を待ち合わせる
   *
   * @param[out] RID   AXI ID
   * @param[out] RRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveRById(const unsigned int RID,
                   unsigned int *RLAST,
                   unsigned int *RRESP,
                   unsigned char *rdata);


  /** AXI-Rチャネルトランザクション受信サービス
   *
   * 指定されたAXI IDのAXI-Rチャネルトランザクション受信完了を問い合わせる。
   * 未受信の場合はエラーを返す。
   *
   * @param[in]  RID   AXI ID
   * @param[out] RRESP ライト応答
   * @retval 0<= 正常終了
   * @retval <0  エラー
   **/
  int receiveRByIdWithNoWait(const unsigned int RID,
                             unsigned int *RLAST,
                             unsigned int *RESP,
                             unsigned char *rdata);
  
private:
  /** AWペイロード送信スレッド(SC_THREAD)
   *
   * AWペイロードの送信処理を行う。
   * AWペイロードキューに格納されているAWペイロードを取り出し、
   * TLMソケットに対する送信処理を行う。
   */
  void AwSender(void);

  /** Wペイロード送信スレッド(SC_THREAD)
   *
   * Wペイロードの送信処理を行う。
   * Wペイロードキューに格納されているWペイロードを取り出し、
   * TLMソケットに対する送信処理を行う。
   */
  void WSender(void);

  /** ARペイロード送信スレッド(SC_THREAD)
   *
   * ARペイロードの送信処理を行う。
   * ARペイロードキューに格納されているARペイロードを取り出し、
   * TLMソケットに対する送信処理を行う。
   */
  void ArSender(void);

  /** Bペイロード受信コールバック関数
   *
   * Bペイロードを受信した際にTLMソケットからコールバックされる関数
   * TLMソケットから受信したBペイロードを
   * Bペイロードキューに格納する。
   * param[in] TlmAxi3Payload Bペイロード
   */
  void receiveBRequest(TlmAxi3Payload *axi_payload_b);


  /** Rペイロード受信コールバック関数
   *
   * Rペイロードを受信した際にTLMソケットからコールバックされる関数
   * TLMソケットから受信したRペイロードを
   * Rペイロードキューに格納する。
   * param[in] TlmAxi3Payload Rペイロード
   */
  void receiveRRequest(TlmAxi3Payload *axi_payload_r);
  
public:
  TlmAxi3InitiatorPrimitiveIf m_primitive; /**< TLMソケット(TOP接続のため、public) */

private:
  const fj::uint32 m_id_width;                /**< AXI ID幅(bit)               */
  const fj::uint32 m_bus_width;               /**< AXIデータ幅(bit)            */
  const bool       m_no_receive_b;            /**< B応答破棄フラグ             */
  const bool       m_no_receive_r;            /**< R応答破棄フラグ             */
  const fj::uint32 m_write_outstanding_limit; /**< ライトアウトスタンディング制限数 */
  const fj::uint32 m_read_outstanding_limit;  /**< リードアウトスタンディング制限数 */

  fj::uint32 m_id_mask;               /**< AXI IDマスク値                     */
  fj::uint32 m_bus_width_byte;        /**< AXIデータ幅(Byte)                  */
  fj::uint32 m_aw_outstanding_number; /**< AWペイロードアウトスタンディング数 */
  fj::uint32 m_w_outstanding_number;  /**< Wペイロードアウトスタンディング数  */
  fj::uint32 m_ar_outstanding_number; /**< ARペイロードアウトスタンディング数 */

  std::queue<AxiPayloadPtr> m_aw_queue; /* AWペイロードキュー */
  std::queue<AxiPayloadPtr> m_w_queue;  /* Wペイロードキュー  */
  std::queue<AxiPayloadPtr> m_ar_queue; /* ARペイロードキュー */
  std::list<AxiPayloadPtr>  m_b_queue;  /* Bペイロードキュー  */
  std::list<AxiPayloadPtr>  m_r_queue;  /* Rペイロードキュー  */

  sc_event e_aw_queue_pop; /**< AWペイロードキューpopイベント */
  sc_event e_w_queue_pop;  /**< Wペイロードキューpopイベント  */
  sc_event e_ar_queue_pop; /**< ARペイロードキューpopイベント */
  sc_event e_b_queue_push; /**< Bペイロードキューpushイベント */
  sc_event e_r_queue_push; /**< Rペイロードキューpushイベント */

  sc_event e_write_sender;   /**< WriteSender起動イベント   */
  sc_event e_write_receiver; /**< WriteReceiver起動イベント */
  sc_event e_aw_sender;      /**< AwSender起動イベント      */
  sc_event e_w_sender;       /**< WSender起動イベント       */
  sc_event e_read_sender;    /**< ReadSender起動イベント    */
  sc_event e_read_receiver;  /**< ReadReceiver起動イベント  */
  sc_event e_ar_sender;      /**< ArSender起動イベント      */

  sc_event e_aw_response_receive; /**< AWペイロード送信完了イベント */
  sc_event e_w_response_receive;  /**< Wペイロード送信完了イベント  */
  sc_event e_ar_response_receive; /**< ARペイロード送信完了イベント */

  sc_event e_decrease_write_outstanding_number; /**< ライトアウトスタンディング数減少イベント */
  sc_event e_decrease_read_outstanding_number;  /**< リードアウトスタンディング数減少イベント */

  sc_event e_write_response_queue; /**< ライトレスポンスキューセットイベント */
  sc_event e_read_response_queue;  /**< リードレスポンスキューセットイベント */
};

} /* namespace fj */

#endif  /* TLM_AXI_5CHANNEL_INTERFACE_AXI_CX_H */
