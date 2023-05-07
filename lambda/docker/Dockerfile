FROM ubuntu:22.04
ENV DEBIAN_FRONTEND=noninteractive

# Debug or Release 
# ARG BUILD_TYPE=Debug
ARG BUILD_TYPE=Release
ARG INSTALL_PREFIX=/usr/local

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
    cmake .. -DBUILD_SHARED_LIBS=OFF \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX && \
    make && make install

RUN git clone https://github.com/aws/aws-sdk-cpp.git && \
    cd aws-sdk-cpp && \
    git checkout main && \
    git pull origin main && \
    git submodule update --init --recursive && \
    mkdir build && \
    cd build && \
    cmake .. -DBUILD_ONLY="core" \
    -DBUILD_SHARED_LIBS=OFF \
    -DENABLE_UNITY_BUILD=ON \
    -DCUSTOM_MEMORY_MANAGEMENT=OFF \
    -DENABLE_TESTING=OFF \
    -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
    -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX && \
    make && make install
 
COPY ./docker/run.sh $INSTALL_PREFIX/bin/run.sh
RUN chmod +x $INSTALL_PREFIX/bin/run.sh

WORKDIR /tmp/src
ENTRYPOINT ["run.sh"]
