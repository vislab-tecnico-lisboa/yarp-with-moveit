# Copyright: (C) 2010 RobotCub Consortium
# Author: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

# YARP needs CMake 2.6 or greater
cmake_minimum_required(VERSION 2.8.7)

# find YARP
find_package(YARP REQUIRED)

# add YARP include directories
include_directories(${YARP_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# set up our program
add_executable(apply_trajectory apply_trajectory.cpp)
add_executable(apply_trajectory_direct apply_trajectory_direct.cpp)
add_executable(reproduce_serious_message_error reproduce_serious_message_error.cpp)

# link with YARP libraries
target_link_libraries(apply_trajectory ${YARP_LIBRARIES})
target_link_libraries(apply_trajectory_direct ${YARP_LIBRARIES})
target_link_libraries(reproduce_serious_message_error $(YARP_LIBRARIES))