dockerfile:=docker/Dockerfile
dockertag:=lambda-cpp-runtime
linuxtag:=linux

.PHONY: all clean force docker-run docker-build apigw

all: svgs pdf

clean: $(subdirs)
	@\rm -f $(pdf) $(html)
	@echo "clean current directory & sub-directories"

force:

docker-build: force
	@sudo docker image build -t $(dockertag) -f $(dockerfile) .

docker-run: apigw
apigw: force
	@sudo docker run --rm -v $(abspath ./src/$@):/src $(dockertag) aws-lambda-package-api
