cmake_minimum_required(VERSION 3.14)
project(vitis_hls_bug_sample)

# CMake for Vivado/Vitis
include(FetchContent)
FetchContent_Declare(
  vivado_cmake_module
  GIT_REPOSITORY  https://github.com/nodamushi/vivado_cmake_module.git
  GIT_TAG v0.0.5
)
FetchContent_MakeAvailable(vivado_cmake_module)
list(APPEND CMAKE_MODULE_PATH ${vivado_cmake_module_SOURCE_DIR})

find_package(HLS)


add_hls_project(duplicate
  TOP     Duplicate
  NAME    Duplicate
  VERSION 1.0
  PERIOD  10
  PART    xc7z007sclg400-1
  SOURCES duplicate.cpp
)

add_hls_project(duplicate2
  TOP     Duplicate
  NAME    Duplicate
  VERSION 1.0
  PERIOD  10
  PART    xc7z007sclg400-1
  SOURCES duplicate.cpp
  DEFINE  NOCRASH
)


add_hls_project(cosimbug
  TOP        Cosim
  NAME       Cosim
  VERSION    1.0
  PERIOD     10
  PART       xc7z007sclg400-1
  SOURCES    cosim.cpp
  TB_SOURCES cosim_tb.cpp
)

add_hls_project(cosimbug-workaround
  TOP        Cosim
  NAME       Cosim
  VERSION    1.0
  PERIOD     10
  PART       xc7z007sclg400-1
  SOURCES    cosim.cpp
  TB_SOURCES cosim_tb.cpp
  TB_DEFINE  WORKAROUND_COSIMBUG
)
