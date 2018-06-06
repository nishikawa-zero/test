#include "AddressGenerator.h"

//======================================================================
// コンストラクタ
//======================================================================
AddressGenerator::AddressGenerator(unsigned int d,
                                   unsigned long sa,
                                     signed long gs,
                                   unsigned int hs,
                                   unsigned int vs,
                                   unsigned int bhs,
                                   unsigned int bvs,
                                   unsigned int hm,
                                   unsigned int baxisize,
                                   unsigned int baxilength,
                                   bool left):
	dimension(d),
	start_address(sa),
	global_size(gs),
	hsize(hs),
	vsize(vs),
	base_hsize(bhs),
	base_vsize(bvs),
	hmargin(hm),
	base_axi_size(baxisize),
	base_axi_length(baxilength),
	align_left(left),
	sram_mode(false),
	sram_saddr(0),
	sram_size(0),
	num_of_tanzaku(0)
{
	if (align_left == false) {
		align_mode = ALIGN_4K;
	} else {
		align_mode = ALIGN_LEFT;
	}
	// hsize,vsizeが0の場合は1に補正
	hsize = (hsize == 0) ? 1 : hsize;
	vsize = (vsize == 0) ? 1 : vsize;

	switch (dimension) {
	case 1:
		calc_address_1d(start_address, hsize);
		vREflg.pop_back();		vREflg.push_back(true);
		vRflg.pop_back();		vRflg.push_back(true);
		vBflg.pop_back();		vBflg.push_back(true);
		vFEflg.pop_back();		vFEflg.push_back(true);
		break;
	case 2:
		calc_address_2d(start_address, hsize, vsize);
		vRflg.pop_back();		vRflg.push_back(true);
		vBflg.pop_back();		vBflg.push_back(true);
		vFEflg.pop_back();		vFEflg.push_back(true);
		break;
	case 3:
		calc_address_3d();
		break;
	case 4:
		calc_address_4d();
		break;
	default:
		std::cout << "dimension [" << dimension << "] is not supported, abort." << std::endl;
		//exit(-1);
		break;
	}
}
	

AddressGenerator::AddressGenerator(unsigned int d,
                                   unsigned long sa,
                                     signed long gs,
                                   unsigned int  hs,
                                   unsigned int  vs,
                                   unsigned int  bhs,
                                   unsigned int  bvs,
                                   unsigned int  hm,
                                   unsigned int  baxisize,
                                   unsigned int  baxilength,
                                   bool          left,
								   unsigned int  align,
								   bool          srmd,
								   unsigned long sra,
								   unsigned long srs):
	dimension(d),
	start_address(sa),
	global_size(gs),
	hsize(hs),
	vsize(vs),
	base_hsize(bhs),
	base_vsize(bvs),
	hmargin(hm),
	base_axi_size(baxisize),
	base_axi_length(baxilength),
	align_left(left),
	align_mode(align),
	sram_mode(srmd),
	sram_saddr(sra),
	sram_size(srs),
	num_of_tanzaku(0) {

	// hsize,vsizeが0の場合は1に補正
	hsize = (hsize == 0) ? 1 : hsize;
	vsize = (vsize == 0) ? 1 : vsize;

	switch (dimension) {
	case 1:
		calc_address_1d(start_address, hsize);
		vREflg.pop_back();		vREflg.push_back(true);
		vRflg.pop_back();		vRflg.push_back(true);
		vBflg.pop_back();		vBflg.push_back(true);
		vFEflg.pop_back();		vFEflg.push_back(true);
		break;
	case 2:
		calc_address_2d(start_address, hsize, vsize);
		vRflg.pop_back();		vRflg.push_back(true);
		vBflg.pop_back();		vBflg.push_back(true);
		vFEflg.pop_back();		vFEflg.push_back(true);
		break;
	case 3:
		calc_address_3d();
		break;
	case 4:
		calc_address_4d();
		break;
	default:
		std::cout << "dimension [" << dimension << "] is not supported, abort." << std::endl;
		//exit(-1);
		break;
	}
}

