ifeq ($(LFP_PRJ_NAME)$(LFP_ROOT_PATH),)
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst ${LFP_PRJ_NAME},${LFP_PRJ_NAME} ,$(shell pwd)))
endif
include ${LFP_ROOT_PATH}/lfp_rules.make

ifeq ($(LFP_LIBS_SLIST,y)
#lib single list
CUR_SRC_PATH = $(shell pwd)/lfp_libs_slist
endif

ifeq ($(LFP_LIBS_DLIST),y)
#lib double list
CUR_SRC_PATH += $(shell pwd)/lfp_libs_dlist
endif

ifeq ($(LFP_LIBS_SOCKET),y)
#lib socket
CUR_SRC_PATH += $(shell pwd)/lfp_libs_socket
endif

$(CUR_SRC_PATH) = ? || exit -1;

all:make_app_libs

lfp_app_libs = liblfp_app_libs.a

make_app_libs:ECHO_LIBS_DIR
	for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir ; done
	@$(MAKE) lfp_app_libs_assemble
	
ECHO_LIBS_DIR: 
	@echo "Compiling $(shell pwd) ..." 

lfp_app_libs_assemble:$(lfp_app_libs)

$(lfp_app_libs):
	for lib in $(wildcard *.a); do $(LFP_AR) -x $$lib; done
	$(LFP_AR) $(LFP_AR_FLAGS) $@ ./*.o
	cp $@ $(LFP_OBJ_PATH)
	
clean:
	@for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir clean; done
	rm -rf ./*a ./*so ./*.o

	
	
	
