LFP_ROOT_PATH = $(shell pwd)
export LFP_ROOT_PATH

include ./lfp_rules.make

ALL_DIR = $(libs_src-y)
LINK_OBJS = $(libs_obj-y)

all:$(ALL_DIR) $(LFP_EXEC_DIR)

libs:$(ALL_DIR)

$(ALL_DIR):ECHO_SUB_DIR
	@for dir in $@; do $(MAKE) -C $$dir ; done
	
ECHO_SUB_DIR: 
	@echo "Compiling " $(ALL_DIR) "..." 
	
$(LFP_EXEC_DIR):ECHO_EXEC
	make -C $@
	@echo "Packing " $(LFP_EXEC_DIR) "successfully √ √ √ √ √ √ √ √ √ ＜（＾－＾）＞" 

ECHO_EXEC:
	@echo "Packing " $(LFP_EXEC_DIR) "..." 
	
clean:
	@for dir in $(ALL_DIR); do $(MAKE) -C $$dir clean; done
	@$(MAKE) -C $(LFP_EXEC_DIR) clean

	
	
	
