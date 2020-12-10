FROM ubuntu:20.04

RUN apt-get update && apt-get install --no-install-recommends -y \
   graphviz \
   doxygen \
   g++ \
   g++-9 \
   && apt-get install -y git \
   valgrind \
   cppcheck \
   make \
   cmake \
   libgtest-dev\
   && cd /usr/src/gtest \
   && cmake CMakeLists.txt \
   && make \
   && ln -st /usr/lib/ /usr/src/gtest/libgtest.a \
   && ln -st /usr/lib/ /usr/src/gtest/libgtest_main.a \
&& rm -rf /var/lib/apt/lists/*