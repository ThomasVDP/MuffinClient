# MuffinClient
A C++ replica of the well known game Minecraft

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
