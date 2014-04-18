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
add_executable(yarp_joint_publisher yarp_joint_publisher.cpp)
add_executable(yarp_joint_publisher_icub yarp_joint_publisher_icub.cpp)
add_executable(apply_trajectory_problem apply_trajectory_problem.cpp)

# link with YARP libraries
target_link_libraries(apply_trajectory ${YARP_LIBRARIES})
target_link_libraries(yarp_joint_publisher ${YARP_LIBRARIES})
target_link_libraries(yarp_joint_publisher_icub ${YARP_LIBRARIES})
target_link_libraries(apply_trajectory_problem ${YARP_LIBRARIES})
