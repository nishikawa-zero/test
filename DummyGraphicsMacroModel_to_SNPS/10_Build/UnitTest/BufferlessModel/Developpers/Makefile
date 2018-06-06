################################################################################
# Dummy Graphics Macro Model Library for SoC Designer
################################################################################

################################################################################
# Directory
################################################################################

TOP_DIR               = ${REPOSITORY_TOP}/trunk
DUMMY_MODEL_DIR       = ${TOP_DIR}/01_Model/DummyGraphicsMacroModel
WRAPPER_DIR           = ${TOP_DIR}/01_Model/DummyGraphicsMacroModelWrapper
BUFFERLESSMODEL_DIR   = ${TOP_DIR}/01_Model/BufferlessModel
ARBITER_DIR           = ${TOP_DIR}/01_Model/Arbiter
TLM_AXI_3_DIR         = ${TOP_DIR}/02_IF/TlmAxi3
COMMON_DIR            = ${TOP_DIR}/03_LIB/CommonLib
LIB_DIR               = ${TOP_DIR}/03_LIB/CommonLib
ADREESS_GENERATOR_DIR = ${TOP_DIR}/03_LIB/AddressGenerator
SCENARIO_DIR          = ${TOP_DIR}/01_Model/BufferlessModel

################################################################################
# Variable
################################################################################

PACKAGE     = BufferlessModel
SHARED_LIB  = lib${PACKAGE}.so
STATIC_LIB  = lib${PACKAGE}.a
TARGET      = ${SHARED_LIB}

# SoCD supports -m32 binary only
CXX       = g++
CXXFLAGS  = -m32 -pedantic -g \
            -Wall -Wno-long-long -Wwrite-strings -Wpointer-arith \
            -DSC_INCLUDE_DYNAMIC_PROCESSES \
            -DBUSMASTER_IRQ_OUT \
            -DUSE_BufferlessModel \
#            $(DBGFLAGS)
DBGFLAGS  = -DABSTFR_TIMESTAMP \
            -DTLM_AXI_TRANSRECEIVER_DEBUG \
            -DDEBUG_SCENARIO \
            -DDEBUG_DUMMY_GRAPHICS_MACRO_MODEL_SCENARIO_API
LDFLAGS   = 

INC = -I${MAXSIM_HOME}/include \
      -I${MAXSIM_HOME}/include/tlm \
      -I${MAXSIM_PROTOCOLS}/AXIv2/include \
      -I${MAXSIM_PROTOCOLS}/Common/include \
      -I${DUMMY_MODEL_DIR}/include \
      -I${WRAPPER_DIR}/include \
      -I${BUFFERLESSMODEL_DIR}/include \
      -I${ARBITER_DIR}/include \
      -I${TLM_AXI_3_DIR}/Base/include \
      -I${TLM_AXI_3_DIR}/Payload/include \
      -I${TLM_AXI_3_DIR}/Primitive/include \
      -I${TLM_AXI_3_DIR}/FiveChannelInterface/include \
      -I${COMMON_DIR}/include \
      -I${LIB_DIR}/include \
      -I${ADREESS_GENERATOR_DIR}/include \
      -I${SCENARIO_DIR}/include

VPATH = ${DUMMY_MODEL_DIR}/src: \
        ${WRAPPER_DIR}/src: \
        ${BUFFERLESSMODEL_DIR}/src: \
        ${ARBITER_DIR}/src: \
        ${TLM_AXI_3_DIR}/Base/src: \
        ${TLM_AXI_3_DIR}/Payload/src: \
        ${TLM_AXI_3_DIR}/Primitive/src: \
        ${TLM_AXI_3_DIR}/FiveChannelInterface/src \
        ${COMMON_DIR}/src: \
        ${LIB_DIR}/src: \
	${ADREESS_GENERATOR_DIR}/src: \
        ${SCENARIO_DIR}/src: \

OBJS = DummyGraphicsMacroModel.o \
       DummyGraphicsMacroModelBuffer.o \
       DummyGraphicsMacroModelFifo.o \
       DummyGraphicsMacroModelScenarioApi.o \
       DummyGraphicsMacroModelPointerApi.o \
       TlmAxi3FiveChannelInterface_AXI_CX.o \
       TlmAxi3InitiatorBaseIf.o \
       TlmAxi3TargetBaseIf.o \
       TlmAxi3InitiatorPrimitiveIf.o \
       TlmAxi3TargetPrimitiveIf.o \
       BufferlessModel.o \
       BufferlessModel_wrapperbase.o \
       TlmAxiArbiter.o \
       TlmAxiArbiterSlaveInterface.o \
       BufferlessModel_AXI_Master_Port.o \
       DummyGraphicsMacroModel_interrupt_SS.o \
       DummyGraphicsMacroModel_reset_x_SS.o \
       OutputSignalReceiver.o \
       CsvParser.o \
       VcdMaker.o

SCENARIO_OBJS = BufferlessModel_Scenario.o

BOOST = -I${LIB_DIR}/boost/boost_1_51_0

LIB = -L${MAXSIM_PROTOCOLS}/AXIv2/lib -lAXIPorts \
      -L${MAXSIM_PROTOCOLS}/Common/lib -lUtilsCommon \
      -L${MAXSIM_HOME}/lib/`uname`/release -lmaxsimcore

################################################################################
# Make
################################################################################

.PHONY    : all clean
.SUFFIXES : .cpp .o

all : ${TARGET}

clean :
	rm -f ${SHARED_LIB} ${STATIC_LIB}
	rm -f *.o

${SHARED_LIB} : ${STATIC_LIB} ${SCENARIO_OBJS}
	${CXX} ${LDFLAGS} ${SCENARIO_OBJS} -Wl,--whole-archive $< -Wl,--no-whole-archive ${LIB} -shared -o $@

${STATIC_LIB} : ${OBJS}
	ar cr $@ $^

.cpp.o :
	${CXX} ${CXXFLAGS} ${INC} ${BOOST} -fPIC -c $<

