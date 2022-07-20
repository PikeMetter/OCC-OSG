cmake_minimum_required(VERSION 2.8.7)
project(OSGView)

find_package(OpenSceneGraph REQUIRED COMPONENTS osgDB osgViewer)

# Also add some useful compiler flag
set(CMAKE_CXX_FLAGS
   "${CMAKE_CXX_FLAGS} -msse4.1 -msse3 -msse2 -msse -march=native -O3 -std=c++0x"
)

set(SOURCE_FILES
  src/main.cpp
)

include_directories(
  ${OPENSCENEGRAPH_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}  ${OPENSCENEGRAPH_LIBRARIES})