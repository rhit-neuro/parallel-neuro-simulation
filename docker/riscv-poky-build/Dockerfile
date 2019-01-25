# Dockerfile for tag docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/riscv-poky-build:2.1.0
# Contains dependencies required for building riscv-poky
FROM ubuntu:xenial

ENV LANG=en_US.UTF-8
ENV LC_ALL=en_US.UTF-8

# Install dependencies
RUN apt-get update && \
    apt-get install -y \
    bzip2 \
    chrpath \
    cpio \
    cpp \
    diffstat \
    g++ \
    gawk \
    gcc \
    git \
    # iproute2 for ip
    iproute2 \
    # iputils-ping for ping
    iputils-ping \
    locales \
    make \
    python \
    python3 \
    repo \
    # texinfo for makeinfo
    texinfo \
    wget \
    && \
    rm -rf /var/lib/apt/lists/* && \
    locale-gen en_US.UTF-8 && \
    locale && \
    useradd -ms /bin/bash rose && \
    usermod -aG sudo rose && \
    echo "rose:Docker!" | chpasswd

VOLUME /project
WORKDIR /project

# Switch to non-root user as bitbake prefers to be run by
# non-root user
USER rose

CMD bash
