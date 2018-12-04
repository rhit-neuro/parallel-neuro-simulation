# Dockerfile for tag rhneuroprocessor/rocket-chip-env:1.0.0_dev01
# docker build . -t rhneuroprocessor/rocket-chip-env:1.0.0_dev01
FROM ubuntu:artful

# Install dependencies
RUN \
  apt-get update && \
  apt-get upgrade -y && \
  apt-get install -y \
  # riscv-tools dependencies
  g++=4:7.2.0-1ubuntu1 \
  make \
  unzip \
  autoconf \
  automake \
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
  libtool \
  libusb-1.0-0-dev \
  patchutils \
  pkg-config \
  texinfo \
  zlib1g-dev \
  git \
  default-jdk wget && \
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
  # Revert riscv-fesvr version so it supports +disk option
  # This hash comes from riscv-poky at cd3cba2bb49b9366ed10f2b81bffed071da5dc85
  # In the riscv-fesvr recipe at riscv-poky/meta-riscv/recipes-devtools/riscv-tools/riscv-fesvr.bb
  cd $TOP/riscv-tools/riscv-fesvr && \
  git checkout 'f683e01542acf60e50774d061bcb396b628e3e67' && \
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
  # This is not how to test the binary
#  spike pk hello && \
  rm hello && \
  riscv64-unknown-linux-gnu-g++ -o hello hello.c && \
  # This is not how to test the binary;
#  spike pk hello && \
  rm hello hello.c

VOLUME /project
WORKDIR /project

CMD bash
