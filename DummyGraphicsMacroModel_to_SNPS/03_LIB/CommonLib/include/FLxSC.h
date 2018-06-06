/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2008,2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
 */
/**
 * @file FLxSC.h
 *
 * @date $Date: 2009/02/03 00:54:40 $
 * @version $Id: FLxSC.h,v 1.3 2009/02/03 00:54:40 shunsaku Exp $
 */
#include <iterator>
#include <algorithm>
#include <list>
#if defined(__linux__)
# include <byteswap.h>
# if defined(__i386__)
#  define endianswap2bytes(x) bswap_16(x)
#  define endianswap4bytes(x) bswap_32(x)
#  define endianswap8bytes(x) bswap_64(x)
# else
#  define endianswap2bytes(x) (x)
#  define endianswap4bytes(x) (x)
#  define endianswap8bytes(x) (x)
# endif
#else
# if defined(__i386__)
#  define endianswap2bytes(x)  \
     ((((x) & 0xff00)>>8) | (((x) & 0x00ff)<<8))
#  define endianswap4bytes(x) \
     ((((x) & 0xff000000)>>24) | (((x) & 0x00ff0000)>>8) | \
      (((x) & 0x0000ff00)<<8) | (((x) & 0x000000ff)<<24))
#  if defined(_WIN32) && !defined(__CYGWIN32__)
#   if defined(_MSC_VER) && (_MSC_VER < 1300)
#    define endianswap8bytes(x) \
     ((((x) & (((__int64)0xff000000)<<32))>>56) | (((x) & (((__int64)0x00ff0000)<<32))>>40) | \
      (((x) & (((__int64)0x0000ff00)<<32))>>24) | (((x) & (((__int64)0x000000ff)<<32))>>8) | \
      (((x) & ((__int64)0xff000000))<<8) | (((x) & ((__int64)0x00ff0000))<<24) | \
      (((x) & ((__int64)0x0000ff00))<<40) | (((x) & ((__int64)0x000000ff))<<56))
#   else
#    define endianswap8bytes(x) \
     ((((x) & 0xff00000000000000ULL)>>56) | (((x) & 0x00ff000000000000ULL)>>40) | \
      (((x) & 0x0000ff0000000000ULL)>>24) | (((x) & 0x000000ff00000000ULL)>>8) | \
      (((x) & 0x00000000ff000000ULL)<<8) | (((x) & 0x0000000000ff0000ULL)<<24) | \
      (((x) & 0x000000000000ff00ULL)<<40) | (((x) & 0x00000000000000ffULL)<<56))
#   endif
#  else
#   define endianswap8bytes(x) \
     ((((x) & 0xff00000000000000ULL)>>56) | (((x) & 0x00ff000000000000ULL)>>40) | \
      (((x) & 0x0000ff0000000000ULL)>>24) | (((x) & 0x000000ff00000000ULL)>>8) | \
      (((x) & 0x00000000ff000000ULL)<<8) | (((x) & 0x0000000000ff0000ULL)<<24) | \
      (((x) & 0x000000000000ff00ULL)<<40) | (((x) & 0x00000000000000ffULL)<<56))
#  endif
# else
#  define endianswap2bytes(x) (x)
#  define endianswap4bytes(x) (x)
#  define endianswap8bytes(x) (x)
# endif
#endif
#if defined(ARM_MaxSim)
#include <maxsim.h>
#elif defined(NC_SYSTEMC)
#include <scv.h>
#else
#include <systemc.h>
#endif

#ifndef __FLxSC_h
#define __FLxSC_h

#ifndef FLxSC_USE_sc_export
# ifdef SC_RELEASE_STRING
#  define FLxSC_USE_sc_export 1
# endif
#endif

typedef unsigned char bit1_t;
typedef unsigned char bit2_t;
typedef unsigned char bit3_t;
typedef unsigned char bit4_t;
typedef unsigned char bit5_t;
typedef unsigned char bit6_t;
typedef unsigned char bit7_t;
typedef unsigned char bit8_t;
typedef unsigned short bit9_t;
typedef unsigned short bit10_t;
typedef unsigned short bit11_t;
typedef unsigned short bit12_t;
typedef unsigned short bit13_t;
typedef unsigned short bit14_t;
typedef unsigned short bit15_t;
typedef unsigned short bit16_t;
typedef unsigned int bit17_t;
typedef unsigned int bit18_t;
typedef unsigned int bit19_t;
typedef unsigned int bit20_t;
typedef unsigned int bit21_t;
typedef unsigned int bit22_t;
typedef unsigned int bit23_t;
typedef unsigned int bit24_t;
typedef unsigned int bit25_t;
typedef unsigned int bit26_t;
typedef unsigned int bit27_t;
typedef unsigned int bit28_t;
typedef unsigned int bit29_t;
typedef unsigned int bit30_t;
typedef unsigned int bit31_t;
typedef unsigned int bit32_t;
#if defined(_WIN32) && !defined(__CYGWIN32__)
# if defined(_MSC_VER) && (1200 <= _MSC_VER) && (_MSC_VER < 1300)
typedef unsigned __int64 bit33_t;
typedef unsigned __int64 bit34_t;
typedef unsigned __int64 bit35_t;
typedef unsigned __int64 bit36_t;
typedef unsigned __int64 bit37_t;
typedef unsigned __int64 bit38_t;
typedef unsigned __int64 bit39_t;
typedef unsigned __int64 bit40_t;
typedef unsigned __int64 bit41_t;
typedef unsigned __int64 bit42_t;
typedef unsigned __int64 bit43_t;
typedef unsigned __int64 bit44_t;
typedef unsigned __int64 bit45_t;
typedef unsigned __int64 bit46_t;
typedef unsigned __int64 bit47_t;
typedef unsigned __int64 bit48_t;
typedef unsigned __int64 bit49_t;
typedef unsigned __int64 bit50_t;
typedef unsigned __int64 bit51_t;
typedef unsigned __int64 bit52_t;
typedef unsigned __int64 bit53_t;
typedef unsigned __int64 bit54_t;
typedef unsigned __int64 bit55_t;
typedef unsigned __int64 bit56_t;
typedef unsigned __int64 bit57_t;
typedef unsigned __int64 bit58_t;
typedef unsigned __int64 bit59_t;
typedef unsigned __int64 bit60_t;
typedef unsigned __int64 bit61_t;
typedef unsigned __int64 bit62_t;
typedef unsigned __int64 bit63_t;
typedef unsigned __int64 bit64_t;
# elif defined(_MSC_VER) && (1300 <= _MSC_VER)
typedef unsigned long long bit33_t;
typedef unsigned long long bit34_t;
typedef unsigned long long bit35_t;
typedef unsigned long long bit36_t;
typedef unsigned long long bit37_t;
typedef unsigned long long bit38_t;
typedef unsigned long long bit39_t;
typedef unsigned long long bit40_t;
typedef unsigned long long bit41_t;
typedef unsigned long long bit42_t;
typedef unsigned long long bit43_t;
typedef unsigned long long bit44_t;
typedef unsigned long long bit45_t;
typedef unsigned long long bit46_t;
typedef unsigned long long bit47_t;
typedef unsigned long long bit48_t;
typedef unsigned long long bit49_t;
typedef unsigned long long bit50_t;
typedef unsigned long long bit51_t;
typedef unsigned long long bit52_t;
typedef unsigned long long bit53_t;
typedef unsigned long long bit54_t;
typedef unsigned long long bit55_t;
typedef unsigned long long bit56_t;
typedef unsigned long long bit57_t;
typedef unsigned long long bit58_t;
typedef unsigned long long bit59_t;
typedef unsigned long long bit60_t;
typedef unsigned long long bit61_t;
typedef unsigned long long bit62_t;
typedef unsigned long long bit63_t;
typedef unsigned long long bit64_t;
# endif
#else
typedef unsigned long long bit33_t;
typedef unsigned long long bit34_t;
typedef unsigned long long bit35_t;
typedef unsigned long long bit36_t;
typedef unsigned long long bit37_t;
typedef unsigned long long bit38_t;
typedef unsigned long long bit39_t;
typedef unsigned long long bit40_t;
typedef unsigned long long bit41_t;
typedef unsigned long long bit42_t;
typedef unsigned long long bit43_t;
typedef unsigned long long bit44_t;
typedef unsigned long long bit45_t;
typedef unsigned long long bit46_t;
typedef unsigned long long bit47_t;
typedef unsigned long long bit48_t;
typedef unsigned long long bit49_t;
typedef unsigned long long bit50_t;
typedef unsigned long long bit51_t;
typedef unsigned long long bit52_t;
typedef unsigned long long bit53_t;
typedef unsigned long long bit54_t;
typedef unsigned long long bit55_t;
typedef unsigned long long bit56_t;
typedef unsigned long long bit57_t;
typedef unsigned long long bit58_t;
typedef unsigned long long bit59_t;
typedef unsigned long long bit60_t;
typedef unsigned long long bit61_t;
typedef unsigned long long bit62_t;
typedef unsigned long long bit63_t;
typedef unsigned long long bit64_t;
#endif
typedef bit32_t addr32_t;
typedef bit64_t addr64_t;

#ifndef NBBY
#define NBBY 8 /* number of bits in a byte */
#endif /* NBBY */

