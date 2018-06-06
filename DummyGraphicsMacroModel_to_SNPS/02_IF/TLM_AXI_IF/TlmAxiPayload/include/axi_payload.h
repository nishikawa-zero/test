/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU MICROELECTRONICS LTD. 2008,2009
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU MICROELECTRONICS LTD.
 *
 */
/**
 * @file axi_payload.h
 * @brief generic_payload extension class for AXI
 *
 * @date $Date: 2009/02/03 00:54:40 $
 * @version $Id: axi_payload.h,v 1.3 2009/02/03 00:54:40 shunsaku Exp $
 */

#ifndef AXI_PAYLOAD_H
#define AXI_PAYLOAD_H

#include <tlm.h>
#include <systemc.h>

template <class data_type = unsigned int>
class axi_payload : public tlm::tlm_extension<axi_payload<data_type> > {
public:
  axi_payload(void) :
    _AWID(0),
    _AWADDR(0),
    _AWLEN(0),
    _AWSIZE(0),
    _AWBURST(0),
    _AWLOCK(0),
    _AWCACHE(0),
    _AWPROT(0),

    _AWUSER(0),

    _WID(0),
    _WSTRB(0),
    _WLAST(0),

    _WDATA32(0),
    _WDATA64(0),
    _WDATA128(0),

    _BID(0),
    _BRESP(0),

    _ARID(0),
    _ARADDR(0),
    _ARLEN(0),
    _ARSIZE(0),
    _ARBURST(0),
    _ARLOCK(0),
    _ARCACHE(0),
    _ARPROT(0),

    _ARUSER(0),

    _RID(0),
    _RRESP(0),
    _RLAST(0),

    _RDATA32(0),
    _RDATA64(0),
    _RDATA128(0)
  {}

  ~axi_payload(void) {
  }

  // ToDo: delete virtual
  virtual tlm::tlm_extension_base* clone() const {
    axi_payload* axi = new axi_payload();

    axi->_AWID    = this->_AWID;
    axi->_AWADDR  = this->_AWADDR;
    axi->_AWLEN   = this->_AWLEN;
    axi->_AWSIZE  = this->_AWSIZE;
    axi->_AWBURST = this->_AWBURST;
    axi->_AWLOCK  = this->_AWLOCK;
    axi->_AWCACHE = this->_AWCACHE;
    axi->_AWPROT  = this->_AWPROT;

    axi->_AWUSER  = this->_AWUSER;

    axi->_WID     = this->_WID;
    axi->_WSTRB   = this->_WSTRB;
    axi->_WLAST   = this->_WLAST;

    axi->_WDATA32   = this->_WDATA32;
    axi->_WDATA64   = this->_WDATA64;
    axi->_WDATA128  = this->_WDATA128;

    axi->_BID     = this->_BID;
    axi->_BRESP   = this->_BRESP;

    axi->_ARID    = this->_ARID;
    axi->_ARADDR  = this->_ARADDR;
    axi->_ARLEN   = this->_ARLEN;
    axi->_ARSIZE  = this->_ARSIZE;
    axi->_ARBURST = this->_ARBURST;
    axi->_ARLOCK  = this->_ARLOCK;
    axi->_ARCACHE = this->_ARCACHE;
    axi->_ARPROT  = this->_ARPROT;

    axi->_ARUSER  = this->_ARUSER;

    axi->_RID     = this->_RID;
    axi->_RRESP   = this->_RRESP;
    axi->_RLAST   = this->_RLAST;

    axi->_RDATA32   = this->_RDATA32;
    axi->_RDATA64   = this->_RDATA64;
    axi->_RDATA128  = this->_RDATA128;

    return axi;
  }

