ifeq ($(LFP_PRJ_NAME)$(LFP_ROOT_PATH),)
LFP_PRJ_NAME = lfp_tech_advance
LFP_ROOT_PATH = $(firstword $(subst ${LFP_PRJ_NAME},${LFP_PRJ_NAME} ,$(shell pwd)))
endif
include $(LFP_ROOT_PATH)/lfp_rules.make

CUR_SRC_PATH = $(shell pwd)/src
CUR_SRC = $(wildcard $(CUR_SRC_PATH)/*.c)
CUR_OBJS = $(patsubst %.c, %.o, $(CUR_SRC))

INCLUDE_PATH := -I${LFP_ROOT_PATH}/lfp_include/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/include/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/lfp_base_util/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/lfp_arch/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/lfp_arch_adapter/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/lfp_arch_adapter/include/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/lfp_app/lfp_app_libs/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/lfp_app/lfp_app_libs/lfp_libs_dlist/
INCLUDE_PATH += -I${LFP_ROOT_PATH}/lfp_include/lfp_app/lfp_app_libs/lfp_libs_threadpool/

CFLAGS = $(LFP_GLOBAL_FLAGS) $(INCLUDE_PATH)

LIB_THREADPOOL = liblfp_libs_threadpool.a

$(LIB_THREADPOOL):$(CUR_OBJS)
	$(LFP_AR) $(LFP_AR_FLAGS) $@ $^
	cp $@ $(LFP_OBJ_PATH)

%.o:%.c
	$(LFP_CC) $(CFLAGS) -c -o $@ $^

clean:
	@for dir in $(CUR_SRC_PATH); do rm -rf $$dir/*.o ; done
	@rm -rf ./*.a
