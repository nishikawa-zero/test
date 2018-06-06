################################################################################
# Dummy Graphics Macro Model Library for SoC Designer
################################################################################

################################################################################
# Directory
################################################################################

TOP_DIR         = ${REPOSITORY_TOP}/trunk
DUMMY_MODEL_DIR = ${TOP_DIR}/01_Model/DummyGraphicsMacroModel
WRAPPER_DIR     = ${TOP_DIR}/01_Model/DummyGraphicsMacroModelWrapper
TLM_AXI_3_DIR   = ${TOP_DIR}/02_IF/TLM_AXI_IF
COMMON_DIR      = ${TOP_DIR}/03_LIB/CommonLib
LIB_DIR         = ${TOP_DIR}/03_LIB/CommonLib
SCENARIO_DIR 		= ${TOP_DIR}/10_Build/UnitTest/DummyGraphicsMacroModel/Developpers/Scenario

################################################################################
# Variable
################################################################################

PACKAGE     = SD_AXIv2_DummyGraphicsMacroModel
SHARED_LIB  = lib${PACKAGE}.so
STATIC_LIB  = lib${PACKAGE}.a
TARGET      = ${SHARED_LIB}

# SoCD supports -m32 binary only
CXX       = g++
CXXFLAGS  = -m32 -pedantic -g \
            -Wall -Wno-long-long -Wwrite-strings -Wpointer-arith \
            -DSC_INCLUDE_DYNAMIC_PROCESSES \
            -DBUSMASTER_IRQ_OUT \
            -DUSE_SD_AXIv2_DummyGraphicsMacroModel \
#            $(DBGFLAGS)
DBGFLAGS  = -DABSTFR_TIMESTAMP \
            -DTLM_AXI_TRANSRECEIVER_DEBUG \
            -DDEBUG_SCENARIO 
LDFLAGS   = 

INC = -I${MAXSIM_HOME}/include \
      -I${MAXSIM_HOME}/include/tlm \
      -I${MAXSIM_PROTOCOLS}/AXIv2/include \
      -I${MAXSIM_PROTOCOLS}/Common/include \
      -I${DUMMY_MODEL_DIR}/include \
      -I${WRAPPER_DIR}/include \
      -I${TLM_AXI_3_DIR}/TlmAxiBase/include \
      -I${TLM_AXI_3_DIR}/TlmAxiPayload/include \
      -I${TLM_AXI_3_DIR}/TlmAxiPrimitive/include \
      -I${TLM_AXI_3_DIR}/5ChannelInterface/include \
      -I${COMMON_DIR}/include \
      -I${LIB_DIR}/include \
      -I${SCENARIO_DIR}/include

VPATH = ${DUMMY_MODEL_DIR}/src: \
        ${WRAPPER_DIR}/src: \
        ${TLM_AXI_3_DIR}/TlmAxiBase/src: \
        ${TLM_AXI_3_DIR}/TlmAxiPayload/src: \
        ${TLM_AXI_3_DIR}/TlmAxiPrimitive/src: \
        ${TLM_AXI_3_DIR}/5ChannelInterface/src \
        ${COMMON_DIR}/src: \
        ${LIB_DIR}/src: \
        ${SCENARIO_DIR}/src: \

OBJS = DummyGraphicsMacroModel.o \
       DummyGraphicsMacroModelBuffer.o \
       DummyGraphicsMacroModelFifo.o \
       DummyGraphicsMacroModelScenarioApi.o \
       DummyGraphicsMacroModelPointerApi.o \
       TlmAxi5ChannelInterface_AXI_CX.o \
       DummyGraphicsMacroModel_AXI_Master_Port.o \
       DummyGraphicsMacroModel_wrapperbase.o \
       DummyGraphicsMacroModel_interrupt_SS.o \
       DummyGraphicsMacroModel_reset_x_SS.o \
       SD_AXIv2_DummyGraphicsMacroModel.o \
       OutputSignalReceiver.o \
       tlm_axi_transreceiver.o \
       tlm_axi_initiator_base_if.o \
       tlm_axi_target_base_if.o \
       AXIDataFormatControl.o \
       CsvParser.o \
       VcdMaker.o \
       BusTransactionInitiatorInterfacePrimitive.o \
       BusTransactionTargetInterfacePrimitive.o

SCENARIO_OBJS = Scenario.o

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

