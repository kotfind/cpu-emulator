.PHONY: default
default: all

# -------------------- Config --------------------
BUILD_TYPE ?= Release
BUILD_DIR ?= build

SRC_DIRS := stack interpreter
INC_DIRS := .
EXEC_SRCS := stack/test.cpp interpreter/main.cpp

CXXFLAGS += -std=c++23

ifeq ($(BUILD_TYPE),Debug)
	CXXFLAGS += -Wall -Wextra -g3 -O0 -fsanitize=undefined,address
	LDFLAGS += -fsanitize=undefined,address
endif

.PHONY: test
test: $(BUILD_DIR)/stack/test
	@echo Running tests...
	@$(BUILD_DIR)/stack/test

.PHONY: interpreter 
run: $(BUILD_DIR)/interpreter/interpreter
	@echo Running interpreter with args = $(ARGS)...
	@$(BUILD_DIR)/interpreter/interpreter $(ARGS)

# -------------------- Internal Variables --------------------
SRCS := $(shell find $(SRC_DIRS) -name *.cpp)
OBJS := $(SRCS:%.cpp=$(BUILD_DIR)/%.o)
DEPS := $(SRCS:%.cpp=$(BUILD_DIR)/%.d)

EXEC_OBJS := $(EXEC_SRCS:%.cpp=$(BUILD_DIR)/%.o)
NO_EXEC_OBJS := $(filter-out $(EXEC_OBJS),$(OBJS))
EXECS := $(EXEC_SRCS:%.cpp=$(BUILD_DIR)/%)

# INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS += $(INC_FLAGS) -MMD -MP

# -------------------- Targets --------------------
.PHONY: all
all: $(EXECS)

.PHONY: clean
clean:
	@echo Cleaning..
	@rm -rf $(BUILD_DIR)

# Recompile when flags change
.PHONY: flags

FLAG_TYPES := CPP CXX LD
FLAG_TARGETS := $(FLAG_TYPES:%=$(BUILD_DIR)/%FLAGS.txt)

$(foreach FLAG_TYPE,$(FLAG_TYPES),$(eval $(FLAG_TYPE)FLAGS_FILE := $(BUILD_DIR)/$(FLAG_TYPE)FLAGS.txt))

$(FLAG_TARGETS): $(BUILD_DIR)/%FLAGS.txt: flags
	@{ \
		mkdir -p $(BUILD_DIR); \
		TMP=$$(mktemp); \
		echo $($*FLAGS) >> $$TMP; \
		cmp -s $$TMP $@ || mv -f $$TMP $@; \
	}

# Compile to binaries
$(EXECS): %: %.o $(NO_EXEC_OBJS) $(LDFLAGS_FILE)
	@echo Compiling $@...
	@$(CXX) $(NO_EXEC_OBJS) $(LDFLAGS) $< -o $@

# Compile to object files
$(BUILD_DIR)/%.o: %.cpp $(CPPFLAGS_FILE) $(CXXFLAGS_FILE)
	@echo Compiling $@...
	@mkdir -p $(dir $@)
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Add header dependencies
-include $(DEPS)
