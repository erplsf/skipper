cmake_minimum_required(VERSION 3.7...3.19)

if(${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(smok
  VERSION 0.1
  DESCRIPTION "KSP/kRPC/Principia + Orbital Mechanics exploraion"
  LANGUAGES CXX)

add_executable(${PROJECT_NAME} main.cpp calc.cpp)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PUBLIC -Wall)
target_compile_options(${PROJECT_NAME} PUBLIC -Wextra)

# target_compile_options(${PROJECT_NAME} PRIVATE -Q)

include(FetchContent)
FetchContent_Declare(
  protobuf
  GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
  GIT_TAG v3.6.1
  SOURCE_SUBDIR  cmake)
set(protobuf_BUILD_TESTS OFF)
set(protobuf_BUILD_SHARED_LIBS ON)

FetchContent_MakeAvailable(protobuf)

FetchContent_Declare(asio-cmake
  GIT_REPOSITORY https://github.com/kingsamchen/asio-cmake.git
  GIT_TAG        origin/master)

set(ASIO_CMAKE_ASIO_TAG asio-1-12-1)

FetchContent_MakeAvailable(asio-cmake)

include(ExternalProject)

ExternalProject_Add(
  krpc-project
  URL https://github.com/krpc/krpc/releases/download/v0.4.8/krpc-cpp-0.4.8.zip
  INSTALL_DIR "${PROJECT_BINARY_DIR}/_deps/krpc-install"
  CMAKE_ARGS
  "-DProtobuf_LIBRARIES=${protobuf_BINARY_DIR}/libprotobuf.so"
  "-DProtobuf_PROTOC_EXECUTABLE=${protobuf_BINARY_DIR}/protoc"
  "-DProtobuf_INCLUDE_DIR=${protobuf_SOURCE_DIR}/src"
  "-DASIO_SOURCE_DIR=${asio-cmake_SOURCE_DIR}"
  "-DCMAKE_PROJECT_kRPC_INCLUDE=${CMAKE_SOURCE_DIR}/include_asio.cmake"
  "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}/_deps/krpc-install"
  BUILD_BYPRODUCTS "${PROJECT_BINARY_DIR}/_deps/krpc-install/lib/libkrpc.so"
  DEPENDS protobuf::libprotobuf protobuf::protoc asio)

ExternalProject_Get_Property(krpc-project INSTALL_DIR)

set(krpc_INCLUDE_DIR "${INSTALL_DIR}/include")
set(krpc_LIB_DIR "${INSTALL_DIR}")

add_library(krpc-lib SHARED IMPORTED)
set_target_properties(krpc-lib
  PROPERTIES
  IMPORTED_LOCATION ${krpc_LIB_DIR}/lib/libkrpc.so)

add_dependencies(krpc-lib krpc-project)
add_dependencies(${PROJECT_NAME} krpc-project)


target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${krpc_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE "${protobuf_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} protobuf::libprotobuf)
target_link_libraries(${PROJECT_NAME} krpc-lib)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

# target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CONAN_INCLUDE_DIRS_MP-UNITS})
target_link_libraries(${PROJECT_NAME} CONAN_PKG::mp-units)
