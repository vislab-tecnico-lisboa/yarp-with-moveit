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
  ros::init(argc, argv, "moveit_interface");

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
  
  return 0;
}
