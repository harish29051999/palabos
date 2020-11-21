# Palabos

[Palabos](https://palabos.unige.ch/) is an open-source CFD solver based on the [lattice Boltzmann method](https://palabos.unige.ch/lattice-boltzmann/what-lattice-boltzmann/). 
On this page you can download the source code, [access examples](https://gitlab.com/unigespc/palabos/tree/master/examples) and resources, 
and [interact with the user base](http://palabos-forum.unige.ch/).

## How to cite Palabos

```
@article{Palabos2020,
    title = "Palabos: Parallel Lattice Boltzmann Solver",
    journal = "Computers & Mathematics with Applications",
    year = "2020",
    issn = "0898-1221",
    doi = "https://doi.org/10.1016/j.camwa.2020.03.022",
    author = "Jonas Latt and Orestis Malaspinas and Dimitrios Kontaxakis and Andrea Parmigiani and Daniel Lagrava and Federico Brogi and Mohamed Ben Belgacem and Yann Thorimbert and Sébastien Leclaire and Sha Li and Francesco Marson and Jonathan Lemus and Christos Kotsalos and Raphaël Conradin and Christophe Coreixas and Rémy Petkantchin and Franck Raynaud and Joël Beny and Bastien Chopard",
}
```

# Installation

Palabos is very easy to install since it does not depend on any external dependencies.

## Linux Prerequisites

The mandatory packages are the following:

- A modern C++ compiler `gcc` or `clang`
- `make`
- `cmake`

### For Debian based distributions

```
$ sudo apt install gcc clang cmake make
```

### For Arch based distributions

```
$ sudo pacman -S gcc clang make cmake
```

## Linux optional prerequisites

The optional but recommended packages are the following:

- [openmpi](https://www.open-mpi.org/), by default all the examples use MPI.
- [imagemagick](https://imagemagick.org/index.php), some examples output `.gif` which are generated by calling `convert`.
- [hdf5](https://www.hdfgroup.org) for the use of hdf5 output.
- [ccache](https://ccache.dev/) to speed up the compilation process.

### For Debian based distributions

```
$ sudo apt install libopenmpi-dev imagemagick libhdf5-dev libhdf5-mpi-dev ccache
```

### For Arch based distributions

```
$ sudo pacman -S openmpi imagemagick hdf5 hdf5-openmpi ccache
```
  
The majority of the output of Palabos is under the form of `VTK` files. We recommend the use
of [Paraview](https://www.paraview.org/) for their visualization.

## Windows Prerequisites

- Microsoft Visual Studio (VS). VS2019 is recommended, due to its integration with CMake project management.
- Microsoft C++ compiler, installed with Visual Studio (make sure to enable the installation of C++ compiler in the custom installation option of VS). This step can be done even after installing VS for the first time in your system. Simply, re-run the installer and customize it to include the extra features. For more information on how to install C/C++ support in Visual Studio follow [link1](https://docs.microsoft.com/en-us/cpp/build/vscpp-step-0-installation?view=vs-2019) & [link2](https://visualstudio.microsoft.com/vs/features/cplusplus/).
- Optionally the Microsoft Message Passing Interface (MPI). To install MPI follow this [link](https://docs.microsoft.com/en-us/message-passing-interface/microsoft-mpi).
- Optionally the [HDF5](https://www.hdfgroup.org/downloads/hdf5/) library.
- If you use Visual Studio older than VS2019, you may want to install [CMake](https://cmake.org/download/), preferably the latest version, to generate a Visual Studio project file (.sln) from Palabos' CMakeLists.txt

### For Visual Studio 2019
Start Visual Studio 2019 and select "Clone a repository" from the "Get
started" section. Provide the following repository location:

```
https://gitlab.com/unigespc/palabos
```

and click "clone". Watch the messages that unfold in the "Output
messages" window for potential errors. If there is no error, select an
example program from the "Select Startup Item" button in the toolbar.
Click the little arrow next to the selected example to build and
execute it.

You may get error messages in the "Output messages" window if MPI
and/or HDF5 are not installed on your system. In these cases,
deactivate MPI and/or HDF5 by selecting "Manage Configurations" in the
"Configuration" button in the toolbar. In the section "CMake variables
and cache", you should be able to un-click ENABLE_MPI and/or
BUILD_HDF5 (you may need to wait a bit for these to appear). After
this, click "Save and generate CMake cache to load variables" and
proceed as indicated above.

## The installation steps

For nightly `Palabos` clone this repo

```
git clone https://gitlab.com/unigespc/palabos.git
```

or for stable releases download the appropriate version
from [this link](https://gitlab.com/unigespc/palabos/-/tags).
If you downloaded `palabos-v2.1r0.tar.gz` (the version 2.1 of Palabos) you
can extract the files from the archive with

```
$ tar xzvf palabos-v2.1r0.tar.gz
```

Congratulations. You should now have a functioning version of Palabos.
Assuming `palabos` is the directory where the Palabos source is located,
you can check your installation by typing the following commands

**Linux**

```
$ cd palabos/examples/showCases/cavity2d/build
$ cmake ..
$ make
$ cd ..
$ ./cavity2d
```

**Windows**

1. ```cd palabos/examples/showCases/cavity2d```
2. Open CMake (GUI), define source code folder (current folder), and build folder (build/)
3. Configure project (CMake Configure button). A pop-up windows will ask you to specify the generator for this project (Visual Studio that you installed earlier).
4. Generate the project (CMake Generate button).
5. Go to the build folder and open **palabosExample.sln**. This will open Visual Studio, from where you can build the project.
6. After completing the build, there will be a Release or Debug folder in ```palabos/examples/showCases/cavity2d``` with the cavity2d.exe inside. Move the executable one level up and run it either by clicking it or using the command line.

If your installation is fully functional this should generate the following output:

```
$ ./cavity2d(.exe)
step 0; t=0; av energy=3.81587645e-07; av rho=1
Time spent during previous iteration: 0
step 1280; t=0.1; av energy=1.143114423e-06; av rho=0.9999958713
Time spent during previous iteration: 0.000729634
Saving Gif ...

step 2560; t=0.2; av energy=1.464417219e-06; av rho=0.999991746
```

# Compile an example


Once you have an installation we assume that you are located in your Palabos
installation directory (see above).
To compile an example, `boussinesqThermal3d` in this case, do the following commands

```
$ cd examples/showCases/boussinesqThermal3d/build
$ cmake ..
$ make
$ cd ..
```

These commands should generate the `boussinesqThermal3d` executable.
If you have a functioning MPI installation you can run it on 4 cores for example
using the command

```
$ mpirun -np 4 ./rayleighBenard3D 10000
```

The output should look like

```
$ mpirun -np 4 ./rayleighBenard3D 10000
10000 1
time elapsed for rayleighBenardSetup:0.0661382
0 : Writing VTK.
0 : Writing gif.


average=1.00251; stdDev/average=0.0719342
average=0.999835; stdDev/average=0.0373279
3.33333 : Writing VTK.
```

**How to use Cmake to compile your application**

Each example has a CMakeLists.txt to compile under cmake. To compile the previous example with cmake
you can write (**check installation section for Windows**)

```
cd palabos_root_folder/examples/showCases/boussinesqThermal3d
mkdir -p build && cd build
cmake ..
make
```

If you need to create a palabos project with a cmake-based IDE,
you can use the CMakeLists.txt provided in any of the examples. With some minor modifications, you can also use this CMakeLists.txt to compile and build your own application.

In palabos root directory, we provide a CMakeLists.txt file that compiles palabos library and all the available examples.

# Documentation

The documentation of Palabos can be found following this [link](https://palabos.unige.ch/get-started/palabos-documentation/).

# Getting help

If you need help with Palabos, or with the lattice Boltzmann method theory, please use the [Palabos forum](http://palabos-forum.unige.ch/).
<!-- There is also a [matrix room](https://matrix.to/#/!MCMTEdGiUEycWSngZU:matrix.org?via=matrix.org)
where you can discuss things. -->

# Bug reports

When you think you have identified a bug, please open an issue and do not forget to give as many details as possible for us to be able to
reproduce the bug.

# Contributing

To see how to open issues, submit bug reports, create feature requests, submit your additions to the Palabos library, see the [Contributing](https://gitlab.com/unigespc/palabos/blob/master/CONTRIBUTING.md) page.

# Contributors

By alphabetic order

* @beny3
* @ccoreixas
* @daniel-lagrava-niwa
* @dkdk
* @helenmo
* @jfburdet
* @kotsaloscv
* @Latt
* @msguskova
* @omalaspinas
* @onmars
* @parmigiani
* @rconradin
* @swang251 
* @YannThorimbert
* @ysagon