  // ToDo: delete virtual
  virtual void copy_from(tlm::tlm_extension_base const &axi) {
    _AWID    = static_cast<axi_payload<data_type> const &>(axi)._AWID;
    _AWADDR  = static_cast<axi_payload<data_type> const &>(axi)._AWADDR;
    _AWLEN   = static_cast<axi_payload<data_type> const &>(axi)._AWLEN;
    _AWSIZE  = static_cast<axi_payload<data_type> const &>(axi)._AWSIZE;
    _AWBURST = static_cast<axi_payload<data_type> const &>(axi)._AWBURST;
    _AWLOCK  = static_cast<axi_payload<data_type> const &>(axi)._AWLOCK;
    _AWCACHE = static_cast<axi_payload<data_type> const &>(axi)._AWCACHE;
    _AWPROT  = static_cast<axi_payload<data_type> const &>(axi)._AWPROT;

    _AWUSER  = static_cast<axi_payload<data_type> const &>(axi)._AWUSER;

    _WID     = static_cast<axi_payload<data_type> const &>(axi)._WID;
    _WSTRB   = static_cast<axi_payload<data_type> const &>(axi)._WSTRB;
    _WLAST   = static_cast<axi_payload<data_type> const &>(axi)._WLAST;

    _WDATA32   = static_cast<axi_payload<unsigned int> const &>(axi)._WDATA32;
    _WDATA64   = static_cast<axi_payload<unsigned long long> const &>(axi)._WDATA64;
    _WDATA128  = static_cast<axi_payload<sc_biguint<128> > const &>(axi)._WDATA128;

    _BID     = static_cast<axi_payload<data_type> const &>(axi)._BID;
    _BRESP   = static_cast<axi_payload<data_type> const &>(axi)._BRESP;

    _ARID    = static_cast<axi_payload<data_type> const &>(axi)._ARID;
    _ARADDR  = static_cast<axi_payload<data_type> const &>(axi)._ARADDR;
    _ARLEN   = static_cast<axi_payload<data_type> const &>(axi)._ARLEN;
    _ARSIZE  = static_cast<axi_payload<data_type> const &>(axi)._ARSIZE;
    _ARBURST = static_cast<axi_payload<data_type> const &>(axi)._ARBURST;
    _ARLOCK  = static_cast<axi_payload<data_type> const &>(axi)._ARLOCK;
    _ARCACHE = static_cast<axi_payload<data_type> const &>(axi)._ARCACHE;
    _ARPROT  = static_cast<axi_payload<data_type> const &>(axi)._ARPROT;

    _ARUSER  = static_cast<axi_payload<data_type> const &>(axi)._ARUSER;

    _RID     = static_cast<axi_payload<data_type> const &>(axi)._RID;
    _RRESP   = static_cast<axi_payload<data_type> const &>(axi)._RRESP;
    _RLAST   = static_cast<axi_payload<data_type> const &>(axi)._RLAST;

    _RDATA32   = static_cast<axi_payload<unsigned int> const &>(axi)._RDATA32;
    _RDATA64   = static_cast<axi_payload<unsigned long long> const &>(axi)._RDATA64;
    _RDATA128  = static_cast<axi_payload<sc_biguint<128> > const &>(axi)._RDATA128;
  }

  /*
   * Setter
   */

  /* for AW channel  */
  void setAWID(unsigned int AWID)        { _AWID    = AWID;    }
  void setAWADDR(unsigned int  AWADDR)   { _AWADDR  = AWADDR;  }
  void setAWLEN(unsigned char AWLEN)     { _AWLEN   = AWLEN;   }
  void setAWSIZE(unsigned char AWSIZE)   { _AWSIZE  = AWSIZE;  }
  void setAWBURST(unsigned char AWBURST) { _AWBURST = AWBURST; }
  void setAWLOCK(unsigned char AWLOCK)   { _AWLOCK  = AWLOCK;  }
  void setAWCACHE(unsigned char AWCACHE) { _AWCACHE = AWCACHE; }
  void setAWPROT(unsigned char AWPROT)   { _AWPROT  = AWPROT;  }

  void setAWUSER(unsigned int d)         { _AWUSER  = d;       }

  /* for W channel  */
  void setWID(unsigned int WID)          { _WID     = WID;     }
  void setWSTRB(unsigned int WSTRB)      { _WSTRB   = WSTRB;   }
  void setWLAST(bool WLAST)              { _WLAST   = WLAST;   }

  void setWDATA(unsigned int WDATA)       { _WDATA32   = WDATA;   }
  void setWDATA(unsigned long long WDATA) { _WDATA64   = WDATA;   }
  void setWDATA(sc_biguint<128> WDATA)    {
   unsigned int high=31;
   unsigned int low=0;
   for(int i=0; i<4; i++){
      _WDATA128.range(high,low)   = WDATA.range(high,low);
      high=high+32;
      low =low +32;
    }
  }

  /* for B channel  */
  void setBID(unsigned int BID)          { _BID     = BID;     }
  void setBRESP(unsigned char BRESP)     { _BRESP   = BRESP;   }

  /* for AR channel  */
  void setARID(unsigned int ARID)        { _ARID    = ARID;    }
  void setARADDR(unsigned int ARADDR)    { _ARADDR  = ARADDR;  }
  void setARLEN(unsigned char ARLEN)     { _ARLEN   = ARLEN;   }
  void setARSIZE(unsigned char ARSIZE)   { _ARSIZE  = ARSIZE;  }
  void setARBURST(unsigned char ARBURST) { _ARBURST = ARBURST; }
  void setARLOCK(unsigned char ARLOCK)   { _ARLOCK  = ARLOCK;  }
  void setARCACHE(unsigned char ARCACHE) { _ARCACHE = ARCACHE; }
  void setARPROT(unsigned char ARPROT)   { _ARPROT  = ARPROT;  }

  void setARUSER(unsigned int d)         { _ARUSER  = d;       }

  /* for R channel  */
  void setRID(unsigned int RID)          { _RID     = RID;     }
  void setRRESP(unsigned char RRESP)     { _RRESP   = RRESP;   }
  void setRLAST(bool RLAST)              { _RLAST   = RLAST;   }

  void setRDATA(unsigned int RDATA)         { _RDATA32   = RDATA;   }
  void setRDATA(unsigned long long RDATA)   { _RDATA64   = RDATA;   }
  void setRDATA(sc_biguint<128> RDATA)      { _RDATA128  = RDATA;   }

  /*
   * Getter
   */

