FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
  git \
  cmake \
  make \
  g++ \
  zip \
  libcurl4-openssl-dev \
  libssl-dev \
  uuid-dev \
  zlib1g-dev \
  libpulse-dev

WORKDIR /tmp

RUN git clone https://github.com/awslabs/aws-lambda-cpp-runtime.git && \
  cd aws-lambda-cpp-runtime && \
  mkdir build && \
  cd build && \
  # Debug or Release 
  cmake .. -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_INSTALL_PREFIX=~/install && \
  make && make install

RUN git clone https://github.com/aws/aws-sdk-cpp.git && \
  cd aws-sdk-cpp && \
  git checkout main && \
  git pull origin main && \
  git submodule update --init --recursive && \
  mkdir build && \
    cd build && \
  # Debug or Release 
  cmake .. -DBUILD_ONLY="core" \
    -DCMAKE_BUILD_TYPE=Debug \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_UNITY_BUILD=ON \
    -DCUSTOM_MEMORY_MANAGEMENT=OFF \
    -DCMAKE_INSTALL_PREFIX=~/install \
    -DENABLE_TESTING=OFF && \
  make && make install
 
COPY ./docker/run.sh /usr/local/bin/run.sh
RUN chmod +x /usr/local/bin/run.sh

WORKDIR /src
ENTRYPOINT ["run.sh"]