#if defined(ARM_MaxSim)
# define FLxsc_in_ctor(name) ,name(#name)
# define FLxsc_in_port(type, name) sc_in<type> name
# define FLxsc_out_ctor(name) ,name((sc_port<sc_mx_signal_if>*)0)
# define FLxsc_out_port(type, name) sc_port<sc_mx_signal_if>* name
# define FLxsc_signal_assert(name) (name)->driveSignal(1, NULL)
# define FLxsc_signal_assertInitialize(name)
# define FLxsc_signal_drive(name, value) (name)->driveSignal(value, NULL)
# define FLxsc_signal_driveInitialize(name, value)
# define FLxsc_signal_isAssert(name) (1 == (name)->readSignal())
# define FLxsc_signal_isNssert(name) (0 == (name)->readSignal())
# define FLxsc_signal_isxAssert(name) (0 == (name)->readSignal())
# define FLxsc_signal_isxNssert(name) (1 == (name)->readSignal())
# define FLxsc_signal_negate(name) (name)->driveSignal(0, NULL)
# define FLxsc_signal_negateInitialize(name)
# define FLxsc_signal_read(name) (name)->readSignal()
# define FLxsc_signal_xAssert(name) (name)->driveSignal(0, NULL)
# define FLxsc_signal_xAssertInitialize(name)
# define FLxsc_signal_xDrive(name, value) (name)->driveSignal(~(value), NULL)
# define FLxsc_signal_xDriveInitialize(name, value)
# define FLxsc_signal_xNegateInitialize(name)
# define FLxsc_signal_xNegate(name) (name)->driveSignal(1, NULL)
# define FLxsc_signal_xRead(name) ~((name)->readSignal())
# define FLxsc_signal_sensitive_method(name) SC_METHOD(name##_); sensitive << name; dont_initialize()
# define FLxsc_signal_posedge_sensitive_method(name) SC_METHOD(name##_); sensitive << (name).pos(); dont_initialize()
# define FLxsc_signal_negedge_sensitive_method(name) SC_METHOD(name##_); sensitive << (name).neg(); dont_initialize()
#else
# define FLxsc_in_ctor(name) ,name(#name)
# define FLxsc_in_port(type, name) sc_in<type> name
# define FLxsc_out_ctor(name) ,name(#name)
# define FLxsc_out_port(type, name) sc_out<type> name
# define FLxsc_signal_assert(name) (name).write(1)
# define FLxsc_signal_assertInitialize(name) (name).initialize(1)
# define FLxsc_signal_drive(name, value) (name).write(value)
# define FLxsc_signal_driveInitialize(name, value) (name).initialize(value)
# define FLxsc_signal_isAssert(name) (true == (name).read())
# define FLxsc_signal_isNegate(name) (false == (name).read())
# define FLxsc_signal_isxAssert(name) (false == (name).read())
# define FLxsc_signal_isxNegate(name) (true == (name).read())
# define FLxsc_signal_negate(name) (name).write(0)
# define FLxsc_signal_negateInitialize(name) (name).initialize(0)
# define FLxsc_signal_read(name) (name).read()
# define FLxsc_signal_xAssert(name) (name).write(0)
# define FLxsc_signal_xAssertInitialize(name) (name).initialize(0)
# define FLxsc_signal_xDrive(name, value) name.write(~(value))
# define FLxsc_signal_xDriveInitialize(name) (name).initialize(~(value))
# define FLxsc_signal_xNegate(name) (name).write(1)
# define FLxsc_signal_xNegateInitialize(name) (name).initialize(1)
# define FLxsc_signal_xRead(name) ~((name).read())
# define FLxsc_signal_sensitive_method(name) SC_METHOD(name##_); sensitive << name; dont_initialize()
# define FLxsc_signal_posedge_sensitive_method(name) SC_METHOD(name##_); sensitive << (name).pos(); dont_initialize()
# define FLxsc_signal_negedge_sensitive_method(name) SC_METHOD(name##_); sensitive << (name).neg(); dont_initialize()
#endif

#if defined(__FLxSC_h_kernel)
/** ハンドシェイク付きイベント
 *
 * ハンドシェイク付きイベントを表現する。
 */
class FLxsc_events {
 public:
    inline const sc_event& getEvent(void) const { return e; }
    /** イベントの印加
     *
     * イベントを印加する。
     */
    inline void notify(void){
        flags.notified = 1;
        e.notify();
    }
    /** イベントの待ち合わせ
     *
     * イベントを待ち合わせる。
     *
     * @param[in] waiting 待ち合わせ動作フラグ
     */
    inline void wait(const bool waiting = true){
        if (waiting && !flags.notified) sc_core::wait(e);
        flags.notified = 0;
    }
    FLxsc_events(void) : e() {
        memset(&flags, 0, sizeof(flags));
    }
 private:
    sc_event e;
    struct {
        unsigned int notified : 1;
    } flags;
};

template<typename T, int SZ = 0>
class FLxSC_EventedQueue : public std::list<T> {
 public:
    /*
     * type definitions
     */
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    /*
     * iterator support
     */
    typedef typename std::list<T>::iterator iterator;
    typedef typename std::list<T>::const_iterator const_iterator;
    iterator begin(void){ return std::list<T>::begin(); }
    const_iterator begin(void) const { return std::list<T>::begin(); }
    iterator end(void){ return std::list<T>::end(); }
    const_iterator end(void) const { return std::list<T>::end(); }
    /*
     * reverse iterator support
     */
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC_STD_ITERATOR)
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#else
    // workaround for broken reverse_iterator implementations
    typedef std::reverse_iterator<iterator,T> reverse_iterator;
    typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif
    reverse_iterator rbegin(void){ return reverse_iterator(end()); }
    const_reverse_iterator rbegin(void) const { return const_reverse_iterator(end()); }
    reverse_iterator rend(void){ return reverse_iterator(begin()); }
    const_reverse_iterator rend(void) const { return const_reverse_iterator(begin()); }
    /*
     * front() and back()
     */
    reference front(void){ return std::list<T>::front(); }
    const_reference front(void) const { return std::list<T>::front(); }
    reference back(void){ return std::list<T>::back(); }
    const_reference back(void) const { return std::list<T>::back(); }
    /*
     * size is constant
     */
    size_type size(void) const { return std::list<T>::size(); }
    bool empty(void) const { return std::list<T>::empty(); }
    size_type max_size(void) const { return limits; }
    /*
     *
     */
    iterator erase(iterator position){ return std::list<T>::erase(position); }
    void pop(void){
        std::list<T>::pop_front();
        if (refcnt && e_wait) e_wait->notify();
    }
    bool push(reference value){
        if (limits) {
            for (refcnt++; std::list<T>::size() >= limits; ) {
                if (e_wait) sc_core::wait(*e_wait);
                else return refcnt--, false;
            }
            refcnt--;
        }
        std::list<T>::push_back(value);
        if (e_ding) e_ding->notify();
        if (e_ding_handshake) e_ding_handshake->notify();
        return true;
    }
    void setDingEvent(sc_event* const ding){
        e_ding = const_cast<sc_event*>(ding);
        e_ding_handshake = (FLxsc_events*)0;
    }
    void setDingEvent(FLxsc_events* const ding){
        e_ding = (sc_event*)0;
        e_ding_handshake = const_cast<FLxsc_events*>(ding);
    }
    FLxSC_EventedQueue(void) : std::list<T>(), limits(SZ), refcnt(0), e_wait((sc_event*)0), e_ding((sc_event*)0), e_ding_handshake((FLxsc_events*)0) {
        if (limits  && !e_wait) e_wait = new sc_event;
    }
    ~FLxSC_EventedQueue(void){
        if (e_wait) delete e_wait, (e_wait = (sc_event*)0);
    }
 private:
    size_type limits;
    size_type refcnt;
    sc_event* e_wait;
    sc_event* e_ding;
    FLxsc_events* e_ding_handshake;
};

/** ビット・ベクタ
 *
 * ビット・ベクタを表現する。
 */
class FLxSC_BitVector {
 public:
    /** 空か否かの判定
     *
     * ビット・ベクタが空か否かを判定する。
     *
     * @retval true ビット・ベクタは空である
     * @retval false ビット・ベクタは空ではない
     */
    inline bool empty(void) const {
        unsigned long* v = values;
        if (masks) {
            unsigned long* m = masks;
            for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; i; i--, v++, m++) if (*v & ~(*m)) return false;
        } else {
            for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; i; i--, v++) if (*v) return false;
        }
        return true;
    }
    /** 満たされているか否かの判定
     *
     * ビット・ベクタが満たされているか否かを判定する。
     *
     * @retval true ビット・ベクタは満たされている
     * @retval false ビット・ベクタは満たされていない
     */
    inline bool full(void) const {
        unsigned long* v = values;
        for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; i; i--, v++) if (~0UL != *v) return false; /* XXX:FIXME */
        return true;
    }
    /** マスク・ビットのセット
     *
     * 全マスク・ビットをセットする。
     */
    inline void mask(void){
        if (!masks) {
            masks = (unsigned long*)malloc((bits+BitVectorBits-1)/BitVectorBits);
            memset(masks, 0, (bits+BitVectorBits-1)/BitVectorBits);
        }
        unsigned long* v = masks;
        for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; i; i--) *v++ = ~0;
    }
    /** マスク・ビットのセット
     *
     * 指定されたマスク・ビットをセットする。
     *
     * @param[in] pos ビット位置
     * @param[in] val ビット値
     */
    inline void mask(const size_t pos, const bool val = true){
        if (!masks) {
            masks = (unsigned long*)malloc((bits+BitVectorBits-1)/BitVectorBits);
            memset(masks, 0, (bits+BitVectorBits-1)/BitVectorBits);
        }
        if (val) masks[pos/BitVectorBits] |= (1 << (pos % BitVectorBits));
        else masks[pos/BitVectorBits] &= ~(1 << (pos % BitVectorBits));
    }
    /** (値)ビットのクリア
     *
     * 全(値)ビットをクリアする。
     */
    inline void reset(void){
        unsigned long* v = values;
        for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; i; i--) *v++ = 0;
    }
    /** (値)ビットのクリア
     *
     * 指定された(値)ビットをクリアする。
     *
     * @param[in] pos ビット位置
     */
    inline void reset(const size_t pos){
        values[pos/BitVectorBits] &= ~(1 << (pos % BitVectorBits));
    }
    /** (値)ビットのセット
     *
     * 全(値)ビットをセットする。
     */
    inline void set(void){
        unsigned long* v = values;
        for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; i; i--) *v++ = ~0;
    }
    /** (値)ビットのセット
     *
     * 指定された(値)ビットをセットする。
     *
     * @param[in] pos ビット位置
     * @param[in] val ビット値
     */
    inline void set(const size_t pos, const bool val = true){
        if (val) values[pos/BitVectorBits] |= (1 << (pos % BitVectorBits));
        else values[pos/BitVectorBits] &= ~(1 << (pos % BitVectorBits));
    }
    /** ビット・ベクタ長の参照
     *
     * ビット・ベクタ長を参照する。
     *
     * @return ビット・ベクタ長(in bits)
     */
    inline size_t size(void) const {
        return bits;
    }
    /** ビット値の参照
     *
     * 指定されたビットの値を参照する。
     *
     * @param[in] pos ビット位置
     * @return ビット値
     */
    inline bool test(const size_t pos) const {
        unsigned long v;
        if (masks) v = values[pos/BitVectorBits] & ~(masks[pos/BitVectorBits]);
        else v = values[pos/BitVectorBits];
        return (v & (1 << (pos % BitVectorBits)))? true: false;
    }
    /** マスク・ビットのクリア
     *
     * 全マスク・ビットをクリアする。
     */
    inline void unmask(void){
        if (!masks) {
            masks = (unsigned long*)malloc((bits+BitVectorBits-1)/BitVectorBits);
            memset(masks, 0, (bits+BitVectorBits-1)/BitVectorBits);
        }
        unsigned long* v = masks;
        for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; i; i--) *v++ = 0;
    }
    /** マスク・ビットのクリア
     *
     * 指定されたマスク・ビットをクリアする。
     *
     * @param[in] pos ビット位置
     */
    inline void unmask(const size_t pos){
        if (!masks) {
            masks = (unsigned long*)malloc((bits+BitVectorBits-1)/BitVectorBits);
            memset(masks, 0, (bits+BitVectorBits-1)/BitVectorBits);
        }
        masks[pos/BitVectorBits] &= ~(1 << (pos % BitVectorBits));
    }
    FLxSC_BitVector(const size_t bits) : bits(bits) {
        values = (unsigned long*)malloc(sizeof(unsigned long)*((bits+BitVectorBits-1)/BitVectorBits));
        memset(values, 0, sizeof(unsigned long)*((bits+BitVectorBits-1)/BitVectorBits));
        masks = (unsigned long*)0;
    }
    ~FLxSC_BitVector(void){
        if (values) free(values), (values = (unsigned long*)0);
        if (masks) free(masks), (masks = (unsigned long*)0);
    }
 protected:
    enum { BitVectorBits = sizeof(unsigned long) * NBBY} ;
    size_t bits; /**< ビット・ベクタ長(in bits) */
    unsigned long* values; /**< (値)ビット・ベクタ */
    unsigned long* masks; /**< マスク・ビット・ベクタ */
};

