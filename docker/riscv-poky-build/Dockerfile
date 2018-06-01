# Dockerfile for tag rhneuroprocessor/riscv-poky-build:1.0.0
FROM ubuntu:xenial

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# Patch by Nick Kiesel to fix version issues
ADD 01.patch /patches/01.patch
# Path referenced in https://www.mail-archive.com/yocto@yoctoproject.org/msg38119.html to fix SDK build issues
ADD 02.patch /patches/02.patch
# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    git \
    # python is python 2
    python \
    python3 \
    locales \
    bzip2 chrpath cpio cpp diffstat g++ gawk gcc make wget \
    # texinfo for makeinfo
    texinfo \
    # iproute2 for ip
    iproute2 \
    # iputils-ping for ping
    iputils-ping \
    && \
    rm -rf /var/lib/apt/lists/* && \
    locale-gen en_US.UTF-8 && \
    locale && \
    git clone https://github.com/riscv/riscv-poky.git && \
    useradd -ms /bin/bash riscv_poky_user && \
    chown riscv_poky_user riscv-poky -R && \
    cd riscv-poky && \
    git checkout cd3cba2bb49b9366ed10f2b81bffed071da5dc85 && \
    git apply /patches/*.patch && \
    rm -rf /patches/

USER riscv_poky_user
RUN cd /riscv-poky && \
    . /riscv-poky/oe-init-build-env && \
    bitbake core-image-riscv && \
    bitbake meta-toolchain && \
    # Some effort to reduce the image size
    cd /riscv-poky/build && \
    rm -rf cache downloads sstate-cache && \
    cd /riscv-poky/build/tmp && \
    rm -rf cache hosttools sstate-control stamps

USER root

CMD bash
