xterm -e yarpidl_rosmsg --name /typ@/yarpros &
xterm -e optirun roslaunch icub_moveit demo.launch &
xterm -e ./build/yarp_joint_publisher_icub &
xterm -e rosrun miguel_vislab dummie_controller &
xterm -e ./build/apply_trajectory &
xterm -e rosrun miguel_vislab listener &
xterm -e rosrun miguel_vislab planner
