cmake_minimum_required(VERSION 2.8.3)
project(miguel_vislab)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  sensor_msgs
  moveit_ros_planning_interface
  message_generation
)

add_message_files(
  FILES
  ICubArmState.msg
  SimpleTrajectory.msg
  SimpleJointTrajectoryPoint.msg
  FinalPosition.msg
)

generate_messages(
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)

include_directories(include ${catkin_INCLUDE_DIRS})

add_executable(talker src/talker.cpp)
target_link_libraries(talker ${catkin_LIBRARIES})
add_dependencies(talker miguel_vislab_generate_messages_cpp)

add_executable(listener src/listener.cpp)
target_link_libraries(listener ${catkin_LIBRARIES})
add_dependencies(listener miguel_vislab_generate_messages_cpp)

add_executable(listener_problem src/listener_problem.cpp)
target_link_libraries(listener_problem ${catkin_LIBRARIES})
add_dependencies(listener_problem miguel_vislab_generate_messages_cpp)

add_executable(dummie_controller src/dummie_controller.cpp)
target_link_libraries(dummie_controller ${catkin_LIBRARIES})
add_dependencies(dummie_controller miguel_vislab_generate_messages_cpp)

add_executable(planner src/planner.cpp)
target_link_libraries(planner ${catkin_LIBRARIES})
add_dependencies(planner miguel_vislab_generate_messages_cpp)