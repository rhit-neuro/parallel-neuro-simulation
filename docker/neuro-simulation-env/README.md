# neuro-simulation-env
This is the environment that you want to develop the code with.
It has the toolchain for x86_64 and riscv64 built and ready to use.
To launch the Spike simulator to run riscv64 Linux, run the following command:
```bash
# Inside the container
spike +disk=/project/resources/core-image-riscv-riscv64-20180503081258.rootfs.ext2 /project/resources/bbl
```
Then when you see the `riscv64 login:` prompt, type `root` and press enter.

To run the project, refer to the `README.md` file in the root directory.

To build this image, run the following commands:
```bash
# cd into this folder first
cd neuro-simulation-env
docker build . -t rhneuroprocessor/neuro-simulation-env:some_tag
```