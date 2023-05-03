#! /usr/bin/env bash

if [ $# != 1 ]; then
  echo There is no argument.
  exit 1
fi

mkdir -p build
cd build
cmake --build .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/tmp/install
make
make $1
