/*
* ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU LSI TECHNOLOGY LTD. 2009
* LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU LSI TECHNOLOGY LTD.
*/
#ifndef __EndianSwap_h
#define __EndianSwap_h

template < class DATA_TYPE = unsigned long long, class STROBE_TYPE = unsigned char >
class EndianSwap
{

public:
	EndianSwap(void) {
#if 0 //@AKINIWA(100423)
		_data_width = sizeof(DATA_TYPE);
#else
		_data_width = set_width(_data_type);
#endif
		_strobe_width = sizeof(STROBE_TYPE) * 8;
	}

	~EndianSwap(void) {
	}

#if 0 //@AKINIWA(100426)
	DATA_TYPE swapData(DATA_TYPE data) {
		DATA_TYPE mask((DATA_TYPE)0xFF);
		DATA_TYPE result(0);
		for (int i = 0; i < _data_width; i++) {
			DATA_TYPE tmp_data;
			tmp_data = (data >> (i * 8)) & mask;
			result |= tmp_data << ((_data_width - i - 1) * 8);
		}
		return result;
	}
#else
	unsigned int swapData(unsigned int data) {
		unsigned int mask(0xFF);
		unsigned int result(0);
		for (unsigned int i = 0; i < _data_width; i++) { // modify by katomasa 20110615
			unsigned int tmp_data;
			tmp_data = (data >> (i * 8)) & mask;
			result |= tmp_data << ((_data_width - i - 1) * 8);
		}
		return result;
	}
	unsigned long long swapData(unsigned long long data) {
		unsigned int        mask(0xFF);
		unsigned long long  result(0);
		for (unsigned int i = 1; i < _data_width; i++) { // modify by katomasa 20110615
			unsigned long long tmp_data;
			tmp_data = (data >> (i * 8)) & mask;
			result |= tmp_data << ((_data_width - i - 1) * 8);
		}
		return result;
	}
	sc_biguint<128> swapData(sc_biguint<128> data) {
		unsigned int     high=7;
		unsigned int     low =0;
		unsigned int     mask(0xFF);
		sc_biguint<128>  result;
		for (unsigned int i = 0; i < _data_width; i++) { // modify by katomasa 20110615
			result.range(high,low) = data.range(high,low) & mask;
			high = high + 8;
			low  = low  + 8;
		}
		return result;
	}
#endif

	DATA_TYPE swapData(DATA_TYPE data, unsigned int size_byte) {
		DATA_TYPE result(0);
		unsigned int number_of_swap;

		if (_data_width <= size_byte) {
			result = swapData(data);
		} else {
			DATA_TYPE mask(0);
			number_of_swap = _data_width / size_byte;
			for (unsigned int i = 0; i < size_byte; i++) { // modify by katomasa 20110615
				mask |= (DATA_TYPE)0xFF << (i * 8);
			}
			for (unsigned int i = 0; i < number_of_swap; i++) { // modify by katomasa 20110615
				DATA_TYPE tmp_data;
				tmp_data = (data >> (i * 8 * size_byte)) & mask;
				result |= tmp_data << ((number_of_swap - i - 1) * (8 * size_byte));
			}
		}
		return result;
	}

	STROBE_TYPE swapStrobe(STROBE_TYPE strobe) {
#if 0 //@AKINIWA(100426)
		DATA_TYPE mask(0x1);
#else
		unsigned int mask(0x1);
#endif
		STROBE_TYPE result(0);

		for (int i = 0; i < _strobe_width; i++) {
			STROBE_TYPE tmp_strobe;
			tmp_strobe = (strobe >> i) & mask;
			result |= tmp_strobe << (_strobe_width - i - 1);
		}

		return result;
	}

	STROBE_TYPE swapStrobe(STROBE_TYPE strobe, unsigned int size_bit) {
		STROBE_TYPE result(0);
		unsigned int number_of_swap;

		if (_strobe_width <= size_bit) {
			result = swapStrobe(strobe);
		} else {
			STROBE_TYPE mask(0);
			number_of_swap = _strobe_width / size_bit;
			for (unsigned int i = 0; i < size_bit; i++) { // modify by katomasa 20110615
				mask |= (STROBE_TYPE)0x1 << i;
			}
			for (unsigned int i = 0; i < number_of_swap; i++) { // modify by katomasa 20110615
				STROBE_TYPE tmp_strobe;
				tmp_strobe = (strobe >> (i * size_bit)) & mask;
				result |= tmp_strobe << ((number_of_swap - i - 1) * size_bit);
			}
		}
		return result;
	}

#if 1 //@AKINIWA(100426)
	unsigned int set_width(unsigned int type){
		return(sizeof(type));
	}
	unsigned int set_width(unsigned long long type){
		return(sizeof(type));
	}
	unsigned int set_width(sc_biguint<128> type){
		return(128 / 8);
	}

#endif

private:
	DATA_TYPE _data_type;
	//  DATA_TYPE _data_width;
	unsigned int _data_width;
	STROBE_TYPE _strobe_width;

};

template class EndianSwap<unsigned int, unsigned char>;
template class EndianSwap<unsigned long long, unsigned char>;
template class EndianSwap<sc_biguint<128> , unsigned char>;

#endif /* __EndianSwap_h */