//======================================================================
// デストラクタ
//======================================================================
AddressGenerator::~AddressGenerator(void) {
}

//======================================================================
// public関数
//======================================================================
//----------------------------------------------------------------------
// int getParameterChannel
//   count値を引数として、AxADDR、AxLENおよび座標データを返す
//----------------------------------------------------------------------
int
AddressGenerator::getParameterChannel(unsigned long *ADDR,
                                      unsigned int *LEN,
                                      unsigned int *location,
                                      unsigned int count)
{
	unsigned int posX = 0;
	unsigned int posY = 0;
	unsigned long tmp_addr = 0;
	
	if ((count >= vADDR.size()) || (count >= vLEN.size())) {
		return (-1);
	} else {
		tmp_addr = vADDR[count];
		getLocate(tmp_addr,&posX,&posY, 8);
		*location = (posX << 16) | posY;
		if (sram_mode == true) {
			if (tmp_addr >= (sram_saddr + sram_size)) {
				tmp_addr = ((tmp_addr - sram_saddr ) % sram_size) + sram_saddr;
			}
		}
		*ADDR = tmp_addr;
		*LEN = vLEN[count];
	}
	return (0);
}
//----------------------------------------------------------------------
// int getParameterChannel
//   count値を引数として、AxADDR、AxLEN、座標データ、
//   ライン右端/メッシュ右下/画面右下フラグを返す
//----------------------------------------------------------------------
int
AddressGenerator::getParameterChannel(unsigned long *ADDR,
                                      unsigned int *LEN,
                                      unsigned int *location,
                                      unsigned int *leflg,
                                      unsigned int *reflg,
                                      unsigned int *feflg,
                                      unsigned int count)
{
	int rcode = getParameterChannel(ADDR,LEN,location,count);

	if (rcode != 0) {
		return (-1);
	} else {
		*leflg = vLEflg[count];
		*reflg = vREflg[count];
		*feflg = vFEflg[count];
	}
	return (0);
}

//----------------------------------------------------------------------
// int getParameterChannel
//   count値を引数として、AxADDR、AxLEN、座標データ、
//   ライン右端/メッシュ右下/画面右下フラグおよびマージン量を返す
//----------------------------------------------------------------------
int
AddressGenerator::getParameterChannel(unsigned long *ADDR,
                                      unsigned int *LEN,
                                      unsigned int *location,
                                      unsigned int *leflg,
                                      unsigned int *reflg,
                                      unsigned int *feflg,
									  unsigned int *hm,
                                      unsigned int count)
{
	int rcode = getParameterChannel(ADDR,LEN,location,leflg,reflg,feflg,count);
	if (rcode != 0) {
		*hm = 0;
	} else {
		*hm = vhmargin[count];
	}
	return (rcode);
}

//----------------------------------------------------------------------
// int getParameterChannel
//   count値を引数として、AxADDR、AxLEN、座標データ、
//   ライン右端/メッシュ右下/画面右下フラグ、右端メッシュ/下端メッシュフラグ
//   およびマージン量を返す
//----------------------------------------------------------------------
int
	AddressGenerator::getParameterChannel(
	unsigned long *ADDR,
	unsigned int *LEN,
	unsigned int *location,
	unsigned int *leflg,
	unsigned int *reflg,
	unsigned int *feflg,
	unsigned int *rflg,
	unsigned int *bflg,
	unsigned int *hmargin,
	unsigned int count)
{
	int rcode = getParameterChannel(ADDR,LEN,location,leflg,reflg,feflg,hmargin,count);

	if (rcode != 0) {
		return (-1);
	} else {
		*rflg = vRflg[count];
		*bflg = vBflg[count];
	}
	return (0);


}

