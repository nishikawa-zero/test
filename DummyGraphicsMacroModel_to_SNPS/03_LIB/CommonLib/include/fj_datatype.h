/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2010
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file fj_datatype.h
 * @brief データ型統一用ヘッダファイル (include)
 *
 * @author Masahiro Kato <kato.masahiro@jp.fujitsu.com>
 * @date $Date: 2010/06/11 00:00:00 $
 * @version $Id: fj_datatype.h,v 0.1 2010/06/11 00:00:00 FST Exp $
 */

#ifndef FJ_DATATYPE_h
#define FJ_DATATYPE_h

#include "systemc.h"

namespace fj {

#ifdef __GNUC__ /* gcc環境 */

  /* 信号向け変数の型に使用すること */
  typedef unsigned char      bit1;
  typedef unsigned char      bit2;
  typedef unsigned char      bit3;
  typedef unsigned char      bit4;
  typedef unsigned char      bit5;
  typedef unsigned char      bit6;
  typedef unsigned char      bit7;
  typedef unsigned char      bit8;
  typedef unsigned short     bit9;
  typedef unsigned short     bit10;
  typedef unsigned short     bit11;
  typedef unsigned short     bit12;
  typedef unsigned short     bit13;
  typedef unsigned short     bit14;
  typedef unsigned short     bit15;
  typedef unsigned short     bit16;
  typedef unsigned int       bit17;
  typedef unsigned int       bit18;
  typedef unsigned int       bit19;
  typedef unsigned int       bit20;
  typedef unsigned int       bit21;
  typedef unsigned int       bit22;
  typedef unsigned int       bit23;
  typedef unsigned int       bit24;
  typedef unsigned int       bit25;
  typedef unsigned int       bit26;
  typedef unsigned int       bit27;
  typedef unsigned int       bit28;
  typedef unsigned int       bit29;
  typedef unsigned int       bit30;
  typedef unsigned int       bit31;
  typedef unsigned int       bit32;
  typedef unsigned long long bit33;
  typedef unsigned long long bit34;
  typedef unsigned long long bit35;
  typedef unsigned long long bit36;
  typedef unsigned long long bit37;
  typedef unsigned long long bit38;
  typedef unsigned long long bit39;
  typedef unsigned long long bit40;
  typedef unsigned long long bit41;
  typedef unsigned long long bit42;
  typedef unsigned long long bit43;
  typedef unsigned long long bit44;
  typedef unsigned long long bit45;
  typedef unsigned long long bit46;
  typedef unsigned long long bit47;
  typedef unsigned long long bit48;
  typedef unsigned long long bit49;
  typedef unsigned long long bit50;
  typedef unsigned long long bit51;
  typedef unsigned long long bit52;
  typedef unsigned long long bit53;
  typedef unsigned long long bit54;
  typedef unsigned long long bit55;
  typedef unsigned long long bit56;
  typedef unsigned long long bit57;
  typedef unsigned long long bit58;
  typedef unsigned long long bit59;
  typedef unsigned long long bit60;
  typedef unsigned long long bit61;
  typedef unsigned long long bit62;
  typedef unsigned long long bit63;
  typedef unsigned long long bit64;
  typedef sc_biguint<65>     bit65;
  typedef sc_biguint<66>     bit66;
  typedef sc_biguint<67>     bit67;
  typedef sc_biguint<68>     bit68;
  typedef sc_biguint<69>     bit69;
  typedef sc_biguint<70>     bit70;
  typedef sc_biguint<71>     bit71;
  typedef sc_biguint<72>     bit72;
  typedef sc_biguint<73>     bit73;
  typedef sc_biguint<74>     bit74;
  typedef sc_biguint<75>     bit75;
  typedef sc_biguint<76>     bit76;
  typedef sc_biguint<77>     bit77;
  typedef sc_biguint<78>     bit78;
  typedef sc_biguint<79>     bit79;
  typedef sc_biguint<80>     bit80;
  typedef sc_biguint<81>     bit81;
  typedef sc_biguint<82>     bit82;
  typedef sc_biguint<83>     bit83;
  typedef sc_biguint<84>     bit84;
  typedef sc_biguint<85>     bit85;
  typedef sc_biguint<86>     bit86;
  typedef sc_biguint<87>     bit87;
  typedef sc_biguint<88>     bit88;
  typedef sc_biguint<89>     bit89;
  typedef sc_biguint<90>     bit90;
  typedef sc_biguint<91>     bit91;
  typedef sc_biguint<92>     bit92;
  typedef sc_biguint<93>     bit93;
  typedef sc_biguint<94>     bit94;
  typedef sc_biguint<95>     bit95;
  typedef sc_biguint<96>     bit96;
  typedef sc_biguint<97>     bit97;
  typedef sc_biguint<98>     bit98;
  typedef sc_biguint<99>     bit99;
  typedef sc_biguint<100>    bit100;
  typedef sc_biguint<101>    bit101;
  typedef sc_biguint<102>    bit102;
  typedef sc_biguint<103>    bit103;
  typedef sc_biguint<104>    bit104;
  typedef sc_biguint<105>    bit105;
  typedef sc_biguint<106>    bit106;
  typedef sc_biguint<107>    bit107;
  typedef sc_biguint<108>    bit108;
  typedef sc_biguint<109>    bit109;
  typedef sc_biguint<110>    bit110;
  typedef sc_biguint<111>    bit111;
  typedef sc_biguint<112>    bit112;
  typedef sc_biguint<113>    bit113;
  typedef sc_biguint<114>    bit114;
  typedef sc_biguint<115>    bit115;
  typedef sc_biguint<116>    bit116;
  typedef sc_biguint<117>    bit117;
  typedef sc_biguint<118>    bit118;
  typedef sc_biguint<119>    bit119;
  typedef sc_biguint<120>    bit120;
  typedef sc_biguint<121>    bit121;
  typedef sc_biguint<122>    bit122;
  typedef sc_biguint<123>    bit123;
  typedef sc_biguint<124>    bit124;
  typedef sc_biguint<125>    bit125;
  typedef sc_biguint<126>    bit126;
  typedef sc_biguint<127>    bit127;
  typedef sc_biguint<128>    bit128;

