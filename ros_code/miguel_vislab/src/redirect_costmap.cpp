#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include <fstream>
#include <sstream>
#include <string>

ros::Publisher trajectory_pub;
ros::Publisher velocity_pub;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const nav_msgs::OccupancyGrid& msg) {
  ROS_INFO("I heard something!\n\n");
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<nav_msgs::OccupancyGrid>("/map", 1000);

  nav_msgs::OccupancyGrid msg;

  msg.header.seq = 0;
  msg.header.frame_id = "map";

  msg.info.resolution = 0.025;
  msg.info.width = 1152;
  msg.info.height = 1000;
  msg.info.origin.position.x = -25;
  msg.info.origin.position.y = -2;
  msg.info.origin.position.z = 0;

  msg.info.origin.orientation.x = 0;
  msg.info.origin.orientation.y = 0;
  msg.info.origin.orientation.z = 0;
  msg.info.origin.orientation.w = 1;

  std::ifstream infile("/home/miguel/codes.txt");
  std::string line;
  std::getline(infile, line);
  int first = 0, last, exp = 1;
  for(int i = 0; i < line.size(); i++) {
  	if(line[i] == ',') {
  		exp = atoi(line.substr(first,i - 1).c_str());
  		msg.data.push_back(exp);
  		first = i + 2;
  	}
  }
  printf("\n\n%d\n\n", exp);

  while(true) {
  	pub.publish(msg);
  }

  return 0;
}