  /* for AW channel  */
  unsigned int  getAWID(void)    { return _AWID;    }
  unsigned int  getAWADDR(void)  { return _AWADDR;  }
  unsigned char getAWLEN(void)   { return _AWLEN;   }
  unsigned char getAWSIZE(void)  { return _AWSIZE;  }
  unsigned char getAWBURST(void) { return _AWBURST; }
  unsigned char getAWLOCK(void)  { return _AWLOCK;  }
  unsigned char getAWCACHE(void) { return _AWCACHE; }
  unsigned char getAWPROT(void)  { return _AWPROT;  }

  unsigned int  getAWUSER()      { return _AWUSER;  }

  /* for W channel  */
  unsigned int  getWID(void)     { return _WID;     }
  unsigned int  getWSTRB(void)   { return _WSTRB;   }
  bool          getWLAST(void)   { return _WLAST;   }

  data_type getWDATA(void) {
    return _getWDATA(m_width);
  }
  unsigned int       _getWDATA(unsigned int width)         { return _WDATA32;   }
  unsigned long long _getWDATA(unsigned long long width)   { return _WDATA64;   }
  sc_biguint<128>    _getWDATA(sc_biguint<128> width)      { return _WDATA128;  }

  /* for B channel  */
  unsigned int  getBID(void)     { return _BID;     }
  unsigned char getBRESP(void)   { return _BRESP;   }

  /* for AR channel  */
  unsigned int  getARID(void)    { return _ARID;    }
  unsigned int  getARADDR(void)  { return _ARADDR;  }
  unsigned char getARLEN(void)   { return _ARLEN;   }
  unsigned char getARSIZE(void)  { return _ARSIZE;  }
  unsigned char getARBURST(void) { return _ARBURST; }
  unsigned char getARLOCK(void)  { return _ARLOCK;  }
  unsigned char getARCACHE(void) { return _ARCACHE; }
  unsigned char getARPROT(void)  { return _ARPROT;  }

  unsigned int  getARUSER()      { return _ARUSER;  }

  /* for R channel  */
  unsigned int  getRID(void)     { return _RID;     }
  unsigned char getRRESP(void)   { return _RRESP;   }
  bool          getRLAST(void)   { return _RLAST;   }

  data_type getRDATA(void){
    return _getRDATA(m_width);
  }
  unsigned int       _getRDATA(unsigned int width)         { return _RDATA32;   }
  unsigned long long _getRDATA(unsigned long long width)   { return _RDATA64;   }
  sc_biguint<128>    _getRDATA(sc_biguint<128> width)      { return _RDATA128;  }



// ToDo: change to public
// private:



  /* for AW channel  */
  unsigned int  _AWID;    /* AWID   [31:0] */
  unsigned int  _AWADDR;  /* AWADDR [31:0] */
  unsigned char _AWLEN;   /* AWLEN  [ 3:0] */
  unsigned char _AWSIZE;  /* AWSIZE [ 2:0] */
  unsigned char _AWBURST; /* AWBURST[ 1:0] */
  unsigned char _AWLOCK;  /* AWLOCK [ 1:0] */
  unsigned char _AWCACHE; /* AWCACHE[ 3:0] */
  unsigned char _AWPROT;  /* AWPROT [ 2:0] */

  unsigned int  _AWUSER;  /* AWUSER [31:0] */

  /* for W channel  */
  unsigned int  _WID;     /* WID    [31:0] */
  unsigned int  _WSTRB;   /* WSTRB  [31:0] */
  bool          _WLAST;   /* WLAST         */

  unsigned int       _WDATA32;   /* WDATA  [ N:0] */
  unsigned long long _WDATA64;   /* WDATA  [ N:0] */
  sc_biguint<128>    _WDATA128;  /* WDATA  [ N:0] */

  /* for B channel  */
  unsigned int  _BID;     /* BID    [31:0] */
  unsigned char _BRESP;   /* BRESP  [ 1:0] */

  /* for AR channel  */
  unsigned int  _ARID;    /* ARID   [31:0] */
  unsigned int  _ARADDR;  /* ARADDR [31:0] */
  unsigned char _ARLEN;   /* ARLEN  [ 3:0] */
  unsigned char _ARSIZE;  /* ARSIZE [ 2:0] */
  unsigned char _ARBURST; /* ARBURST[ 1:0] */
  unsigned char _ARLOCK;  /* ARLOCK [ 1:0] */
  unsigned char _ARCACHE; /* ARCACHE[ 3:0] */
  unsigned char _ARPROT;  /* ARPROT [ 2:0] */

  unsigned int  _ARUSER;  /* ARUSER [31:0] */

  /* for R channel  */
  unsigned int  _RID;     /* RID    [31:0] */
  unsigned char _RRESP;   /* RRESP  [ 1:0] */
  bool          _RLAST;   /* RLAST         */

  unsigned int        _RDATA32;   /* RDATA  [ N:0] */
  unsigned long long  _RDATA64;   /* RDATA  [ N:0] */
  sc_biguint<128>     _RDATA128;  /* RDATA  [ N:0] */

  data_type     m_width;
};

#endif  // AXI_PAYLOAD_H
