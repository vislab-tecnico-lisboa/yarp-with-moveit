#include <yarp/os/all.h>
#include <stdio.h>
#include <stdlib.h>
#include <SimpleJointTrajectoryPoint.h>
#include <SimpleTrajectory.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/Vector.h>

using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;

const double PI = 3.1415926;

int main(int argc, char *argv[]) {

  /* Set up YARP Network */
  Network yarp;
  
  /* Setting the ROS node and the port as read only (ROS subscriber) */
  Node node("/yarp/listener");
  
  /* Alternative not working */
  //BufferedPort<SimpleTrajectory> port;
  Port port;
  port.setReadOnly();
  if (!port.open("/left_arm_planned_trajectory@/yarp/listener")) return 1;
  while (true) {
    //SimpleTrajectory* msg = port.read();
    //Bottle *msg;
    //port.read(*msg);
    /*printf("Got [%d]\n", (int)msg->points.size());
    for(int i = 0; i < msg->points.size(); i++) {
      printf("Got [%d]\n", (int)msg->points[i].positions.size());
      for(int j = 0; j < msg->points[i].positions.size(); j++) {
        printf("Got [%f]\n", msg->points[i].positions[j]);
      }
    }*/
  }
  
  return 0;
}