//----------------------------------------------------------------------
// void disp_address()
//   count値を引数として、AxADDR、AxLEN、ライン右端/メッシュ右下/画面右下フラグを画面に出力する
//----------------------------------------------------------------------
void
AddressGenerator::disp_address(unsigned int count) {
	if (count >= vADDR.size()) {
		printf("count %3d is overflow!!\n", count);
	} else {
		printf("[%3d][0x%08lx][%2d][%d][%d][%d]\n", count, vADDR[count],vLEN[count],vLEflg[count],vREflg[count],vFEflg[count]);
	}
}

//----------------------------------------------------------------------
// unsigned int size()
//   総リクエスト回数を返す
//----------------------------------------------------------------------
unsigned int
AddressGenerator::size(void) {
  return vADDR.size();
}

//----------------------------------------------------------------------
// bool isLE()
//   count値の転送がライン右端ならtrueを返す
//----------------------------------------------------------------------
bool
AddressGenerator::isLE(unsigned int x) {
	if (vLEflg.size() > x) {
		return((vLEflg[x] == 1) ? true : false);
	} else {
#ifdef ADDRESS_GENERATOR_DEBUG
		std::cout << "AddressGenerator ERROR: count " << std::dec << x << " is out of range." << std::endl;
#endif
		return(false);
	}
}

//----------------------------------------------------------------------
// bool isRE()
//   count値の転送がメッシュ右下ならtrueを返す
//----------------------------------------------------------------------
bool
AddressGenerator::isRE(unsigned int x) {
	if (vREflg.size() > x) {
		return((vREflg[x] == 1) ? true : false);
	} else {
#ifdef ADDRESS_GENERATOR_DEBUG
		std::cout << "AddressGenerator ERROR: count " << std::dec << x << " is out of range." << std::endl;
#endif
		return(false);
	}
}

//----------------------------------------------------------------------
// bool isFE()
//   count値の転送が画面右下(=最終転送)ならtrueを返す
//----------------------------------------------------------------------
bool
AddressGenerator::isFE(unsigned int x) {
	if (vFEflg.size() > x) {
		return(vFEflg[x]);
	} else {
#ifdef ADDRESS_GENERATOR_DEBUG
		std::cout << "AddressGenerator ERROR: count " << std::dec << x << " is out of range." << std::endl;
#endif
		return(false);
	}
}

//----------------------------------------------------------------------
// bool isRIGHT()
//   count値の転送が右端メッシュの転送ならtrueを返す
//----------------------------------------------------------------------
bool
AddressGenerator::isRIGHT(unsigned int x) {
	if (vRflg.size() > x) {
		return(vRflg[x]);
	} else {
#ifdef ADDRESS_GENERATOR_DEBUG
		std::cout << "AddressGenerator ERROR: count " << std::dec << x << " is out of range." << std::endl;
#endif
		return(false);
	}
}
//----------------------------------------------------------------------
// bool isBOTTOM()
//   count値の転送が最下段の転送ならtrueを返す
//----------------------------------------------------------------------
bool
AddressGenerator::isBOTTOM(unsigned int x) {
	if (vBflg.size() > x) {
		return(vBflg[x]);
	} else {
#ifdef ADDRESS_GENERATOR_DEBUG
		std::cout << "AddressGenerator ERROR: count " << std::dec << x << " is out of range." << std::endl;
#endif
		return(false);
	}
}

//----------------------------------------------------------------------
// unsigned int getLocation_bottom()
//   count値の転送における右端側座標を返す
//----------------------------------------------------------------------
unsigned int
AddressGenerator::getLocation_bottom(unsigned int count)
{
	unsigned int posX = 0;
	unsigned int posY = 0;
	unsigned int location = 0;

	if ((count >= vADDR.size()) || (count >= vLEN.size())) {
		return(0);
	} else {
		getLocate(vADDR[count],&posX,&posY, 8);
		posX += ((vLEN[count]+1)*(2<<(base_axi_size-1)))-1;
		location = (posX << 16) | posY;
		return(location);
	}
}

