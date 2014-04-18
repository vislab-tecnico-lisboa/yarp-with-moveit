#include "ros/ros.h"
#include <stdio.h>
#include <stdlib.h>
#include <moveit/move_group_interface/move_group.h>
#include "miguel_vislab/FinalPosition.h"
#include <ros/callback_queue.h>

const double PI = 3.1415926;
move_group_interface::MoveGroup *group;

void chatterCallback(const miguel_vislab::FinalPosition& msg) {
  ROS_INFO("The end effector is: %s\n", group->getEndEffectorLink().c_str());
  //group->setGoalTolerance(0.05);
  ROS_INFO("The orientation tolerance is: %f\n", group->getGoalOrientationTolerance());
  ROS_INFO("The position tolerance is: %f\n", group->getGoalPositionTolerance());
  group->setStartStateToCurrentState();  
  
  geometry_msgs::PoseStamped position =	group->getRandomPose();
  position.pose.position.x = msg.xp;
  position.pose.position.y = msg.yp;
  position.pose.position.z = msg.zp;
  position.pose.orientation.x = msg.xo;
  position.pose.orientation.y = msg.yo;
  position.pose.orientation.z = msg.zo;
  position.pose.orientation.w = msg.wo;
  
  ROS_INFO("The pose is: %f,%f,%f,%f,%f,%f,%f.", position.pose.position.x, position.pose.position.y, position.pose.position.z, position.pose.orientation.x, position.pose.orientation.y, position.pose.orientation.z, position.pose.orientation.w);
  group->setPoseTarget(position);
  
  moveit::planning_interface::MoveGroup::Plan my_plan;
  ROS_INFO("WILL PLAN NOW!\n");
  ROS_INFO_STREAM("Experience!!");
  bool ok = group->plan(my_plan);
  //sleep(5.0);
  geometry_msgs::PoseStamped achievedPos =	group->getCurrentPose();
  ROS_INFO("The achieved pose is: %f,%f,%f,%f,%f,%f,%f.", achievedPos.pose.position.x, achievedPos.pose.position.y, achievedPos.pose.position.z, achievedPos.pose.orientation.x, achievedPos.pose.orientation.y, achievedPos.pose.orientation.z, achievedPos.pose.orientation.w);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "planner");

  ros::NodeHandle n;
  ros::CallbackQueue my_callback_queue;
  n.setCallbackQueue(&my_callback_queue);
  group = new move_group_interface::MoveGroup("right_arm");
  
  ros::Subscriber sub = n.subscribe("/pose_to_achieve", 1000, chatterCallback);
  
  ROS_INFO("PLANNER\n");
  ROS_INFO("READY\n");
  ros::AsyncSpinner spinner(0, &my_callback_queue);
	spinner.start();


	ros::spin();
  //ros::spin();
  
  //while(true) {
    
    //group->setRandomTarget();
    /*double x_pos, y_pos, z_pos, x_ori, y_ori, z_ori, w_ori;
    std::cout << "Please enter a double value for the x_pos: ";
    std::cin >> x_pos;
    std::cout << "Please enter a double value for the y_pos: ";
    std::cin >> y_pos;
    std::cout << "Please enter a double value for the z_pos: ";
    std::cin >> z_pos;
    std::cout << "Please enter a double value for the x_ori: ";
    std::cin >> x_ori;
    std::cout << "Please enter a double value for the y_ori: ";
    std::cin >> y_ori;
    std::cout << "Please enter a double value for the z_ori: ";
    std::cin >> z_ori;
    std::cout << "Please enter a double value for the w_ori: ";
    std::cin >> w_ori;
    group->setPositionTarget(x_pos, y_pos, z_pos, "right_palm");
    group->setOrientationTarget(x_ori, y_ori, z_ori, w_ori,"right_palm");*/
    
    /*geometry_msgs::Pose target_pose1;
    target_pose1.orientation.w = 1.0;
    target_pose1.position.x = 0.28;
    target_pose1.position.y = -0.7;
    target_pose1.position.z = 1.0;
    group->setPoseTarget(target_pose1);*/
    
    /*ROS_INFO("0%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("10%%...WAITING FOR NEXT PLAN!\n");
    sleep(2.0);
    ROS_INFO("20%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("30%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("40%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("50%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("60%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("70%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("80%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("90%%...WAITING FOR NEXT PLAN!\n");
    sleep(1.0);
    ROS_INFO("100%%...WAITING FOR NEXT PLAN!\n");*/
  //}
  
  return 0;
}
