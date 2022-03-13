
include ./lfp_rules.make
include ./build.config

ALL_DIR = $(build_src-y) $(LFP_EXEC_DIR)

all: make_env $(ALL_DIR)

all_clean := $(addprefix __clean__, $(ALL_DIR))

make_env: FORCE
	$(shell if [ ! -d $(LFP_OBJ_PATH) ];then mkdir -p $(LFP_OBJ_PATH); fi)

$(ALL_DIR):building_steps FORCE
	cd $@ && make

building_steps:FORCE 
	@echo "Compiling " $(ALL_DIR) "..." 
	
$(LFP_EXEC_DIR): building_main FORCE
	make -C $@
	@echo "Packing " $(LFP_EXEC_DIR) "successfully √ √ √ √ √ √ √ √ √ ＜（＾－＾）＞" 

building_main:FORCE
	@echo "Packing " $(LFP_EXEC_DIR) "..." 
	
clean:FORCE
	make clean_all_objs

clean_all_objs: $(all_clean) FORCE

$(all_clean): FORCE
	cd $(patsubst __clean__%, , $@) && make clean

FORCE:

.PHONY:
	all make_env building_steps building_main clean clean_all_objs FORCE

	
	
	
