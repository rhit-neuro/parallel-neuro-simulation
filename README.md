Parallel Neuro-Simulation
=========

**Neuron Simulation using the Hodgkin-Huxley Model**
This project is a single-threaded implementation of the Hodgkin-Huxley neuron model that allows for the use of hardware- and software-based lookup tables.  
Hardware-based lookup tables are only supported on a custom RISC-V processor.

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

See the `README.md` in the [deca-docker](https://github.com/rhit-neuro/deca-docker) repository for details on installing and using docker.

###### Workflow
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
make parallel-neuro-sim # For example, we want to build the executable that runs simulation
```

As of now, the CMake configuration of the `src` module (`CMakeLists.txt` inside the `src` folder), there are two make targets:
- `parallel-neuro-sim`
- `parallel-neuro-sim_test`

The `parallel-neuro-sim` target builds the parallel-neuro-sim executable to run the neuro-simulation, whereas the `parallel-neuro-sim_test` target builds the GTests to run the unit tests.
When running `make`, you can specify number of tasks available to run in parallel, so you can do `make parallel-neuro-sim -j 4` to run at most 4 compilation tasks in parallel.

###### Note on GitLab CI/CD Pipeline

The `.gitlab-ci.yml` records the configuration for GitLab CI/CD Pipeline on Ada.
Currently, there is a Kubernetes cluster that manages Docker runners for Ada,
and we are using `kubernetes` tag to point to their staging runners. This tag might change in the future.

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

## Building the Project
First, make a build directory
```bash
mkdir build
cd build
```
Now use `cmake` to configure how the project will build
```bash
# Example configuration to build a static binary for x86 with LUTs enabled
# See Project Configuration Options below for more details on these options
cmake .. -DCMAKE_BUILD_TYPE=Release -DINCLUDE_LUT_SUPPORT=ON
```
Now you can build the main application with:
```bash
make -j parallel-neuro-sim
```
You can build the tests with:
```bash
make -j parallel-neuro-sim_test
```
Or you can build the main application and tests at the same time with:
```bash
make -j
```

The resultant binary will be located in the `build/src/` directory

### Project Configuration Options

For each of the configuration options below, if it applies to CMake, you can apply the change by calling
```bash
cmake <project path> -D<some key>=<some value>
# For example
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

#### CMAKE_BUILD_TYPE
This is a CMake built-in variable. The values we use in this project are `Debug` and `Release`
This value also affects CMake built-in variables with the suffix convention, such as `CMAKE_CXX_FLAGS_DEBUG`
(appended after `CMAKE_CXX_FLAGS` if the build type is `Debug`). Other than affecting CMake variable usage,
when built with the `Debug` build type, we will use dynamic linking, disable optimization and use `-g` option (which
will generate debug information), but if the project is built with the `Release` build type, we will use static
linking and use maximum optimization

#### INCLUDE_LUT_SUPPORT
This variable determines whether LUT-related library/code while be compiled during builds. You probably want
to use a RISC-V toolchain before turning this on.

#### USE_OPENMP
Currently, the project by default builds without OpenMP support, to enable it, configure CMake with `USE_OPENMP=ON`

#### USE_RISCV_DOCKER_PRESETS
When this option is set to true, CMake will use hardcoded variables for the following:
  - `CMAKE_C_COMPILER` - Path to C compiler, comparable to the `CC` environment variable
  - `CMAKE_CXX_COMPILER` - Path to C++ compiler, comparable to the `CXX` environment variable
  - `CMAKE_PREFIX_PATH` - Library path prefix used when searching for libraries

These variables are consistent with the setup in the Docker image, but not necessary with
your own setup. Therefore, if you don't use the Docker image, consider supplying these variables yourself

#### RISCV
Use this option to enable certain RISC-V only features (such as hardware LUTs) when not using USE_RISCV_DOCKER_PRESETS. If you use USE_RISCV_DOCKER_PRESETS, you do not need to specify this option.

## Running the Project
For details on running the project, see [sample-configs/README.md](sample-configs/README.md).

## Running the Tests
Running the tests is pretty simple. After building the tests, go into the `build/src` directory and run:
```bash
./parallel-neuro-sim_test
```

### Using spike
To launch the Spike simulator to run riscv64 Linux, run the following command:
```bash
# Inside the container
spike +disk=/project/resources/buildroot-neuro.rootfs.ext2 /project/resources/bbl
```
Then when you see the `riscv64 login:` prompt, use `root` as the username and `sifive` as the password.
