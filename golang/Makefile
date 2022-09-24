CXX=clang++-14

SRCS=$(wildcard *.cpp)
LIBS=PocoUtil PocoXML PocoJSON PocoNet PocoFoundation

BUILDDIR=build
TARGET=$(basename $(SRCS))

CXXFLAGS+=-std=c++20
CXXFLAGS+=$(addprefix -l, $(LIBS))

.PHONY: all clean
all: $(TARGET)

clean: 
	@\rm -rf \#* *~ \.\#*

define template
$(basename $1): $1
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(1) -o $(BUILDDIR)/$(basename $1)
endef
$(foreach src, $(SRCS), $(eval $(call template, $(src))))

