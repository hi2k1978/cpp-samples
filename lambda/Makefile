## SELF
UID:=$(shell id -u)
GID:=$(shell id -g)

## Docker variables
DOCKER_FILE:=docker/Dockerfile
DOCKER_TAG:=lambda-cpp-runtime:latest
DOCKER_SRCDIR:=$(abspath .)
DOCKER_WORKDIR:=/tmp/src

## Makefile variables
# TARGET:=CppSamplesGet
TARGET:=CppSamplesGet CppSamplesPost

# ARGS
ARGS:=

all: build
.PHONY : all

clean: 
	@echo "clean current directory & sub-directories"
	@# for dir in $(TARGET); do sudo rm -rf ./src/$$dir/build; done
	@rm -rf ./build
.PHONY : clean

force:
.PHONY : force

show:
	@echo
	@echo Makefile Variables
	@echo ==================
	@echo "UID: " $(UID)
	@echo "GID: " $(GID)
	@echo "DOCKER_FILE: " $(DOCKER_FILE)
	@echo "DOCKER_TAG: " $(DOCKER_TAG)
	@echo "DOCKER_SRCDIR: " $(DOCKER_SRCDIR)
	@echo "DOCKER_WORKDIR: " $(DOCKER_WORKDIR)
	@echo "TARGET: " $(TARGET)
	@echo
.PHONY : show

lint:
	$(eval target:=$(wildcard src/**/*.h) $(wildcard src/**/*.cpp)) 
	cpplint $(target)
.PHONY : lint

# compiler
compiler-build: force
	docker image build -t $(DOCKER_TAG) -f $(DOCKER_FILE) .
.PHONY : compiler-build

compiler-clean: force
	docker image rm -f $(DOCKER_TAG)
.PHONY : compiler-clean

compiler-rebuild: compiler-clean compiler-build
.PHONY : compiler-rebuild
# build
build-binary:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) all # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-binary

build-tests:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) aws-lambda-test # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-tests

build-packages:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) aws-lambda-package # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-packages

build: build-tests
.PHONY : build

rebuild: clean build
.PHONY : rebuild

# deploy
deploy: build-packages
	./aws/deploy.sh
.PHONY : deploy

## EXAMPLES
# $ ./google-test --gtest_filter=*CppLambda.*
# example: make test ARGS="--gtest_filter=*__CppLambda.*"
test:
	@echo
	@echo "################################################################"
	@echo "  RUN TEST"
	@echo "################################################################"
	@echo
	@echo "ARGS: $(ARGS)"
	@echo "TEST TYPE:"
	@echo "  [N]: Normal"
	@echo "  [Q]: Quasi-normal"
	@echo "  [A]: Abnormal"
	@echo
	@echo
	./build/tests/cpptest $(ARGS)
	@echo
	@echo "################################################################"
	@echo "if you want to run specific tests, use gtest_filter"
	@echo "EX: make test ARGS=\"--gtest_filter=*_Example.*\""
	@echo "################################################################"
	@echo
.PHONY : test


define sam-invoke-resource
sam-invoke-$1-options: force
	$(eval event:=$(wildcard ls ./events/event-$1-options.json))
ifeq ($(event), ./events/event-$1-options.json)
	@echo $1 ": OPTIONS"
	@echo "================================"
	@sam local invoke --event $(event) $1 2> /dev/null
	@echo 
	@echo 
endif
.PHONY : sam-invoke-$1-options

sam-invoke-$1-get: force
	$(eval event:=$(wildcard ls ./events/event-$1-get.json))
ifeq ($(event), ./events/event-$1-get.json)
	@echo $1 ": GET"
	@echo "================================"
	@sam local invoke --event $(event) $1 2> /dev/null
	@echo 
	@echo 
endif
.PHONY : sam-invoke-$1-get

sam-invoke-$1-post: force
	$(eval event:=$(wildcard ls ./events/event-$1-post.json))
ifeq ($(event), ./events/event-$1-post.json)
	@echo $1 ": POST"
	@echo "================================"
	@sam local invoke --event $(event) $1 2> /dev/null
	@echo 
	@echo 
endif
.PHONY : sam-invoke-$1-post

sam-invoke-$1: sam-invoke-$1-options sam-invoke-$1-get sam-invoke-$1-post force
.PHONY : sam-invoke-$1
endef
$(foreach resource, $(TARGET), $(eval $(call sam-invoke-resource,$(resource))))

# sam-invoke: build-packages $(addprefix sam-invoke-,$(addsuffix -options,$(TARGET)) $(addsuffix -get,$(TARGET)) $(addsuffix -post,$(TARGET)))
# .PHONY : sam-invoke
sam-invoke-options: $(addprefix sam-invoke-,$(addsuffix -options,$(TARGET)))
.PHONY : sam-invoke-options
sam-invoke-get: $(addprefix sam-invoke-,$(addsuffix -get,$(TARGET)))
.PHONY : sam-invoke-get
sam-invoke-post: $(addprefix sam-invoke-,$(addsuffix -post,$(TARGET)))
.PHONY : sam-invoke-post
sam-invoke: build-packages sam-invoke-options sam-invoke-get sam-invoke-post
.PHONY : sam-invoke



