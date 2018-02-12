# Dockerfile for tag 1.2.1
FROM ubuntu:artful

# Install dependencies
RUN \
  apt-get update && \
  apt-get upgrade -y && \
  # Google Protocol Buffer dependencies
  apt-get install -y autoconf automake libtool curl make g++=4:7.2.0-1ubuntu1 unzip \
  # Project dependencies
  gcc=4:7.2.0-1ubuntu1 libboost-all-dev=1.62.0.1 \
  # Build dependencies
  git cmake \
  # Utilities
  htop

# Install Google Protocol Buffer
RUN \
  git clone --branch v3.5.1.1 --depth 1 https://github.com/google/protobuf.git && \
  cd protobuf && \
  ./autogen.sh && \
  ./configure && \
  make && \
  make check && \
  make install && \
  ldconfig && \
  cd .. && \
  rm -rf protobuf

VOLUME /project
WORKDIR /project

CMD bash
