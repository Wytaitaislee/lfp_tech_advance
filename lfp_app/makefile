ifeq ($(LFP_PRJ_NAME)$(LFP_ROOT_PATH),)
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst ${LFP_PRJ_NAME},${LFP_PRJ_NAME} ,$(shell pwd)))
endif
include ${LFP_ROOT_PATH}/lfp_rules.make

CUR_SRC_PATH = lfp_app_busybox lfp_app_libs lfp_app_modules lfp_app_unity_test

apps:$(CUR_SRC_PATH)

$(CUR_SRC_PATH):ECHO_SUB_DIR
	@for dir in $@; do $(MAKE) -C $$dir ; done
	
ECHO_SUB_DIR: 
	@echo "Compiling " $(CUR_SRC_PATH) "..." 
	
clean:
	@for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir clean; done


	
	
	