/** 優先度付きビット・ベクタ
 *
 * 優先度付きビット・ベクタを表現する。
 */
class FLxSC_PrioBitVector : public FLxSC_BitVector {
 public:
    /** "0(零)のビット並び"のビット幅の算出
     *
     * 昇順にて、"0(零)のビット並び"のビット幅を算出する。
     *
     * @return "0(零)のビット並び"のビット幅(in bits)
     */
    size_t countLeadingZerosByAscending(void) const {
        size_t ret = 0;
        unsigned long b = 0, *v = values, *m = masks;
        for (size_t i = 0; i < ((bits+BitVectorBits-1)/BitVectorBits); i++, v++) {
            if (masks) {
                if (!(b = (*v & ~(*m++)))) continue;
            } else {
                if (!(b = *v)) continue;
            }
            if (!(b & 0x0000ffff)) ret += 16, b >>= 16;
            b &= 0x0000ffff;
            if (!(b & 0x00ff)) ret += 8, b >>= 8;
            b &= 0x00ff;
            if (!(b & 0x0f)) ret += 4, b >>= 4;
            b &= 0x0f;
            if (b & 0x01) ret += 0;
            else if (b & 0x02) ret += 1;
            else if (b & 0x04) ret += 2;
            else if (b & 0x08) ret += 3;
            ret += BitVectorBits * i;
            break;
        }
        return ret;
    }
    /** "0(零)のビット並び"のビット幅の算出
     *
     * 降順にて、"0(零)のビット並び"のビット幅を算出する。
     *
     * @return "0(零)のビット並び"のビット幅(in bits)
     */
    size_t countLeadingZerosByDesending(void) const {
        size_t ret = 0;
        unsigned long b = 0, *v = &(values[((bits+BitVectorBits-1)/BitVectorBits)-1]), *m = (unsigned long*)0;
        for (size_t i = (bits+BitVectorBits-1)/BitVectorBits; 0 < i; i--, v--) {
            if (masks) {
                if (!m) m = &(masks[((bits+BitVectorBits-1)/BitVectorBits)-1]);
                if (!(b = (*v & ~(*m--)))) continue;
            } else {
                if (!(b = *v)) continue;
            }
            if (b & 0xffff0000) ret += 16, b >>= 16;
            b &= 0x0000ffff;
            if (b & 0xff00) ret += 8, b >>= 8;
            b &= 0x00ff;
            if (b & 0xf0) ret += 4, b >>= 4;
            b &= 0x0f;
            if (b & 0x08) ret += 3;
            else if (b & 0x04) ret += 2;
            else if (b & 0x02) ret += 1;
            else if (b & 0x01) ret += 0;
            ret += BitVectorBits * (i - 1);
            break;
        }
        return ret;
    }
    FLxSC_PrioBitVector(const size_t bits) : FLxSC_BitVector(bits) {}
    ~FLxSC_PrioBitVector(void){}
};


class FLxSC_TickCycleWait {
 public:
    sc_time time(const unsigned int delta){
        return sc_time(dt * delta)/* sc_time(SC_ZERO_TIME) */;
    }
    void wait(const unsigned int delta){
        sc_core::wait(dt * delta)/* sc_core::wait(SC_ZERO_TIME) */;
    }
    FLxSC_TickCycleWait(void) : dt(SC_ZERO_TIME) {}
    FLxSC_TickCycleWait(const double cycle, const sc_time_unit time_unit) : dt(cycle, time_unit) {}
    ~FLxSC_TickCycleWait(void){}
 private:
    sc_time dt;
};

class FLxSC_ClockCycleWait : public sc_module {
 public:
    sc_time time(const unsigned int delta){
        return sc_time(SC_ZERO_TIME);
    }
    void wait(const unsigned int delta){
        if (delta) {
            unsigned int d = delta;
            sc_event* e = (sc_event*)0;
            std::list<timer*>::iterator itr;
            if (!freeEvents.empty()) (e = freeEvents.front()), freeEvents.pop_front();
            else e = new sc_event();
            for (itr = activeEvents.begin(); itr != activeEvents.end(); itr++) {
                timer* tmr = *itr;
                if (tmr->delta < d) {
                    if (tmr->delta) d -= tmr->delta;
                } else if (tmr->delta > d) {
                    tmr = new timer(d, e);
                    activeEvents.insert(itr, tmr);
                    break;
                } else /* if (tmr->delta == d) */ {
                    if (tmr->delta) d -= tmr->delta;
                    tmr = new timer(d, e);
                    activeEvents.insert(itr, tmr);
                    break;
                }
            }
            if (itr == activeEvents.end()) {
                timer* tmr = new timer(d, e);
                activeEvents.push_back(tmr);
            }
            sc_core::wait(*e);
        } else sc_core::wait(SC_ZERO_TIME);
    }
    SC_HAS_PROCESS(FLxSC_ClockCycleWait);
    FLxSC_ClockCycleWait(sc_in<bool>& clock, sc_module_name name = "FLxSC_ClockCycleWait") : sc_module(name) {
        SC_METHOD(cyclic); sensitive << clock.pos(); dont_initialize();
    }
    ~FLxSC_ClockCycleWait(void){
        for (timer* tmr = (timer*)0; !activeEvents.empty(); ) {
            (tmr = activeEvents.front()), activeEvents.pop_front();
            delete tmr->event, (tmr->event = (sc_event*)0);
            delete tmr, (tmr = (timer*)0);
        }
        for (sc_event* e = (sc_event*)0; !freeEvents.empty(); ) {
            (e = freeEvents.front()), freeEvents.pop_front();
            delete e, (e = (sc_event*)0);
        }
    }
 private:
    class timer {
      public:
        timer(const unsigned int delta, sc_event* event) : delta(delta), event(event) {}
      public:
        unsigned int delta;
        sc_event* event;
    };
    void cyclic(void){
        if (activeEvents.empty()) return;
        timer* tmr = activeEvents.front();
        if (!(--(tmr->delta))) {
            activeEvents.pop_front();
            (tmr->event)->notify(), freeEvents.push_back(tmr->event);
            delete tmr, (tmr = (timer*)0);
            while (!activeEvents.empty()) {
                tmr = activeEvents.front();
                if (tmr->delta) break;
                activeEvents.pop_front();
                (tmr->event)->notify(), freeEvents.push_back(tmr->event);
                delete tmr, (tmr = (timer*)0);
            }
        }
    }
    std::list<timer*> activeEvents;
    std::list<sc_event*> freeEvents;
};

#define FLxSC_CycleTime(ptr, delta) ((ptr)? (ptr)->time(delta): sc_time(SC_ZERO_TIME))
#define FLxSC_CycleWait(ptr, delta) ((ptr)? (ptr)->wait(delta): wait(SC_ZERO_TIME))

