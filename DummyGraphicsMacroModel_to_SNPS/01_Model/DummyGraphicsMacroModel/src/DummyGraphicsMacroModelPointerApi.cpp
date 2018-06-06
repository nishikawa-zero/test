/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModelPointerApi.cpp
 * @brief DummyGraphicsMacroModelPointerApi (source)
 */
#include "DummyGraphicsMacroModelPointerApi.h"

namespace {
  std::map<unsigned int, DummyGraphicsMacroModelBase*> g_model_pointers;
}

void setDummyGraphicsMacroModelBasePointer(unsigned int model_id,
                                           DummyGraphicsMacroModelBase* pointer) {
  std::map<unsigned int, DummyGraphicsMacroModelBase*>::iterator itr = g_model_pointers.find(model_id);

  if (itr != g_model_pointers.end()) {
    std::cout << "[ERROR] cannot set model (model_id=" << model_id << ")" << std::endl;
    assert(0);
  }

  g_model_pointers.insert(std::make_pair(model_id, pointer));
}

DummyGraphicsMacroModelBase* getDummyGraphicsMacroModelBasePointer(unsigned int model_id) {
  std::map<unsigned int, DummyGraphicsMacroModelBase*>::iterator itr = g_model_pointers.find(model_id);
  
  if (itr == g_model_pointers.end()) {
    std::cout << "[ERROR] cannot get model (model_id=" << model_id << ")" << std::endl;
    assert(0);
  }

  return itr->second;
}


