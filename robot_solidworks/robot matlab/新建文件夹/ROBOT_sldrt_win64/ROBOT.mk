# Abstract:
#	Template makefile for building Simulink Desktop Real-Time compatible
#       real-time version of Simulink model using generated C or C++ code and
#       the built-in Clang compiler.
#
# 	This makefile is designed to be used with GNU Make (gmake) which is
#       located in matlabroot/bin/<arch>.
#
# 	Note that this template is automatically customized by the Simulink
#	Coder build procedure to create "<model>.mk"
#
#       The following defines (macro names) can be used to modify the behavior
#       of the build:
#	  OPT_OPTS       - Optimization options.
#	  OPTS           - User-specified compiler options.
#         CPP_OPTS       - User-specified C++ compiler options.
#	  USER_SRCS      - Additional user objects, such as files needed by
#			   S-functions.
#	  USER_INCLUDES  - Additional include paths (i.e.
#			   "USER_INCLUDES=include-path1;include-path2")
#                          Use a '/' as a file separator instead of '\'.
#
#       Consider using the "Build process" dialog in Code Generation
#       options page instead of trying to change OPT_OPTS here.
#
#       This template makefile is designed to be used with a system target
#       file that contains 'rtwgensettings.ProjectDirSuffix', see grt.tlc .
#
# !!! THIS FILE IS AUTO-GENERATED !!!
# Copyright 1994-2016 The MathWorks, Inc.



#------------------------ Macros read by make_rtw -----------------------------
#
# The following macros are read by the code generation build procedure:
#  MAKECMD         - This is the command used to invoke the make utility
#  HOST            - What platform this template makefile is targeted for
#                    (i.e. PC or UNIX)
#  BUILD           - Invoke make from the code generation build procedure
#                    (yes/no)?
#  SYS_TARGET_FILE - Name of system target file.
#

MAKECMD         = "E:/Matlab/bin/win64/gmake"
HOST            = ANY
BUILD           = yes
SYS_TARGET_FILE = sldrt.tlc
COMPILER_TOOL_CHAIN = default
MAKEFILE_FILESEP = /


#---------------------- Tokens expanded by make_rtw ---------------------------
#
# The following tokens, when wrapped with "|>" and "<|" are expanded by the
# code generation build procedure.
#
#  MODEL_NAME          - Name of the Simulink block diagram
#  MODEL_MODULES       - Any additional generated source modules
#  MAKEFILE_NAME       - Name of makefile created from template makefile <model>.mk
#  MATLAB_ROOT         - Path to were MATLAB is installed.
#  MATLAB_BIN          - Path to MATLAB executable.
#  S_FUNCTIONS         - List of S-functions.
#  S_FUNCTIONS_LIB     - List of S-functions libraries to link.
#  SOLVER              - Solver source file name
#  NUMST               - Number of sample times
#  TID01EQ             - yes (1) or no (0): Are sampling rates of continuous
#                        task (tid=0) and 1st discrete task equal.
#  NCSTATES            - Number of continuous states
#  BUILDARGS           - Options passed in at the command line.
#  MULTITASKING        - yes (1) or no (0): Is solver mode multitasking
#  EXT_MODE            - yes (1) or no (0): Build for external mode
#  EXTMODE_TRANSPORT   - Name of transport mechanism (e.g. tcpip, serial) for extmode
#  EXTMODE_STATIC      - yes (1) or no (0): Use static instead of dynamic mem alloc.
#  EXTMODE_STATIC_SIZE - Size of static memory allocation buffer.
#
#  CC_LISTING          - yes (1) or no (0): Generate assembly listings
#  REBUILD_ALL         - yes (1) or no (0): Rebuild all files

