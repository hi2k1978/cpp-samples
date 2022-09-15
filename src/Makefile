CXX=clang++-14

CXXFLAGS+=-std=c++20
CXXFLAGS+=-lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation

SRC=$(wildcard *.cpp)
TARGET=$(basename $(SRC))

all: $(TARGET)

.PHONY: clean
clean: 
	@\rm -rf \#* *~ \.\#* $(TARGET)

define template
$@: $^
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@
endef
$(foreach src, $(SRC), $(eval $(call template, $(src))))

