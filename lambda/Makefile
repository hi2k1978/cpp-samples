## SELF
UID:=$(shell id -u)
GID:=$(shell id -g)

## Docker variables
DOCKER_FILE:=docker/Dockerfile
DOCKER_TAG:=lambda-cpp-runtime:latest
DOCKER_SRCDIR:=$(abspath .)
DOCKER_WORKDIR:=/tmp/src

## Makefile variables
# TARGET:=CppSamplesGet CppSamplesPost
TARGET:=CppSamplesGet

# ARGS
ARGS:=

all: build
.PHONY : all

clean: 
	@echo "clean current directory & sub-directories"
	@for dir in $(TARGET); do sudo rm -rf ./src/$$dir/build; done
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

compiler-build: force
	docker image build -t $(DOCKER_TAG) -f $(DOCKER_FILE) .
.PHONY : compiler-build

compiler-clean: force
	docker image rm -f $(DOCKER_TAG)
.PHONY : compiler-clean

compiler-rebuild: compiler-clean compiler-build
.PHONY : compiler-rebuild

full: build sam-invoke
.PHONY : full

# define build-resource
# build-$1:
# 	$(eval path:=$(abspath ./src/$1))
# 	$(eval dest:=/tmp/src)
# 	docker container run --rm \
# 		-v $(path):$(dest) \
# 		-v $(path)/../include:$(dest)/include \
# 		-v $(path)/../lib:$(dest)/lib \
# 		$(DOCKER_TAG) aws-lambda-package-$1_handler
# 		# $(DOCKER_TAG) all
# .PHONY : build-$1
# endef
# $(foreach resource, $(TARGET), $(eval $(call build-resource,$(resource))))

# build: $(addprefix build-,$(TARGET))
# .PHONY : build
build-source:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) all # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-source

build-test:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) aws-lambda-test # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-test

build-package:
	docker container run --rm \
		-v $(DOCKER_SRCDIR):$(DOCKER_WORKDIR) \
		$(DOCKER_TAG) $(UID) $(GID) aws-lambda-package # CAUTION: Security Risk of Privilege Escalation.
.PHONY : build-package

build: build-source
.PHONY : build

rebuild: clean build
.PHONY : rebuild

deploy: build-package
	./aws/deploy.sh
.PHONY : deploy

## EXAMPLES
# $ ./google-test --gtest_filter=Cpp*Get.hoge-*-hige
test:
	@echo "ARGS: " $(ARGS)
	./build/tests/lambda_test $(ARGS)
.PHONY : test


define sam-invoke-resource
sam-invoke-$1-get: force
	$(eval event:=$(wildcard ls ./events/event-$1-get.json))
ifeq ($(event), ./events/event-$1-get.json)
	sam local invoke --event $(event) $1; 
endif
.PHONY : sam-invoke-$1-get

sam-invoke-$1-post: force
	$(eval event:=$(wildcard ls ./events/event-$1-post.json))
ifeq ($(event), ./events/event-$1-post.json)
	sam local invoke --event ./events/event-$1-post.json $1
endif
.PHONY : sam-invoke-$1-post
endef
$(foreach resource, $(TARGET), $(eval $(call sam-invoke-resource,$(resource))))

sam-invoke: $(addprefix sam-invoke-,$(addsuffix -get,$(TARGET)) $(addsuffix -post,$(TARGET)))
.PHONY : sam-invoke



