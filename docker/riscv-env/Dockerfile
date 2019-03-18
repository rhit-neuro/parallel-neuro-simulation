# Dockerfile for tag docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/riscv-env:1.0.0
FROM ubuntu:artful

# Install dependencies
RUN \
  apt-get update && \
  apt-get install -y \
  # riscv-tools dependencies
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
  # Linux target riscv-gcc dependencies
  python \
  libglib2.0-dev \
  # Build dependencies
  git && \
  # Cleanup
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
  # Build riscv-gcc with linux target
  cd $TOP/riscv-tools/riscv-gnu-toolchain && \
  git clean -fxd && \
  git submodule foreach --recursive git clean -fxd && \
  ./configure --prefix=$RISCV && \
  make linux && \
  cd $TOP && \
  rm -rf riscv-tools

CMD bash