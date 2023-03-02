## user info
# USER:=$(shell id -u -n)
# GROUP:=$(shell id -g -n)

## Docker variables
DOCKERFILE:=docker/Dockerfile
DOCKERTAG:=lambda-cpp-runtime

## Makefile variables
TARGET:=cpp-sample-get cpp-sample-post

.PHONY: all clean force compiler-build sam-build sam-test build push full $(TARGET) 

all: build

clean: $(subdirs)
	@echo "clean current directory & sub-directories"

force:

compiler-build: force
	docker image build -t $(DOCKERTAG) -f $(DOCKERFILE) .

sam-build: force
	for package in $(TARGET); do cp ./src/scripts/Dockerfile ./src/$${package}; done
	sam build
	for package in $(TARGET); do rm ./src/$${package}/Dockerfile; done

sam-test: force
	sam local invoke CppSampleGet

build: $(TARGET) sam-build

push: 
	./aws/update.sh

test: 
	./aws/test.sh

full: build push test

define handler-build
$1: force
	cp ./src/scripts/CMakeLists.txt ./src/$1
	docker container run --rm -v $(abspath ./src/$1):/src $(DOCKERTAG) aws-lambda-package-handler
	rm ./src/$1/CMakeLists.txt
endef
$(foreach api, $(TARGET), $(eval $(call handler-build,$(api))))