class FLxSC_8bitsRegister {
 public:
    bit8_t& c_value(void){ return value; }
    bit8_t c_value(void) const { return value; }
    bit8_t read(void) const { return value & readMask; }
    void setReadMask(bit8_t x){ readMask = x; }
    void setWriteMask(bit8_t x){ writeMask = x; }
    void write(bit8_t x){ value = (value & ~writeMask) | (x & writeMask); }
    bit8_t operator () (void){ return value; }
    /*
     * constructor
     */
    FLxSC_8bitsRegister(void) : readMask(~(bit8_t)0), writeMask(~(bit8_t)0), value(0) {} /**< default constructor */
    FLxSC_8bitsRegister(bit8_t x, bit8_t readMask = ~(bit8_t)0, bit8_t writeMask = ~(bit8_t)0) : readMask(readMask), writeMask(writeMask), value(x) {} /**< constructor */
    FLxSC_8bitsRegister(const FLxSC_8bitsRegister& x) : readMask(x.readMask), writeMask(x.writeMask), value(x.value) {} /**< copy constructor */
    /*
     * assignment operator
     */
    const FLxSC_8bitsRegister& operator = (const FLxSC_8bitsRegister& x){ value = x.value; return *this; }
    const FLxSC_8bitsRegister& operator += (const FLxSC_8bitsRegister& x){ value = value + x.value; return *this; }
    const FLxSC_8bitsRegister& operator -= (const FLxSC_8bitsRegister& x){ value = value - x.value; return *this; }
    const FLxSC_8bitsRegister& operator *= (const FLxSC_8bitsRegister& x){ value = value * x.value; return *this; }
    const FLxSC_8bitsRegister& operator /= (const FLxSC_8bitsRegister& x){ value = value / x.value; return *this; }
    const FLxSC_8bitsRegister& operator %= (const FLxSC_8bitsRegister& x){ value = value % x.value; return *this; }
    const FLxSC_8bitsRegister& operator <<= (const FLxSC_8bitsRegister& x){ value = value << x.value; return *this; }
    const FLxSC_8bitsRegister& operator >>= (const FLxSC_8bitsRegister& x){ value = value >> x.value; return *this; }
    const FLxSC_8bitsRegister& operator &= (const FLxSC_8bitsRegister& x){ value = value & x.value; return *this; }
    const FLxSC_8bitsRegister& operator |= (const FLxSC_8bitsRegister& x){ value = value | x.value; return *this; }
    const FLxSC_8bitsRegister& operator ^= (const FLxSC_8bitsRegister& x){ value = value ^ x.value; return *this; }
    const FLxSC_8bitsRegister& operator = (const bit8_t x){ value = x; return *this; }
    const FLxSC_8bitsRegister& operator += (const bit8_t x){ value = value + x; return *this; }
    const FLxSC_8bitsRegister& operator -= (const bit8_t x){ value = value - x; return *this; }
    const FLxSC_8bitsRegister& operator *= (const bit8_t x){ value = value * x; return *this; }
    const FLxSC_8bitsRegister& operator /= (const bit8_t x){ value = value / x; return *this; }
    const FLxSC_8bitsRegister& operator %= (const bit8_t x){ value = value % x; return *this; }
    const FLxSC_8bitsRegister& operator <<= (const bit8_t x){ value = value << x; return *this; }
    const FLxSC_8bitsRegister& operator >>= (const bit8_t x){ value = value >> x; return *this; }
    const FLxSC_8bitsRegister& operator &= (const bit8_t x){ value = value & x; return *this; }
    const FLxSC_8bitsRegister& operator |= (const bit8_t x){ value = value | x; return *this; }
    const FLxSC_8bitsRegister& operator ^= (const bit8_t x){ value = value ^ x; return *this; }
    const FLxSC_8bitsRegister& operator = (const int x){ value = x; return *this; }
    const FLxSC_8bitsRegister& operator += (const int x){ value = value + x; return *this; }
    const FLxSC_8bitsRegister& operator -= (const int x){ value = value - x; return *this; }
    const FLxSC_8bitsRegister& operator *= (const int x){ value = value * x; return *this; }
    const FLxSC_8bitsRegister& operator /= (const int x){ value = value / x; return *this; }
    const FLxSC_8bitsRegister& operator %= (const int x){ value = value % x; return *this; }
    const FLxSC_8bitsRegister& operator <<= (const int x){ value = value << x; return *this; }
    const FLxSC_8bitsRegister& operator >>= (const int x){ value = value >> x; return *this; }
    const FLxSC_8bitsRegister& operator &= (const int x){ value = value & x; return *this; }
    const FLxSC_8bitsRegister& operator |= (const int x){ value = value | x; return *this; }
    const FLxSC_8bitsRegister& operator ^= (const int x){ value = value ^ x; return *this; }
    /*
     * cast operator
     */
    operator unsigned char (void) const { return static_cast<unsigned char>(value); }
    operator unsigned char& (void){ return value; }
    operator unsigned short (void) const { return static_cast<unsigned short>(value); }
    operator unsigned int (void) const { return static_cast<unsigned int>(value); }
#if defined(_WIN32) && !defined(__CYGWIN32__)
# if defined(_MSC_VER) && (1200 <= _MSC_VER) && (_MSC_VER < 1300)
    operator unsigned __int64 (void) const { return static_cast<unsigned __int64>(value); }
# elif defined(_MSC_VER) && (1300 <= _MSC_VER)
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
# endif
#else
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
#endif
    /*
     * address operator
     */
    bit8_t* operator & (void){ return &value; }
    const bit8_t* operator & (void) const { return &value; }
    /*
     * unary operator
     */
    FLxSC_8bitsRegister operator + (void) const { return FLxSC_8bitsRegister(value); }
    FLxSC_8bitsRegister operator - (void) const { return FLxSC_8bitsRegister(-value); }
    FLxSC_8bitsRegister operator ~ (void) const { return FLxSC_8bitsRegister(~value); }
    bool operator ! (void) const { return !value; }
    /*
     * prefix/postfix operator
     */
    const FLxSC_8bitsRegister& operator ++ (void){ value = value + 1; return *this; }
    const FLxSC_8bitsRegister& operator -- (void){ value = value - 1; return *this; }
    FLxSC_8bitsRegister operator ++ (int){ FLxSC_8bitsRegister tmp(*this); value = value + 1; return tmp; }
    FLxSC_8bitsRegister operator -- (int){ FLxSC_8bitsRegister tmp(*this); value = value - 1; return tmp; }
    /*
     * binary operator
     */
    friend FLxSC_8bitsRegister operator + (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value + y.value); }
    friend FLxSC_8bitsRegister operator - (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value - y.value); }
    friend FLxSC_8bitsRegister operator * (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value * y.value); }
    friend FLxSC_8bitsRegister operator / (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value / y.value); }
    friend FLxSC_8bitsRegister operator % (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value % y.value); }
    friend FLxSC_8bitsRegister operator << (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value << y.value); }
    friend FLxSC_8bitsRegister operator >> (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value >> y.value); }
    friend FLxSC_8bitsRegister operator & (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value & y.value); }
    friend FLxSC_8bitsRegister operator | (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value | y.value); }
    friend FLxSC_8bitsRegister operator ^ (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x.value ^ y.value); }
    friend bool operator == (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return x.value == y.value; }
    friend bool operator != (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return x.value != y.value; }
    friend bool operator <= (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return x.value <= y.value; }
    friend bool operator >= (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return x.value >= y.value; }
    friend bool operator < (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return x.value < y.value; }
    friend bool operator > (const FLxSC_8bitsRegister& x, const FLxSC_8bitsRegister& y){ return x.value > y.value; }
    friend FLxSC_8bitsRegister operator + (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value + y); }
    friend FLxSC_8bitsRegister operator + (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x + y.value); }
    friend FLxSC_8bitsRegister operator - (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value - y); }
    friend FLxSC_8bitsRegister operator - (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x - y.value); }
    friend FLxSC_8bitsRegister operator * (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value * y); }
    friend FLxSC_8bitsRegister operator * (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x * y.value); }
    friend FLxSC_8bitsRegister operator / (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value / y); }
    friend FLxSC_8bitsRegister operator / (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x / y.value); }
    friend FLxSC_8bitsRegister operator << (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value << y); }
    friend FLxSC_8bitsRegister operator << (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x << y.value); }
    friend FLxSC_8bitsRegister operator >> (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value >> y); }
    friend FLxSC_8bitsRegister operator >> (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x >> y.value); }
    friend FLxSC_8bitsRegister operator & (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value & y); }
    friend FLxSC_8bitsRegister operator & (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x & y.value); }
    friend FLxSC_8bitsRegister operator | (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value | y); }
    friend FLxSC_8bitsRegister operator | (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x | y.value); }
    friend FLxSC_8bitsRegister operator ^ (const FLxSC_8bitsRegister& x, bit8_t y){ return FLxSC_8bitsRegister(x.value ^ y); }
    friend FLxSC_8bitsRegister operator ^ (bit8_t x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_8bitsRegister& x, bit8_t y){ return x.value == y; }
    friend bool operator == (bit8_t x, const FLxSC_8bitsRegister& y){ return x == y.value; }
    friend bool operator != (const FLxSC_8bitsRegister& x, bit8_t y){ return x.value != y; }
    friend bool operator != (bit8_t x, const FLxSC_8bitsRegister& y){ return x != y.value; }
    friend bool operator <= (const FLxSC_8bitsRegister& x, bit8_t y){ return x.value <= y; }
    friend bool operator <= (bit8_t x, const FLxSC_8bitsRegister& y){ return x <= y.value; }
    friend bool operator >= (const FLxSC_8bitsRegister& x, bit8_t y){ return x.value >= y; }
    friend bool operator >= (bit8_t x, const FLxSC_8bitsRegister& y){ return x >= y.value; }
    friend bool operator < (const FLxSC_8bitsRegister& x, bit8_t y){ return x.value < y; }
    friend bool operator < (bit8_t x, const FLxSC_8bitsRegister& y){ return x < y.value; }
    friend bool operator > (const FLxSC_8bitsRegister& x, bit8_t y){ return x.value > y; }
    friend bool operator > (bit8_t x, const FLxSC_8bitsRegister& y){ return x > y.value; }
    friend FLxSC_8bitsRegister operator + (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value + y); }
    friend FLxSC_8bitsRegister operator + (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x + y.value); }
    friend FLxSC_8bitsRegister operator - (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value - y); }
    friend FLxSC_8bitsRegister operator - (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x - y.value); }
    friend FLxSC_8bitsRegister operator * (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value * y); }
    friend FLxSC_8bitsRegister operator * (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x * y.value); }
    friend FLxSC_8bitsRegister operator / (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value / y); }
    friend FLxSC_8bitsRegister operator / (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x / y.value); }
    friend FLxSC_8bitsRegister operator << (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value << y); }
    friend FLxSC_8bitsRegister operator << (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x << y.value); }
    friend FLxSC_8bitsRegister operator >> (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value >> y); }
    friend FLxSC_8bitsRegister operator >> (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x >> y.value); }
    friend FLxSC_8bitsRegister operator & (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value & y); }
    friend FLxSC_8bitsRegister operator & (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x & y.value); }
    friend FLxSC_8bitsRegister operator | (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value | y); }
    friend FLxSC_8bitsRegister operator | (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x | y.value); }
    friend FLxSC_8bitsRegister operator ^ (const FLxSC_8bitsRegister& x, int y){ return FLxSC_8bitsRegister(x.value ^ y); }
    friend FLxSC_8bitsRegister operator ^ (int x, const FLxSC_8bitsRegister& y){ return FLxSC_8bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_8bitsRegister& x, int y){ return x.value == static_cast<bit8_t>(y); }
    friend bool operator == (int x, const FLxSC_8bitsRegister& y){ return static_cast<bit8_t>(x) == y.value; }
    friend bool operator != (const FLxSC_8bitsRegister& x, int y){ return x.value != static_cast<bit8_t>(y); }
    friend bool operator != (int x, const FLxSC_8bitsRegister& y){ return static_cast<bit8_t>(x) != y.value; }
    friend bool operator <= (const FLxSC_8bitsRegister& x, int y){ return x.value <= static_cast<bit8_t>(y); }
    friend bool operator <= (int x, const FLxSC_8bitsRegister& y){ return static_cast<bit8_t>(x) <= y.value; }
    friend bool operator >= (const FLxSC_8bitsRegister& x, int y){ return x.value >= static_cast<bit8_t>(y); }
    friend bool operator >= (int x, const FLxSC_8bitsRegister& y){ return static_cast<bit8_t>(x) >= y.value; }
    friend bool operator < (const FLxSC_8bitsRegister& x, int y){ return x.value < static_cast<bit8_t>(y); }
    friend bool operator < (int x, const FLxSC_8bitsRegister& y){ return static_cast<bit8_t>(x) < y.value; }
    friend bool operator > (const FLxSC_8bitsRegister& x, int y){ return x.value > static_cast<bit8_t>(y); }
    friend bool operator > (int x, const FLxSC_8bitsRegister& y){ return static_cast<bit8_t>(x) > y.value; }
 protected:
    bit8_t readMask;
    bit8_t writeMask;
    bit8_t value;
};

