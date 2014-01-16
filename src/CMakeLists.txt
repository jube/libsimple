cmake_minimum_required(VERSION 2.8)

project(LIBSIMPLE CXX)

option(WITH_TEST "Build with tests." ON)

# include(CPackConfig.cmake)

add_definitions(-Wall -g -O2)

if (WIN32)
  add_definitions(-std=c++0x)
else (WIN32)
  add_definitions(-std=c++11)
endif (WIN32)

include_directories("${CMAKE_SOURCE_DIR}/include")

add_subdirectory(lib)

if (WITH_TEST)
  enable_testing()
  add_subdirectory(tests)
endif (WITH_TEST)

find_package(Doxygen)

if(DOXYGEN_FOUND)
  configure_file("${CMAKE_SOURCE_DIR}/Doxyfile.cmake" "${CMAKE_BINARY_DIR}/Doxyfile" @ONLY)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} "${CMAKE_BINARY_DIR}/Doxyfile")
endif(DOXYGEN_FOUND)

configure_file("${CMAKE_SOURCE_DIR}/libsimple0.pc.in" "${CMAKE_BINARY_DIR}/libsimple0.pc" @ONLY)
install(
  FILES "${CMAKE_BINARY_DIR}/libsimple0.pc"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}/pkgconfig"
)

install(
  DIRECTORY "${CMAKE_SOURCE_DIR}/include/simple"
  DESTINATION include
)
