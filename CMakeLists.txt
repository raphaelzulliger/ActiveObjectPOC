cmake_minimum_required(VERSION 2.19)
project(ActiveObject)

set(CMAKE_CXX_STANDARD 17)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
  message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.16.1/conan.cmake"
                "${CMAKE_BINARY_DIR}/conan.cmake"
                EXPECTED_HASH SHA256=396e16d0f5eabdc6a14afddbcfff62a54a7ee75c6da23f32f7a31bc85db23484
                TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(REQUIRES mpmcqueue/1.0
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})


add_executable(ActiveObject
    main.cpp
    TestItf.h
    Test.h
)

target_link_libraries(ActiveObject CONAN_PKG::mpmcqueue)
