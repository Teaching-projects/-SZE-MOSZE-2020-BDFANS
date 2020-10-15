#!/bin/bash

apt install libgtest-dev 
cd /usr/src/gtest 
cmake CMakeLists.txt 
make 
ln -s /usr/lib/ /usr/src/gtest/libgtest.a 
ln -s /usr/lib/ /usr/src/gtest/libgtest_main.a