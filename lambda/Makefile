## user info
USER:=$(shell id -u -n)
GROUP:=$(shell id -g -n)

## Docker variables
DOCKERFILE:=docker/Dockerfile
DOCKERTAG:=lambda-cpp-runtime

## Makefile variables
TARGET:=apigw

.PHONY: all clean force docker-build build push $(TARGET)

all: build push

clean: $(subdirs)
	@echo "clean current directory & sub-directories"

force:

docker-build: force
	docker image build -t $(DOCKERTAG) -f $(DOCKERFILE) .

build: $(TARGET)

define lambda-cpp
$1: force
	docker container run --rm -v $(abspath ./src):/src $(DOCKERTAG) aws-lambda-package-$1
endef
$(foreach api, $(TARGET), $(eval $(call lambda-cpp,$(api))))

push: 
	./aws/update.sh



test:
	./aws/test.sh
