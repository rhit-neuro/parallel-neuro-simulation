# Dockerfile for tag docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/rocket-chip-env:1.1.0
FROM ubuntu:artful as install-vivado

COPY install_config.txt /
ADD Xilinx_Vivado_SDK_2016.2_0605_1.tar.gz /

RUN /Xilinx_Vivado_SDK_2016.2_0605_1/xsetup --agree 3rdPartyEULA,WebTalkTerms,XilinxEULA --batch Install --config /install_config.txt


FROM docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/riscv-env:1.0.0

# Copy Vivado files from first build stage
COPY --from=install-vivado /opt/Xilinx /opt/Xilinx

# Install dependencies
RUN \
  apt-get update && \
  apt-get install -y \
  cpio \
  default-jdk \
  lib32ncurses5 \
  lib32z1 \
  sudo \
  u-boot-tools \
  wget && \
  rm -rf /var/lib/apt/lists/* && \
  wget https://dl.bintray.com/sbt/debian/sbt-1.2.8.deb && \
  dpkg --install sbt-1.2.8.deb && \
  rm -f sbt-1.2.8.deb && \
  useradd -ms /bin/bash rose && \
  usermod -aG sudo rose && \
  echo "rose:Docker!" | chpasswd

# Source Vivado's settings in rose user's bashrc
RUN echo "source /opt/Xilinx/Vivado/2016.2/settings64.sh" >> /home/rose/.bashrc

# Fixes 'GLIBCXX_3.4.20 not found' error when running spike
RUN cd /opt/Xilinx/Vivado/2016.2/lib/lnx64.o && \
    mv libstdc++.so.6 libstdc++.so.6.orig && \
    ln -s /usr/lib/x86_64-linux-gnu/libstdc++.so.6  libstdc++.so.6 && \
    unset LD_LIBRARY_PATH

VOLUME /project
WORKDIR /project

USER rose

CMD bash
