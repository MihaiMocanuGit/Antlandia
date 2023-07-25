# Antlandia
An Ant colony simulator made in C++.

# Description

This app's purpose is to simulate the behaviour of an ant colony. 


# Compiling the app
## Needed Dependencies: 
* SFML 2
* c++20
* CMake
* Doxyen (For documentation generation)
* g++ (Other compilers can be supported if the debug flags are updated in CMakeLists.txt)


## Features
* The world is composed of Chunks so as to speed up simulation speed when dealing with large numbers of objects.
* The code design refrains from using inheritance, prefering the use of composition instead. 

# Notes: 
* This is in a early stage of development
* As of now, it has only been tested in Linux.
