FROM public.ecr.aws/lambda/provided:al2 as builder 
# RUN yum install -y gcc gcc-c++
COPY build/handler /var/runtime/bootstrap
RUN chmod +x /var/runtime/bootstrap

WORKDIR /
CMD ["handler"]
