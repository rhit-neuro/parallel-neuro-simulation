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
# replace <username> with your computer username below
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
We recommend you complete at least the first two parts of the official [Get Started](https://docs.docker.com/get-started/) tutorial to familiarize yourself with docker.

### Docker Registry Info
We have a docker registry integrated into this repository on `ada` and one hosted publicly on [Docker Hub](https://hub.docker.com/r/rhneuroprocessor/). The public registry isn't being used anymore for two main reasons:
1. Since `ada` is on-campus, downloading large docker images from it on-campus won't contribute to your monitored bandwidth usage
2. The public registry has one set of credentials for the team to share while each member has their own credentials for the `ada` hosted regisry.

### Registry login
If you want to use one of the docker images hosted in this repository's registry, you must first login:
```bash
# The username and password used here are for your account on ada.csse.rose-hulman.edu
docker login docker.csse.rose-hulman.edu
```
note: you only need to login one time

### Download images
To download a docker image:
```bash
# replace <image name> with the name of the image you want to download
# e.g. rocket-chip-env
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

### Managing your images and containers
#### Seeing your containers and images
If you want to see what images you have downloaded, run:
```bash
docker image ls
```
If you want to see which containers you have that are running, run:
```bash
docker container ls
```
If you want to see all your containers, run:
```docker
docker container ls -a
```
#### Deleting contianers and images
If you want to delete a container, run:
```bash
# Replace containerName with the name of the container to delete
docker rm containerName
```
If you want to delete an image, you first have to delete all containers that use that image and then run:
```bash
# Replace imageName with the name of the container to delete
docker image rm imageName
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