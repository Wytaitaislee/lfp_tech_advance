ifeq ($(LFP_PRJ_NAME)$(LFP_ROOT_PATH),)
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst ${LFP_PRJ_NAME},${LFP_PRJ_NAME} ,$(shell pwd)))
endif
include ${LFP_ROOT_PATH}/lfp_rules.make

LIBS_PATH = ./$(LFP_OBJDIR)
#CUR_OBJS := $(wildcard $(LIBS_PATH)/*.a)
#CUR_OBJS += $(wildcard $(LIBS_PATH)/*.so)
CUR_OBJS := $(libs_obj-y)
$(warning $(CUR_OBJS))

${LFP_EXEC}:
	$(LFP_CC) $(LFP_GLOBAL_FLAGS) -o $@ -L$(LIBS_PATH) $(CUR_OBJS)
	
clean:
	rm -rf $(LFP_OBJ_PATH)/*
	rm -rf $(LFP_EXEC)