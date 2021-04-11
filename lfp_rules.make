LFP_CROSS_COMPILER_PREFIX :=
LFP_CC = ${LFP_CROSS_COMPILER_PREFIX}gcc
LFP_AR = ar
LFP_AR_FLAGS = -rc
LFP_MAKE = make
LFP_GLOBAL_FLAGS = -g -W -O1 -Wall

LFP_OBJDIR = objs
LFP_EXEC = lfp_core
LFP_EXEC_DIR = lfp_exec
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst ${LFP_PRJ_NAME},${LFP_PRJ_NAME} ,$(shell pwd)))
export LFP_ROOT_PATH LFP_PRJ_NAME
LFP_OBJ_PATH = $(LFP_ROOT_PATH)/$(LFP_EXEC_DIR)/$(LFP_OBJDIR)
LFP_EXEC_PATH = $(LFP_ROOT_PATH)/$(LFP_EXEC_DIR)/$(LFP_EXEC)

include $(LFP_ROOT_PATH)/menuconfig

define lfp_auto_generate_linking
	@echo "my name is "
endef