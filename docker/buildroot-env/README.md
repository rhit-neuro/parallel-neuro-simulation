# buildroot-env

## Features
This is the environment that you will use to build linux with the `firesim-software` repository. The environment has all the dependencies for building RISC-V Linux with buildroot.

## Running for the first time
Download this docker image with:
```bash
docker pull docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/buildroot-env
```

Start your container for the first time with:
```bash
# <firesim-software repo location> is where you cloned the firesim-software repo
docker run -it -v <firesim-software repo location>:/project --name buildroot docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/buildroot-env:latest bash
```
* `--name buildroot` - names this container `buildroot`.
* `-v <firesim-software repo location>:/project` - mounts `<firesim-software repo location>` on your host computer to `/project` in this container.

## Running susequent times
See [`README.md`](../README.md) in this directory's parent directory.

## Building
To build this image, run the following command:
```bash
# cd into this folder first
# Make sure to replace <version> with your version number for the image you're building
docker build . -t docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/buildroot-env:<version>
```