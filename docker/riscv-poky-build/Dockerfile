# Dockerfile for tag rhneuroprocessor/riscv-poky-build:2.0.0
# Contains dependencies required for building riscv-poky
FROM ubuntu:xenial

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

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
    useradd -ms /bin/bash riscv_poky_user 

# Switch to non-root user as bitbake prefers to be run by
# non-root user
USER riscv_poky_user

CMD bash