//----------------------------------------------------------------------
// unsigned int getNumberOfTanzaku()
//   短冊の数を返す
//----------------------------------------------------------------------
unsigned int
AddressGenerator::getNumberOfTanzaku(void)
{
	return(num_of_tanzaku);
}

//----------------------------------------------------------------------
// int getCountFromTanzaku()
//   指定短冊の最初の転送となるcount値を返す
//----------------------------------------------------------------------
int
AddressGenerator::getCountFromTanzaku(unsigned int* count, unsigned int NumOfTanzaku)
{
	if (NumOfTanzaku > num_of_tanzaku) {
		return -1;
	}
	*count = vRCT[NumOfTanzaku];
	return 0;
}

//======================================================================
// private関数
//======================================================================
//-------------------------------------------------------------
// int calc_address_1d()
//   1次元アドレッシングの計算
//-------------------------------------------------------------
int
AddressGenerator::calc_address_1d(unsigned long line_start_address,
                                  unsigned int datasize)
{
	return(calc_address_1d(line_start_address, datasize, datasize,TAN_LEFT,0));
}

int
AddressGenerator::calc_address_1d(unsigned long line_start_address,
                                  unsigned int datasize,
								  unsigned int datasize_original,
								  unsigned int tanzaku_mode,
								  unsigned int norisiroL)
{
	unsigned int offset = 0;
	unsigned long remain;
	unsigned int arlen_tmp, arlen, arlen_tmp4k, remain_arlen;
	unsigned long tmp_next_addr;
	unsigned int  count_of_req = 0;
	unsigned int  tanzaku_remain_left = 0;
	unsigned int  tanzaku_remain_right = 0;
	bool arlen_4k_flg;

#ifdef ADDRESS_GENERATOR_DEBUG
  std::cout << "line start" << std::endl;
#endif

	arlen_tmp4k = 0;
	arlen_4k_flg = false;
	remain_arlen = 0;

	unsigned long tmp_line_start_address = line_start_address;
	correct_address_size(&line_start_address, &datasize);

	switch(tanzaku_mode) {
	case TAN_LEFT:
		tanzaku_remain_left  = (tmp_line_start_address - line_start_address) + norisiroL;
		tanzaku_remain_right = datasize - datasize_original - tanzaku_remain_left;
		break;

	case TAN_MIDDLE:
		tanzaku_remain_left  = (tmp_line_start_address - line_start_address) + norisiroL;
		tanzaku_remain_right = datasize - datasize_original - tanzaku_remain_left;
		break;

	case TAN_RIGHT:
		tanzaku_remain_left  = (tmp_line_start_address - line_start_address) + norisiroL;
		tanzaku_remain_right = datasize - datasize_original - tanzaku_remain_left;
		break;
	}

	while (offset < datasize) {
		vADDR.push_back(line_start_address + offset);
		remain = datasize - offset;
		arlen_tmp = 0;
		switch (align_mode) {
		case ALIGN_LEFT:
			arlen_tmp = base_axi_length - (((line_start_address + offset) >> base_axi_size) % (base_axi_length + 1) );
			break;

		case ALIGN_4K:
			if (arlen_4k_flg == true) {
				arlen_tmp = remain_arlen;
				arlen_4k_flg = false;
			} else {
				arlen_tmp = base_axi_length;
			}
			tmp_next_addr = line_start_address + offset;
      
			if (4096 - (tmp_next_addr % 4096) < (1 << base_axi_size) * (base_axi_length + 1)) {
				arlen_tmp4k = (4096 - (tmp_next_addr % 4096)) % ((1 << base_axi_size) * (base_axi_length + 1));
				arlen_tmp4k = (arlen_tmp4k >> (base_axi_size)) - 1;
				remain_arlen = arlen_tmp - arlen_tmp4k - 1;
				arlen_tmp = arlen_tmp4k;
				arlen_4k_flg = true;
			} else {
				arlen_tmp4k = 0;
				arlen_4k_flg = false;
			}
			break;

		case ALIGN_2K:
			arlen_tmp = base_axi_length;
			tmp_next_addr = line_start_address + offset;
      
			if (2048 - (tmp_next_addr % 2048) < (1 << base_axi_size) * (base_axi_length + 1)) {
				arlen_tmp4k = (2048 - (tmp_next_addr % 2048)) % ((1 << base_axi_size) * (base_axi_length + 1));
				arlen_tmp4k = (arlen_tmp4k >> (base_axi_size)) - 1;
				remain_arlen = arlen_tmp - arlen_tmp4k - 1;
				arlen_tmp = arlen_tmp4k;
			} else {
				arlen_tmp4k = 0;
			}
			break;

		default:
			break;
		}

		arlen = ((remain < ((arlen_tmp + 1) * (1 << base_axi_size))) ? ((remain >> base_axi_size) - 1) : arlen_tmp);

#ifdef ADDRESS_GENERATOR_DEBUG
		std::cout << "araddr = " << std::hex << line_start_address+offset << " arlen = " << std::dec << arlen << std::endl;
#endif
		
		vLEN.push_back(arlen);
		vLEflg.push_back(false);
		vREflg.push_back(false);
		vFEflg.push_back(false);
		vRflg.push_back(false);
		vBflg.push_back(false);

		unsigned int tmp_size = ((arlen+1) * (1 << base_axi_size));

		if (tanzaku_remain_left > 0) {
			if ( tmp_size < tanzaku_remain_left) {
				vhmargin.push_back(tmp_size);
				tanzaku_remain_left -= tmp_size;
			} else {
				vhmargin.push_back(tanzaku_remain_left);
				tanzaku_remain_left = 0;
			}
		} else {
			vhmargin.push_back(0);
		}

		offset += tmp_size;
	}

	// ライン右端なのでフラグをセット
	vLEflg.pop_back();
	vLEflg.push_back(true);

	// 右側のhmargin量を計算
	unsigned int tmp_size = ((vLEN[vLEN.size()-1]+1) * (1 << base_axi_size));
	unsigned int tmp_count = vhmargin.size()-1;
	while ((tmp_size < tanzaku_remain_right)&&(tmp_count >= 0)) {
		vhmargin[tmp_count] = tmp_size;
		tanzaku_remain_right -= tmp_size;
		tmp_count --;
		tmp_size = ((vLEN[tmp_count]+1) * (1 << base_axi_size));
	}
	if (tanzaku_remain_right > 0) {
		vhmargin[tmp_count] += tanzaku_remain_right;
	}

#ifdef ADDRESS_GENERATOR_DEBUG
	std::cout << "line end" << std::endl;
#endif

	return 0;
}

