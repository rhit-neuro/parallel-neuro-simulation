# riscv-poky-build
This is the Docker image for building `riscv-poky`.
It takes significant amount of space to build and run the image. Building the
reference version of `riscv-poky` uses around 120 GB disk space while a trimmed
down version only uses around 50 GB. Therefore, we only build it
to extract the rootfs and bbl for use with the Spike simulator.
A built copy is in /resources folder. 

## Building riscv-poky
If you need to add any programs to the `riscv-poky`, you will need to re-build
`riscv-poky`. If you keep all the files produced while building `riscv-poky`,
subsequent builts will take much less time than the original build. In order
to build `riscv-poky`, you must first download `riscv-poky`'s build files:
```bash
# cd into a location with ample disk space (e.g. external hard drive)
git clone https://github.com/heidecjj/riscv-poky.git
# the neurosim branch has the right configuration files for building poky for this project
git checkout neurosim
```
Then you must build this docker image or pull it from
the docker hub.
To build this image, run the following commands:
```bash
# cd into this folder first
docker build . -t rhneuroprocessor/riscv-poky-build:some_tag
```
Or you can pull the image from the docker hub:
```bash
docker pull rhneuroprocessor/riscv-poky-build:latest
```
Then to run the image for the first time:
```bash
# <riscv-poky repo location> is where you cloned the riscv-poky repo
docker run -it -v <riscv-poky repo location>:/riscv-poky --name build-poky rhneuroprocessor/riscv-poky-build:latest bash
```
It is best to build `riscv-poky` as a non-root user. If your bash terminal shows `root@<numbers>` instead of `riscv_poky_user@<numbers>` then run:
```bash
su riscv_poky_user
```
Then to start building `riscv-poky` run the following commands:
```bash
cd /riscv-poky
source oe-init-build-env
# the above command should move you into the build dir
bitbake core-image-riscv
```
Note: I had problems with bitbake not being able to start when the hard drive I built
`riscv-poky` on was formatted with exFAT. Reformatting this drive to ext4 fixed my problems.

When `riscv-poky` finishes building, you can find the rootfs and bbl at:
```
ROOTFS: /riscv-poky/build/tmp/deploy/images/riscv64/core-image-riscv-riscv64-<build date and time>.rootfs.ext2
BBL: /riscv-poky/build/tmp/work/riscv64-poky-linux/riscv-pk/1.0-r0/build/bbl
```