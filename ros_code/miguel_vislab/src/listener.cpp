#include "ros/ros.h"
#include "moveit_msgs/MoveGroupActionResult.h"
#include "miguel_vislab/SimpleTrajectory.h"
#include "miguel_vislab/SimpleJointTrajectoryPoint.h"

ros::Publisher trajectory_pub;
ros::Publisher velocity_pub;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const moveit_msgs::MoveGroupActionResult& msg) { 
  miguel_vislab::SimpleTrajectory simpleTrajectory;
  miguel_vislab::SimpleTrajectory simpleVelocity;
  ROS_INFO("I heard: [%d]", (int)msg.result.planned_trajectory.joint_trajectory.points.size());
  for(int i = 0; i < msg.result.planned_trajectory.joint_trajectory.points.size(); i++) {
    miguel_vislab::SimpleJointTrajectoryPoint auxPoint;
    miguel_vislab::SimpleJointTrajectoryPoint auxVelocity;
    for(int j = 0; j < 7; j++) {
      auxPoint.positions.push_back(msg.result.planned_trajectory.joint_trajectory.points[i].positions[j]);
      auxVelocity.positions.push_back(msg.result.planned_trajectory.joint_trajectory.points[i].velocities[j]);
    }
    simpleTrajectory.points.push_back(auxPoint);
    simpleVelocity.points.push_back(auxVelocity);
  }
  
  trajectory_pub.publish(simpleTrajectory);
  velocity_pub.publish(simpleVelocity);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/move_group/result", 1000, chatterCallback);
  trajectory_pub = n.advertise<miguel_vislab::SimpleTrajectory>("left_arm_planned_trajectory", 1000);
  velocity_pub = n.advertise<miguel_vislab::SimpleTrajectory>("left_arm_planned_velocity", 1000);

  ros::spin();

  return 0;
}
