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
This is the Docker image with `riscv-poky` built inside.
It takes significant amount of space to build and run the image, so
be prepared to use around 120 GB disk space. Therefore, we only build it
to extract the rootfs and bbl for use with the Spike simulator.
A built copy is in /resources folder. To extract it yourself, consider
mounting a volume and copy the files to that volume. The `/scripts/runspike` script
contains code to identify rootfs and bbl locations, and as of now, they are located at:
```
ROOTFS: /build/tmp/deploy/images/riscv64/core-image-riscv-riscv64-<build date and time>.rootfs.ext2
BBL: /riscv-poky/build/tmp/work/riscv64-poky-linux/riscv-pk/1.0-r0/build/bbl
```

To build this image, run the following commands:
```bash
# cd into this folder first
docker build patches/ -f riscv-poky-build/Dockerfile -t rhneuroprocessor/riscv-poky-build:some_tag
```

Note: For `riscv-poky-build, a non-privileged user named `riscv_poky_user` is available
