CXX=clang++-14
INCLUDEDIR=./include
LIBDIR=./lib

SRC=hoge.cpp
OBJS=hige.o moge.o
CXXFLAGS+=-std=c++20

SUBDIRS:=include lib
BUILDDIR=build

CPPFLAGS+=$(addprefix -I,$(INCLUDEDIR)) $(addprefix -L,$(LIBDIR))
TARGET:=$(SRC:.cpp=)

.PHONY: all clean $(SUBDIRS) $(TARGET)

all: $(SUBDIRS) $(TARGET) $(TASK2)

clean: $(SUBDIRS)
	@\rm -rf \#* *~ \.\#*

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

$(TARGET): $(SRC) $(addprefix $(LIBDIR)/,$(OBJS))
	@mkdir -p $(BUILDDIR) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $(addprefix $(BUILDDIR)/, $@)

