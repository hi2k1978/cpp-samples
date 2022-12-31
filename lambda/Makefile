user:=inokuchi
group:=inokuchi
dockerfile:=docker/Dockerfile
dockertag:=lambda-cpp-runtime
linuxtag:=linux
apis=apigw

.PHONY: all clean force docker-run docker-build apigw

all: svgs pdf

clean: $(subdirs)
	@\rm -f $(pdf) $(html)
	@echo "clean current directory & sub-directories"

force:

docker-build: force
	@sudo docker image build -t $(dockertag) -f $(dockerfile) .

docker-run: $(apis)

define template
$1: force
	@sudo docker run --rm -v $(abspath ./src/$1):/src $(dockertag) aws-lambda-package-api
	@sudo chown -R $(user):$(group) ./src/$1/build

endef
$(foreach api, $(apis), $(eval $(call template,$(api))))
