cmake_minimum_required(VERSION 3.7...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(skipper
  VERSION 0.1
  DESCRIPTION autopilot
  LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

include(FetchContent)
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  SOURCE_SUBDIR  cmake
  )

set(protobuf_BUILD_TESTS OFF)
# set(protobuf_MODULE_COMPATIBLE ON)

FetchContent_MakeAvailable(protobuf)

set(Protobuf_DIR "${protobuf_SOURCE_DIR}/cmake")
message("${Protobuf_DIR}")

include(FindProtobuf)
find_package(Protobuf REQUIRED NO_DEFAULT_PATH)

# message("   --> PROTOBUF LIB: ${PROTOBUF_LIBRARIES}")
# message("   --> PROTOBUF INCLUDE: ${PROTOBUF_INCLUDE_DIRS}")
# message("   --> PROTOBUF VERSION: ${Protobuf_VERSION}")
# message("   --> PROTOBUF Found: ${Protobuf_FOUND}")

include(ExternalProject)

ExternalProject_Add(
  krpc
  URL https://github.com/krpc/krpc/releases/download/v0.4.8/krpc-cpp-0.4.8.zip)
