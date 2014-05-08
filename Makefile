
TOP_DIR := $(shell pwd)

COMMON_DIR  := $(TOP_DIR)/common
INCLUDE_DIR := $(TOP_DIR)/include
INSTALL_DIR := $(TOP_DIR)/_install


CXX_SURFIX   := cpp
FORCE_STATIC :=

CROSS_PREFIX :=
CXX := $(CROSS_PREFIX)g++
CC  := $(CROSS_PREFIX)gcc
AR  := $(CROSS_PREFIX)ar
STRIP := $(CROSS_PREFIX)strip

CFLAGS   += -Wall
CPPFLAGS += -I$(INCLUDE_DIR)
CXXFLAGS += $(FORCE_STATIC) -Wall -lc
#CXXFLAGS += -g $(FORCE_STATIC) -Wl,--whole-archive -lpthread -Wl,--no-whole-archive -lc
LDFLAGS  :=

C_SRC    := $(shell find $(TOP_DIR) -maxdepth 4 -name '*.c')
C_OBJS   := $(C_SRC:%.c=%.o)
CXX_SRC    := $(shell find $(TOP_DIR) -maxdepth 4 -name '*.$(CXX_SURFIX)')
CXX_OBJS := $(CXX_SRC:%.$(CXX_SURFIX)=%.o)

TARGET := jpeg.tools

.PHONY: all
all : $(TARGET)

.PHONY: install
install : all
	@mkdir -p $(INSTALL_DIR)

.PHONY: clean
clean :
	@rm -f $(C_OBJS) $(CXX_OBJS) $(TARGET)

.PHONY: distclean
distclean : clean
	@rm -rf $(INSTALL_DIR)


$(C_OBJS):%.o:%.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(CXX_OBJS):%.o:%.$(CXX_SURFIX)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(TARGET): $(C_OBJS) $(CXX_OBJS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(FORCE_STATIC) $^ -o $@ $(LDFLAGS)

