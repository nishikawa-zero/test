/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2012
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file  MappedQueue.h
 * @brief �n�b�V���t���L���[�N���X
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
   * �v�f�̒ǉ�
   *
   * �w�肳�ꂽ�L�[�̃L���[�̖����ɗv�f��ǉ�����B
   * �w�肳�ꂽ�L�[�̃L���[�����݂��Ȃ��ꍇ�̓L���[��V�K�쐬���A
   * �V�K�쐬�����L���[�ɗv�f��ǉ�����B
   *
   * @param[in] key �L�[
   * @param element �ǉ�����v�f
   */
  void push(KeyType key, QueueType element) {
    MappedQueueItr itr = m_mapped_queue.find(key);

	  /* �L���[��������Ȃ������ꍇ�A�V�K�쐬 */
    if (itr == m_mapped_queue.end()) {
      std::queue<QueueType> tmp_queue; /* �e���|���� */
      itr = m_mapped_queue.insert(m_mapped_queue.begin(), std::pair<KeyType, std::queue<QueueType> >(key, tmp_queue));
    }

    /* �v�f�̒ǉ� */
    itr->second.push(element);
  }

  /**
   * �v�f�̍폜
   *
   * �w�肳�ꂽ�L�[�̃L���[�̐擪�̗v�f���폜����B
   * �폜�̌��ʃL���[�̗v�f����0�ɂȂ����ꍇ�́A�L���[���̂̍폜���s���B
   * �w�肳�ꂽ�L�[�̃L���[�����݂��Ȃ��ꍇ�͂Ȃɂ����Ȃ��B
   *
   * @param[in] key �L�[
   */
  void pop(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);

    /* �L���[�����������ꍇ�A�擪�v�f���폜 */
    if (itr != m_mapped_queue.end()) {
      itr->second.pop();

      /* �L���[�̗v�f����0�ɂȂ����ꍇ�A�L���[���̂��폜 */
      if (itr->second.empty()) {
        m_mapped_queue.erase(itr);
      }
    }
  }

  /**
   * �擪�v�f�̎Q��
   *
   * �w�肳�ꂽ�L�[�̃L���[�̐擪�̗v�f���Q�Ƃ���B
   * �w�肳�ꂽ�L�[�̃L���[�����݂��Ȃ��ꍇ��Warning���b�Z�[�W��\������B
   * �܂��A���̏ꍇ�̕Ԃ�l�͖���`�B
   *
   * @param[in] key �L�[
   * @retval �擪�v�f
   */
  QueueType front(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);
    QueueType result = QueueType();

    /* �L���[��������Ȃ��ꍇ�AWarning���o�� */
    if (itr == m_mapped_queue.end()) {
      std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: Queue was not found. (key=" << key << ")" << std::endl;
    } else {
      return result = itr->second.front();
    }
    return result;
  }

  /**
   * �����v�f�̎Q��
   *
   * �w�肳�ꂽ�L�[�̃L���[�̖����̗v�f���Q�Ƃ���B
   * �w�肳�ꂽ�L�[�̃L���[�����݂��Ȃ��ꍇ��Warning���b�Z�[�W��\������B
   * �܂��A���̏ꍇ�̕Ԃ�l�͖���`�B
   *
   * @param[in] key �L�[
   * @retval �����v�f
   */
  QueueType back(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);
    QueueType result = QueueType();

    /* �L���[��������Ȃ��ꍇ�AWarning���o�� */
    if (itr == m_mapped_queue.end()) {
      std::cout << __FILE__ << ": line " << __LINE__ << ": Warning: Queue was not found. (key=" << key << ")" << std::endl;
    } else {
      result = itr->second.back();
    }

    return result;
  }

  /**
   * �󔻒�
   *
   * �w�肳�ꂽ�L�[�̃L���[����ł��邩���肷��B
   * �w�肳�ꂽ�L�[�̃L���[�����݂��Ȃ��ꍇ����Ƃ��Ĕ��肳���B
   *
   * @param[in] key �L�[
   * @retval �����v�f
   */
  bool empty(KeyType key) {
    MappedQueueItr itr = m_mapped_queue.find(key);
    bool result = true;

    /* �L���[�����������ꍇ�A�����̃L���[����ł��邩�m�F���� */
    if (itr != m_mapped_queue.end()) {
      result = itr->second.empty();
    }

    return result;
  }

private:
  std::map<KeyType, std::queue<QueueType> > m_mapped_queue;  /**< �n�b�V���t���L���[�����f�[�^ */
};

} /* namespace fj */

#endif /* MAPPED_QUEUE_H */
