/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2012
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file  MappedQueue.h
 * @brief ハッシュ付きキュークラス
 */
#include <map>
#include <queue>
#include <iostream>

#ifndef MAPPED_QUEUE_H
#define MAPPED_QUEUE_H

namespace fj
{

template<class KeyType, class QueueType>
class MappedQueue
{
  typedef typename std::map<KeyType, std::queue<QueueType> >::iterator MappedQueueItr;

public:
  /**
   * 要素の追加
   *
   * 指定されたキーのキューの末尾に要素を追加する。
   * 指定されたキーのキューが存在しない場合はキューを新規作成し、
   * 新規作成したキューに要素を追加する。
   *
   * @param[in] key キー
   * @param element 追加する要素
   */
  void push(KeyType key, QueueType element) {
    MappedQueueItr itr = m_mapped_queue.find(key);

	  /* キューが見つからなかった場合、新規作成 */
    if (itr == m_mapped_queue.end()) {
      std::queue<QueueType> tmp_queue; /* テンポラリ */
      itr = m_mapped_queue.insert(m_mapped_queue.begin(), std::pair<KeyType, std::queue<QueueType> >(key, tmp_queue));
    }

    /* 要素の追加 */
    itr->second.push(element);
  }

  /**
   * 要素の削除
   *
   * 指定されたキーのキューの先頭の要素を削除する。
   * 削除の結果キューの要素数が0になった場合は、キュー自体の削除を行う。
   * 指定されたキーのキューが存在しない場合はなにもしない。
   *
   * @param[in] key キー
   */
  void pop(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);

    /* キューが見つかった場合、先頭要素を削除 */
    if (itr != m_mapped_queue.end()) {
      itr->second.pop();

      /* キューの要素数が0になった場合、キュー自体を削除 */
      if (itr->second.empty()) {
        m_mapped_queue.erase(itr);
      }
    }
  }

  /**
   * 先頭要素の参照
   *
   * 指定されたキーのキューの先頭の要素を参照する。
   * 指定されたキーのキューが存在しない場合はWarningメッセージを表示する。
   * また、その場合の返り値は未定義。
   *
   * @param[in] key キー
   * @retval 先頭要素
   */
  QueueType front(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);
    QueueType result = QueueType();

    /* キューが見つからない場合、Warningを出力 */
    if (itr == m_mapped_queue.end()) {
      std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: Queue was not found. (key=" << key << ")" << std::endl;
    } else {
      return result = itr->second.front();
    }
    return result;
  }

  /**
   * 末尾要素の参照
   *
   * 指定されたキーのキューの末尾の要素を参照する。
   * 指定されたキーのキューが存在しない場合はWarningメッセージを表示する。
   * また、その場合の返り値は未定義。
   *
   * @param[in] key キー
   * @retval 末尾要素
   */
  QueueType back(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);
    QueueType result = QueueType();

    /* キューが見つからない場合、Warningを出力 */
    if (itr == m_mapped_queue.end()) {
      std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: Queue was not found. (key=" << key << ")" << std::endl;
    } else {
      result = itr->second.back();
    }

    return result;
  }

  /**
   * 空判定
   *
   * 指定されたキーのキューが空であるか判定する。
   * 指定されたキーのキューが存在しない場合も空として判定される。
   *
   * @param[in] key キー
   * @retval 末尾要素
   */
  bool empty(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);
    bool result = true;

    /* キューが見つかった場合、内部のキューが空であるか確認する */
    if (itr != m_mapped_queue.end()) {
      result = itr->second.empty();
    }

    return result;
  }

private:
  std::map<KeyType, std::queue<QueueType> > m_mapped_queue;  /**< ハッシュ付きキュー内部データ */
};

} /* namespace fj */

#endif /* MAPPED_QUEUE_H */
