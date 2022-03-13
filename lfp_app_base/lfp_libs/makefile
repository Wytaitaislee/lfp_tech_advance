
include ./build.config

ALL_DIR = $(build_src-y)

all: $(ALL_DIR)

all_clean := $(addprefix __clean__, $(ALL_DIR))

$(ALL_DIR):building_steps FORCE
	cd $@ && make

building_steps:FORCE 
	@echo "Compiling " $(ALL_DIR) "..." 

clean:FORCE
	make clean_all_libs

clean_all_libs: $(all_clean) FORCE

$(all_clean): FORCE
	cd $(patsubst __clean__%, , $@) && make clean

FORCE:

.PHONY:
	all make_env building_steps clean clean_all_libs FORCE

