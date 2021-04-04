ifeq ($(LFP_PRJ_NAME)$(LFP_ROOT_PATH),)
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst ${LFP_PRJ_NAME},${LFP_PRJ_NAME} ,$(shell pwd)))
endif
include ${LFP_ROOT_PATH}/lfp_rules.make

CUR_PATH = $(shell pwd)

#lib single list
ifeq ($(LFP_LIBS_SLIST),y)
CUR_SRC_PATH = $(CUR_PATH)/lfp_libs_slist
endif

#lib double list
ifeq ($(LFP_LIBS_DLIST),y)
CUR_SRC_PATH += $(CUR_PATH)/lfp_libs_dlist
endif

#lib socket
ifeq ($(LFP_LIBS_SOCKET),y)
CUR_SRC_PATH += $(CUR_PATH)/lfp_libs_socket
endif

#lib socket
ifeq ($(LFP_LIBS_THREADPOOL),y)
CUR_SRC_PATH += $(CUR_PATH)/lfp_libs_threadpool
endif

#lib safe c
CUR_SRC_PATH += $(CUR_PATH)/lfp_libs_safec

#lib open sources
CUR_SRC_PATH += $(CUR_PATH)/lfp_libs_open_sources

$(CUR_SRC_PATH) = ? || exit -1;

lfp_app_libs = liblfp_app_libs.a

make_app_libs:ECHO_LIBS_DIR
	for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir ; done
	@$(MAKE) lfp_app_libs_assemble
	
ECHO_LIBS_DIR: 
	@echo "Compiling $(CUR_SRC_PATH) ..." 

lfp_app_libs_assemble:$(lfp_app_libs)

$(lfp_app_libs):
	for lib in $(wildcard *.a); do $(LFP_AR) -x $$lib; done
	$(LFP_AR) $(LFP_AR_FLAGS) $@ ./*.o
	cp $@ $(LFP_OBJ_PATH)
	
clean:
	@for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir clean; done
	rm -rf ./*a ./*so ./*.o

	
	
	
