#include "ros/ros.h"
#include <stdio.h>
#include <stdlib.h>
#include "miguel_vislab/ICubArmState.h"
#include "sensor_msgs/JointState.h"
#include <moveit/move_group_interface/move_group.h>

ros::Publisher chatter_pub;
const double PI = 3.1415926;

void chatterCallback(const miguel_vislab::ICubArmState::ConstPtr& msgReceived) {
  ROS_INFO("Size is: [%d]", (int)msgReceived->data.size());
  for(int i = 0; i < msgReceived->data.size(); i++) {
    ROS_INFO(" [%f] ", (double)msgReceived->data[i]);
  }
  printf("\n\n");
    
  sensor_msgs::JointState msg;
  msg.name.push_back("Front"); // 0
  msg.name.push_back("F_W"); // 1
  msg.name.push_back("Back"); // 2
  msg.name.push_back("B_W"); // 3
  msg.name.push_back("Right"); // 4
  msg.name.push_back("Left"); // 5
  msg.name.push_back("M0"); // 6
  msg.name.push_back("M0L"); // 7
  msg.name.push_back("M1L"); // 8
  msg.name.push_back("M2L"); // 9
  msg.name.push_back("M3L"); // 10
  msg.name.push_back("M4L"); // 11
  msg.name.push_back("M5L"); // 12
  msg.name.push_back("M6L"); // 13
  msg.name.push_back("M7L"); // 14
  msg.name.push_back("M0R"); // 15
  msg.name.push_back("M1R"); // 16
  msg.name.push_back("M2R"); // 17
  msg.name.push_back("M3R"); // 18
  msg.name.push_back("M4R"); // 19
  msg.name.push_back("M5R"); // 20
  msg.name.push_back("M6R"); // 21
  msg.name.push_back("M7R"); // 22
  msg.name.push_back("M1"); // 23
  msg.name.push_back("M2"); // 24
  msg.name.push_back("M3"); // 25
  msg.name.push_back("M4"); // 26
  msg.name.push_back("M5"); // 27
  
  for(int i = 0; i < 28; i++) {
    switch(i) {
      case 23:
        msg.position.push_back((double)msgReceived->data[0] / (180/PI));
        break;
      case 24:
        msg.position.push_back((double)msgReceived->data[1] / (180/PI));
        break;
      case 25:
        msg.position.push_back((double)msgReceived->data[2] / (180/PI));
        break;
      case 6:
        msg.position.push_back((double)msgReceived->data[3] / (180/PI));
        break;
      case 7:
        msg.position.push_back((double)msgReceived->data[4] / (180/PI));
        break;
      case 8:
        msg.position.push_back((double)msgReceived->data[5] / (180/PI));
        break;
      case 9:
        msg.position.push_back((double)msgReceived->data[6] / (180/PI));
        break;
      case 10:
        msg.position.push_back((double)msgReceived->data[7] / (180/PI));
        break;
      case 11:
        msg.position.push_back((double)msgReceived->data[8] / (180/PI));
        break;
      case 12:
        msg.position.push_back((double)msgReceived->data[9] / (180/PI));
        break;
      case 13:
        msg.position.push_back((double)msgReceived->data[10] / (180/PI));
        break;
      case 14:
        msg.position.push_back((double)msgReceived->data[11] / (180/PI));
        break;
      case 15:
        msg.position.push_back((double)msgReceived->data[12] / (180/PI));
        break;
      case 16:
        msg.position.push_back((double)msgReceived->data[13] / (180/PI));
        break;
      case 17:
        msg.position.push_back((double)msgReceived->data[14] / (180/PI));
        break;
      case 18:
        msg.position.push_back((double)msgReceived->data[15] / (180/PI));
        break;
      case 19:
        msg.position.push_back((double)msgReceived->data[16] / (180/PI));
        break;
      case 20:
        msg.position.push_back((double)msgReceived->data[17] / (180/PI));
        break;
      case 21:
        msg.position.push_back((double)msgReceived->data[18] / (180/PI));
        break;
      case 22:
        msg.position.push_back((double)msgReceived->data[19] / (180/PI));
        break;
      default:
        msg.position.push_back(0.0);
    }
  }
  chatter_pub.publish(msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "vizzy_joint_publisher");

  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("/yarp_vizzy_publisher", 1000, chatterCallback);
  chatter_pub = n.advertise<sensor_msgs::JointState>("vizzy_joint_states", 1000);

  ros::spin();

  return 0;
}