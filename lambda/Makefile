## Docker variables
DOCKERFILE:=docker/Dockerfile
DOCKERTAG:=lambda-cpp-runtime:latest

## Makefile variables
# TARGET:=CppSamplesGet CppSamplesPost
TARGET:=CppSamplesGet

all: build
.PHONY : all

clean: 
	@echo "clean current directory & sub-directories"
	@for dir in $(TARGET); do sudo rm -rf ./src/$$dir/build; done
	ls src/**
.PHONY : clean

force:
.PHONY : force

compiler-build: force
	docker image build -t $(DOCKERTAG) -f $(DOCKERFILE) .
.PHONY : compiler-build

compiler-clean: force
	docker image rm -f $(DOCKERTAG)
.PHONY : compiler-clean

compiler-rebuild: compiler-clean compiler-build
.PHONY : compiler-rebuild

deploy: 
	./aws/deploy.sh
.PHONY : deploy

test: 
	./aws/test.sh
.PHONY : test

full: build push test
.PHONY : full

define build-resource
build-$1: force
	$(eval path:=$(abspath ./src/$1))
	$(eval dest:=/tmp/src)
	cp ./src/scripts/CMakeLists.txt $(path)
	docker container run --rm \
		-v $(path):$(dest) \
		-v $(path)/../include:$(dest)/include \
		-v $(path)/../lib:$(dest)/lib \
		$(DOCKERTAG) aws-lambda-package-handler
	rm $(path)/CMakeLists.txt
.PHONY : build-$1
endef
$(foreach resource, $(TARGET), $(eval $(call build-resource,$(resource))))

build: $(addprefix build-,$(TARGET))
.PHONY : build


define sam-invoke-resource
sam-invoke-$1: force
	sam local invoke --event ./events/event.json $1
.PHONY : sam-invoke-$1
endef
$(foreach resource, $(TARGET), $(eval $(call sam-invoke-resource,$(resource))))

sam-invoke: $(addprefix sam-invoke-,$(TARGET))
.PHONY : sam-invoke
