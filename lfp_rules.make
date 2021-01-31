LFP_CROSS_COMPILER_PREFIX :=
LFP_CC = ${LFP_CROSS_COMPILER_PREFIX}gcc
LFP_AR = ar
LFP_AR_FLAGS = -rc
LFP_MAKE = make
LFP_GLOBAL_FLAGS = -g -W -O1 -Wall

MAKEFLAGS += -rR --include-dir=$(CURDIR)/lfp_include/include

LFP_OBJDIR = objs
LFP_EXEC = lfp_core
LFP_EXEC_DIR = lfp_exec
LFP_OBJ_PATH = ${LFP_ROOT_PATH}/${LFP_EXEC_DIR}/${LFP_OBJDIR}
LFP_EXEC_PATH = ${LFP_ROOT_PATH}/${LFP_EXEC_DIR}/${LFP_EXEC}

include ${LFP_ROOT_PATH}/menuconfig
include ${LFP_ROOT_PATH}/lfp_linking

LFP_GLOBAL_FLAGS += ${LFP_FLAGS}
