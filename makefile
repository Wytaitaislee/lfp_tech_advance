
libs_src-y :=
libs_obj-y :=
include ./lfp_rules.make
include ./lfp_linking
$(shell rm -rf .config)
$(shell touch .config)

ALL_DIR = $(libs_src-y)
LFP_LINK_OBJS = $(libs_obj-y)
export LFP_LINK_OBJS

all:$(ALL_DIR) $(LFP_EXEC_DIR)

libs:$(ALL_DIR)

$(ALL_DIR):MKDIR_BUILD_OUTPUT ECHO_SUB_DIR
	@for dir in $@; do $(MAKE) -C $$dir; done
	
MKDIR_BUILD_OUTPUT:
	$(shell if [ ! -d $(LFP_OBJ_PATH) ];then mkdir -p $(LFP_OBJ_PATH);fi)

ECHO_SUB_DIR: 
	@echo "Compiling " $(ALL_DIR) "..." 
	
$(LFP_EXEC_DIR): ECHO_EXEC
	make -C $@
	@echo "Packing " $(LFP_EXEC_DIR) "successfully √ √ √ √ √ √ √ √ √ ＜（＾－＾）＞" 

ECHO_EXEC:
	@echo "Packing " $(LFP_EXEC_DIR) "..." 
	
clean:
	@for dir in $(ALL_DIR); do $(MAKE) -C $$dir clean; done
	@$(MAKE) -C $(LFP_EXEC_DIR) clean

	
	
	
