[![Build Status](https://travis-ci.org/gooddoog/fishing-time.svg?branch=master)](https://travis-ci.org/gooddoog/fishing-time)
[![Build status](https://ci.appveyor.com/api/projects/status/dmb4hl04kuy7h1li?svg=true)](https://ci.appveyor.com/project/gooddoog/fishing-time)
[![Actions Status](https://github.com/gooddoog/fishing-time/workflows/Build%20application/badge.svg)](https://github.com/gooddoog/fishing-time/actions)

# Fishing Time

### Requirements
- [CMake](https://cmake.org/download/) 3.0+
- [Qt5](https://www.qt.io/download)

### Build and run

```console
$ mkdir build
$ cd build
$ cmake .. -DCMAKE_PREFIX_PATH="/path/to/qt/"
$ cmake --build .
$ ./bin/fishing-time
```

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
