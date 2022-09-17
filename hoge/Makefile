CXX=clang++-14
INCLUDEDIR=./include
LIBDIR=./lib

SRC=hoge.cpp
OBJ=hige.o moge.o
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

$(TARGET): $(SRC) $(addprefix $(LIBDIR)/,$(OBJ))
	@mkdir -p $(BUILDDIR) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $(addprefix $(BUILDDIR)/, $@)
define template
$@: $^
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
endef
$(foreach src, $(SRC), $(eval $(call template, $(src))))

