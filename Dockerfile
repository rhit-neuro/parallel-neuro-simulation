FROM ubuntu:artful

# Install dependencies
RUN \
  apt-get update && \
  apt-get upgrade -y && \
  apt-get install gcc-7 g++-7 autoconf automake libtool curl make unzip cmake libboost-all-dev=1.62.0.1 git -y && \
  update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 60 --slave /usr/bin/g++ g++ /usr/bin/g++-7

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