  /* 信号向け以外の変数に使用すること */
  typedef signed char        int8;
  typedef signed short       int16;
  typedef signed int         int32;
  typedef signed long long   int64;
  typedef sc_bigint<128>     int128;
  typedef unsigned char      uint8;
  typedef unsigned short     uint16;
  typedef unsigned int       uint32;
  typedef unsigned long long uint64;
  typedef sc_biguint<128>    uint128;

#else /* Visual C/C++ 環境 */

  /* 信号向け変数の型に使用すること */
  typedef unsigned __int8  bit1;
  typedef unsigned __int8  bit2;
  typedef unsigned __int8  bit3;
  typedef unsigned __int8  bit4;
  typedef unsigned __int8  bit5;
  typedef unsigned __int8  bit6;
  typedef unsigned __int8  bit7;
  typedef unsigned __int8  bit8;
  typedef unsigned __int16 bit9;
  typedef unsigned __int16 bit10;
  typedef unsigned __int16 bit11;
  typedef unsigned __int16 bit12;
  typedef unsigned __int16 bit13;
  typedef unsigned __int16 bit14;
  typedef unsigned __int16 bit15;
  typedef unsigned __int16 bit16;
  typedef unsigned __int32 bit17;
  typedef unsigned __int32 bit18;
  typedef unsigned __int32 bit19;
  typedef unsigned __int32 bit20;
  typedef unsigned __int32 bit21;
  typedef unsigned __int32 bit22;
  typedef unsigned __int32 bit23;
  typedef unsigned __int32 bit24;
  typedef unsigned __int32 bit25;
  typedef unsigned __int32 bit26;
  typedef unsigned __int32 bit27;
  typedef unsigned __int32 bit28;
  typedef unsigned __int32 bit29;
  typedef unsigned __int32 bit30;
  typedef unsigned __int32 bit31;
  typedef unsigned __int32 bit32;
  typedef unsigned __int64 bit33;
  typedef unsigned __int64 bit34;
  typedef unsigned __int64 bit35;
  typedef unsigned __int64 bit36;
  typedef unsigned __int64 bit37;
  typedef unsigned __int64 bit38;
  typedef unsigned __int64 bit39;
  typedef unsigned __int64 bit40;
  typedef unsigned __int64 bit41;
  typedef unsigned __int64 bit42;
  typedef unsigned __int64 bit43;
  typedef unsigned __int64 bit44;
  typedef unsigned __int64 bit45;
  typedef unsigned __int64 bit46;
  typedef unsigned __int64 bit47;
  typedef unsigned __int64 bit48;
  typedef unsigned __int64 bit49;
  typedef unsigned __int64 bit50;
  typedef unsigned __int64 bit51;
  typedef unsigned __int64 bit52;
  typedef unsigned __int64 bit53;
  typedef unsigned __int64 bit54;
  typedef unsigned __int64 bit55;
  typedef unsigned __int64 bit56;
  typedef unsigned __int64 bit57;
  typedef unsigned __int64 bit58;
  typedef unsigned __int64 bit59;
  typedef unsigned __int64 bit60;
  typedef unsigned __int64 bit61;
  typedef unsigned __int64 bit62;
  typedef unsigned __int64 bit63;
  typedef unsigned __int64 bit64;
  typedef sc_biguint<65>   bit65;
  typedef sc_biguint<66>   bit66;
  typedef sc_biguint<67>   bit67;
  typedef sc_biguint<68>   bit68;
  typedef sc_biguint<69>   bit69;
  typedef sc_biguint<70>   bit70;
  typedef sc_biguint<71>   bit71;
  typedef sc_biguint<72>   bit72;
  typedef sc_biguint<73>   bit73;
  typedef sc_biguint<74>   bit74;
  typedef sc_biguint<75>   bit75;
  typedef sc_biguint<76>   bit76;
  typedef sc_biguint<77>   bit77;
  typedef sc_biguint<78>   bit78;
  typedef sc_biguint<79>   bit79;
  typedef sc_biguint<80>   bit80;
  typedef sc_biguint<81>   bit81;
  typedef sc_biguint<82>   bit82;
  typedef sc_biguint<83>   bit83;
  typedef sc_biguint<84>   bit84;
  typedef sc_biguint<85>   bit85;
  typedef sc_biguint<86>   bit86;
  typedef sc_biguint<87>   bit87;
  typedef sc_biguint<88>   bit88;
  typedef sc_biguint<89>   bit89;
  typedef sc_biguint<90>   bit90;
  typedef sc_biguint<91>   bit91;
  typedef sc_biguint<92>   bit92;
  typedef sc_biguint<93>   bit93;
  typedef sc_biguint<94>   bit94;
  typedef sc_biguint<95>   bit95;
  typedef sc_biguint<96>   bit96;
  typedef sc_biguint<97>   bit97;
  typedef sc_biguint<98>   bit98;
  typedef sc_biguint<99>   bit99;
  typedef sc_biguint<100>  bit100;
  typedef sc_biguint<101>  bit101;
  typedef sc_biguint<102>  bit102;
  typedef sc_biguint<103>  bit103;
  typedef sc_biguint<104>  bit104;
  typedef sc_biguint<105>  bit105;
  typedef sc_biguint<106>  bit106;
  typedef sc_biguint<107>  bit107;
  typedef sc_biguint<108>  bit108;
  typedef sc_biguint<109>  bit109;
  typedef sc_biguint<110>  bit110;
  typedef sc_biguint<111>  bit111;
  typedef sc_biguint<112>  bit112;
  typedef sc_biguint<113>  bit113;
  typedef sc_biguint<114>  bit114;
  typedef sc_biguint<115>  bit115;
  typedef sc_biguint<116>  bit116;
  typedef sc_biguint<117>  bit117;
  typedef sc_biguint<118>  bit118;
  typedef sc_biguint<119>  bit119;
  typedef sc_biguint<120>  bit120;
  typedef sc_biguint<121>  bit121;
  typedef sc_biguint<122>  bit122;
  typedef sc_biguint<123>  bit123;
  typedef sc_biguint<124>  bit124;
  typedef sc_biguint<125>  bit125;
  typedef sc_biguint<126>  bit126;
  typedef sc_biguint<127>  bit127;
  typedef sc_biguint<128>  bit128;

  /* 信号向け以外の変数に使用すること */
  typedef __int8           int8;
  typedef __int16          int16;
  typedef __int32          int32;
  typedef __int64          int64;
  typedef sc_bigint<128>   int128;
  typedef unsigned __int8  uint8;
  typedef unsigned __int16 uint16;
  typedef unsigned __int32 uint32;
  typedef unsigned __int64 uint64;
  typedef sc_biguint<128>  uint128;

#endif

}

#endif /* FJ_DATATYPE_h */

