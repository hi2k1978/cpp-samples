#! /usr/bin/env bash

if [ $# != 3 ]; then
  echo There is no argument.
  exit 1
fi

uid=$1
gid=$2
target=$3


mkdir -p build
chown ${uid}:${gid} build
cd build
cmake ..
# cmake --build .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/tmp/install
# cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/tmp/install
# make
make ${target}
cd ..
chown -R ${uid}:${gid} build
