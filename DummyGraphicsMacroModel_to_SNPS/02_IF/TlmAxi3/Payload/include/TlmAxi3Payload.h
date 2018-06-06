/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 *
 */
/**
 * @file TlmAxi3Payload.h
 * @brief generic_payload extension class for AXI3
 */

#ifndef TLM_AXI3_PAYLOAD_H
#define TLM_AXI3_PAYLOAD_H

#include <tlm.h>
#include <systemc.h>

class TlmAxi3Payload: public tlm::tlm_extension<TlmAxi3Payload> {
private:
  TlmAxi3Payload(void) {
  }

public:
  explicit TlmAxi3Payload(const unsigned int byte_size):
    m_AWID(0),
    m_AWADDR(0),
    m_AWLEN(0),
    m_AWSIZE(0),
    m_AWBURST(0),
    m_AWLOCK(0),
    m_AWCACHE(0),
    m_AWPROT(0),    
    m_AWUSER(0),
    m_WID(0),
    m_WLAST(0),
    m_BID(0),
    m_BRESP(0),
    m_ARID(0),
    m_ARADDR(0),
    m_ARLEN(0),
    m_ARSIZE(0),
    m_ARBURST(0),
    m_ARLOCK(0),
    m_ARCACHE(0),
    m_ARPROT(0),
    m_ARUSER(0),
    m_RID(0),
    m_RRESP(0),
    m_RLAST(0),
    m_byte_size(byte_size) {
  }

  ~TlmAxi3Payload(void) {
  }

  tlm::tlm_extension_base* clone() const {
    TlmAxi3Payload* axi = new TlmAxi3Payload(m_byte_size);

    axi->m_AWID    = this->m_AWID;
    axi->m_AWADDR  = this->m_AWADDR;
    axi->m_AWLEN   = this->m_AWLEN;
    axi->m_AWSIZE  = this->m_AWSIZE;
    axi->m_AWBURST = this->m_AWBURST;
    axi->m_AWLOCK  = this->m_AWLOCK;
    axi->m_AWCACHE = this->m_AWCACHE;
    axi->m_AWPROT  = this->m_AWPROT;
    axi->m_AWUSER  = this->m_AWUSER;
    axi->m_WID     = this->m_WID;
    axi->m_WLAST   = this->m_WLAST;
    memcpy(axi->m_wdata, this->m_wdata, m_byte_size);
    memcpy(axi->m_wstrb, this->m_wstrb, m_byte_size);
    axi->m_BID     = this->m_BID;
    axi->m_BRESP   = this->m_BRESP;
    axi->m_ARID    = this->m_ARID;
    axi->m_ARADDR  = this->m_ARADDR;
    axi->m_ARLEN   = this->m_ARLEN;
    axi->m_ARSIZE  = this->m_ARSIZE;
    axi->m_ARBURST = this->m_ARBURST;
    axi->m_ARLOCK  = this->m_ARLOCK;
    axi->m_ARCACHE = this->m_ARCACHE;
    axi->m_ARPROT  = this->m_ARPROT;
    axi->m_ARUSER  = this->m_ARUSER;
    axi->m_RID     = this->m_RID;
    axi->m_RRESP   = this->m_RRESP;
    axi->m_RLAST   = this->m_RLAST;
    memcpy(axi->m_rdata, this->m_rdata, m_byte_size);

    return axi;
  }

