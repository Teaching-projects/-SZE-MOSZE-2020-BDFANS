#!/bin/bash

cd /usr/src/gtest 
cmake CMakeLists.txt 
make 
ln -st /usr/lib/ /usr/src/gtest/libgtest.a 
ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a