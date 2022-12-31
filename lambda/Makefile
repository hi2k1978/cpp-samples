user:=inokuchi
group:=inokuchi
dockerfile:=docker/Dockerfile
dockertag:=lambda-cpp-runtime
linuxtag:=linux
target=apigw

.PHONY: all clean force docker-run docker-build $(target)

all: docker-run

clean: $(subdirs)
	@\rm -f $(pdf) $(html)
	@echo "clean current directory & sub-directories"

force:

docker-build: force
	@sudo docker image build -t $(dockertag) -f $(dockerfile) .

docker-run: $(target)

define template
$1: force
	@sudo docker run --rm -v $(abspath ./src/$1):/src $(dockertag) aws-lambda-package-api
	@sudo chown -R $(user):$(group) ./src/$1/build

endef
$(foreach api, $(target), $(eval $(call template,$(api))))