  void copy_from(tlm::tlm_extension_base const &extension) {
    m_AWID    = static_cast<TlmAxi3Payload const &>(extension).m_AWID;
    m_AWADDR  = static_cast<TlmAxi3Payload const &>(extension).m_AWADDR;
    m_AWLEN   = static_cast<TlmAxi3Payload const &>(extension).m_AWLEN;
    m_AWSIZE  = static_cast<TlmAxi3Payload const &>(extension).m_AWSIZE;
    m_AWBURST = static_cast<TlmAxi3Payload const &>(extension).m_AWBURST;
    m_AWLOCK  = static_cast<TlmAxi3Payload const &>(extension).m_AWLOCK;
    m_AWCACHE = static_cast<TlmAxi3Payload const &>(extension).m_AWCACHE;
    m_AWPROT  = static_cast<TlmAxi3Payload const &>(extension).m_AWPROT;
    m_AWUSER  = static_cast<TlmAxi3Payload const &>(extension).m_AWUSER;
    m_WID     = static_cast<TlmAxi3Payload const &>(extension).m_WID;
    m_WLAST   = static_cast<TlmAxi3Payload const &>(extension).m_WLAST;
    memcpy(m_wdata, static_cast<TlmAxi3Payload const &>(extension).m_wdata, m_byte_size);
    memcpy(m_wstrb, static_cast<TlmAxi3Payload const &>(extension).m_wstrb, m_byte_size);
    m_BID     = static_cast<TlmAxi3Payload const &>(extension).m_BID;
    m_BRESP   = static_cast<TlmAxi3Payload const &>(extension).m_BRESP;
    m_ARID    = static_cast<TlmAxi3Payload const &>(extension).m_ARID;
    m_ARADDR  = static_cast<TlmAxi3Payload const &>(extension).m_ARADDR;
    m_ARLEN   = static_cast<TlmAxi3Payload const &>(extension).m_ARLEN;
    m_ARSIZE  = static_cast<TlmAxi3Payload const &>(extension).m_ARSIZE;
    m_ARBURST = static_cast<TlmAxi3Payload const &>(extension).m_ARBURST;
    m_ARLOCK  = static_cast<TlmAxi3Payload const &>(extension).m_ARLOCK;
    m_ARCACHE = static_cast<TlmAxi3Payload const &>(extension).m_ARCACHE;
    m_ARPROT  = static_cast<TlmAxi3Payload const &>(extension).m_ARPROT;
    m_ARUSER  = static_cast<TlmAxi3Payload const &>(extension).m_ARUSER;
    m_RID     = static_cast<TlmAxi3Payload const &>(extension).m_RID;
    m_RRESP   = static_cast<TlmAxi3Payload const &>(extension).m_RRESP;
    m_RLAST   = static_cast<TlmAxi3Payload const &>(extension).m_RLAST;
    memcpy(m_rdata, static_cast<TlmAxi3Payload const &>(extension).m_rdata, m_byte_size);
  }

  /*
   * Setter
   */
  inline void setAWID(const unsigned int AWID)        { m_AWID    = AWID;    }
  inline void setAWADDR(const unsigned int  AWADDR)   { m_AWADDR  = AWADDR;  }
  inline void setAWLEN(const unsigned char AWLEN)     { m_AWLEN   = AWLEN;   }
  inline void setAWSIZE(const unsigned char AWSIZE)   { m_AWSIZE  = AWSIZE;  }
  inline void setAWBURST(const unsigned char AWBURST) { m_AWBURST = AWBURST; }
  inline void setAWLOCK(const unsigned char AWLOCK)   { m_AWLOCK  = AWLOCK;  }
  inline void setAWCACHE(const unsigned char AWCACHE) { m_AWCACHE = AWCACHE; }
  inline void setAWPROT(const unsigned char AWPROT)   { m_AWPROT  = AWPROT;  }
  inline void setAWUSER(const unsigned int AWUSER)    { m_AWUSER  = AWUSER;  }
  inline void setWID(const unsigned int WID)          { m_WID     = WID;     }
  inline void setWLAST(const bool WLAST)              { m_WLAST   = WLAST;   }
  inline void setWDATA(const unsigned char *wdata)    { memcpy(m_wdata, wdata, m_byte_size); }
  inline void setWSTRB(const unsigned char *wstrb)    { memcpy(m_wstrb, wstrb, m_byte_size); }
  inline void setBID(const unsigned int BID)          { m_BID     = BID;     }
  inline void setBRESP(const unsigned char BRESP)     { m_BRESP   = BRESP;   }
  inline void setARID(const unsigned int ARID)        { m_ARID    = ARID;    }
  inline void setARADDR(const unsigned int ARADDR)    { m_ARADDR  = ARADDR;  }
  inline void setARLEN(const unsigned char ARLEN)     { m_ARLEN   = ARLEN;   }
  inline void setARSIZE(const unsigned char ARSIZE)   { m_ARSIZE  = ARSIZE;  }
  inline void setARBURST(const unsigned char ARBURST) { m_ARBURST = ARBURST; }
  inline void setARLOCK(const unsigned char ARLOCK)   { m_ARLOCK  = ARLOCK;  }
  inline void setARCACHE(const unsigned char ARCACHE) { m_ARCACHE = ARCACHE; }
  inline void setARPROT(const unsigned char ARPROT)   { m_ARPROT  = ARPROT;  }
  inline void setARUSER(const unsigned int d)         { m_ARUSER  = d;       }
  inline void setRID(const unsigned int RID)          { m_RID     = RID;     }
  inline void setRRESP(const unsigned char RRESP)     { m_RRESP   = RRESP;   }
  inline void setRLAST(const bool RLAST)              { m_RLAST   = RLAST;   }
  inline void setRDATA(const unsigned char *rdata)    { memcpy(m_rdata, rdata, m_byte_size); }