MODEL                := ROBOT
MODULES              := ROBOT_2da83c1f_1.c ROBOT_2da83c1f_1_create.c ROBOT_2da83c1f_1_setParameters.c ROBOT_2da83c1f_1_asserts.c ROBOT_2da83c1f_1_deriv.c ROBOT_2da83c1f_1_checkDynamics.c ROBOT_2da83c1f_1_assembly.c ROBOT_2da83c1f_1_computeConstraintError.c ROBOT_2da83c1f_1_gateway.c pm_printf.c rt_backsubrr_dbl.c rt_forwardsubrr_dbl.c rt_lu_real.c rt_matrixlib_dbl.c ROBOT_data.cpp ROBOT_tgtconn.cpp rtGetInf.cpp rtGetNaN.cpp rt_nonfinite.cpp
MAKEFILE             := ROBOT.mk
MATLAB_ROOT          := E:/Matlab
MATLAB_BIN           := E:/Matlab/bin
S_FUNCTIONS          := 
S_FUNCTIONS_LIB      := 
SOLVER               := 
NUMST                := 2
TID01EQ              := 1
NCSTATES             := 0
BUILDARGS            :=  ISPROTECTINGMODEL=NOTPROTECTING EXTMODE_STATIC_ALLOC=0 EXTMODE_STATIC_ALLOC_SIZE=1000000 TMW_EXTMODE_TESTING=0 OPTS="-DTGTCONN -DON_TARGET_WAIT_FOR_START=1"
MULTITASKING         := 0
EXT_MODE             := 1
EXTMODE_TRANSPORT    := 0

MODELREFS            := 
SHARED_SRC           := 
SHARED_SRC_DIR       := 
SHARED_BIN_DIR       := 
SHARED_LIB           := 
TARGET_LANG_EXT      := cpp
OPTIMIZATION_FLAGS   := -O4
ADDITIONAL_LDFLAGS   := 
DEFINES_CUSTOM       := 

# Simulink Desktop Real-Time specific parameters
SLDRTDIR             := E:/Matlab/toolbox/sldrt
TARGETARCH           := win64
CC_LISTING           := 0
REBUILD_ALL          := 0

# ensure MATLAB_ROOT uses forward slashes on Windows - necessary for UNC paths
ifeq ($(OS),Windows_NT)
  override MATLAB_ROOT := $(subst \,/,$(MATLAB_ROOT))
endif

# if SLDRTDIR contains spaces, construct it from MATLAB_ROOT instead
ifneq ($(words $(SLDRTDIR)),1)
  SLDRTDIR := $(MATLAB_ROOT)/toolbox/sldrt
endif

# create a variable that contains a space
EMPTY :=
SPACE := $(EMPTY) $(EMPTY)

# compute RXEXT based on target architecture
RXEXT := $(if $(filter maci64,$(TARGETARCH)),rxm64,$(subst win,rxw,$(TARGETARCH)))

#--------------------------- Model and reference models -----------------------
#
MODELLIB                  := ROBOTlib_sldrt.lib
MODELREF_LINK_LIBS        := 
MODELREF_LINK_RSPFILE     := ROBOT_ref.rsp
MODELREF_INC_PATH         := 
RELATIVE_PATH_TO_ANCHOR   := ..
MODELREF_TARGET_TYPE      := NONE


#------------------------------- OS-specific tools ----------------------------
#
ifeq ($(OS),Windows_NT)
  DELETEFILE = if exist $(1) del /f $(subst /,\,$(1))
  SHELL := cmd
else
  DELETEFILE = rm -f $(1)
endif


#------------------------ External mode ---------------------------------------
#
# To add a new transport layer, see the comments in
#   <matlabroot>/toolbox/simulink/simulink/extmode_transports.m
ifeq ($(EXT_MODE),1)
  EXT_CC_OPTS := -DEXT_MODE
endif


#------------------------------ Include Path -----------------------------
#
# MATLAB includes
REQ_INCLUDES := $(MATLAB_ROOT)/simulink/include;$(MATLAB_ROOT)/extern/include;$(MATLAB_ROOT)/rtw/c/src;$(MATLAB_ROOT)/rtw/c/src/ext_mode/common

# target-specific and compiler-specific includes
REQ_INCLUDES += ;$(MATLAB_ROOT)/toolbox/shared/can/src/scanutil;$(SLDRTDIR)/src

