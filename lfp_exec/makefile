ifeq ($(LFP_ROOT_PATH),)
LFP_ROOT_PATH = ../
endif

include $(LFP_ROOT_PATH)/rules.make

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