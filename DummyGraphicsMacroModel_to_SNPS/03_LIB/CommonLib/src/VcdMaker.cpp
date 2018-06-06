/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file VcdMaker.cpp
 * @brief VCD format file maker (source )
 */
#include "VcdMaker.h"

VcdMaker::VcdMaker(const char *file_name,
                   const char *module_name,
                   const char *time_unit):
  m_is_make_header(false),
  m_is_finish(false),
  m_current_time(0ULL) {
  m_is_open = false;

  if ((file_name != NULL) && (module_name != NULL) && (time_unit != NULL)) {
    m_file_name = file_name;
    m_module_name = module_name;
    m_time_unit = time_unit;

    m_ofs.open(m_file_name.c_str());
    if (m_ofs) {
      m_is_open = true;
    }
  }
}

VcdMaker::~VcdMaker(void) {
}

bool
VcdMaker::isOpen(void) {
  return m_is_open;
}

int
VcdMaker::makeValue(const char *name,
                    const char category,
                    const unsigned int id,
                    const unsigned int width,
                    const unsigned long long initial_value) {
  int result = -1;

  if (m_is_open && !m_is_finish && !m_is_make_header) {
    if (1 <= width) {
      IdMapItr id_map_itr = m_id_map.find(category);
      
      if (id_map_itr == m_id_map.end()) {
        VcdValueMap *vcd_value_map = new VcdValueMap;
        m_id_map[category] = vcd_value_map;
        id_map_itr = m_id_map.find(category);
      }
      
      VcdValueMap *vcd_value_map = id_map_itr->second;
      VcdValueMapItr vcd_value_map_itr = vcd_value_map->find(id);
    
      if (vcd_value_map_itr == vcd_value_map->end()) {
        VcdValue *vcd_value = new VcdValue;
        vcd_value->name = name;
        vcd_value->category = category;
        vcd_value->id = id;
        vcd_value->width = width;
        vcd_value->initial_value = initial_value;
        vcd_value->pre_value = initial_value;
        
        (*vcd_value_map)[id] = vcd_value;
        
        result = 0;
      }
    }
  }

  return result;
}

int
VcdMaker::setValue(const unsigned long long time,
                   const char category,
                   const unsigned int id,
                   const unsigned long long value) {
  int result = -1;

  if (m_is_open && !m_is_finish) {
    if (!m_is_make_header) {
      makeHeader();
    }
    if (m_current_time <= time) {
      if (time != m_current_time) {
        flushUpdateList();
        m_current_time = time;
      }
      
      IdMapItr id_map_itr = m_id_map.find(category);
      
      if (id_map_itr != m_id_map.end()) {  
        VcdValueMap *vcd_value_map = id_map_itr->second;
        VcdValueMapItr vcd_value_map_itr = vcd_value_map->find(id);
        
        if (vcd_value_map_itr != vcd_value_map->end()) {
          VcdValue *vcd_value = vcd_value_map_itr->second;
          UpdateListItr update_list_itr = m_update_list.find(vcd_value);
          
          if (update_list_itr == m_update_list.end()) {
            m_update_list[vcd_value] = vcd_value;
          }
          vcd_value->value = value;        
        }
      }
    }
  }

  return result;
}

void
VcdMaker::finish(unsigned long long time) {
  m_is_finish = true;
  flushUpdateList();
  m_ofs << "#" << time << std::endl;  
}

void
VcdMaker::flushUpdateList(void) {
  if (!m_update_list.empty()) {
    UpdateListItr update_list_itr = m_update_list.begin();
    
    m_ofs << "#" << m_current_time << std::endl;
    
    while (update_list_itr != m_update_list.end()) {
      if (update_list_itr->second->value != update_list_itr->second->pre_value) {
        dumpBinaryValue(m_ofs,
                        update_list_itr->second->category,
                        update_list_itr->second->id,
                        update_list_itr->second->width,
                        update_list_itr->second->value);
        update_list_itr->second->pre_value = update_list_itr->second->value;
      }
      ++update_list_itr;
    }
    m_update_list.clear();
  }
}

void
VcdMaker::makeHeader(void) {
  if (m_ofs && !m_is_make_header) {
    m_ofs << "$timescale" << std::endl;
    m_ofs << "  1" << m_time_unit <<  std::endl;
    m_ofs << "$end" <<  std::endl;
    m_ofs << "$scope modeule " << m_module_name << " $end" <<  std::endl;

    IdMapItr id_map_itr = m_id_map.begin();
    while (id_map_itr != m_id_map.end()) {
      VcdValueMap *vcd_value_map = id_map_itr->second;
      VcdValueMapItr vcd_value_map_itr = vcd_value_map->begin();
      while (vcd_value_map_itr != vcd_value_map->end()) {
        m_ofs << "  $var wire " << vcd_value_map_itr->second->width << " " << id_map_itr->first << vcd_value_map_itr->first << " " << vcd_value_map_itr->second->name << " $end" << std::endl;  
        ++vcd_value_map_itr;  
      }
      ++id_map_itr;  
    }

    m_ofs << "$upscope $end" <<  std::endl;
    m_ofs << "$enddefinitions $end" <<  std::endl;

    m_ofs << "$dumpvars" <<  std::endl;
    id_map_itr = m_id_map.begin();
    while (id_map_itr != m_id_map.end()) {
      VcdValueMap *vcd_value_map = id_map_itr->second;
      VcdValueMapItr vcd_value_map_itr = vcd_value_map->begin();
      while (vcd_value_map_itr != vcd_value_map->end()) {
        dumpBinaryValue(m_ofs,
                        vcd_value_map_itr->second->category,
                        vcd_value_map_itr->second->id,
                        vcd_value_map_itr->second->width,
                        vcd_value_map_itr->second->initial_value);
        ++vcd_value_map_itr;  
      }
      ++id_map_itr;  
    }
    m_ofs << "$end" <<  std::endl;

    m_is_make_header = true;
  }
}

void
VcdMaker::dumpBinaryValue(std::ofstream &ofs,
                          const char category,
                          const unsigned int id,
                          const unsigned int width, 
                          const unsigned long long value) {
  if (width == 1) {
    ofs << (value & 0x1) << category << id << std::endl;
  } else {
    ofs << "b";
    for (unsigned int i = 0; i < width; ++i) {
      ofs << ((value >> (width - i - 1)) & 0x1);
    }
    ofs << " " << category << id << std::endl;
  }
}