  /*
   * Getter
   */
  inline unsigned int  getAWID(void)    { return m_AWID;    }
  inline unsigned int  getAWADDR(void)  { return m_AWADDR;  }
  inline unsigned char getAWLEN(void)   { return m_AWLEN;   }
  inline unsigned char getAWSIZE(void)  { return m_AWSIZE;  }
  inline unsigned char getAWBURST(void) { return m_AWBURST; }
  inline unsigned char getAWLOCK(void)  { return m_AWLOCK;  }
  inline unsigned char getAWCACHE(void) { return m_AWCACHE; }
  inline unsigned char getAWPROT(void)  { return m_AWPROT;  }
  inline unsigned int  getAWUSER()      { return m_AWUSER;  }
  inline unsigned int  getWID(void)     { return m_WID;     }
  inline bool          getWLAST(void)   { return m_WLAST;   }
  inline unsigned char* getWDATA(void)  { return m_wdata;   }
  inline unsigned char* getWSTRB(void)  { return m_wstrb;   }
  inline unsigned int  getBID(void)     { return m_BID;     }
  inline unsigned char getBRESP(void)   { return m_BRESP;   }
  inline unsigned int  getARID(void)    { return m_ARID;    }
  inline unsigned int  getARADDR(void)  { return m_ARADDR;  }
  inline unsigned char getARLEN(void)   { return m_ARLEN;   }
  inline unsigned char getARSIZE(void)  { return m_ARSIZE;  }
  inline unsigned char getARBURST(void) { return m_ARBURST; }
  inline unsigned char getARLOCK(void)  { return m_ARLOCK;  }
  inline unsigned char getARCACHE(void) { return m_ARCACHE; }
  inline unsigned char getARPROT(void)  { return m_ARPROT;  }
  inline unsigned int  getARUSER()      { return m_ARUSER;  }
  inline unsigned int  getRID(void)     { return m_RID;     }
  inline unsigned char getRRESP(void)   { return m_RRESP;   }
  inline bool          getRLAST(void)   { return m_RLAST;   }
  inline unsigned char* getRDATA(void)  { return m_rdata;   }

  inline unsigned int getByteSize(void)   const { return m_byte_size; }

public:
  unsigned int  m_AWID;    /* AWID    */
  unsigned int  m_AWADDR;  /* AWADDR  */
  unsigned char m_AWLEN;   /* AWLEN   */
  unsigned char m_AWSIZE;  /* AWSIZE  */
  unsigned char m_AWBURST; /* AWBURST */
  unsigned char m_AWLOCK;  /* AWLOCK  */
  unsigned char m_AWCACHE; /* AWCACHE */
  unsigned char m_AWPROT;  /* AWPROT  */
  unsigned int  m_AWUSER;  /* AWUSER  */
  unsigned int  m_WID;     /* WID     */
  bool          m_WLAST;   /* WLAST   */
  unsigned char m_wdata[16];  /* WDATA   */
  unsigned char m_wstrb[16];  /* WSTRB   */
  unsigned int  m_BID;     /* BID     */
  unsigned char m_BRESP;   /* BRESP   */
  unsigned int  m_ARID;    /* ARID    */
  unsigned int  m_ARADDR;  /* ARADDR  */
  unsigned char m_ARLEN;   /* ARLEN   */
  unsigned char m_ARSIZE;  /* ARSIZE  */
  unsigned char m_ARBURST; /* ARBURST */
  unsigned char m_ARLOCK;  /* ARLOCK  */
  unsigned char m_ARCACHE; /* ARCACHE */
  unsigned char m_ARPROT;  /* ARPROT  */
  unsigned int  m_ARUSER;  /* ARUSER  */
  unsigned int  m_RID;     /* RID     */
  unsigned char m_RRESP;   /* RRESP   */
  bool          m_RLAST;   /* RLAST   */
  unsigned char m_rdata[16];  /* RDATA   */

  unsigned int m_byte_size; /* Size of WDATA/RDATA (Byte) */
};

#endif  /* TLM_AXI3_PAYLOAD_H */
