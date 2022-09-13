CXX=clang++-14

CXXFLAGS+=-std=c++20
CXXFLAGS+=-lPocoUtil -lPocoXML -lPocoJSON -lPocoNet -lPocoFoundation

SRC=$(wildcard *.cpp)
AOUT=$(basename $(SRC))

all: $(AOUT)

clean:
	@\rm -rf \#* *~ $(AOUT)

define template
$(basename $(1)): $(1)
	$(CXX) $(CXXFLAGS) $(1) -o $(basename $(1))
endef
$(foreach src, $(SRC), $(eval $(call template, $(src))))

