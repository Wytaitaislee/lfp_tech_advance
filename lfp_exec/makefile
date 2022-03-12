LFP_ROOT_PATH = $(firstword $(subst lfp_tech_advance,lfp_tech_advance ,$(shell pwd)))
include $(LFP_ROOT_PATH)/lfp_rules.make

include $(LFP_ROOT_PATH)/lfp_rules.make
include $(LFP_ROOT_PATH)/.config

LIBS_PATH = ./$(LFP_OBJDIR)

$(LFP_EXEC):
	$(LFP_CC) $(LFP_GLOBAL_FLAGS) -o $@ -L$(LIBS_PATH) $(LFP_LINK_OBJS)
	
clean:
	@rm -rf $(LFP_OBJ_PATH)/*
	@rm -rf $(LFP_EXEC)