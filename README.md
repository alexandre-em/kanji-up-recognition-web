# Installation

## Assets (Model)

Create a new directory `assets`:

```sh
mkdir assets
```

and copy your model in this folder. You will have then to convert it into a C++ header file to embed the model into the program and then the WASM with :

```sh
xxd -i kanji_model.tflite > kanji_model_data.h
```

## Prerequired

To compile into a WASM execute file. You will have to first clone :

- [enscripten](https://github.com/emscripten-core/emsdk.git)

First you will have to install enscripten, that will allows to compile the program into a WASM.

If you have some errors, check if you have to install some libraries :

```sh
# For mac
brew cmake install webp libopenjp2 zlib openjpeg libtiff tbb ittnotify protobuf flatbuffers opencv
```

## Conan

### Installation

```sh
pip install conan
```

### Setting profile

```sh
conan profile detect
```

### Install dependencies

```sh
conan install . --build=missing
```

You will have to update on the `CMakeLists.txt` file the path of emscripten (l.10)

### Configure with CMake

```sh
emcmake cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
```

### Build with Emscripten

```sh
emmake make -C build
```

it will then generate a `.wasm` and `.js` files that you can use on your Javascript application 🎉
