Parallel Neuro-Simulation 
=========

**Rewritten neuro-simulation project that aims to optimize using parallelization.**

## Platforms Supported:
 - Linux
 - Mac OSX

## Technologies used:
#### Build Tools:
|Name|Version|Description|
|---|---|---|
| [CMake](http://www.cmake.org/) | 3.x | CMake build system |
| [Docker](https://www.docker.com//) | latest | Containerization support for cross-platform development and CI/CD pipelines |

#### Libraries:
|Name|Version|Description|
|---|---|---|
| [Boost](http://www.boost.org/) | 1.62.0.1 | Cross Compatible C++ Libraries |
| [Protobuf](https://github.com/google/protobuf) | 3.5.1.1 | Google Protocol Buffer |

#### Testing Frameworks:
|Name|Version|Description|
|---|---|---|
| [GTest](http://code.google.com/p/googletest/) | 1.7.0 | C++ Unit Testing Framework |
| [GMock](http://code.google.com/p/googletest/) | 1.7.0 | C++ Mocking Framework |

## Set up your environment:
#### Using Docker
We recommend developing the project with Docker, as it guarantees the same environment is used for both development and testing.

Installation on [Windows](https://docs.docker.com/docker-for-windows/install/) and [macOS](https://docs.docker.com/docker-for-mac/install/)
is as simple as running an installer in the host OS. (Except on Windows, you will need to install additional components provided by Microsoft)
For [Ubuntu](https://docs.docker.com/install/linux/docker-ce/ubuntu/), both apt repo and a convenience installation script are provided.
But [additional steps](https://docs.docker.com/install/linux/linux-postinstall/) needs to be taken in order to run docker without sudo.
There are various instructions available for other Linux variants too.

###### Docker Repo Info

The image is hosted publicly on [Docker Hub](https://hub.docker.com/r/rhneuroprocessor/neuro-simulation-env/).
You don't need to log in to use this image, but if you want to push new ones, you will need to obtain the account credentials.

###### Workflow

We recommend you complete at least the first two parts of the official [Get Started](https://docs.docker.com/get-started/) tutorial.

Assuming you have cd'ed into this root directory of the project folder and are using a UNIX terminal, here are some short-cut commands you can use

To pull the latest version of the image (not always necessary):

```bash
docker pull rhneuroprocessor/neuro-simulation-env:latest # Or use a specific tag
```
   
To run the image in a container for the first time:

```bash
docker run -it -v $(pwd):/project --name nsenv rhneuroprocessor/neuro-simulation-env:latest bash
```

To stop the container:

```bash
docker stop nsenv
```

To start the container after you restart the computer, or stop the container manually:

```bash
docker start nsenv
docker exec -it nsenv bash
```

Within the container, you can use the terminal to run CMake and Make commands.
The overall CMake workflow is the following:
  - Generate Makefiles using CMakeLists.txt (Therefore, whenever you make changes to CMakeLists.txt, you will have to rerun this step)
  - Make the target
  - Run the binary compiled by Make

However, to prevent CMake from polluting project workspace, people prefer to create a separate folder like this (You can see this in the Dockerfile too):

```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
# Then proceed to use make
make main # For example, we want to build the executable that runs simulation
```

As of now, the CMake configuration of the `src` module (`CMakeLists.txt` inside the `src` folder), there are two make targets:
- `main`
- `main_test`

The `main` target builds the main executable to run the neuro-simulation, whereas the `main_test` target builds the GTests to run the unit tests.
When running `make`, you can specify number of tasks available to run in parallel, so you can do `make main -j 4` to run at most 4 compilation tasks in parallel.

###### Making New Images

The commands to build the image and push them to Docker Hub are the following:

```bash
docker build . -t rhneuroprocessor/neuro-simulation-env:latest
docker tag rhneuroprocessor/neuro-simulation-env:latest rhneuroprocessor/neuro-simulation-env:mx.my.mz # mx.my.mz is your new version number
docker push rhneuroprocessor/neuro-simulation-env:latest
docker push rhneuroprocessor/neuro-simulation-env:mx.my.mz
```

We use [Semantic Versioning/SemVer](https://semver.org/) scheme to bump the version of the container.
The rules of thumb to bump the version are:
  - If the new image only has new versions of secondary dependencies (dependencies except gcc, Boost, and Protobuf), bump patch
  - If the new image has new versions of primary dependencies (gcc, Boost, and Protobuf, their versions are hardcoded), bump the version according to their version change (if they bump major, we bump major, and so on)
  - If the new image adds or removes secondary dependencies (tools, utilities, etc.), bump minor
  - If the new image adds or removes primary dependencies (compile-time libraries), bump major
  
Make sure you update the version in the first line of `Dockerfile` and `.gitlab-ci.yml` too.
We use specific versions in `.gitlab-ci.yml` to prevent mistakes like forgetting to push the image which leads to inconsistent environment.

###### Note on GitLab CI/CD Pipeline

The `.gitlab-ci.yml` records the configuration for GitLab CI/CD Pipeline on Ada.
Currently, there is a Kubernetes cluster that manages Docker runners for Ada,
and we are using `kubernetes-staging` tag to point to their staging runners. This tag might change in the future.

#### Manual setup

Manual setup is not recommended as it will necessarily modify your system, and (especially for Linux) the cost of misconfiguration can involve reinstalling the OS.

###### macOS:

Note: It's harder to use the exact same versions for the dependencies because Homebrew doesn't have every version of the dependency packages.

First, install [Homebrew](https://brew.sh/) using their one-liner install command.

Then install gcc:

```bash
brew install gcc cmake
```

As of this writing, Homebrew doesn't overwrite the link to the default `clang` compiler with the gcc we just installed.
Instead, you have to export `CC` and `CXX` variables to your environment. To do this automatically, you will want to add these lines to ~/.bash_profile

```bash
export CC=/usr/local/bin/gcc-7
export CXX=/usr/local/bin/g++-7
```

After restarting your terminal session (or run `source ~/.bash_profile`), you will need to install boost and protobuf from source

```bash
brew install boost --build-from-source # If you want to be extra sure you are using gcc, add --cc=gcc-7
brew install protobuf --build-from-source # Same here, you can add --cc=gcc-7
```

###### Debian (Ubuntu):

You can simply run the commands in the Dockerfile to get the same dependencies installed, except you will have to use sudo for `apt-get`, `make install`, and `ldconfig`

## Project Configuration Options

For each of the configuration options below, if it applies to CMake, you can apply the change by calling
```bash
cmake <project path> -D<some key>=<some value>
# For example
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

#### CMAKE_BUILD_TYPE
This is a CMake default variable. The values we use in this project are `Debug` and `Release`
This value also affects CMake built-in variables with the suffix convention, such as `CMAKE_CXX_FLAGS_DEBUG`
(appended after `CMAKE_CXX_FLAGS` if the build type is `Debug`). Other than affecting CMake variable usage,
when built with the `Debug` build type, we will use dynamic linking, disable optimization and use `-g` option (which
will generate debug information), but if the project is built with the `Release` build type, we will use static
linking and use maximum optimization
