CXX=clang++-14

CXXFLAGS+=-std=c++20

INCLUDE+=-I../include
SRCS=$(wildcard *.cpp)
OBJS=$(SRCS:.cpp=.o)
SHARED=libhigemoge.so

.PHONY: all clean 

all: $(TARGET) $(SHARED)

clean:
	@\rm -rf \#* *~ \.\#* *.o *.so

.cpp.o: 
	$(CXX) $(INCLUDE) $(CPPFLAGS) $(CXXFLAGS) -c $<
$(SHARED): $(OBJS)
	$(CXX) $(INCLUDE) $(CPPFLAGS) $(CXXFLAGS) -shared -o $@ $^
