/*
 * ALL RIGHTS RESERVED, COPYRIGHT (C) FUJITSU SEMICONDUCTOR LTD. 2014
 * LICENSED MATERIAL - PROGRAM PROPERTY OF FUJITSU SEMICONDUCTOR LTD.
 */
/**
 * @file DummyGraphicsMacroModelPointerApi.h
 * @brief DummyGraphicsMacroModelPointerApi (header)
 */
#include <assert.h>
#include <iostream>
#include <map>

#include "DummyGraphicsMacroModelBase.h"

#ifndef DUMMY_GRAPHICS_MACRO_MODEL_POINTER_API_H
#define DUMMY_GRAPHICS_MACRO_MODEL_POINTER_API_H

void setDummyGraphicsMacroModelBasePointer(unsigned int model_id,
                                           DummyGraphicsMacroModelBase* pointer);
DummyGraphicsMacroModelBase* getDummyGraphicsMacroModelBasePointer(unsigned int model_id);

#endif /* DUMMY_GRAPHICS_MACRO_MODEL_POINTER_API_H */
