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

## Compilation

To compile into a WASM execute file. You will have to first clone :

- [enscripten](https://github.com/emscripten-core/emsdk.git)
- [tensorflow](https://github.com/tensorflow/tensorflow)
- [flatbuffers](https://github.com/google/flatbuffers.git)

First you will have to install enscripten, that will allows to compile the program into a WASM.

Then build them to be able to use them on compiling into WASM.

```sh
mkdir build_opencv
cd build_opencv
cmake -DCMAKE_BUILD_TYPE=Release -DBUILD_EXAMPLES=ON ../opencv
```

If you have some errors, check if you have to install some libraries :

```sh
# For mac
brew cmake install webp libopenjp2 zlib openjpeg libtiff tbb ittnotify protobuf flatbuffers opencv
```

Then retry once again. If no errors have been thrown, you can build openCv :

```sh
emmake make -j4
emmake make install
```

You can finally compile the program with :

```sh
emcc kanji_recognition.cpp -o kanjiRecognition.js -s EXPORTED_FUNCTIONS='["_runModel"]' -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']" -s WASM=1 -I"tensorflow" -I"flatbuffers/include" -I"/opt/homebrew/Cellar/opencv@3/3.4.20/include" -I"/opt/homebrew/Cellar/opencv@3/3.4.20/lib" -lopencv_core -lopencv_imgproc -lopencv_imgcodecs -L"tensorflow" -ltensorflowlite -std=c++17
```
