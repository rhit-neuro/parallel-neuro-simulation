# Dockerfile for tag 2.0.0-dev
FROM ubuntu:artful

# Install dependencies
RUN \
  apt-get update && \
  apt-get upgrade -y && \
  apt-get install -y \
  # Google Protocol Buffer dependencies
  autoconf \
  automake \
  curl \
  g++=4:7.2.0-1ubuntu1 \
  libtool \
  make \
  unzip \
  # riscv-tools dependencies
# autoconf \ # Already in the dependencies of Google Protocol Buffer, same below
# automake \
  autotools-dev \
  bc \
  bison \
  build-essential \
  curl \
  device-tree-compiler \
  flex \
  gawk \
  gperf \
  libgmp-dev \
  libmpc-dev \
  libmpfr-dev \
#  libtool \
  libusb-1.0-0-dev \
  patchutils \
  pkg-config \
  texinfo \
  zlib1g-dev \
  # Linux target riscv-gcc dependencies
  python \
  libglib2.0-dev \
  # Boost library with riscv-gcc dependencies
#  python-dev \
  # Project dependencies
  gcc=4:7.2.0-1ubuntu1 \
  # Build dependencies
  git cmake \
  # Utilities
  htop && \
  rm -rf /var/lib/apt/lists/*

# Set up RISC-V Toolchain environment variables and directory
ENV TOP /
ENV RISCV /riscv
ENV PATH $PATH:$RISCV/bin
RUN mkdir -p $RISCV

# Build riscv-tools
RUN \
  cd $TOP && \
  git clone https://github.com/riscv/riscv-tools.git && \
  cd $TOP/riscv-tools && \
  git checkout 8ad8d4839acf2cdac0129b8fed8fe12136e77307 && \
  git submodule update --init --recursive && \
  # This hash uses risc-qemu 1.x, which is not compatible with riscv-glibc; manualy bump version
  cd $TOP/riscv-tools/riscv-gnu-toolchain/riscv-qemu && \
  git checkout 'v2.11.1' && \
  cd $TOP/riscv-tools && \
  ./build.sh && \
  # Testing Your Toolchain
  cd $TOP && \
  (echo '#include <stdio.h>\n int main(void) { printf("Hello world!\\n"); return 0; }' > hello.c) && \
  echo 'Testing riscv64-unknown-elf-gcc' && \
  riscv64-unknown-elf-gcc -o hello hello.c && \
  spike pk hello && \
  rm hello && \
  echo 'Testing riscv64-unknown-elf-g++' && \
  riscv64-unknown-elf-g++ -o hello hello.c && \
  spike pk hello && \
  rm hello && \
  # Build riscv-gcc with linux target
  cd $TOP/riscv-tools/riscv-gnu-toolchain && \
  git clean -fxd && \
  git submodule foreach --recursive git clean -fxd && \
  ./configure --prefix=$RISCV && \
  make linux && \
  # Not sure what this does, not required consistently across tutorials
#  make report-linux && \
  cd $TOP && \
  rm -rf riscv-tools && \
  echo 'Testing riscv64-unknown-linux-gnu-gcc' && \
  riscv64-unknown-linux-gnu-gcc -o hello hello.c && \
  # This is not how to test the binary; TODO add script to build riscv-linux
#  spike pk hello && \
  rm hello && \
  riscv64-unknown-linux-gnu-g++ -o hello hello.c && \
  # This is not how to test the binary;
#  spike pk hello && \
  rm hello hello.c

# Update linked library path
ENV LD_LIBRARY_PATH $LD_LIBRARY_PATH:$RISCV/lib

# Install Boost
RUN \
  cd $TOP && \
  git clone --depth 1 --branch 'boost-1.66.0' https://github.com/boostorg/boost.git && \
  cd boost && \
  git submodule update --depth 1 --init --recursive && \
  # Build for gcc
  ./bootstrap.sh --without-libraries=python && \
  ./b2 install && \
  # Build for risc-gcc
  git clean -fxd && \
  git submodule foreach --recursive git clean -fxd && \
  ./bootstrap.sh --prefix=$RISCV --without-libraries=python && \
  echo 'using gcc : : riscv64-unknown-linux-gnu-g++ ;' > tools/build/src/user-config.jam && \
  ./b2 install && \
  cd $TOP && \
  rm -rf boost

## Install Google Protocol Buffer
RUN \
  cd $TOP && \
  git clone --depth 1 --branch 'v3.5.1' https://github.com/google/protobuf.git && \
  cd protobuf && \
  # Build for gcc
  ./autogen.sh && \
  ./configure && \
  make && \
  make check && \
  make install && \
  ldconfig && \
  # Build for risc-gcc
  git clean -fxd && \
  ./autogen.sh && \
  CC=riscv64-unknown-linux-gnu-gcc CXX=riscv64-unknown-linux-gnu-g++ \
    ./configure --prefix=$RISCV --target=riscv64-unknown-linux-gnu --host=x86_64-pc-linux-gnu && \
  # Does not compile for now
#  make && \
#  make check && \
#  make install && \
  cd $TOP && \
  rm -rf protobuf

VOLUME /project
WORKDIR /project

CMD bash