//-------------------------------------------------------------
// int calc_address_2d()
//   2次元アドレッシングの計算
//-------------------------------------------------------------
int
AddressGenerator::calc_address_2d(unsigned long saddr,
                                  unsigned int hsz,
                                  unsigned int vsz) {
	unsigned long line_start_address = saddr;
  
#ifdef ADDRESS_GENERATOR_DEBUG
	std::cout << "2D start" << std::endl;
#endif

	for (unsigned int i = 0; i < vsz; ++i) {
		calc_address_1d(line_start_address, hsz);
		line_start_address += global_size;
	}
	vREflg.pop_back();
	vREflg.push_back(true);

#ifdef ADDRESS_GENERATOR_DEBUG
	std::cout << "2D end" << std::endl;
#endif

	return 0;
}

int
AddressGenerator::calc_address_2d(unsigned long saddr,
                                  unsigned int hsz,
                                  unsigned int vsz,
								  unsigned int original_datasize,
								  unsigned int tanzaku_mode,
								  unsigned int norisiroL) {
	unsigned long line_start_address = saddr;
  
#ifdef ADDRESS_GENERATOR_DEBUG
	std::cout << "2D start" << std::endl;
#endif

	for (unsigned int i = 0; i < vsz; ++i) {
		calc_address_1d(line_start_address, hsz, original_datasize, tanzaku_mode, norisiroL);
		line_start_address += global_size;
	}
	vREflg.pop_back();
	vREflg.push_back(true);

#ifdef ADDRESS_GENERATOR_DEBUG
	std::cout << "2D end" << std::endl;
#endif

	return 0;
}