class FLxSC_16bitsRegister {
 public:
    bit16_t& c_value(void){ return value; }
    bit16_t c_value(void) const { return value; }
    bit16_t read(void) const { return value & readMask; }
    void setReadMask(bit16_t x){ readMask = x; }
    void setWriteMask(bit16_t x){ writeMask = x; }
    void write(bit16_t x){ value = (value & ~writeMask) | (x & writeMask); }
    bit16_t operator () (void){ return value; }
    /*
     * constructor
     */
    FLxSC_16bitsRegister(void) : readMask(~(bit16_t)0), writeMask(~(bit16_t)0), value(0) {} /**< default constructor */
    FLxSC_16bitsRegister(bit16_t x, bit16_t readMask = ~(bit16_t)0, bit16_t writeMask = ~(bit16_t)0) : readMask(readMask), writeMask(writeMask), value(x) {} /**< constructor */
    FLxSC_16bitsRegister(const FLxSC_16bitsRegister& x) : readMask(x.readMask), writeMask(x.writeMask), value(x.value) {} /**< copy constructor */
    /*
     * assignment operator
     */
    const FLxSC_16bitsRegister& operator = (const FLxSC_16bitsRegister& x){ value = x.value; return *this; }
    const FLxSC_16bitsRegister& operator += (const FLxSC_16bitsRegister& x){ value = value + x.value; return *this; }
    const FLxSC_16bitsRegister& operator -= (const FLxSC_16bitsRegister& x){ value = value - x.value; return *this; }
    const FLxSC_16bitsRegister& operator *= (const FLxSC_16bitsRegister& x){ value = value * x.value; return *this; }
    const FLxSC_16bitsRegister& operator /= (const FLxSC_16bitsRegister& x){ value = value / x.value; return *this; }
    const FLxSC_16bitsRegister& operator %= (const FLxSC_16bitsRegister& x){ value = value % x.value; return *this; }
    const FLxSC_16bitsRegister& operator <<= (const FLxSC_16bitsRegister& x){ value = value << x.value; return *this; }
    const FLxSC_16bitsRegister& operator >>= (const FLxSC_16bitsRegister& x){ value = value >> x.value; return *this; }
    const FLxSC_16bitsRegister& operator &= (const FLxSC_16bitsRegister& x){ value = value & x.value; return *this; }
    const FLxSC_16bitsRegister& operator |= (const FLxSC_16bitsRegister& x){ value = value | x.value; return *this; }
    const FLxSC_16bitsRegister& operator ^= (const FLxSC_16bitsRegister& x){ value = value ^ x.value; return *this; }
    const FLxSC_16bitsRegister& operator = (const bit16_t x){ value = x; return *this; }
    const FLxSC_16bitsRegister& operator += (const bit16_t x){ value = value + x; return *this; }
    const FLxSC_16bitsRegister& operator -= (const bit16_t x){ value = value - x; return *this; }
    const FLxSC_16bitsRegister& operator *= (const bit16_t x){ value = value * x; return *this; }
    const FLxSC_16bitsRegister& operator /= (const bit16_t x){ value = value / x; return *this; }
    const FLxSC_16bitsRegister& operator %= (const bit16_t x){ value = value % x; return *this; }
    const FLxSC_16bitsRegister& operator <<= (const bit16_t x){ value = value << x; return *this; }
    const FLxSC_16bitsRegister& operator >>= (const bit16_t x){ value = value >> x; return *this; }
    const FLxSC_16bitsRegister& operator &= (const bit16_t x){ value = value & x; return *this; }
    const FLxSC_16bitsRegister& operator |= (const bit16_t x){ value = value | x; return *this; }
    const FLxSC_16bitsRegister& operator ^= (const bit16_t x){ value = value ^ x; return *this; }
    const FLxSC_16bitsRegister& operator = (const int x){ value = x; return *this; }
    const FLxSC_16bitsRegister& operator += (const int x){ value = value + x; return *this; }
    const FLxSC_16bitsRegister& operator -= (const int x){ value = value - x; return *this; }
    const FLxSC_16bitsRegister& operator *= (const int x){ value = value * x; return *this; }
    const FLxSC_16bitsRegister& operator /= (const int x){ value = value / x; return *this; }
    const FLxSC_16bitsRegister& operator %= (const int x){ value = value % x; return *this; }
    const FLxSC_16bitsRegister& operator <<= (const int x){ value = value << x; return *this; }
    const FLxSC_16bitsRegister& operator >>= (const int x){ value = value >> x; return *this; }
    const FLxSC_16bitsRegister& operator &= (const int x){ value = value & x; return *this; }
    const FLxSC_16bitsRegister& operator |= (const int x){ value = value | x; return *this; }
    const FLxSC_16bitsRegister& operator ^= (const int x){ value = value ^ x; return *this; }
    /*
     * cast operator
     */
    operator unsigned char (void) const { return static_cast<unsigned char>(value); }
    operator unsigned short (void) const { return static_cast<unsigned short>(value); }
    operator unsigned short& (void){ return value; }
    operator unsigned int (void) const { return static_cast<unsigned int>(value); }
#if defined(_WIN32) && !defined(__CYGWIN32__)
# if defined(_MSC_VER) && (1200 <= _MSC_VER) && (_MSC_VER < 1300)
    operator unsigned __int64 (void) const { return static_cast<unsigned __int64>(value); }
# elif defined(_MSC_VER) && (1300 <= _MSC_VER)
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
# endif
#else
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
#endif
    /*
     * address operator
     */
    bit16_t* operator & (void){ return &value; }
    const bit16_t* operator & (void) const { return &value; }
    /*
     * unary operator
     */
    FLxSC_16bitsRegister operator + (void) const { return FLxSC_16bitsRegister(value); }
    FLxSC_16bitsRegister operator - (void) const { return FLxSC_16bitsRegister(-value); }
    FLxSC_16bitsRegister operator ~ (void) const { return FLxSC_16bitsRegister(~value); }
    bool operator ! (void) const { return !value; }
    /*
     * prefix/postfix operator
     */
    const FLxSC_16bitsRegister& operator ++ (void){ value = value + 1; return *this; }
    const FLxSC_16bitsRegister& operator -- (void){ value = value - 1; return *this; }
    FLxSC_16bitsRegister operator ++ (int){ FLxSC_16bitsRegister tmp(*this); value = value + 1; return tmp; }
    FLxSC_16bitsRegister operator -- (int){ FLxSC_16bitsRegister tmp(*this); value = value - 1; return tmp; }
    /*
     * binary operator
     */
    friend FLxSC_16bitsRegister operator + (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value + y.value); }
    friend FLxSC_16bitsRegister operator - (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value - y.value); }
    friend FLxSC_16bitsRegister operator * (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value * y.value); }
    friend FLxSC_16bitsRegister operator / (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value / y.value); }
    friend FLxSC_16bitsRegister operator % (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value % y.value); }
    friend FLxSC_16bitsRegister operator << (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value << y.value); }
    friend FLxSC_16bitsRegister operator >> (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value >> y.value); }
    friend FLxSC_16bitsRegister operator & (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value & y.value); }
    friend FLxSC_16bitsRegister operator | (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value | y.value); }
    friend FLxSC_16bitsRegister operator ^ (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x.value ^ y.value); }
    friend bool operator == (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return x.value == y.value; }
    friend bool operator != (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return x.value != y.value; }
    friend bool operator <= (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return x.value <= y.value; }
    friend bool operator >= (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return x.value >= y.value; }
    friend bool operator < (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return x.value < y.value; }
    friend bool operator > (const FLxSC_16bitsRegister& x, const FLxSC_16bitsRegister& y){ return x.value > y.value; }
    friend FLxSC_16bitsRegister operator + (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value + y); }
    friend FLxSC_16bitsRegister operator + (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x + y.value); }
    friend FLxSC_16bitsRegister operator - (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value - y); }
    friend FLxSC_16bitsRegister operator - (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x - y.value); }
    friend FLxSC_16bitsRegister operator * (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value * y); }
    friend FLxSC_16bitsRegister operator * (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x * y.value); }
    friend FLxSC_16bitsRegister operator / (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value / y); }
    friend FLxSC_16bitsRegister operator / (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x / y.value); }
    friend FLxSC_16bitsRegister operator << (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value << y); }
    friend FLxSC_16bitsRegister operator << (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x << y.value); }
    friend FLxSC_16bitsRegister operator >> (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value >> y); }
    friend FLxSC_16bitsRegister operator >> (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x >> y.value); }
    friend FLxSC_16bitsRegister operator & (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value & y); }
    friend FLxSC_16bitsRegister operator & (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x & y.value); }
    friend FLxSC_16bitsRegister operator | (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value | y); }
    friend FLxSC_16bitsRegister operator | (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x | y.value); }
    friend FLxSC_16bitsRegister operator ^ (const FLxSC_16bitsRegister& x, bit16_t y){ return FLxSC_16bitsRegister(x.value ^ y); }
    friend FLxSC_16bitsRegister operator ^ (bit16_t x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_16bitsRegister& x, bit16_t y){ return x.value == y; }
    friend bool operator == (bit16_t x, const FLxSC_16bitsRegister& y){ return x == y.value; }
    friend bool operator != (const FLxSC_16bitsRegister& x, bit16_t y){ return x.value != y; }
    friend bool operator != (bit16_t x, const FLxSC_16bitsRegister& y){ return x != y.value; }
    friend bool operator <= (const FLxSC_16bitsRegister& x, bit16_t y){ return x.value <= y; }
    friend bool operator <= (bit16_t x, const FLxSC_16bitsRegister& y){ return x <= y.value; }
    friend bool operator >= (const FLxSC_16bitsRegister& x, bit16_t y){ return x.value >= y; }
    friend bool operator >= (bit16_t x, const FLxSC_16bitsRegister& y){ return x >= y.value; }
    friend bool operator < (const FLxSC_16bitsRegister& x, bit16_t y){ return x.value < y; }
    friend bool operator < (bit16_t x, const FLxSC_16bitsRegister& y){ return x < y.value; }
    friend bool operator > (const FLxSC_16bitsRegister& x, bit16_t y){ return x.value > y; }
    friend bool operator > (bit16_t x, const FLxSC_16bitsRegister& y){ return x > y.value; }
    friend FLxSC_16bitsRegister operator + (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value + y); }
    friend FLxSC_16bitsRegister operator + (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x + y.value); }
    friend FLxSC_16bitsRegister operator - (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value - y); }
    friend FLxSC_16bitsRegister operator - (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x - y.value); }
    friend FLxSC_16bitsRegister operator * (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value * y); }
    friend FLxSC_16bitsRegister operator * (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x * y.value); }
    friend FLxSC_16bitsRegister operator / (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value / y); }
    friend FLxSC_16bitsRegister operator / (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x / y.value); }
    friend FLxSC_16bitsRegister operator << (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value << y); }
    friend FLxSC_16bitsRegister operator << (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x << y.value); }
    friend FLxSC_16bitsRegister operator >> (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value >> y); }
    friend FLxSC_16bitsRegister operator >> (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x >> y.value); }
    friend FLxSC_16bitsRegister operator & (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value & y); }
    friend FLxSC_16bitsRegister operator & (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x & y.value); }
    friend FLxSC_16bitsRegister operator | (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value | y); }
    friend FLxSC_16bitsRegister operator | (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x | y.value); }
    friend FLxSC_16bitsRegister operator ^ (const FLxSC_16bitsRegister& x, int y){ return FLxSC_16bitsRegister(x.value ^ y); }
    friend FLxSC_16bitsRegister operator ^ (int x, const FLxSC_16bitsRegister& y){ return FLxSC_16bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_16bitsRegister& x, int y){ return x.value == static_cast<bit16_t>(y); }
    friend bool operator == (int x, const FLxSC_16bitsRegister& y){ return static_cast<bit16_t>(x) == y.value; }
    friend bool operator != (const FLxSC_16bitsRegister& x, int y){ return x.value != static_cast<bit16_t>(y); }
    friend bool operator != (int x, const FLxSC_16bitsRegister& y){ return static_cast<bit16_t>(x) != y.value; }
    friend bool operator <= (const FLxSC_16bitsRegister& x, int y){ return x.value <= static_cast<bit16_t>(y); }
    friend bool operator <= (int x, const FLxSC_16bitsRegister& y){ return static_cast<bit16_t>(x) <= y.value; }
    friend bool operator >= (const FLxSC_16bitsRegister& x, int y){ return x.value >= static_cast<bit16_t>(y); }
    friend bool operator >= (int x, const FLxSC_16bitsRegister& y){ return static_cast<bit16_t>(x) >= y.value; }
    friend bool operator < (const FLxSC_16bitsRegister& x, int y){ return x.value < static_cast<bit16_t>(y); }
    friend bool operator < (int x, const FLxSC_16bitsRegister& y){ return static_cast<bit16_t>(x) < y.value; }
    friend bool operator > (const FLxSC_16bitsRegister& x, int y){ return x.value > static_cast<bit16_t>(y); }
    friend bool operator > (int x, const FLxSC_16bitsRegister& y){ return static_cast<bit16_t>(x) > y.value; }
 protected:
    bit16_t readMask;
    bit16_t writeMask;
    bit16_t value;
};

