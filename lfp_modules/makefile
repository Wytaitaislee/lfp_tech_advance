ifeq ($(LFP_ROOT_PATH),)
LFP_ROOT_PATH = ../
endif

include $(LFP_ROOT_PATH)/rules.make

ifeq ($(LFP_SINGLE_LIST_MODULE),y)
#lib module single list
CUR_SRC_PATH = $(shell pwd)/lfp_single_list
endif

ifeq ($(LFP_DOUBLE_LIST_MODULE),y)
#lib module single list
CUR_SRC_PATH += $(shell pwd)/lfp_double_list
endif

ifeq ($(LFP_SOCKET_APP),y)
#lib module single list
CUR_SRC_PATH += $(shell pwd)/lfp_socket_app
endif

$(CUR_SRC_PATH) = ? || exit -1;

all:make_modules

lfp_lib_modules = liblfp_modules.a

$(warning ${CUR_SRC_PATH})

make_modules:ECHO_MODULES_DIR
	for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir ; done
	@$(MAKE) lfp_modules
	
ECHO_MODULES_DIR: 
	@echo "Compiling $(shell pwd) ..." 

lfp_modules:$(lfp_lib_modules)

$(lfp_lib_modules):
	for lib in $(wildcard *.a); do $(LFP_AR) -x $$lib; done
	$(LFP_AR) $(LFP_AR_FLAGS) $@ ./*.o
	cp $@ $(LFP_OBJ_PATH)
	
clean:
	@for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir clean; done
	rm -rf ./*a ./*so ./*.o

	
	
	