//----------------------------------------------------------------------
// int calc_address_3d()
//   4次元アドレッシング時のアドレス計算
//----------------------------------------------------------------------
int
AddressGenerator::calc_address_3d(void) {
	unsigned long tanzaku_start_address = start_address;  
	unsigned int hsize_remain = hsize;
	unsigned int tanzaku_hsize;
	unsigned int tanzaku_count = 0;
	unsigned int max_tanzaku_count;
	unsigned int tan_mode;
	unsigned int original_tanhsize;
	unsigned int norisiroL;
	vRCT.push_back(0);

	if (base_hsize == 0) {
		std::cout << "ERROR: base_hsize is 0" << std::endl;
		return -1;
	}
	max_tanzaku_count = (hsize + (base_hsize - 1)) / base_hsize;
	while (hsize_remain > 0) {
		tanzaku_start_address = start_address + base_hsize * tanzaku_count;
		tanzaku_hsize = (hsize_remain > base_hsize) ? base_hsize : hsize_remain;
		hsize_remain -= tanzaku_hsize;
		original_tanhsize = tanzaku_hsize;
		if (tanzaku_count == 0) {	// left tanzaku
			tan_mode = TAN_LEFT;
			tanzaku_hsize += hmargin;
			norisiroL = 0;
		} else if (tanzaku_count == max_tanzaku_count - 1) {	// right tanzaku
			tan_mode = TAN_RIGHT;
			tanzaku_hsize += hmargin;
			tanzaku_start_address -= hmargin;
			norisiroL = hmargin;
		} else {	// middle tanzaku
			tan_mode = TAN_MIDDLE;
			tanzaku_hsize += hmargin * 2;
			tanzaku_start_address -= hmargin;
			norisiroL = hmargin;
		}
		calc_address_2d(tanzaku_start_address, tanzaku_hsize, vsize, original_tanhsize, tan_mode, norisiroL);
		++tanzaku_count;
		vRCT.push_back(vLEflg.size());
		vBflg.pop_back();	vBflg.push_back(true);
		if (tan_mode == TAN_RIGHT) {
			vRflg.pop_back(); vRflg.push_back(true);
		}
	}
	vFEflg.pop_back();	vFEflg.push_back(true);
	num_of_tanzaku = max_tanzaku_count;

	return 0;
}

