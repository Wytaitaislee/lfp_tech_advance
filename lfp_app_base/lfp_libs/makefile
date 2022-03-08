ifeq ($(LFP_PRJ_NAME)$(LFP_ROOT_PATH),)
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst $(LFP_PRJ_NAME),$(LFP_PRJ_NAME) ,$(shell pwd)))
endif
include $(LFP_ROOT_PATH)/lfp_rules.make

CUR_PATH = $(shell pwd)

include $(CUR_PATH)/lfp_libs_linking

LIBS_ALL = $(libs_src-y)

$(LIBS_ALL) = ? || exit -1;

libs_all:$(LIBS_ALL)

$(LIBS_ALL):ECHO_LIBS_DIR
	for dir in $@; do $(MAKE) -C $$dir ; done
	
ECHO_LIBS_DIR: 
	@echo "Compiling $(LIBS_ALL) ..." 
	
clean:
	@for dir in $(LIBS_ALL); do $(MAKE) -C $$dir clean; done
	@rm -rf ./*a ./*so ./*.o


	
	
	