class FLxSC_32bitsRegister {
 public:
    bit32_t& c_value(void){ return value; }
    bit32_t c_value(void) const { return value; }
    bit32_t read(void) const { return value & readMask; }
    void setReadMask(bit32_t x){ readMask = x; }
    void setWriteMask(bit32_t x){ writeMask = x; }
    void write(bit32_t x){ value = (value & ~writeMask) | (x & writeMask); }
    bit32_t operator () (void){ return value; }
    /*
     * constructor
     */
    FLxSC_32bitsRegister(void) : readMask(~(bit32_t)0), writeMask(~(bit32_t)0), value(0) {} /**< default constructor */
    FLxSC_32bitsRegister(bit32_t x, bit32_t readMask = ~(bit32_t)0, bit32_t writeMask = ~(bit32_t)0) : readMask(readMask), writeMask(writeMask), value(x) {} /**< constructor */
    FLxSC_32bitsRegister(const FLxSC_32bitsRegister& x) : readMask(x.readMask), writeMask(x.writeMask), value(x.value) {} /**< copy constructor */
    /*
     * assignment operator
     */
    const FLxSC_32bitsRegister& operator = (const FLxSC_32bitsRegister& x){ value = x.value; return *this; }
    const FLxSC_32bitsRegister& operator += (const FLxSC_32bitsRegister& x){ value = value + x.value; return *this; }
    const FLxSC_32bitsRegister& operator -= (const FLxSC_32bitsRegister& x){ value = value - x.value; return *this; }
    const FLxSC_32bitsRegister& operator *= (const FLxSC_32bitsRegister& x){ value = value * x.value; return *this; }
    const FLxSC_32bitsRegister& operator /= (const FLxSC_32bitsRegister& x){ value = value / x.value; return *this; }
    const FLxSC_32bitsRegister& operator %= (const FLxSC_32bitsRegister& x){ value = value % x.value; return *this; }
    const FLxSC_32bitsRegister& operator <<= (const FLxSC_32bitsRegister& x){ value = value << x.value; return *this; }
    const FLxSC_32bitsRegister& operator >>= (const FLxSC_32bitsRegister& x){ value = value >> x.value; return *this; }
    const FLxSC_32bitsRegister& operator &= (const FLxSC_32bitsRegister& x){ value = value & x.value; return *this; }
    const FLxSC_32bitsRegister& operator |= (const FLxSC_32bitsRegister& x){ value = value | x.value; return *this; }
    const FLxSC_32bitsRegister& operator ^= (const FLxSC_32bitsRegister& x){ value = value ^ x.value; return *this; }
    const FLxSC_32bitsRegister& operator = (const bit32_t x){ value = x; return *this; }
    const FLxSC_32bitsRegister& operator += (const bit32_t x){ value = value + x; return *this; }
    const FLxSC_32bitsRegister& operator -= (const bit32_t x){ value = value - x; return *this; }
    const FLxSC_32bitsRegister& operator *= (const bit32_t x){ value = value * x; return *this; }
    const FLxSC_32bitsRegister& operator /= (const bit32_t x){ value = value / x; return *this; }
    const FLxSC_32bitsRegister& operator %= (const bit32_t x){ value = value % x; return *this; }
    const FLxSC_32bitsRegister& operator <<= (const bit32_t x){ value = value << x; return *this; }
    const FLxSC_32bitsRegister& operator >>= (const bit32_t x){ value = value >> x; return *this; }
    const FLxSC_32bitsRegister& operator &= (const bit32_t x){ value = value & x; return *this; }
    const FLxSC_32bitsRegister& operator |= (const bit32_t x){ value = value | x; return *this; }
    const FLxSC_32bitsRegister& operator ^= (const bit32_t x){ value = value ^ x; return *this; }
    const FLxSC_32bitsRegister& operator = (const int x){ value = x; return *this; }
    const FLxSC_32bitsRegister& operator += (const int x){ value = value + x; return *this; }
    const FLxSC_32bitsRegister& operator -= (const int x){ value = value - x; return *this; }
    const FLxSC_32bitsRegister& operator *= (const int x){ value = value * x; return *this; }
    const FLxSC_32bitsRegister& operator /= (const int x){ value = value / x; return *this; }
    const FLxSC_32bitsRegister& operator %= (const int x){ value = value % x; return *this; }
    const FLxSC_32bitsRegister& operator <<= (const int x){ value = value << x; return *this; }
    const FLxSC_32bitsRegister& operator >>= (const int x){ value = value >> x; return *this; }
    const FLxSC_32bitsRegister& operator &= (const int x){ value = value & x; return *this; }
    const FLxSC_32bitsRegister& operator |= (const int x){ value = value | x; return *this; }
    const FLxSC_32bitsRegister& operator ^= (const int x){ value = value ^ x; return *this; }
    /*
     * cast operator
     */
    operator unsigned char (void) const { return static_cast<unsigned char>(value); }
    operator unsigned short (void) const { return static_cast<unsigned short>(value); }
    operator unsigned int (void) const { return static_cast<unsigned int>(value); }
    operator unsigned int& (void){ return value; }
#if defined(_WIN32) && !defined(__CYGWIN32__)
# if defined(_MSC_VER) && (1200 <= _MSC_VER) && (_MSC_VER < 1300)
    operator unsigned __int64 (void) const { return static_cast<unsigned __int64>(value); }
# elif defined(_MSC_VER) && (1300 <= _MSC_VER)
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
# endif
#else
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
#endif
    /*
     * address operator
     */
    bit32_t* operator & (void){ return &value; }
    const bit32_t* operator & (void) const { return &value; }
    /*
     * unary operator
     */
    FLxSC_32bitsRegister operator + (void) const { return FLxSC_32bitsRegister(value); }
    FLxSC_32bitsRegister operator - (void) const { return FLxSC_32bitsRegister(-value); }
    FLxSC_32bitsRegister operator ~ (void) const { return FLxSC_32bitsRegister(~value); }
    bool operator ! (void) const { return !value; }
    /*
     * prefix/postfix operator
     */
    const FLxSC_32bitsRegister& operator ++ (void){ value = value + 1; return *this; }
    const FLxSC_32bitsRegister& operator -- (void){ value = value - 1; return *this; }
    FLxSC_32bitsRegister operator ++ (int){ FLxSC_32bitsRegister tmp(*this); value = value + 1; return tmp; }
    FLxSC_32bitsRegister operator -- (int){ FLxSC_32bitsRegister tmp(*this); value = value - 1; return tmp; }
    /*
     * binary operator
     */
    friend FLxSC_32bitsRegister operator + (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value + y.value); }
    friend FLxSC_32bitsRegister operator - (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value - y.value); }
    friend FLxSC_32bitsRegister operator * (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value * y.value); }
    friend FLxSC_32bitsRegister operator / (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value / y.value); }
    friend FLxSC_32bitsRegister operator % (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value % y.value); }
    friend FLxSC_32bitsRegister operator << (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value << y.value); }
    friend FLxSC_32bitsRegister operator >> (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value >> y.value); }
    friend FLxSC_32bitsRegister operator & (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value & y.value); }
    friend FLxSC_32bitsRegister operator | (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value | y.value); }
    friend FLxSC_32bitsRegister operator ^ (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x.value ^ y.value); }
    friend bool operator == (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return x.value == y.value; }
    friend bool operator != (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return x.value != y.value; }
    friend bool operator <= (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return x.value <= y.value; }
    friend bool operator >= (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return x.value >= y.value; }
    friend bool operator < (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return x.value < y.value; }
    friend bool operator > (const FLxSC_32bitsRegister& x, const FLxSC_32bitsRegister& y){ return x.value > y.value; }
    friend FLxSC_32bitsRegister operator + (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value + y); }
    friend FLxSC_32bitsRegister operator + (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x + y.value); }
    friend FLxSC_32bitsRegister operator - (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value - y); }
    friend FLxSC_32bitsRegister operator - (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x - y.value); }
    friend FLxSC_32bitsRegister operator * (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value * y); }
    friend FLxSC_32bitsRegister operator * (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x * y.value); }
    friend FLxSC_32bitsRegister operator / (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value / y); }
    friend FLxSC_32bitsRegister operator / (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x / y.value); }
    friend FLxSC_32bitsRegister operator << (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value << y); }
    friend FLxSC_32bitsRegister operator << (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x << y.value); }
    friend FLxSC_32bitsRegister operator >> (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value >> y); }
    friend FLxSC_32bitsRegister operator >> (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x >> y.value); }
    friend FLxSC_32bitsRegister operator & (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value & y); }
    friend FLxSC_32bitsRegister operator & (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x & y.value); }
    friend FLxSC_32bitsRegister operator | (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value | y); }
    friend FLxSC_32bitsRegister operator | (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x | y.value); }
    friend FLxSC_32bitsRegister operator ^ (const FLxSC_32bitsRegister& x, bit32_t y){ return FLxSC_32bitsRegister(x.value ^ y); }
    friend FLxSC_32bitsRegister operator ^ (bit32_t x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_32bitsRegister& x, bit32_t y){ return x.value == y; }
    friend bool operator == (bit32_t x, const FLxSC_32bitsRegister& y){ return x == y.value; }
    friend bool operator != (const FLxSC_32bitsRegister& x, bit32_t y){ return x.value != y; }
    friend bool operator != (bit32_t x, const FLxSC_32bitsRegister& y){ return x != y.value; }
    friend bool operator <= (const FLxSC_32bitsRegister& x, bit32_t y){ return x.value <= y; }
    friend bool operator <= (bit32_t x, const FLxSC_32bitsRegister& y){ return x <= y.value; }
    friend bool operator >= (const FLxSC_32bitsRegister& x, bit32_t y){ return x.value >= y; }
    friend bool operator >= (bit32_t x, const FLxSC_32bitsRegister& y){ return x >= y.value; }
    friend bool operator < (const FLxSC_32bitsRegister& x, bit32_t y){ return x.value < y; }
    friend bool operator < (bit32_t x, const FLxSC_32bitsRegister& y){ return x < y.value; }
    friend bool operator > (const FLxSC_32bitsRegister& x, bit32_t y){ return x.value > y; }
    friend bool operator > (bit32_t x, const FLxSC_32bitsRegister& y){ return x > y.value; }
    friend FLxSC_32bitsRegister operator + (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value + y); }
    friend FLxSC_32bitsRegister operator + (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x + y.value); }
    friend FLxSC_32bitsRegister operator - (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value - y); }
    friend FLxSC_32bitsRegister operator - (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x - y.value); }
    friend FLxSC_32bitsRegister operator * (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value * y); }
    friend FLxSC_32bitsRegister operator * (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x * y.value); }
    friend FLxSC_32bitsRegister operator / (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value / y); }
    friend FLxSC_32bitsRegister operator / (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x / y.value); }
    friend FLxSC_32bitsRegister operator << (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value << y); }
    friend FLxSC_32bitsRegister operator << (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x << y.value); }
    friend FLxSC_32bitsRegister operator >> (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value >> y); }
    friend FLxSC_32bitsRegister operator >> (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x >> y.value); }
    friend FLxSC_32bitsRegister operator & (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value & y); }
    friend FLxSC_32bitsRegister operator & (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x & y.value); }
    friend FLxSC_32bitsRegister operator | (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value | y); }
    friend FLxSC_32bitsRegister operator | (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x | y.value); }
    friend FLxSC_32bitsRegister operator ^ (const FLxSC_32bitsRegister& x, int y){ return FLxSC_32bitsRegister(x.value ^ y); }
    friend FLxSC_32bitsRegister operator ^ (int x, const FLxSC_32bitsRegister& y){ return FLxSC_32bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_32bitsRegister& x, int y){ return x.value == static_cast<bit32_t>(y); }
    friend bool operator == (int x, const FLxSC_32bitsRegister& y){ return static_cast<bit32_t>(x) == y.value; }
    friend bool operator != (const FLxSC_32bitsRegister& x, int y){ return x.value != static_cast<bit32_t>(y); }
    friend bool operator != (int x, const FLxSC_32bitsRegister& y){ return static_cast<bit32_t>(x) != y.value; }
    friend bool operator <= (const FLxSC_32bitsRegister& x, int y){ return x.value <= static_cast<bit32_t>(y); }
    friend bool operator <= (int x, const FLxSC_32bitsRegister& y){ return static_cast<bit32_t>(x) <= y.value; }
    friend bool operator >= (const FLxSC_32bitsRegister& x, int y){ return x.value >= static_cast<bit32_t>(y); }
    friend bool operator >= (int x, const FLxSC_32bitsRegister& y){ return static_cast<bit32_t>(x) >= y.value; }
    friend bool operator < (const FLxSC_32bitsRegister& x, int y){ return x.value < static_cast<bit32_t>(y); }
    friend bool operator < (int x, const FLxSC_32bitsRegister& y){ return static_cast<bit32_t>(x) < y.value; }
    friend bool operator > (const FLxSC_32bitsRegister& x, int y){ return x.value > static_cast<bit32_t>(y); }
    friend bool operator > (int x, const FLxSC_32bitsRegister& y){ return static_cast<bit32_t>(x) > y.value; }
 protected:
    bit32_t readMask;
    bit32_t writeMask;
    bit32_t value;
};

