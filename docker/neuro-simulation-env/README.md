# neuro-simulation-env

## Features
This is the environment that you want to develop the code with.
It has the toolchain for x86_64 and riscv64 built and ready to use.

## Running for the first time
Download this docker image with:
```bash
docker pull docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/neuro-simulation-env
```

Start your container for the first time with:
```bash
# <parallel-neuro-simulation repo location> is where you cloned the parallel-neuro-simulation repo
docker run -it -v <parallel-neuro-simulation repo location>:/project --name nsenv docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/neuro-simulation-env:latest bash
```
* `--name nsenv` - names this container `nsenv`.
* `-v <parallel-neuro-simulation repo location>:/project` - mounts `<parallel-neuro-simulation repo location>` on your host computer to `/project` in this container.

## Running susequent times
See [`README.md`](../README.md) in this directory's parent directory.

## Building
To build this image, run the following command:
```bash
# cd into this folder first
# Make sure to replace <version> with your version number for the image you're building
docker build . -t docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/neuro-simulation-env:<version>
```