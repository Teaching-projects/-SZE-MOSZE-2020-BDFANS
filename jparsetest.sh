#!/bin/bash

cmake CMakeLists.txt
make
./jparsetest $1