class FLxSC_64bitsRegister {
 public:
    bit64_t& c_value(void){ return value; }
    bit64_t c_value(void) const { return value; }
    bit64_t read(void) const { return value & readMask; }
    void setReadMask(bit64_t x){ readMask = x; }
    void setWriteMask(bit64_t x){ writeMask = x; }
    void write(bit64_t x){ value = (value & ~writeMask) | (x & writeMask); }
    bit64_t operator () (void){ return value; }
    /*
     * constructor
     */
    FLxSC_64bitsRegister(void) : readMask(~(bit64_t)0), writeMask(~(bit64_t)0), value(0) {} /**< default constructor */
    FLxSC_64bitsRegister(bit64_t x, bit64_t readMask = ~(bit64_t)0, bit64_t writeMask = ~(bit64_t)0) : readMask(readMask), writeMask(writeMask), value(x) {} /**< constructor */
    FLxSC_64bitsRegister(const FLxSC_64bitsRegister& x) : readMask(x.readMask), writeMask(x.writeMask), value(x.value) {} /**< copy constructor */
    /*
     * assignment operator
     */
    const FLxSC_64bitsRegister& operator = (const FLxSC_64bitsRegister& x){ value = x.value; return *this; }
    const FLxSC_64bitsRegister& operator += (const FLxSC_64bitsRegister& x){ value = value + x.value; return *this; }
    const FLxSC_64bitsRegister& operator -= (const FLxSC_64bitsRegister& x){ value = value - x.value; return *this; }
    const FLxSC_64bitsRegister& operator *= (const FLxSC_64bitsRegister& x){ value = value * x.value; return *this; }
    const FLxSC_64bitsRegister& operator /= (const FLxSC_64bitsRegister& x){ value = value / x.value; return *this; }
    const FLxSC_64bitsRegister& operator %= (const FLxSC_64bitsRegister& x){ value = value % x.value; return *this; }
    const FLxSC_64bitsRegister& operator <<= (const FLxSC_64bitsRegister& x){ value = value << x.value; return *this; }
    const FLxSC_64bitsRegister& operator >>= (const FLxSC_64bitsRegister& x){ value = value >> x.value; return *this; }
    const FLxSC_64bitsRegister& operator &= (const FLxSC_64bitsRegister& x){ value = value & x.value; return *this; }
    const FLxSC_64bitsRegister& operator |= (const FLxSC_64bitsRegister& x){ value = value | x.value; return *this; }
    const FLxSC_64bitsRegister& operator ^= (const FLxSC_64bitsRegister& x){ value = value ^ x.value; return *this; }
    const FLxSC_64bitsRegister& operator = (const bit64_t x){ value = x; return *this; }
    const FLxSC_64bitsRegister& operator += (const bit64_t x){ value = value + x; return *this; }
    const FLxSC_64bitsRegister& operator -= (const bit64_t x){ value = value - x; return *this; }
    const FLxSC_64bitsRegister& operator *= (const bit64_t x){ value = value * x; return *this; }
    const FLxSC_64bitsRegister& operator /= (const bit64_t x){ value = value / x; return *this; }
    const FLxSC_64bitsRegister& operator %= (const bit64_t x){ value = value % x; return *this; }
    const FLxSC_64bitsRegister& operator <<= (const bit64_t x){ value = value << x; return *this; }
    const FLxSC_64bitsRegister& operator >>= (const bit64_t x){ value = value >> x; return *this; }
    const FLxSC_64bitsRegister& operator &= (const bit64_t x){ value = value & x; return *this; }
    const FLxSC_64bitsRegister& operator |= (const bit64_t x){ value = value | x; return *this; }
    const FLxSC_64bitsRegister& operator ^= (const bit64_t x){ value = value ^ x; return *this; }
    const FLxSC_64bitsRegister& operator = (const int x){ value = x; return *this; }
    const FLxSC_64bitsRegister& operator += (const int x){ value = value + x; return *this; }
    const FLxSC_64bitsRegister& operator -= (const int x){ value = value - x; return *this; }
    const FLxSC_64bitsRegister& operator *= (const int x){ value = value * x; return *this; }
    const FLxSC_64bitsRegister& operator /= (const int x){ value = value / x; return *this; }
    const FLxSC_64bitsRegister& operator %= (const int x){ value = value % x; return *this; }
    const FLxSC_64bitsRegister& operator <<= (const int x){ value = value << x; return *this; }
    const FLxSC_64bitsRegister& operator >>= (const int x){ value = value >> x; return *this; }
    const FLxSC_64bitsRegister& operator &= (const int x){ value = value & x; return *this; }
    const FLxSC_64bitsRegister& operator |= (const int x){ value = value | x; return *this; }
    const FLxSC_64bitsRegister& operator ^= (const int x){ value = value ^ x; return *this; }
    /*
     * cast operator
     */
    operator unsigned char (void) const { return static_cast<unsigned char>(value); }
    operator unsigned short (void) const { return static_cast<unsigned short>(value); }
    operator unsigned int (void) const { return static_cast<unsigned int>(value); }
#if defined(_WIN32) && !defined(__CYGWIN32__)
# if defined(_MSC_VER) && (1200 <= _MSC_VER) && (_MSC_VER < 1300)
    operator unsigned __int64 (void) const { return static_cast<unsigned __int64>(value); }
    operator unsigned __int64& (void){ return value; }
# elif defined(_MSC_VER) && (1300 <= _MSC_VER)
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
    operator unsigned long long& (void){ return value; }
#endif
#else
    operator unsigned long long (void) const { return static_cast<unsigned long long>(value); }
    operator unsigned long long& (void){ return value; }
#endif
    /*
     * address operator
     */
    bit64_t* operator & (void){ return &value; }
    const bit64_t* operator & (void) const { return &value; }
    /*
     * unary operator
     */
    FLxSC_64bitsRegister operator + (void) const { return FLxSC_64bitsRegister(value); }
    FLxSC_64bitsRegister operator - (void) const { return FLxSC_64bitsRegister(-value); }
    FLxSC_64bitsRegister operator ~ (void) const { return FLxSC_64bitsRegister(~value); }
    bool operator ! (void) const { return !value; }
    /*
     * prefix/postfix operator
     */
    const FLxSC_64bitsRegister& operator ++ (void){ value = value + 1; return *this; }
    const FLxSC_64bitsRegister& operator -- (void){ value = value - 1; return *this; }
    FLxSC_64bitsRegister operator ++ (int){ FLxSC_64bitsRegister tmp(*this); value = value + 1; return tmp; }
    FLxSC_64bitsRegister operator -- (int){ FLxSC_64bitsRegister tmp(*this); value = value - 1; return tmp; }
    /*
     * binary operator
     */
    friend FLxSC_64bitsRegister operator + (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value + y.value); }
    friend FLxSC_64bitsRegister operator - (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value - y.value); }
    friend FLxSC_64bitsRegister operator * (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value * y.value); }
    friend FLxSC_64bitsRegister operator / (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value / y.value); }
    friend FLxSC_64bitsRegister operator % (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value % y.value); }
    friend FLxSC_64bitsRegister operator << (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value << y.value); }
    friend FLxSC_64bitsRegister operator >> (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value >> y.value); }
    friend FLxSC_64bitsRegister operator & (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value & y.value); }
    friend FLxSC_64bitsRegister operator | (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value | y.value); }
    friend FLxSC_64bitsRegister operator ^ (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x.value ^ y.value); }
    friend bool operator == (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return x.value == y.value; }
    friend bool operator != (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return x.value != y.value; }
    friend bool operator <= (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return x.value <= y.value; }
    friend bool operator >= (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return x.value >= y.value; }
    friend bool operator < (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return x.value < y.value; }
    friend bool operator > (const FLxSC_64bitsRegister& x, const FLxSC_64bitsRegister& y){ return x.value > y.value; }
    friend FLxSC_64bitsRegister operator + (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value + y); }
    friend FLxSC_64bitsRegister operator + (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x + y.value); }
    friend FLxSC_64bitsRegister operator - (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value - y); }
    friend FLxSC_64bitsRegister operator - (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x - y.value); }
    friend FLxSC_64bitsRegister operator * (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value * y); }
    friend FLxSC_64bitsRegister operator * (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x * y.value); }
    friend FLxSC_64bitsRegister operator / (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value / y); }
    friend FLxSC_64bitsRegister operator / (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x / y.value); }
    friend FLxSC_64bitsRegister operator << (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value << y); }
    friend FLxSC_64bitsRegister operator << (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x << y.value); }
    friend FLxSC_64bitsRegister operator >> (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value >> y); }
    friend FLxSC_64bitsRegister operator >> (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x >> y.value); }
    friend FLxSC_64bitsRegister operator & (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value & y); }
    friend FLxSC_64bitsRegister operator & (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x & y.value); }
    friend FLxSC_64bitsRegister operator | (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value | y); }
    friend FLxSC_64bitsRegister operator | (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x | y.value); }
    friend FLxSC_64bitsRegister operator ^ (const FLxSC_64bitsRegister& x, bit64_t y){ return FLxSC_64bitsRegister(x.value ^ y); }
    friend FLxSC_64bitsRegister operator ^ (bit64_t x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_64bitsRegister& x, bit64_t y){ return x.value == y; }
    friend bool operator == (bit64_t x, const FLxSC_64bitsRegister& y){ return x == y.value; }
    friend bool operator != (const FLxSC_64bitsRegister& x, bit64_t y){ return x.value != y; }
    friend bool operator != (bit64_t x, const FLxSC_64bitsRegister& y){ return x != y.value; }
    friend bool operator <= (const FLxSC_64bitsRegister& x, bit64_t y){ return x.value <= y; }
    friend bool operator <= (bit64_t x, const FLxSC_64bitsRegister& y){ return x <= y.value; }
    friend bool operator >= (const FLxSC_64bitsRegister& x, bit64_t y){ return x.value >= y; }
    friend bool operator >= (bit64_t x, const FLxSC_64bitsRegister& y){ return x >= y.value; }
    friend bool operator < (const FLxSC_64bitsRegister& x, bit64_t y){ return x.value < y; }
    friend bool operator < (bit64_t x, const FLxSC_64bitsRegister& y){ return x < y.value; }
    friend bool operator > (const FLxSC_64bitsRegister& x, bit64_t y){ return x.value > y; }
    friend bool operator > (bit64_t x, const FLxSC_64bitsRegister& y){ return x > y.value; }
    friend FLxSC_64bitsRegister operator + (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value + y); }
    friend FLxSC_64bitsRegister operator + (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x + y.value); }
    friend FLxSC_64bitsRegister operator - (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value - y); }
    friend FLxSC_64bitsRegister operator - (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x - y.value); }
    friend FLxSC_64bitsRegister operator * (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value * y); }
    friend FLxSC_64bitsRegister operator * (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x * y.value); }
    friend FLxSC_64bitsRegister operator / (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value / y); }
    friend FLxSC_64bitsRegister operator / (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x / y.value); }
    friend FLxSC_64bitsRegister operator << (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value << y); }
    friend FLxSC_64bitsRegister operator << (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x << y.value); }
    friend FLxSC_64bitsRegister operator >> (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value >> y); }
    friend FLxSC_64bitsRegister operator >> (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x >> y.value); }
    friend FLxSC_64bitsRegister operator & (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value & y); }
    friend FLxSC_64bitsRegister operator & (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x & y.value); }
    friend FLxSC_64bitsRegister operator | (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value | y); }
    friend FLxSC_64bitsRegister operator | (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x | y.value); }
    friend FLxSC_64bitsRegister operator ^ (const FLxSC_64bitsRegister& x, int y){ return FLxSC_64bitsRegister(x.value ^ y); }
    friend FLxSC_64bitsRegister operator ^ (int x, const FLxSC_64bitsRegister& y){ return FLxSC_64bitsRegister(x ^ y.value); }
    friend bool operator == (const FLxSC_64bitsRegister& x, int y){ return x.value == static_cast<bit64_t>(y); }
    friend bool operator == (int x, const FLxSC_64bitsRegister& y){ return static_cast<bit64_t>(x) == y.value; }
    friend bool operator != (const FLxSC_64bitsRegister& x, int y){ return x.value != static_cast<bit64_t>(y); }
    friend bool operator != (int x, const FLxSC_64bitsRegister& y){ return static_cast<bit64_t>(x) != y.value; }
    friend bool operator <= (const FLxSC_64bitsRegister& x, int y){ return x.value <= static_cast<bit64_t>(y); }
    friend bool operator <= (int x, const FLxSC_64bitsRegister& y){ return static_cast<bit64_t>(x) <= y.value; }
    friend bool operator >= (const FLxSC_64bitsRegister& x, int y){ return x.value >= static_cast<bit64_t>(y); }
    friend bool operator >= (int x, const FLxSC_64bitsRegister& y){ return static_cast<bit64_t>(x) >= y.value; }
    friend bool operator < (const FLxSC_64bitsRegister& x, int y){ return x.value < static_cast<bit64_t>(y); }
    friend bool operator < (int x, const FLxSC_64bitsRegister& y){ return static_cast<bit64_t>(x) < y.value; }
    friend bool operator > (const FLxSC_64bitsRegister& x, int y){ return x.value > static_cast<bit64_t>(y); }
    friend bool operator > (int x, const FLxSC_64bitsRegister& y){ return static_cast<bit64_t>(x) > y.value; }
 protected:
    bit64_t readMask;
    bit64_t writeMask;
    bit64_t value;
};

