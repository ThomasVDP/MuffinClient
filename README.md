# MuffinClient
### DISCLAIMER: This project is definitely nowhere near it's goal and development is already paused!!!!
A C++ replica (definitely not, still very early development and already paused!!!!!!!) of the well known game Minecraft

## Building
### Requirements
- CMake
- Conan
### Building
To build this project, clone the repository:
```
git clone --recursive https://github.com/ThomasVDP/MuffinClient
```
Create a build dir:
```
cd MuffinClient
mkdir build; cd build
```
First run conan install:
```
conan install ..
```
Finally run Cmake:
```
cmake -G "Unix Makefiles" ..
make
```
The `MuffinClient` executable can be found in `build/bin`!
