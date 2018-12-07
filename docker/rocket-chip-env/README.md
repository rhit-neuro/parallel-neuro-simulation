# rocket-chip-env

## Features
The `rocket-chip-env` docker image has `riscv-tools` and `Xilinx Vivado` installed and is ready to build a `rocket-chip` from scratch targeting either the `verilator` or an actual FPGA.

## Running for the first time
Download this docker image with:
```bash
docker pull docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/rocket-chip-env
```
Now `cd` into the directory with the Rocket Chip project you're working on. For example, if you're using the `fpga-zynq` repository as the base for your project, `cd` into the `fpga-zynq` directory. Now to create a new docker container from this docker image, run:
```bash
docker run -it --name rcenv -v $(pwd):/project/fpga-zynq -v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/rocket-chip-env
```
* `--name rcenv` - names this container `rcenv`.
* `-v $(pwd):/project/fpga-zynq` - mounts your current directory to `/project/fpga-zynq` in this container. You could alternatively replace `$(pwd)` with the absolute path on your host computer to whatever folder you want to mount at `/project/fpga-zynq` in this container.
* `-v /tmp/.X11-unix:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY` - handles connecting programs like `Vivado` running in this container to your display outside the container.

## Running susequent times

## Building