typedef FLxSC_8bitsRegister FLxSC_1bRegister;
typedef FLxSC_8bitsRegister FLxSC_2bRegister;
typedef FLxSC_8bitsRegister FLxSC_3bRegister;
typedef FLxSC_8bitsRegister FLxSC_4bRegister;
typedef FLxSC_8bitsRegister FLxSC_5bRegister;
typedef FLxSC_8bitsRegister FLxSC_6bRegister;
typedef FLxSC_8bitsRegister FLxSC_7bRegister;
typedef FLxSC_8bitsRegister FLxSC_8bRegister;
typedef FLxSC_16bitsRegister FLxSC_9bRegister;
typedef FLxSC_16bitsRegister FLxSC_10bRegister;
typedef FLxSC_16bitsRegister FLxSC_11bRegister;
typedef FLxSC_16bitsRegister FLxSC_12bRegister;
typedef FLxSC_16bitsRegister FLxSC_13bRegister;
typedef FLxSC_16bitsRegister FLxSC_14bRegister;
typedef FLxSC_16bitsRegister FLxSC_15bRegister;
typedef FLxSC_16bitsRegister FLxSC_16bRegister;
typedef FLxSC_32bitsRegister FLxSC_17bRegister;
typedef FLxSC_32bitsRegister FLxSC_18bRegister;
typedef FLxSC_32bitsRegister FLxSC_19bRegister;
typedef FLxSC_32bitsRegister FLxSC_20bRegister;
typedef FLxSC_32bitsRegister FLxSC_21bRegister;
typedef FLxSC_32bitsRegister FLxSC_22bRegister;
typedef FLxSC_32bitsRegister FLxSC_23bRegister;
typedef FLxSC_32bitsRegister FLxSC_24bRegister;
typedef FLxSC_32bitsRegister FLxSC_25bRegister;
typedef FLxSC_32bitsRegister FLxSC_26bRegister;
typedef FLxSC_32bitsRegister FLxSC_27bRegister;
typedef FLxSC_32bitsRegister FLxSC_28bRegister;
typedef FLxSC_32bitsRegister FLxSC_29bRegister;
typedef FLxSC_32bitsRegister FLxSC_30bRegister;
typedef FLxSC_32bitsRegister FLxSC_31bRegister;
typedef FLxSC_32bitsRegister FLxSC_32bRegister;
typedef FLxSC_64bitsRegister FLxSC_33bRegister;
typedef FLxSC_64bitsRegister FLxSC_34bRegister;
typedef FLxSC_64bitsRegister FLxSC_35bRegister;
typedef FLxSC_64bitsRegister FLxSC_36bRegister;
typedef FLxSC_64bitsRegister FLxSC_37bRegister;
typedef FLxSC_64bitsRegister FLxSC_38bRegister;
typedef FLxSC_64bitsRegister FLxSC_39bRegister;
typedef FLxSC_64bitsRegister FLxSC_40bRegister;
typedef FLxSC_64bitsRegister FLxSC_41bRegister;
typedef FLxSC_64bitsRegister FLxSC_42bRegister;
typedef FLxSC_64bitsRegister FLxSC_43bRegister;
typedef FLxSC_64bitsRegister FLxSC_44bRegister;
typedef FLxSC_64bitsRegister FLxSC_45bRegister;
typedef FLxSC_64bitsRegister FLxSC_46bRegister;
typedef FLxSC_64bitsRegister FLxSC_47bRegister;
typedef FLxSC_64bitsRegister FLxSC_48bRegister;
typedef FLxSC_64bitsRegister FLxSC_49bRegister;
typedef FLxSC_64bitsRegister FLxSC_50bRegister;
typedef FLxSC_64bitsRegister FLxSC_51bRegister;
typedef FLxSC_64bitsRegister FLxSC_52bRegister;
typedef FLxSC_64bitsRegister FLxSC_53bRegister;
typedef FLxSC_64bitsRegister FLxSC_54bRegister;
typedef FLxSC_64bitsRegister FLxSC_55bRegister;
typedef FLxSC_64bitsRegister FLxSC_56bRegister;
typedef FLxSC_64bitsRegister FLxSC_57bRegister;
typedef FLxSC_64bitsRegister FLxSC_58bRegister;
typedef FLxSC_64bitsRegister FLxSC_59bRegister;
typedef FLxSC_64bitsRegister FLxSC_60bRegister;
typedef FLxSC_64bitsRegister FLxSC_61bRegister;
typedef FLxSC_64bitsRegister FLxSC_62bRegister;
typedef FLxSC_64bitsRegister FLxSC_63bRegister;
typedef FLxSC_64bitsRegister FLxSC_64bRegister;
#else /* defined(__FLxSC_h_kernel) */
class FLxsc_events;
class FLxSC_EventedQueue;
class FLxSC_PrioBitVector;
class FLxSC_TickCycleWait;
class FLxSC_ClockCycleWait;
#endif /* defined(__FLxSC_h_kernel) */

#endif /* __FLxSC_h */
