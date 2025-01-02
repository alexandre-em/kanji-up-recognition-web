cmake_minimum_required(VERSION 3.10)

# Set the project name
project(kanji_recognition)

# Automatically include Conan dependencies
include(${CMAKE_BINARY_DIR}/Release/generators/conan_toolchain.cmake)

# Set Emscripten toolchain file TODO: To update to your own path
set(CMAKE_TOOLCHAIN_FILE /path/to/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake)

# Set the C++ standard to 17 (if not already set)
set(CMAKE_CXX_STANDARD 17)

message(STATUS "emscripten: ${EMSCRIPTEN}")

# Set the output format to WebAssembly
if (EMSCRIPTEN)
    # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s ALLOW_MEMORY_GROWTH=1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "Emscripten")
      message(STATUS "Configuring for Emscripten")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
      set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s WASM=1 -s ALLOW_MEMORY_GROWTH=1")
    endif()
endif()

# Add all deps location by hand
set(OpenCV_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(protobuf_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(ZLIB_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(ade_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(OpenEXR_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(Imath_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(libdeflate_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(TIFF_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(JPEG_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(jbig_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(zstd_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(LibLZMA_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(WebP_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(quirc_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(ffmpeg_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(Iconv_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(freetype_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(PNG_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(BZip2_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(brotli_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(OpenJPEG_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(openh264_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(Vorbis_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(Ogg_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(Opus_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(libx264_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(libx265_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(libvpx_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(libmp3lame_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(fdk-aac_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(OpenSSL_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(libaom-av1_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(dav1d_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(TensorFlowLite_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(absl_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(farmhash_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(fft_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(flatbuffers_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(gemmlowp_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(ruy_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(cpuinfo_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(xnnpack_DIR "${CMAKE_BINARY_DIR}/Release/generators")
set(pthreadpool_DIR "${CMAKE_BINARY_DIR}/Release/generators")

# Add Conan dependencies
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
find_package(TensorFlowLite REQUIRED)
message(STATUS "TensorFlowLite_DIR: ${TensorFlowLite_DIR}")

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add your source files
add_executable(kanji_recognition kanji_recognition.cpp)

# Link with required libraries
# target_link_libraries(kanji_recognition_wasm ${OpenCV_LIBS} ${TensorFlowLite_LIBS})
target_link_libraries(kanji_recognition ${OpenCV_LIBS} tensorflow::tensorflowlite)


