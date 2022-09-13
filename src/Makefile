CXX=clang++-14

CXXFLAGS+=-std=c++20
CXXFLAGS+=-lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation

SRC=$(wildcard *.cpp)
AOUT=$(basename $(SRC))

all: $(AOUT)

.PHONY: clean
clean:
	@\rm -rf \#* *~ \.\#* $(AOUT)

define template
$@: $^
	$(CXX) $(CXXFLAGS) $^ -o $@
endef
$(foreach src, $(SRC), $(eval $(call template, $(src))))

