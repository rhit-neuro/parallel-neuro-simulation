Dockerfiles
=========

There are currently two docker images we use:
* neuro-simulation-env
* riscv-poky-build

## Making New Images

The commands to build the image and push them to Docker Hub are the following:

```bash
docker build . -t rhneuroprocessor/<image name>:latest
docker tag rhneuroprocessor/<image name>:latest rhneuroprocessor/<image name>:mx.my.mz # mx.my.mz is your new version number
docker push rhneuroprocessor/<image name>:latest
docker push rhneuroprocessor/<image name>:mx.my.mz
```

We use [Semantic Versioning/SemVer](https://semver.org/) scheme to bump the version of the container.
The rules of thumb to bump the version are:
  - If the new image only has new versions of secondary dependencies (dependencies except gcc, Boost, and Protobuf), bump patch
  - If the new image has new versions of primary dependencies (gcc, Boost, and Protobuf, their versions are hardcoded), bump the version according to their version change (if they bump major, we bump major, and so on)
  - If the new image adds or removes secondary dependencies (tools, utilities, etc.), bump minor
  - If the new image adds or removes primary dependencies (compile-time libraries), bump major
  
Make sure you update the version in the first line of `Dockerfile` and `.gitlab-ci.yml` too.
We use specific versions in `.gitlab-ci.yml` to prevent mistakes like forgetting to push the image which leads to inconsistent environment.

## neuro-simulation-env
This is the environment that you want to develop the code with.
It has the toolchain for x86_64 and riscv64 built and ready to use.
To launch the Spike simulator to run riscv64 Linux, run the following command:
```bash
# Inside the container
spike +disk=/project/resources/core-image-riscv-riscv64-20180503081258.rootfs.ext2 /project/resources/bbl
```

To run the project, refer to the `README.md` file in the root directory.

To build this image, run the following commands:
```bash
# cd into this folder first
cd neuro-simulation-env
docker build . -t rhneuroprocessor/neuro-simulation-env:some_tag
```

## riscv-poky-build
This is the Docker image for building `riscv-poky`.
It takes significant amount of space to build and run the image. Building the
reference version of `riscv-poky` uses around 120 GB disk space while a trimmed
down version only uses around 50 GB. Therefore, we only build it
to extract the rootfs and bbl for use with the Spike simulator.
A built copy is in /resources folder. 

### Building riscv-poky
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