//----------------------------------------------------------------------
// int calc_address_4d()
//   4次元アドレッシング時のアドレス計算
//----------------------------------------------------------------------
int
AddressGenerator::calc_address_4d(void) {
	unsigned long rect_start_address;
  
	unsigned int hsize_remain = hsize;
	unsigned int vsize_remain = vsize;
	unsigned int rect_hsize, rect_vsize;
	unsigned int rect_hcount = 0;
	unsigned int rect_vcount = 0;
	unsigned int max_rect_hcount = 0;
	unsigned int max_rect_vcount = 0;

	vRCT.push_back(0);

	if (base_hsize == 0) {
		std::cout << "ERROR: base_hsize is 0" << std::endl;
		return -1;
	}
		if (base_vsize == 0) {
		std::cout << "ERROR: base_vsize is 0" << std::endl;
		return -1;
	}
	max_rect_hcount = (hsize + (base_hsize - 1)) / base_hsize;
	max_rect_vcount = (vsize + (base_vsize - 1)) / base_vsize;

	while (vsize_remain > 0) {
		rect_start_address = start_address + (rect_vcount * global_size * base_vsize);
		rect_vsize = (vsize_remain > base_vsize) ? base_vsize : vsize_remain;
		vsize_remain -= rect_vsize;
		hsize_remain = hsize;
		while (hsize_remain > 0) {
			rect_hsize = (hsize_remain > base_hsize) ? base_hsize : hsize_remain;
			hsize_remain -= rect_hsize;	
			calc_address_2d(rect_start_address, rect_hsize, rect_vsize);
			rect_start_address += base_hsize;
			++rect_hcount;
			vRCT.push_back(vLEflg.size());
			if (rect_hcount == max_rect_hcount) {
				vRflg.pop_back(); vRflg.push_back(true);
			}
			if (rect_vcount == max_rect_vcount - 1) {
				vBflg.pop_back(); vBflg.push_back(true);
			}
		}
		++rect_vcount;
		rect_hcount = 0;
	}
	vFEflg.pop_back();
	vFEflg.push_back(true);
	num_of_tanzaku = max_rect_hcount * max_rect_vcount;

	return 0;
}
//-------------------------------------------------------------
// void correct_address_size()
//   アドレスと転送量をバス幅に合わせて補正する
//-------------------------------------------------------------
void
AddressGenerator::correct_address_size(unsigned long *a, unsigned int *s)
{
#ifdef ADDRESS_GENERATOR_DEBUG
	std::cout << "Correct Address start: *a= 0x" << std::hex << *a << " *s = 0x" << *s << std::endl;
#endif
	*s += (*a % (1<<base_axi_size));
	*a = (*a >> base_axi_size) << base_axi_size;	// AXI bus_size align
	*s = ((*s + (1<<base_axi_size)-1)/(1<<base_axi_size))*(1<<base_axi_size);	// roundup AXI bus_size
#ifdef ADDRESS_GENERATOR_DEBUG
	std::cout << "Correct Address end  : *a= 0x" << std::hex << *a << " *s = 0x" << *s << std::endl;
#endif
}
//----------------------------------------------------------------------
// int getLocate()
//   アドレスおよび1ピクセルのbit深度を引数にして、XY座標を返す
//----------------------------------------------------------------------
int
AddressGenerator::getLocate(
unsigned long address,
unsigned int *posX,
unsigned int *posY,
unsigned int bdepth)
{
	int tmp_X,tmp_Y;
	unsigned long tmp_start_address = start_address;

	if (global_size == 0) {
		tmp_Y = 0;
	} else if (global_size < 0) {
		tmp_start_address += global_size*(vsize-1);
		tmp_Y = (address - tmp_start_address) / (-global_size);
	} else {
		tmp_Y = (address - tmp_start_address) / global_size;
	}
	if ((tmp_Y < 0)||(tmp_Y > vsize)) {
		return -1;
	}
	*posY = (unsigned int)tmp_Y;
	if (global_size == 0) {
		tmp_X = (address - tmp_start_address)*8/bdepth;
	} else if (global_size < 0) {
		tmp_X = ((address - tmp_start_address) % (-global_size))*8/bdepth;
	} else {
		tmp_X = ((address - tmp_start_address) % global_size)*8/bdepth;
	}
	if ((tmp_X < 0)||(tmp_X > hsize)) {
		return -1;
	}
	*posX = (unsigned int)tmp_X;

	return 0;
}

//----------------------------------------------------------------------
// int getAddress()
//   XY座標および1ピクセルのbit深度を引数にして、アドレスを返す
//----------------------------------------------------------------------
int
AddressGenerator::getAddress(
unsigned long *address,
unsigned int posX,
unsigned int posY,
unsigned int bdepth)
{
	posX = posX * bdepth / 8;

	if ((posY < 0)||(posY > vsize)) {
		return -1;
	}
	if ((posX < 0)||(posX > hsize)) {
		return -1;
	}
	if (global_size >= 0) {
		*address = start_address + posX + (global_size)*posY;
	} else {
		*address = start_address + posX + (global_size)*(vsize - posY);
	}

	return 0;
}

// EOF
