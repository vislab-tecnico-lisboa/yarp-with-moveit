#include "ros/ros.h"
#include <stdio.h>
#include <stdlib.h>
#include "miguel_vislab/ICubArmState.h"

ros::Publisher chatter_pub;
int counter = 0;
std::vector<double> new_pos;
const double PI = 3.1415926;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const miguel_vislab::ICubArmState::ConstPtr& msgReceived) {
  ROS_INFO("I heard size is: [%d]", (int)msgReceived->data.size());
  for(int i = 0; i < msgReceived->data.size(); i++) {
    ROS_INFO("I heard: [%f]", (double)msgReceived->data[i]);
  }
  //ROS_INFO("HEY\n");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;
  ROS_INFO("HELLO\n");
  ros::Subscriber sub = n.subscribe("/icub_feedback", 1000, chatterCallback);

  ros::spin();
  
  /*while(true) {
    miguel_vislab::SimpleTrajectory simpleTrajectory;
    for(int i = 0; i < 30; i++) {
      //ROS_INFO("I heard: [%d]", i);
      miguel_vislab::SimpleJointTrajectoryPoint auxPoint;
      for(int j = 0; j < 7; j++) {
        auxPoint.positions.push_back(1.0);
      }
      simpleTrajectory.points.push_back(auxPoint);
    }
    trajectory_pub.publish(simpleTrajectory);
  }*/

  return 0;
}
