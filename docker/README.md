Dockerfiles
=========

There are currently three docker images we use:
* [neuro-simulation-env](neuro-simulation-env/)
* [riscv-poky-build](riscv-poky-build/)
* [rocket-chip-env](rocket-chip-env/)

## Setting up Docker
First, you'll want to install docker:
```bash
sudo apt install docker
```
Now you need to add your user to the `docker` group so that you don't need to be root to run docker commands:
```bash
sudo groupadd docker
# replace <username> with your username below
sudo usermod -aG docker <username>
```
Now logout and log back in for your group membership to be re-evaluated. Now you can start up the docker daemon with:
```bash
sudo systemctl start docker
```
docker can be stopped similarly with:
```bash
sudo systemctl stop docker
```

## Using Docker
### Registry login
If you want to use one of the docker images hosted in this repository's registry, you must first login:
```bash
docker login docker.csse.rose-hulman.edu
```
note: you only need to login one time

### Download images
To download a docker image:
```bash
# replace <image name> with something like rocket-chip-env
docker pull docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/<image name>:latest
```
### Upload images
You can push built docker images to this repository's registry with the following:
```bash
docker push docker.csse.rose-hulman.edu/neuroprocessor-group/parallel-neuro-simulation/<image name>:<image tag>
```

### Running a container for the first time
See this directory's sub-directories for specific instructions for each image on running containers for the first time.

### Running container's subsequent times
Once you've created a container, you can start it with:
```bash
docker start <container name>
```
To open start a shell in a running container, run:
```bash
docker exec -it <container name> bash
```
To stop a running container:
```bash
docker stop <container name>
```

### Tagging images
Tagging is the way you associate a version number with a docker image. You can change the version or tag of a docker image with the following:
```bash
docker tag <image name>:<original tag> <image name>:<new tag>
```

## Making New Images
### Versioning
We use [Semantic Versioning/SemVer](https://semver.org/) scheme to bump the version of docker images. Version numbers look like `<major>.<minor>.<patch>`.
The rules of thumb to bump the version are:
  - If the new image only has new versions of secondary dependencies (dependencies except gcc, Boost, and Protobuf), bump patch
  - If the new image has new versions of primary dependencies (gcc, Boost, and Protobuf, their versions are hardcoded), bump the version according to their version change (if they bump major, we bump major, and so on)
  - If the new image adds or removes secondary dependencies (tools, utilities, etc.), bump minor
  - If the new image adds or removes primary dependencies (compile-time libraries), bump major
  
Make sure you update the version in the first line of `Dockerfile` and `.gitlab-ci.yml` too.
We use specific versions in `.gitlab-ci.yml` to prevent mistakes like forgetting to push the image which leads to inconsistent environment.

#### Versioning while developing a new image
While developing a new docker image, you should take a slightly different approach to version numbering. Let's look at an example to see a good way to handle versioning.

Let's say `neuro-simulation-env` is currently at version `2.3.1` and we want to add a new primary dependency which would bump our verision number to `3.0.0`. While you are experimenting with building this new image, start with version number `3.0.0_dev01`. If the changes you tried didn't actually work, then you just need to bump the dev number (`3.0.0_dev02`) for your next attept at building your new image. Once you get a dev image to work, you can change its version number to your target version number of `3.0.0`.