# additional includes
REQ_INCLUDES += ;C:/Users/Robotic/Desktop/ROBOT_~1/ROBOTM~1/新建文~1;$(MATLAB_ROOT)/simulink/include/sf_runtime;C:/Users/Robotic/Desktop/ROBOT_~1/ROBOTM~1/新建文~1/ROBOT_sldrt_win64;$(MATLAB_ROOT)/rtw/c/src/ext_mode/common;$(MATLAB_ROOT)/toolbox/physmod/sm/ssci/c;$(MATLAB_ROOT)/toolbox/physmod/sm/core/c;$(MATLAB_ROOT)/toolbox/physmod/pm_math/c;$(MATLAB_ROOT)/toolbox/physmod/simscape/engine/sli/c;$(MATLAB_ROOT)/toolbox/physmod/simscape/engine/core/c;$(MATLAB_ROOT)/toolbox/physmod/simscape/compiler/core/c;$(MATLAB_ROOT)/toolbox/physmod/network_engine/c;$(MATLAB_ROOT)/toolbox/physmod/common/math/core/c;$(MATLAB_ROOT)/toolbox/physmod/common/lang/core/c;$(MATLAB_ROOT)/toolbox/physmod/common/external/library/c;$(MATLAB_ROOT)/toolbox/physmod/common/foundation/core/c

# shared includes
ifneq ($(SHARED_SRC_DIR),)
  REQ_INCLUDES += ;$(SHARED_SRC_DIR)
endif

INCLUDES := $(USER_INCLUDES);.;$(RELATIVE_PATH_TO_ANCHOR);$(REQ_INCLUDES)$(MODELREF_INC_PATH)


#-------------------------------- Required compiler options ------------------
#
# compiler commands
include $(SLDRTDIR)/rtw/sldrtclang.mk
REQ_OPTS := $(subst ;,$(SPACE)-I,$(INCLUDES))

# linker commands
ifeq ($(CC_LISTING),1)
LINKLISTING = $(LLC) -filetype=asm -x86-asm-syntax=intel -o $(notdir $(basename $@)).asm $(notdir $(basename $@)).bc
endif


#-------------------------------- C Flags --------------------------------
#
OPT_OPTS ?= $(DEFAULT_OPT_OPTS)
COMMON_OPTS := $(REQ_OPTS) $(OPT_OPTS) $(OPTS) $(EXT_CC_OPTS)

REQ_DEFINES := -DUSE_RTMODEL -DMODEL=$(MODEL) -DRT -DNUMST=$(NUMST) \
               -DTID01EQ=$(TID01EQ) -DNCSTATES=$(NCSTATES) \
               -DMT=$(MULTITASKING) $(DEFINES_CUSTOM)

USER_INCLUDES ?=

# form the complete compiler command
CC += $(CLANG_CC_OPTS) $(COMMON_OPTS) $(REQ_DEFINES)
CPP += $(CLANG_CPP_OPTS) $(CPP_OPTS) $(COMMON_OPTS) $(REQ_DEFINES)


#------------------------------- Source Files ---------------------------------
#
# standard target
ifeq ($(MODELREF_TARGET_TYPE),NONE)
  PRODUCT     := $(RELATIVE_PATH_TO_ANCHOR)/$(MODEL).$(RXEXT)
  REQ_SRCS    := $(MODEL).$(TARGET_LANG_EXT) $(MODULES) \
                 sldrt_main.c rt_sim.c

ifeq ($(EXT_MODE),1)
  REQ_SRCS    += ext_svr.c updown_sldrt.c 
endif

# model reference target
else
  PRODUCT  := $(MODELLIB)
  REQ_SRCS := $(MODULES)
endif

SRCS := $(REQ_SRCS) $(USER_SRCS) $(S_FUNCTIONS)
SRCS += $(SOLVER)
OBJS := $(patsubst %.c,%.obj,$(patsubst %.cpp,%.obj,$(SRCS)))

SHARED_OBJS := $(addsuffix .obj, $(basename $(wildcard $(SHARED_SRC))))


