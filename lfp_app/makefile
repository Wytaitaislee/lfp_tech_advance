LFP_ROOT_PATH = $(firstword $(subst lfp_tech_advance,lfp_tech_advance ,$(shell pwd)))
include $(LFP_ROOT_PATH)/lfp_rules.make

APP_ALL = $(libs_app_src-y)

CUR_OBJS = $(patsubst %.c, %.o, $(wildcard *.c))

INCLUDE_PATH := -I$(LFP_ROOT_PATH)/lfp_include/
INCLUDE_PATH += -I$(LFP_ROOT_PATH)/lfp_include/lfp_util/
INCLUDE_PATH += -I$(LFP_ROOT_PATH)/lfp_include/lfp_app/
INCLUDE_PATH += -I$(LFP_ROOT_PATH)/lfp_include/lfp_app_base/

CFLAGS = $(LFP_GLOBAL_FLAGS) $(INCLUDE_PATH)

#$(APP_ALL) = ? || exit -1;

lfp_app = liblfp_app.a

app_all:$(APP_ALL)

$(APP_ALL):ECHO_SUB_DIR
	@for dir in $@; do $(MAKE) -C $$dir ; done
	@$(MAKE) lfp_app_init
	
ECHO_SUB_DIR: 
	@echo "Compiling " $(APP_ALL) "..." 
	
lfp_app_init:$(CUR_OBJS)
	$(LFP_AR) $(LFP_AR_FLAGS) $(lfp_app) $^
	cp $(lfp_app) $(LFP_OBJ_PATH)

%.o:%.c
	$(LFP_CC) $(CFLAGS) -c -o $@ $^
	
clean:
	@for dir in $(APP_ALL); do $(MAKE) -C $$dir clean; done
	@rm -rf ./*a ./*so ./*.o




	
	
	
