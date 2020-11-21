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
&& rm -rf /var/lib/apt/lists/*