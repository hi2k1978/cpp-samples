## My IDs
UID:=$(shell id -u)
GID:=$(shell id -g)

## Docker variables
DOCKER_FILE:=docker/Dockerfile
DOCKER_TAG:=lambda-cpp-runtime:latest
DOCKER_SRCDIR:=$(abspath .)
DOCKER_WORKDIR:=/tmp/src

## Makefile variables
# LAMBDAS:=CppSamplesGet
LAMBDAS:=CppSamplesGet CppSamplesPost

# ARGS
ARGS:=

all: build
.PHONY : all

clean: 
	@echo "remove ./build"
	@# for lambda in $(LAMBDAS); do sudo rm -rf ./src/$$lambda/build; done
	@rm -rf ./build
.PHONY : clean

show:
	@echo
	@echo Makefile Variable List
	@echo ======================
	@echo UID: $(UID)
	@echo GID: $(GID)
	@echo DOCKER_FILE: $(DOCKER_FILE)
	@echo DOCKER_TAG: $(DOCKER_TAG)
	@echo DOCKER_SRCDIR: $(DOCKER_SRCDIR)
	@echo DOCKER_WORKDIR: $(DOCKER_WORKDIR)
	@echo LAMBDAS: $(LAMBDAS)
	@echo
.PHONY : show

lint:
	$(eval target:=$(wildcard src/**/*.h) $(wildcard src/**/*.cpp)) 
	cpplint $(target)
.PHONY : lint
################################################################
## build compiler
################################################################
compiler-build: 
	docker image build -t $(DOCKER_TAG) -f $(DOCKER_FILE) .
.PHONY : compiler-build

compiler-clean: 
	docker image rm -f $(DOCKER_TAG)
.PHONY : compiler-clean

compiler-rebuild: compiler-clean compiler-build
.PHONY : compiler-rebuild

################################################################
## build lambdas & tests
################################################################
build-binaries:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) all # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-binaries

build-tests:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) build-tests # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-tests

build-packages:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) build-packages # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-packages

build: build-tests
.PHONY : build

rebuild: clean build
.PHONY : rebuild

################################################################
## deploy
################################################################
deploy: build-packages
	./aws/deploy.sh
.PHONY : deploy

################################################################
## run test
################################################################
## EXAMPLES
# $ ./google-test --gtest_filter=*CppLambda.*
# example: make test ARGS="--gtest_filter=*__CppLambda.*"
test:
	@echo
	@echo ################################################################
	@echo   RUN TEST
	@echo ################################################################
	@echo
	@echo ARGS: $(ARGS)
	@echo TEST TYPE:
	@echo   [N]: Normal
	@echo   [Q]: Quasi-normal
	@echo   [A]: Abnormal
	@echo
	@echo
	./build/tests/cpptest $(ARGS)
	@echo
	@echo ################################################################
	@echo if you want to run specific tests, use gtest_filter
	@echo EX: make test ARGS="--gtest_filter=*_Example.*"
	@echo ################################################################
	@echo
.PHONY : test


################################################################
## sam-invoke
################################################################
define sam-invoke-lambda
sam-invoke-options-$1: 
	$(eval event:=$(wildcard ls ./events/event-$1-options.json))
ifeq ($(event), ./events/event-$1-options.json)
	@echo $1 ": OPTIONS"
	@echo "================================"
	@sam local invoke --event $(event) $1 2> /dev/null
	@echo 
	@echo 
endif
.PHONY : sam-invoke-options-$1

sam-invoke-get-$1: 
	$(eval event:=$(wildcard ls ./events/event-$1-get.json))
ifeq ($(event), ./events/event-$1-get.json)
	@echo $1 ": GET"
	@echo "================================"
	@sam local invoke --event $(event) $1 2> /dev/null
	@echo 
	@echo 
endif
.PHONY : sam-invoke-get-$1

sam-invoke-post-$1: 
	$(eval event:=$(wildcard ls ./events/event-$1-post.json))
ifeq ($(event), ./events/event-$1-post.json)
	@echo $1 ": POST"
	@echo "================================"
	@sam local invoke --event $(event) $1 2> /dev/null
	@echo 
	@echo 
endif
.PHONY : sam-invoke-post-$1

sam-invoke-$1: sam-invoke-options-$1 sam-invoke-get-$1 sam-invoke-post-$1
.PHONY : sam-invoke-$1
endef
$(foreach lambda, $(LAMBDAS), $(eval $(call sam-invoke-lambda,$(lambda))))

sam-invoke-options: $(addprefix sam-invoke-options-,$(LAMBDAS))
.PHONY : sam-invoke-options
sam-invoke-get: $(addprefix sam-invoke-get-,$(LAMBDAS))
.PHONY : sam-invoke-get
sam-invoke-post: $(addprefix sam-invoke-post-,$(LAMBDAS))
.PHONY : sam-invoke-post
sam-invoke: build-packages sam-invoke-options sam-invoke-get sam-invoke-post
.PHONY : sam-invoke



