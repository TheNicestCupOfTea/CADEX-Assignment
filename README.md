# CADEX Assignment
The solution for a test assignment.

# Requirements:
Design a small program in C++ that would implement support of 3D curves hierarchy.
1. Support a few types of 3D geometric curves – circles, ellipses and 3D helixes. (Simplified
definitions are below). Each curve should be able to return a 3D point and a first derivative (3D
vector) per parameter t along the curve.
2. Populate a container (e.g. vector or list) of objects of these types created in random manner with
random parameters.
3. Print coordinates of points and derivatives of all curves in the container at t=PI/4.
4. Populate a second container that would contain only circles from the first container. Make sure the
second container shares (i.e. not clones) circles of the first one, e.g. via pointers.
5. Sort the second container in the ascending order of circles’ radii. That is, the first element has the
smallest radius, the last - the greatest.
6. Compute the total sum of radii of all curves in the second container.
(*) Additional optional requirements:
7. Split implementation into a library of curves (.dll or .so) and executable which uses API of this
library.
8. Implement computation of the total sum of radii using parallel computations (e.g. OpenMP or Intel
TBB library).



# Project desciption
This project satisfies all given requrements. 

The project compiles two files:
## Curves.dll 
The dynamic library that provides classes and functions to work with curves.
* Curves.cpp - Defines classes of curves and interface functions to work with them.
* Curves.h - Header file for Curves.cpp, provides names of classes and DLL interface functions.
* DllEntryPoint.cpp - An important bit of code for compiling the DLL.
   
## Main.exe 
Main executable, uses Curves.dll to do given tasks.
* Main.cpp - Main code, loads Curves.dll and interacts with it
* Main.h - Header file for Curves.cpp
* Curves.h - Names of classes and DLL interface functions for Main.cpp

# How to compile the project
Open the folder in Visual Studio, build and run Main.exe using CMake.

**IMPORTANT: Compilation is done using g++ compiler.**
