#!/bin/bash

if [[ -z "${BUILD_TYPE}" ]]; then
  BUILD_TYPE="Release"
fi

if [[ -z "${FILE}" ]]; then
  echo "A file must be provided"
  exit 1
fi

mkdir -p build
cmake . -B ./build -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DFILE_ROUTE=$FILE
make -C ./build
