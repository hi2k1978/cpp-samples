## user info
USER:=$(shell id -u -n)
GROUP:=$(shell id -g -n)

## Docker variables
DOCKERFILE:=docker/Dockerfile
DOCKERTAG:=lambda-cpp-runtime
DOCKERARGS:=aws-lambda-package-api

## Makefile variables
TARGET:=apigw

.PHONY: all clean force docker-build build push $(TARGET)

all: build

clean: $(subdirs)
	@echo "clean current directory & sub-directories"

force:

image-build: force
	docker image build -t $(DOCKERTAG) -f $(DOCKERFILE) .

build: $(TARGET)

define template
$1: force
	docker container run --rm -v $(abspath ./src/$1):/src $(DOCKERTAG) $(DOCKERARGS)
endef
$(foreach api, $(TARGET), $(eval $(call template,$(api))))

push: 



