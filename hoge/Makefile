CXX=clang++-14
INCLUDE=./include
LIB=./lib

SRC=hoge.cpp
OBJ=hige.o moge.o
CXXFLAGS+=-std=c++20

SUBDIRS:=include lib
BUILDDIR=build

CPPFLAGS+=$(addprefix -I,$(INCLUDE)) $(addprefix -L,$(LIB))
TARGET:=$(SRC:.cpp=)

.PHONY: all clean $(SUBDIRS) $(TARGET)
all: $(SUBDIRS) $(TARGET)

clean: $(SUBDIRS)
	@echo \rm -rf \#* *~ \.\#* $(TARGET) 

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

$(TARGET): $(SRC) $(addprefix $(LIB)/,$(OBJ))
	-@mkdir $(BUILDDIR) 
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $(addprefix $(BUILDDIR)/, $@)
define template
$@: $^
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
endef
$(foreach src, $(SRC), $(eval $(call template, $(src))))

