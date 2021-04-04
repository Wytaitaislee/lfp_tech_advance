ifeq ($(LFP_PRJ_NAME)$(LFP_ROOT_PATH),)
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst ${LFP_PRJ_NAME},${LFP_PRJ_NAME} ,$(shell pwd)))
endif
include ${LFP_ROOT_PATH}/lfp_rules.make

CUR_OBJS = $(patsubst %.c, %.o, ./)

INCLUDE_PATH := -I${LFP_ROOT_PATH}/lfp_include/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/include/

CUR_SRC_PATH = lfp_app_busybox \
			   lfp_app_libs \
			   
			   #lfp_app_modules \
			   #lfp_app_unity_test

lfp_app = liblfp_app.a

make_app:ECHO_LIBS_DIR
	for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir ; done
	@$(MAKE) lfp_register
	@$(MAKE) lfp_app_assemble
	
ECHO_LIBS_DIR: 
	@echo "Compiling $(CUR_SRC_PATH) ..." 

lfp_register:$(CUR_OBJS)

%.o:%.c
	$(LFP_CC) $(CFLAGS) -c -o $@ $^

lfp_app_assemble:$(lfp_app)

$(lfp_app):
	for lib in $(wildcard *.a); do $(LFP_AR) -x $$lib; done
	$(LFP_AR) $(LFP_AR_FLAGS) $@ ./*.o
	cp $@ $(LFP_OBJ_PATH)
	
clean:
	@for dir in $(CUR_SRC_PATH); do $(MAKE) -C $$dir clean; done
	rm -rf ./*a ./*so ./*.o


	
	
	
