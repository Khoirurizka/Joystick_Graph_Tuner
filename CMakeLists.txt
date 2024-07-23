cmake_minimum_required(VERSION 3.10)

# Project name
project(JoystickGraphTuner)



#find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

#find_package(pybind11 2.13.1 REQUIRED) #set spesific when crash with ROS lib

# Find GTK+3 package
find_package(PkgConfig REQUIRED)
#pkg_check_modules(GTK REQUIRED gtk+-3.0)

#find_package(VTK REQUIRED)
#find_package(Boost REQUIRED COMPONENTS iostreams system filesystem)

#add_subdirectory(matplotlib-cpp)
#find_package( matplotlib_cpp)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
# Include GTK headers
include_directories(${GTK_INCLUDE_DIRS})
# Find the SymEngine package
#find_package(SymEngine REQUIRED)


#include_directories(${VTK_INCLUDE_DIRS})
#include(${VTK_USE_FILE})
#include_directories(${Boost_INCLUDE_DIRS})
#include_directories(${Python3_INCLUDE_DIRS})
#include_directories(/usr/local/include)
#message("scan: ${Python3_INCLUDE_DIRS}")
#include_directories(/usr/local/include/symengine)

# Add executable
add_executable(JoystickGraphTuner src/main.cpp)

# Link GTK libraries

#target_link_libraries(JoystickGraphTuner INTERFACE
#  Python3::Python
#  Python3::Module
#)
target_link_libraries(JoystickGraphTuner  ${GTK_LIBRARIES}) 
#${VTK_LIBRARIES} ${Boost_LIBRARIES} pybind11::embed Python3::Python Python3::Module ${PYTHON_LIBRARIES}


# Set C++ standard
set_property(TARGET JoystickGraphTuner PROPERTY CXX_STANDARD 11)

