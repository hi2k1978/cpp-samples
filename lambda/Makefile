## Docker variables
DOCKERFILE:=docker/Dockerfile
DOCKERTAG:=lambda-cpp-runtime:latest

## Makefile variables
TARGET:=CppSampleGet CppSamplePost

.PHONY: all clean force compiler-build sam-test build push full $(TARGET) 

all: build

clean: $(TARGET)
	@echo "clean current directory & sub-directories"
	@for dir in $(TARGET); do sudo rm -rf ./src/$$dir/build; done
	ls src/**

force:

compiler-build: force
	docker image build -t $(DOCKERTAG) -f $(DOCKERFILE) .

compiler-clean: force
	docker image rm -f $(DOCKERTAG)

compiler-rebuild: compiler-clean compiler-build



deploy: 
	./aws/update.sh

test: 
	./aws/test.sh

full: build push test

define build-resource
build-$1: force
	cp ./src/scripts/CMakeLists.txt ./src/$1
	docker container run --rm -v $(abspath ./src/$1):/tmp/src $(DOCKERTAG) aws-lambda-package-handler
	rm ./src/$1/CMakeLists.txt
endef
$(foreach resource, $(TARGET), $(eval $(call build-resource,$(resource))))

build: $(addprefix build-,$(TARGET))


define sam-invoke-resource
sam-invoke-$1: force
	sam local invoke --event ./events/event.json CppSampleGet
endef
$(foreach resource, $(TARGET), $(eval $(call sam-invoke-resource,$(resource))))

sam-invoke: $(addprefix sam-invoke-,$(TARGET))