#---------------------------- Additional Libraries ----------------------------
#
LIBS := 

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/sm_ssci_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/sm_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/pm_math_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/ssc_sli_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/ssc_core_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/ne_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/mc_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/ex_sldrt.lib

LIBS += $(MATLAB_ROOT)/toolbox/sldrt/lib/win64/pm_sldrt.lib




#-------------------------- Rules ---------------------------------------
#
# decide what should get built
.DEFAULT_GOAL := $(if $(filter 1,$(REBUILD_ALL)), rebuild, $(PRODUCT))

# rule to rebuild everything unconditionally
.PHONY : rebuild
rebuild :
	$(MAKE) -B -f $(MAKEFILE) REBUILD_ALL=0

# libraries to link with the executable
ALLLIBS := $(strip $(LIBS) $(SHARED_LIB) $(MODELREF_LINK_LIBS))

# rules for linking the executable or modelref static library
ifeq ($(MODELREF_TARGET_TYPE),NONE)
$(PRODUCT) : $(OBJS) $(ALLLIBS)
	$(LINK) \
          -Bstatic \
	  -o $(notdir $(basename $@)).bc \
	  $(strip $(OBJS)) \
	  $(strip $(wildcard $(SHARED_OBJS))) \
	  $(strip $(ALLLIBS)) \
	  $(SLDRTDIR)/lib/$(TARGETARCH)/imports.obj \
	  $(SLDRTDIR)/lib/$(TARGETARCH)/sldrtlib.lib
	$(LLC) -filetype=obj -o $@ $(notdir $(basename $@)).bc
	$(LINKLISTING)
	$(info ### Created Simulink Desktop Real-Time module $(notdir $@))
else
$(PRODUCT) : $(OBJS) $(SHARED_LIB)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(OBJS)
	$(info ### Created static library $@)
endif

# object build macros
CC_CPP := $(if $(filter cpp,$(TARGET_LANG_EXT)),$(CPP),$(CC))
define BUILDOBJ
	$(info ### Compiling $<)
	$(1) -o "$@" "$<"
	$(CCLISTING)
endef

# rules for compiling objects
sldrt_main.obj : $(SLDRTDIR)/src/sldrt_main.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC_CPP))

%.obj : $(SLDRTDIR)/src/%.c
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.c
	$(call BUILDOBJ, $(CC))

%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(call BUILDOBJ, $(CC))

%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(call BUILDOBJ, $(CPP))

%.obj : %.c
	$(call BUILDOBJ, $(CC))

%.obj : %.cpp
	$(call BUILDOBJ, $(CPP))

# additional sources
%.obj : $(MATLAB_ROOT)/toolbox/physmod/sm/ssci/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/sm/core/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/pm_math/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/simscape/engine/sli/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/simscape/engine/core/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/simscape/compiler/core/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/network_engine/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/math/core/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/lang/core/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/external/library/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/foundation/core/c/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/simulink/src/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.c $(MAKEFILE)
	$(call BUILDOBJ, $(CC))



%.obj : $(MATLAB_ROOT)/toolbox/physmod/sm/ssci/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/sm/core/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/pm_math/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/simscape/engine/sli/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/simscape/engine/core/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/simscape/compiler/core/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/network_engine/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/math/core/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/lang/core/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/external/library/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/toolbox/physmod/common/foundation/core/c/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/simulink/src/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))

%.obj : $(MATLAB_ROOT)/rtw/c/src/ext_mode/common/%.cpp $(MAKEFILE)
	$(call BUILDOBJ, $(CPP))



# simulink/src helper files
%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(call BUILDOBJ, $(CC))

%.obj : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(call BUILDOBJ, $(CPP))

# model-referencing shared objects
$(SHARED_BIN_DIR)/%.obj : $(SHARED_SRC_DIR)/%.c 
	$(call BUILDOBJ, $(CC))

$(SHARED_BIN_DIR)/%.obj : $(SHARED_SRC_DIR)/%.cpp 
	$(call BUILDOBJ, $(CPP))


