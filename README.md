[![Build status](https://ci.appveyor.com/api/projects/status/dmb4hl04kuy7h1li?svg=true)](https://ci.appveyor.com/project/aobolensk/fishing-time)
[![Actions Status](https://github.com/aobolensk/fishing-time/workflows/Build%20application/badge.svg)](https://github.com/aobolensk/fishing-time/actions)

# Fishing Time

### Requirements
- [CMake](https://cmake.org/download/) 3.12+
- [Qt5](https://www.qt.io/download) 5.12+

### Build and run

#### CMake

```console
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_PREFIX_PATH="/path/to/qt/"
$ cmake --build .
$ ./bin/fishing-time
```

#### QtCreator

1. Open QtCreator
1. `File > Open File or Project...` and select file CMakeLists.txt
1. Select at least one configuration option and press "Configure Project"
1. Wait until configuration is finished and press "Play" button (Ctrl + R)

### Create standalone build
fishing-time build depends on Qt runtime. In order to include this runtime into the build and be able to run this executable on different machines you need to perform the following steps:

#### Windows

```console
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_PREFIX_PATH="path\to\qt\"
$ cmake --build . --config Release
$ path\to\qt\bin\windeployqt.exe bin\fishing-time.exe --release --compiler-runtime --force --no-translations
```
