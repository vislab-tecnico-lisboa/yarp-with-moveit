#include "ros/ros.h"
#include "moveit_msgs/MoveGroupActionResult.h"
#include "miguel_vislab/SimpleTrajectory.h"
#include "miguel_vislab/SimpleJointTrajectoryPoint.h"
#include "trajectory_msgs/JointTrajectory.h"
#include "trajectory_msgs/JointTrajectoryPoint.h"

ros::Publisher trajectory_pub;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  trajectory_pub = n.advertise<trajectory_msgs::JointTrajectory>("left_arm_planned_trajectory", 1000);
  
  while(true) {
    trajectory_msgs::JointTrajectory simpleTrajectory;
    for(int i = 0; i < 30; i++) {
      //ROS_INFO("I heard: [%d]", i);
      trajectory_msgs::JointTrajectoryPoint auxPoint;
      for(int j = 0; j < 7; j++) {
        auxPoint.positions.push_back(1.0);
      }
      simpleTrajectory.points.push_back(auxPoint);
    }
    trajectory_pub.publish(simpleTrajectory);
  }

  return 0;
}