# model-referencing shared library
$(SHARED_LIB) : $(SHARED_OBJS)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $^
	$(info ### Created shared library $@)


# rules for building libraries



# rules for precompiled libraries
MODULES_sm_ssci := \
	sm_ssci_3dd14f0a.obj \
	sm_ssci_646478c5.obj \
	sm_ssci_916e6db1.obj \
	sm_ssci_b2b6b422.obj \
	sm_ssci_c16a187b.obj \


sm_ssci.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_sm_ssci)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_sm_ssci)
	$(info ### Created precompiled library $@)

MODULES_sm := \
	sm_440126a7.obj \
	sm_6166f1eb.obj \
	sm_62d41fb5.obj \
	sm_67d72683.obj \
	sm_6fbd150d.obj \
	sm_73d210b9.obj \
	sm_9abcb56e.obj \
	sm_b402b573.obj \
	sm_badd8656.obj \
	sm_bc63e36c.obj \
	sm_c0ba649d.obj \
	sm_d3d946fd.obj \
	sm_e8bab6d7.obj \
	sm_efdfa66e.obj \
	sm_f7683dd1.obj \


sm.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_sm)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_sm)
	$(info ### Created precompiled library $@)

MODULES_pm_math := \
	pm_math_1966ea7d.obj \
	pm_math_1ad202b7.obj \
	pm_math_1c69d5b2.obj \
	pm_math_2cdd2951.obj \
	pm_math_3463da5d.obj \
	pm_math_360e4b46.obj \
	pm_math_48bd51fb.obj \
	pm_math_5a01dda4.obj \
	pm_math_646fa971.obj \
	pm_math_a001e9ec.obj \
	pm_math_b7b980b1.obj \
	pm_math_bad43c87.obj \
	pm_math_d1be0f30.obj \
	pm_math_da630bd2.obj \
	pm_math_f760e8f6.obj \


pm_math.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_pm_math)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_pm_math)
	$(info ### Created precompiled library $@)

MODULES_ssc_sli := \
	ssc_sli_0763c151.obj \
	ssc_sli_0bd269e6.obj \
	ssc_sli_360cfd63.obj \
	ssc_sli_43618287.obj \
	ssc_sli_466b08dd.obj \
	ssc_sli_4e028390.obj \
	ssc_sli_51dbd3b5.obj \
	ssc_sli_550a4805.obj \
	ssc_sli_5a0cb974.obj \
	ssc_sli_62d81790.obj \
	ssc_sli_77063d8b.obj \
	ssc_sli_7a618260.obj \
	ssc_sli_7f630b0f.obj \
	ssc_sli_89d0f30a.obj \
	ssc_sli_8a64c4e2.obj \
	ssc_sli_9c030181.obj \
	ssc_sli_c7dda239.obj \
	ssc_sli_dcd66f69.obj \
	ssc_sli_eb0a5702.obj \
	ssc_sli_fa0ce53e.obj \
	ssc_sli_fbdf29da.obj \


ssc_sli.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_ssc_sli)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_ssc_sli)
	$(info ### Created precompiled library $@)

MODULES_ssc_core := \
	ssc_core_01dcc633.obj \
	ssc_core_04da2c69.obj \
	ssc_core_05058dd9.obj \
	ssc_core_06ba68a6.obj \
	ssc_core_09b5fa6e.obj \
	ssc_core_0bd666aa.obj \
	ssc_core_0f019bd9.obj \
	ssc_core_0f0420a6.obj \
	ssc_core_1b0cafd5.obj \
	ssc_core_1c6b0332.obj \
	ssc_core_1fd25120.obj \
	ssc_core_24b4cdee.obj \
	ssc_core_2568b075.obj \
	ssc_core_280c0222.obj \
	ssc_core_2cd54448.obj \
	ssc_core_3169e4b7.obj \
	ssc_core_330acdca.obj \
	ssc_core_37d4ea84.obj \
	ssc_core_40dfdbdc.obj \
	ssc_core_41017299.obj \
	ssc_core_4666b45b.obj \
	ssc_core_48b08af1.obj \
	ssc_core_48b1386a.obj \
	ssc_core_4965213d.obj \
	ssc_core_4ad9135b.obj \
	ssc_core_4db6bd68.obj \
	ssc_core_4db86fcc.obj \
	ssc_core_4e03e39d.obj \
	ssc_core_4e04eecd.obj \
	ssc_core_54d55ae9.obj \
	ssc_core_56b1a2bf.obj \
	ssc_core_59b034b8.obj \
	ssc_core_5d6ba758.obj \
	ssc_core_67d1f118.obj \
	ssc_core_68da074b.obj \
	ssc_core_6b6b89d2.obj \
	ssc_core_6dd833f3.obj \
	ssc_core_73d9c2b7.obj \
	ssc_core_76d825be.obj \
	ssc_core_79dd08ab.obj \
	ssc_core_7a613edb.obj \
	ssc_core_83db8762.obj \
	ssc_core_856738f2.obj \
	ssc_core_8569edc5.obj \
	ssc_core_8a6471dc.obj \
	ssc_core_8d0064b8.obj \
	ssc_core_96061071.obj \
	ssc_core_97d767fe.obj \
	ssc_core_9b6a1dd2.obj \
	ssc_core_9c01d168.obj \
	ssc_core_9dd110ad.obj \
	ssc_core_9fb0e229.obj \
	ssc_core_9fb25b4f.obj \
	ssc_core_a1d393be.obj \
	ssc_core_a4d4c45e.obj \
	ssc_core_a4da1d0a.obj \
	ssc_core_a6b78ccc.obj \
	ssc_core_a867d880.obj \
	ssc_core_a9bf1ff2.obj \
	ssc_core_abd05c18.obj \
	ssc_core_abd5e7b4.obj \
	ssc_core_acb64294.obj \
	ssc_core_acb6462e.obj \
	ssc_core_b1038cbb.obj \
	ssc_core_b10e34f4.obj \
	ssc_core_b2b3b239.obj \
	ssc_core_b402b40d.obj \
	ssc_core_b96ebc21.obj \
	ssc_core_bb0b2992.obj \
	ssc_core_bc648043.obj \
	ssc_core_c3003040.obj \
	ssc_core_c5b050d7.obj \
	ssc_core_c5b63cb2.obj \
	ssc_core_c607b660.obj \
	ssc_core_c8d83e88.obj \
	ssc_core_cab615c8.obj \
	ssc_core_cabdc251.obj \
	ssc_core_cc067f58.obj \
	ssc_core_ce6a84bb.obj \
	ssc_core_d06d763c.obj \
	ssc_core_d3d34d7c.obj \
	ssc_core_d70a6a09.obj \
	ssc_core_d807fa59.obj \
	ssc_core_d9d13dac.obj \
	ssc_core_dcda6edd.obj \
	ssc_core_deb7fd8d.obj \
	ssc_core_e0d0866d.obj \
	ssc_core_e2b61d72.obj \
	ssc_core_e400c1c2.obj \
	ssc_core_ee000fbe.obj \
	ssc_core_ee01086d.obj \
	ssc_core_ee0f0141.obj \
	ssc_core_f9b6dbed.obj \
	ssc_core_fa09e9e6.obj \
	ssc_core_fbd34e62.obj \
	ssc_core_fd6bfe36.obj \
	ssc_core_ff06d9a4.obj \


ssc_core.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_ssc_core)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_ssc_core)
	$(info ### Created precompiled library $@)

MODULES_ne := \
	ne_59b4e14a.obj \


ne.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_ne)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_ne)
	$(info ### Created precompiled library $@)

MODULES_mc := \
	mc_026e4f4b.obj \
	mc_03b98f6f.obj \
	mc_0bd30dee.obj \
	mc_0ed73c49.obj \
	mc_10d4ab75.obj \
	mc_11086079.obj \
	mc_110e6c6c.obj \
	mc_15d12d95.obj \
	mc_15d828ca.obj \
	mc_220ba961.obj \
	mc_2565d6e0.obj \
	mc_2a642f54.obj \
	mc_2bbf87e3.obj \
	mc_2cdc96b4.obj \
	mc_32d501e3.obj \
	mc_32dc008a.obj \
	mc_3b66f800.obj \
	mc_3e66abdf.obj \
	mc_47b8cebe.obj \
	mc_47b91db1.obj \
	mc_4b0301c6.obj \
	mc_4c6117e3.obj \
	mc_51d4094e.obj \
	mc_52623861.obj \
	mc_52688a58.obj \
	mc_53b1fc84.obj \
	mc_550847c3.obj \
	mc_5766048f.obj \
	mc_59b6e413.obj \
	mc_5d65cd86.obj \
	mc_630dda0e.obj \
	mc_67da200d.obj \
	mc_67da4f41.obj \
	mc_6b6d311a.obj \
	mc_6fb1c336.obj \
	mc_7a613aec.obj \
	mc_7bbf41f0.obj \
	mc_7cd58f0b.obj \
	mc_7cdbe436.obj \
	mc_7d0547c8.obj \
	mc_7d099de7.obj \
	mc_7eb21b39.obj \
	mc_81b0ada5.obj \
	mc_81b5717e.obj \
	mc_870ec75e.obj \
	mc_89d597cf.obj \
	mc_90b6aa0a.obj \
	mc_9ab7d9b0.obj \
	mc_9b6376d1.obj \
	mc_9b6c1529.obj \
	mc_a2647600.obj \
	mc_a26bab1a.obj \
	mc_a3b90582.obj \
	mc_a865d1dd.obj \
	mc_af0cc4c9.obj \
	mc_b0de9cbc.obj \
	mc_b362c5eb.obj \
	mc_b7b03d44.obj \
	mc_b96a0bad.obj \
	mc_bb0520ee.obj \
	mc_bdbb9b78.obj \
	mc_c2dbf4b2.obj \
	mc_c8d25d23.obj \
	mc_cab8a1f9.obj \
	mc_d20085b7.obj \
	mc_d9d38185.obj \
	mc_dbbb14d2.obj \
	mc_dcdddfae.obj \
	mc_debb448f.obj \
	mc_e7bc2f1a.obj \
	mc_e969ae87.obj \
	mc_edbf543c.obj \
	mc_ee000fbe.obj \
	mc_efdea3a7.obj \
	mc_f3be157c.obj \
	mc_fcb15a9b.obj \
	mc_fd619d14.obj \
	mc_fd6341bb.obj \


mc.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_mc)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_mc)
	$(info ### Created precompiled library $@)

MODULES_ex := \
	ex_04d5441d.obj \
	ex_076caee1.obj \
	ex_09b84ed2.obj \
	ex_136645f8.obj \
	ex_18b4440a.obj \
	ex_2ebcd5b2.obj \
	ex_316a81de.obj \
	ex_40d5be33.obj \
	ex_436c54cf.obj \
	ex_47b11894.obj \
	ex_53ba9332.obj \
	ex_5d6f13be.obj \
	ex_690b7cd0.obj \
	ex_79d100f1.obj \
	ex_8a6fc761.obj \
	ex_b2b40ad5.obj \
	ex_b7b137d8.obj \
	ex_bb0efd4b.obj \
	ex_d4b33b97.obj \
	ex_debffef2.obj \
	ex_e40d74b8.obj \
	ex_f3b1cdf6.obj \
	ex_f866102d.obj \


ex.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_ex)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_ex)
	$(info ### Created precompiled library $@)

MODULES_pm := \
	pm_09bc42e2.obj \
	pm_14098e54.obj \
	pm_26dc3230.obj \
	pm_4fd5f5b9.obj \
	pm_fed8c2c9.obj \


pm.lib : $(MAKEFILE) rtw_proj.tmw $(MODULES_pm)
	@$(call DELETEFILE,$@)
	$(LIBTOOL) $@ $(MODULES_pm)
	$(info ### Created precompiled library $@)


