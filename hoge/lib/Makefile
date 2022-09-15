CXX=clang++-14

CXXFLAGS+=-std=c++20

INCLUDE+=-I../include
SRC=$(wildcard *.cpp)
OBJ=$(SRC:.cpp=.o)
SHARED=libhigemoge.so

.PHONY: all clean 

all: $(TARGET) $(SHARED)

clean:
	@\rm -rf \#* *~ \.\#* *.o *.so

.cpp.o: 
	$(CXX) $(INCLUDE) $(CPPFLAGS) $(CXXFLAGS) -c $<
$(SHARED): $(OBJ)
	$(CXX) $(INCLUDE) $(CPPFLAGS) $(CXXFLAGS) -shared -o $@ $^
