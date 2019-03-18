# Dockerfile for tag docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/buildroot-env:1.0.0
# Contains dependencies required for building linux with buildroot
FROM docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/riscv-env:1.0.0

# ENV LANG=en_US.UTF-8
# ENV LC_ALL=en_US.UTF-8

USER root

ENV DEBIAN_FRONTEND noninteractive

# Install dependencies
RUN /usr/share/debconf/fix_db.pl && \
  apt-get update && \
  apt-get install -y \
  locales \
  sudo \
  # Mandatory packages
  bash bc binutils build-essential bzip2 cpio file g++ gcc \
  gzip make patch perl python rsync sed tar unzip wget \
  # Optional packages
  asciidoc cvs dblatex git graphviz gtk2.0 libglib2.0-dev \
  libncurses5-dev mercurial openssh-client python-glade2 \
  python-matplotlib qt4-default subversion w3m \
  && \
  rm -rf /var/lib/apt/lists/* && \
  locale-gen en_US.UTF-8 && \
  useradd -ms /bin/bash rose && \
  usermod -aG sudo rose && \
  echo "rose:Docker!" | chpasswd

VOLUME /project
WORKDIR /project

# Switch to non-root user
USER rose

CMD bash
