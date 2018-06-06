#include <iostream>
#include <vector>
#include <stdio.h>

#ifndef ADDRESS_GENERATOR_H
#define ADDRESS_GENERATOR_H

typedef enum {TAN_LEFT, TAN_MIDDLE, TAN_RIGHT} tanzaku_mode_t; 
typedef enum {ALIGN_LEFT, ALIGN_4K,ALIGN_2K} align_mode_t;

class	AddressGenerator {			
public:
	AddressGenerator(unsigned int d,
                   unsigned long sa,
                     signed long gs,
                   unsigned int hs,
                   unsigned int vs,
                   unsigned int bhs,
                   unsigned int bvs,
                   unsigned int hm,
                   unsigned int baxisize,
                   unsigned int baxilength,
                   bool left);
	AddressGenerator(unsigned int d,
                   unsigned long sa,
                     signed long gs,
                   unsigned int hs,
                   unsigned int vs,
                   unsigned int bhs,
                   unsigned int bvs,
                   unsigned int hm,
                   unsigned int baxisize,
                   unsigned int baxilength,
                   bool left,
				   unsigned int align,
				   bool srmd,
				   unsigned long sra,
				   unsigned long srs);
  ~AddressGenerator(void);

	int getParameterChannel(unsigned long *ADDR,
                          unsigned int *LEN,
                          unsigned int *location,
                          unsigned int count);
	int getParameterChannel(unsigned long *ADDR,
                          unsigned int *LEN,
                          unsigned int *location,
                          unsigned int *leflg,
                          unsigned int *reflg,
                          unsigned int *feflg,
                          unsigned int count);
	int getParameterChannel(unsigned long *ADDR,
                          unsigned int *LEN,
                          unsigned int *location,
                          unsigned int *leflg,
                          unsigned int *reflg,
                          unsigned int *feflg,
						  unsigned int *hmargin,
                          unsigned int count);
	int getParameterChannel(unsigned long *ADDR,
                          unsigned int *LEN,
                          unsigned int *location,
                          unsigned int *leflg,
                          unsigned int *reflg,
                          unsigned int *feflg,
						  unsigned int *rflg,
						  unsigned int *bflg,
						  unsigned int *hmargin,
                          unsigned int count);

	void disp_address(unsigned int count);
	unsigned int getLocation_bottom(unsigned int count);
	unsigned int size(void);
	bool isLE(unsigned int count);
	bool isRE(unsigned int count);
	bool isFE(unsigned int count);
	bool isRIGHT(unsigned int count);
	bool isBOTTOM(unsigned int count);

	unsigned int getNumberOfTanzaku(void);
	int getCountFromTanzaku(unsigned int* count, unsigned int NumOfTanzaku);

private:
	int getLocate(unsigned long address, unsigned int *posX, unsigned int *posY, unsigned int bdepth);
	int getAddress(unsigned long *address, unsigned int posX,unsigned int posY, unsigned int bdepth);

	int calc_address_1d(unsigned long line_start_address,
                      unsigned int datasize);
	int calc_address_1d(unsigned long line_start_address,
                      unsigned int datasize,
					  unsigned int datasize_original,
					  unsigned int tanzaku_mode);
	int calc_address_1d(unsigned long line_start_address,
                      unsigned int datasize,
					  unsigned int datasize_original,
					  unsigned int tanzaku_mode,
					  unsigned int norisiroL);
	int calc_address_2d(unsigned long saddr,
                      unsigned int hsz,
                      unsigned int vsz);
	int calc_address_2d(unsigned long saddr,
                      unsigned int hsz,
                      unsigned int vsz,
					  unsigned int datasize_original,
					  unsigned int tanzaku_mode,
					  unsigned int norisiroL);
	int calc_address_3d(void);
	int calc_address_4d(void);
	void correct_address_size(unsigned long *, unsigned int *);

private:
	unsigned int   dimension;
	unsigned long  start_address;
	  signed long  global_size;
	unsigned int   hsize;
	unsigned int   vsize;
	unsigned int   base_hsize;
	unsigned int   base_vsize;
	unsigned int   hmargin;
	unsigned int   base_axi_size;
	unsigned int   base_axi_length;
	bool           align_left;
	unsigned int   align_mode;
	unsigned int   num_of_tanzaku;
	bool           sram_mode;
	unsigned long  sram_saddr;
	unsigned long  sram_size;

  std::vector<unsigned long> vADDR;
	std::vector<unsigned long> vLEN;
	std::vector<unsigned long> vlocation;
	std::vector<unsigned long> vhmargin;
	std::vector<unsigned int> vLEflg;	// Line  End flag
	std::vector<unsigned int> vREflg;	// Rect  End flag
	std::vector<unsigned int> vFEflg;	// Frame End flag
	std::vector<unsigned int> vRflg;	// Right Rectangle flag
	std::vector<unsigned int> vBflg;	// Bottom Rectangle flag
	std::vector<unsigned int> vNorisiroSize;	// Norisiro size(bytes)
	std::vector<unsigned int> vRCT;	// request count of every tanzaku
};
#endif
