BUILDDIR=build
SRCDIR=src
TESTDIR=tests
HANDLER=handler
GTEST=test_main

all: build
.PHONY: all

clean:
	\rm -rf $(BUILDDIR)
.PHONY: clean

build:
	mkdir -p $(BUILDDIR)
	cd $(BUILDDIR) && cmake .. && make
.PHONY: build

run:
	@echo
	@echo "################################"
	./$(BUILDDIR)/$(SRCDIR)/$(HANDLER)
.PHONY: run

test:
	@echo
	@echo "################################"
	./$(BUILDDIR)/$(TESTDIR)/$(GTEST)
.PHONY: test
