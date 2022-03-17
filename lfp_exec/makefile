# 1. loading building configs
include make.config

# 2. Compile params
CPPFLAGS := $(MODULE_INCLUDE_DIR)
CFLAGS := $(LFP_GLOBAL_FLAGS)
ifeq ($(TARGET_TYPE), .so)
    CFLAGS += -fPIC
endif

# 3. Compile dependencies
LDFLAGS :=
ifneq ($(MODULE_DEPS_DIR)$(MODULE_DEPS_LIBS),)
    LDFLAGS := -L$(MODULE_DEPS_DIR) $(MODULE_DEPS_LIBS)
endif

# 4. objs
SRCS := $(foreach dir, $(MODULE_SRC_DIR), $(wildcard $(dir)/*))
C_SRCS := $(filter %.c, $(SRCS))
C_OBJS := $(C_SRCS:%.c=%.o)
CPP_SRCS := $(filter %.cpp, $(SRCS))
CPP_OBJS := $(CPP_SRCS:%.cpp=%.o)
MODULE_CLEAN_SUB_DIRS := $(addprefix __clean__, $(MODULE_SUB_DIRS))

TARGET := lib$(TARGET_NAME)$(TARGET_TYPE)

# 5. building
build: $(TARGET)

$(TARGET):$(C_OBJS) $(CPP_OBJS) FORCE
# 5.1 .a objs building template
ifeq ($(TARGET_TYPE), .a)
	$(MAKE) sublibs
	$(LFP_AR) $(LFP_AR_FLAGS) $@ $(C_OBJS) $(CPP_OBJS)
	$(LFP_RANLIB) $@
	cp $@ $(LFP_OBJ_PATH)

# 5.2 .so objs building template
else ifeq ($(TARGET_TYPE), .so)
	$(MAKE) sublibs
	$(LFP_CC) -shared -fPIC -o $@ $(C_OBJS) $(CPP_OBJS) $(LDFLAGS)
	cp $@ $(LFP_OBJ_PATH)

# 5.3 .exe objs building template
else ifeq ($(TARGET_TYPE), .exe)
	$(MAKE) sublibs
	$(LFP_CC) -o $@ $(CPPFLAGS) $(CFLAGS) $(CPP_OBJS) $(C_OBJS) $(LDFLAGS)
	$(LFP_STRIP) $@
	$(LFP_STRIP) -x -R .note -R .comment $@
	cp $@ $(LFP_EXEC_PATH)
	@echo -e "\n make $(TARGET) successfully (●'◡'●) !!!!!!"

else
	$(error target type[$(TARGET_TYPE)] not supported !!!)
endif

sublibs:$(MODULE_SUB_DIRS) FORCE
	@echo "start building $(TARGET)."
sublibs_clean:$(MODULE_CLEAN_SUB_DIRS) FORCE
	@echo "cleanup $(TARGET)."

$(MODULE_SUB_DIRS):FORCE
	cd $@ && make

$(MODULE_CLEAN_SUB_DIRS):FORCE
	cd $(patsubst __clean__%, %, $@) && make clean

%.o:%.c
	$(LFP_CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $^

%.o:%.cpp
	$(LFP_CXX) $(CPPFLAGS) $(CFLAGS) -c -o $@ $^
	
clean:
	@$(MAKE) sublibs_clean
	@rm -f $(TARGET)
	@rm -f $(CPP_OBJS) $(C_OBJS)
	@rm -f $(LFP_OBJ_PATH)/$(TARGET)

help:
	$echo 'make        -- Building target'
	$echo 'make clean  -- Building target'

FORCE:

.PHONY:
	build sublibs sublibs_clean clean help FORCE