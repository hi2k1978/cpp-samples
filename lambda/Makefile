dockerfile:=docker/Dockerfile
dockertag:=lambda-cpp-runtime
linuxtag:=linux

.PHONY: all clean force docker-run docker-build 

all: svgs pdf

clean: $(subdirs)
	@\rm -f $(pdf) $(html)
	@echo "clean current directory & sub-directories"

force:

docker-run: force
	@sudo docker run -dit amazonlinux:latest
docker-build: force
	@sudo docker image build -t $(dockertag) -f $(dockerfile) .

