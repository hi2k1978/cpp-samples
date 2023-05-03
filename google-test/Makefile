BUILDDIR=build
SRCDIR=src
TESTDIR=tests
HANDLER=handler
GTEST=unittest

all: build
.PHONY: all

clean:
	\rm -rf $(BUILDDIR)
.PHONY: clean

build:
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && cmake .. && make
.PHONY: build

test: build
	# ./$(BUILDDIR)/$(SRCDIR)/$(HANDLER)
	./$(BUILDDIR)/$(TESTDIR)/$(GTEST)
.PHONY: test
