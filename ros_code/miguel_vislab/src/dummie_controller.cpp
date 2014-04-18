#include "ros/ros.h"
#include <stdio.h>
#include <stdlib.h>
#include "miguel_vislab/ICubArmState.h"
#include "sensor_msgs/JointState.h"
#include <moveit/move_group_interface/move_group.h>

ros::Publisher chatter_pub;
const double PI = 3.1415926;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const miguel_vislab::ICubArmState::ConstPtr& msgReceived) {
  ROS_INFO("Size is: [%d]", (int)msgReceived->data.size());
  for(int i = 0; i < msgReceived->data.size(); i++) {
    ROS_INFO(" [%f] ", (double)msgReceived->data[i]);
  }
  printf("\n\n", (int)msgReceived->data.size());
    
  sensor_msgs::JointState msg;
  msg.name.push_back("j1");
  msg.name.push_back("j2");
  msg.name.push_back("j3");
  msg.name.push_back("j4");
  msg.name.push_back("j5");
  msg.name.push_back("j6");
  msg.name.push_back("j7");
  msg.name.push_back("j8");
  msg.name.push_back("j7s");
  msg.name.push_back("j8s");
  msg.name.push_back("raj1");
  msg.name.push_back("raj2");
  msg.name.push_back("raj3");
  msg.name.push_back("raj4");
  msg.name.push_back("raj5");
  msg.name.push_back("raj6");
  msg.name.push_back("laj1");
  msg.name.push_back("laj2");
  msg.name.push_back("laj3");
  msg.name.push_back("laj4");
  msg.name.push_back("laj5");
  msg.name.push_back("laj6");
  msg.name.push_back("rlaj1");
  msg.name.push_back("rlaj2");
  msg.name.push_back("rlaj3");
  msg.name.push_back("rlaj4");
  msg.name.push_back("rlaj5");
  msg.name.push_back("rlaj6");
  msg.name.push_back("llaj1");
  msg.name.push_back("llaj2");
  msg.name.push_back("llaj3");
  msg.name.push_back("llaj4");
  msg.name.push_back("llaj5");
  msg.name.push_back("llaj6");
  msg.name.push_back("right_wrist_yaw");
  msg.name.push_back("tj2");
  msg.name.push_back("tj4");
  msg.name.push_back("tj5");
  msg.name.push_back("tj6");
  msg.name.push_back("ij3");
  msg.name.push_back("ij4");
  msg.name.push_back("ij5");
  msg.name.push_back("mj3");
  msg.name.push_back("mj4");
  msg.name.push_back("mj5");
  msg.name.push_back("rij3");
  msg.name.push_back("rij4");
  msg.name.push_back("rij5");
  msg.name.push_back("lij3");
  msg.name.push_back("lij4");
  msg.name.push_back("lij5");
  msg.name.push_back("left_wrist_yaw");
  msg.name.push_back("ltj2");
  msg.name.push_back("ltj4");
  msg.name.push_back("ltj5");
  msg.name.push_back("ltj6");
  msg.name.push_back("laij3");
  msg.name.push_back("laij4");
  msg.name.push_back("laij5");
  msg.name.push_back("lmj3");
  msg.name.push_back("lmj4");
  msg.name.push_back("lmj5");
  msg.name.push_back("lrij3");
  msg.name.push_back("lrij4");
  msg.name.push_back("lrij5");
  msg.name.push_back("llij3");
  msg.name.push_back("llij4");
  msg.name.push_back("llij5");
  
  for(int i = 0; i < 68; i++) {
    switch(i) {
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
      case 34:
        msg.position.push_back((double)msgReceived->data[13] / (180/PI));
        break;
      case 16:
        msg.position.push_back((double)msgReceived->data[0] / (180/PI));
        break;
      case 17:
        msg.position.push_back((double)msgReceived->data[1] / (180/PI));
        break;
      case 18:
        msg.position.push_back((double)msgReceived->data[2] / (180/PI));
        break;
      case 19:
        msg.position.push_back((double)msgReceived->data[3] / (180/PI));
        break;
      case 20:
        msg.position.push_back((double)msgReceived->data[4] / (180/PI));
        break;
      case 21:
        msg.position.push_back((double)msgReceived->data[5] / (180/PI));
        break;
      case 51:
        msg.position.push_back((double)msgReceived->data[6] / (180/PI));
        break;
      default:
        msg.position.push_back(0.0);
    }
  }
  chatter_pub.publish(msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "dummie_controller");

  ros::NodeHandle n;
  ROS_INFO("HELLO\n");
  ros::Subscriber sub = n.subscribe("/icub_feedback", 1000, chatterCallback);
  chatter_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1000);

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
