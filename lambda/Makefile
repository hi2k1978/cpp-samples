## user info
USER:=$(shell id -u -n)
GROUP:=$(shell id -g -n)

## Docker variables
DOCKERFILE:=docker/Dockerfile
DOCKERTAG:=lambda-cpp-runtime

## Makefile variables
TARGET:=sample-get sample-post

.PHONY: all clean force docker-build build push full $(TARGET) 

all: build

clean: $(subdirs)
	@echo "clean current directory & sub-directories"

force:

docker-build: force
	docker image build -t $(DOCKERTAG) -f $(DOCKERFILE) .

build: $(TARGET)

push: 
	./aws/update.sh

test: 
	./aws/test.sh

full: build push test

define lambda-build
$1: force
	cp ./src/CMakeLists.txt ./src/${1}
	docker container run --rm -v $(abspath ./src/${1}):/src $(DOCKERTAG) aws-lambda-package-handler
	rm ./src/${1}/CMakeLists.txt
endef
$(foreach api, $(TARGET), $(eval $(call lambda-build,$(api))))

