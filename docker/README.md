Dockerfiles
=========

There are currently two docker images we use:
* neuro-simulation-env
* riscv-poky-build

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
mounting a volume and run the following commands:
```bash

```

To build this image, run the following commands:
```bash
# cd into this folder first
docker build patches/ -f riscv-poky-build/Dockerfile -t rhneuroprocessor/riscv-poky-build:some_tag
```

Note: For `riscv-poky-build, a non-privileged user named `riscv_poky_user` is available
