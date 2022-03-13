
include ./make.build

ALL_DIR = $(build_src-y)

all: $(ALL_DIR) building_this

all_clean := $(addprefix __clean__, $(ALL_DIR))

$(ALL_DIR):building_steps FORCE
	cd $@ && make

building_steps:FORCE 
	@echo "Compiling " $(ALL_DIR) "..." 
	
building_this: FORCE
	$(MAKE) -f makefile.this

clean:FORCE
	make clean_all_objs

clean_all_objs: $(all_clean) FORCE

$(all_clean): cleanup_this FORCE
	cd $(patsubst __clean__%, , $@) && make clean

cleanup_this:FORCE
	$(MAKE) -f makefile.this clean

FORCE:

.PHONY:
	all make_env building_steps building_this clean clean_all_objs cleanup_this FORCE

	
	
	
