ifeq ($(LFP_ROOT_PATH),)
LFP_ROOT_PATH = ../../
endif

include $(LFP_ROOT_PATH)/rules.make
CUR_SRC_PATH = $(shell pwd)/src
CUR_SRC = $(wildcard ${CUR_SRC_PATH}/*.c)
CUR_OBJS = $(patsubst %.c, %.o, $(CUR_SRC))

INCLUDE_PATH := -Iinclude
#INCLUDE_PATH += -I../../lfp_include/lfp_arch_adapter/

CFLAGS = $(LFP_GLOBAL_FLAGS) $(INCLUDE_PATH)

LIB_OS = liblfp_arch_linux.a

${LIB_OS}:$(CUR_OBJS)
	$(LFP_AR) $(LFP_AR_FLAGS) $@ $^
	cp $@ $(LFP_OBJ_PATH)

%.o:%.c
	$(LFP_CC) $(CFLAGS) -c -o $@ $^
clean:
	@for dir in $(CUR_SRC_PATH); do rm -rf $$dir/*.o ; done
	@rm -rf ./*.a