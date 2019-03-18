# Dockerfile for tag docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/neuro-simulation-env:2.2.1
FROM docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/riscv-env:1.0.0

# Install dependencies
RUN \
  apt-get update && \
  apt-get install -y \
  # Google Protocol Buffer dependencies
  # autoconf \
  # automake \
  # curl \
  g++=4:7.2.0-1ubuntu1 \
  # libtool \
  # make \
  unzip \
  # Boost library with riscv-gcc dependencies
#  python-dev \
  # Project dependencies
  gcc=4:7.2.0-1ubuntu1 \
  # Build dependencies
  cmake \
  # Utilities
  htop \
  sudo && \
  rm -rf /var/lib/apt/lists/* && \
  useradd -ms /bin/bash rose && \
  usermod -aG sudo rose && \
  echo "rose:Docker!" | chpasswd

# Install Boost
RUN \
  cd $TOP && \
  git clone --depth 1 --branch 'boost-1.65.0' https://github.com/boostorg/boost.git && \
  cd $TOP/boost && \
  git submodule update --init --recursive && \
  # Build for gcc
  ./bootstrap.sh --without-libraries=python && \
  # For source code on GitHub, need to run ./b2 headers before running ./b2 install
  ./b2 headers && \
  ./b2 install && \
  # Build for risc-gcc
  git clean -fxd && \
  git submodule foreach --recursive git clean -fxd && \
  ./bootstrap.sh --prefix=$RISCV --without-libraries=python && \
  echo 'using gcc : : riscv64-unknown-linux-gnu-g++ ;' > tools/build/src/user-config.jam && \
  ./b2 headers && \
  ./b2 install && \
  cd $TOP && \
  rm -rf $TOP/boost

# Install Google Protocol Buffer
RUN \
  cd $TOP && \
  git clone https://github.com/google/protobuf.git && \
  cd $TOP/protobuf && \
  # Since this is not released, we check out a specific commit
  git checkout '7bf47a6b5d10382a4b427677cf7ca9288f4e2833' && \
  git submodule update --init --recursive && \
  # Build for gcc
  ./autogen.sh && \
  ./configure && \
  make && \
  make check && \
  make install && \
  ldconfig && \
  # Build for risc-gcc
  git clean -fxd && \
  git submodule foreach --recursive git clean -fxd && \
  # Set up fake user information to allow git revert
  git config --global user.email "you@example.com" && \
  git config --global user.name "Your Name" && \
  # Revert the commit that upgrades from ACX_PTHREAD to AC_PTHREAD
  git revert 'cab5eae3e0dc8cc13d06b8d94bf4759d14e1c20e' --no-edit && \
  ./autogen.sh && \
  CC=riscv64-unknown-linux-gnu-gcc CXX=riscv64-unknown-linux-gnu-g++ \
    ./configure --prefix=$RISCV --with-protoc=protoc --target=riscv64-unknown-linux-gnu --host=x86_64-pc-linux-gnu && \
  make && \
  # Currently fails checking because protoc itself is cross-compiled
#  make check && \
  make install && \
  cd $TOP && \
  rm -rf $TOP/protobuf

VOLUME /project
WORKDIR /project

USER rose

CMD bash
