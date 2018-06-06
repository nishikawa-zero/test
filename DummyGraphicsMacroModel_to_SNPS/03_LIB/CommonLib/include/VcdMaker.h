/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file VcdMaker.h
 * @brief VCD format file maker (header)
 */
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <map>
#include <cassert>

class VcdMaker {
private:
  struct VcdValue {
    std::string name;
    char category;
    unsigned int id;
    unsigned int width;
    unsigned long long initial_value;
    unsigned long long value;
    unsigned long long pre_value;
  };

public:
  VcdMaker(const char *file_name,
           const char *module_name,
           const char *time_unit = "ns");
  ~VcdMaker(void);

  bool isOpen();
  int makeValue(const char *name,
                const char category,
                const unsigned int id,
                const unsigned int width, 
                const unsigned long long initial_value);
  int setValue(const unsigned long long time,
               const char category,
               const unsigned int id,
               const unsigned long long value);
  void finish(const unsigned long long time);

private:
  void flushUpdateList(void);
  void makeHeader(void);
  void dumpBinaryValue(std::ofstream &ofs,
                       const char category,
                       const unsigned int id,
                       const unsigned int width, 
                       const unsigned long long value);

private:
  std::string m_file_name;
  std::string m_module_name;
  std::string m_time_unit;
  
  bool m_is_open;
  bool m_is_make_header;
  bool m_is_finish;
  std::ofstream m_ofs;

  typedef std::map<unsigned int, VcdValue*> VcdValueMap;
  typedef VcdValueMap::iterator VcdValueMapItr;

  typedef std::map<char, VcdValueMap*> IdMap;
  typedef IdMap::iterator IdMapItr;

  typedef std::map<VcdValue*, VcdValue*> UpdateList;
  typedef UpdateList::iterator UpdateListItr;

  IdMap m_id_map;
  VcdValueMap m_value_map;
  UpdateList m_update_list;
  unsigned long long m_current_time;
};
