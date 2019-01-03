# Dockerfile for tag docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/rocket-chip-env:1.0.1
FROM ubuntu:artful as install-vivado

COPY install_config.txt /
ADD Xilinx_Vivado_SDK_2016.2_0605_1.tar.gz /

RUN /Xilinx_Vivado_SDK_2016.2_0605_1/xsetup --agree 3rdPartyEULA,WebTalkTerms,XilinxEULA --batch Install --config /install_config.txt


FROM ubuntu:artful

# Install dependencies
RUN \
  apt-get update && \
  apt-get upgrade -y && \
  apt-get install -y \
  # riscv-tools dependencies
  autoconf \
  automake \
  autotools-dev \
  bc \
  bison \
  build-essential \
  curl \
  default-jdk \
  device-tree-compiler \
  flex \
  gawk \
  git \
  gperf \
  g++=4:7.2.0-1ubuntu1 \
  libgmp-dev \
  libmpc-dev \
  libmpfr-dev \
  libtool \
  libusb-1.0-0-dev \
  make \
  patchutils \
  pkg-config \
  python \
  sudo \
  texinfo \
  unzip \
  wget \
  zlib1g-dev && \
  rm -rf /var/lib/apt/lists/* && \
  useradd -ms /bin/bash rose && \
  usermod -aG sudo rose && \
  echo "rose:Docker!" | chpasswd

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
  # neuro-simulation-env reverts riscv-fesvr version so it supports +disk option
  # don't do this here as it breaks the verilator
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

# Copy Vivado files from first build stage
COPY --from=install-vivado /opt/Xilinx /opt/Xilinx
# Source Vivado's settings in rose user's bashrc
RUN echo "source /opt/Xilinx/Vivado/2016.2/settings64.sh" >> /home/rose/.bashrc

# Fixes 'GLIBCXX_3.4.20 not found' error when running spike
RUN cd /opt/Xilinx/Vivado/2016.2/lib/lnx64.o && \
    mv libstdc++.so.6 libstdc++.so.6.orig && \
    ln -s /usr/lib/x86_64-linux-gnu/libstdc++.so.6  libstdc++.so.6

VOLUME /project
WORKDIR /project

USER rose

CMD bash
