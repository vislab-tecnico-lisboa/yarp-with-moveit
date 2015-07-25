#include <yarp/os/all.h>
#include <stdio.h>
#include <stdlib.h>
#include <moveit_msgs_MoveGroupActionResult.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/sig/Vector.h>
#include <cmath>

using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;

const double PI = 3.1415926;

int main(int argc, char *argv[]) {

  /* Set up YARP Network */
  Network yarp;
  
  // Make a port called /yarp_to_ros/yarp_receiver to receive the data from the yarp port unknown on the ROSCORE
  // We'll send "Bottles" (a simple nested list container) between these ports
  BufferedPort<Bottle> inPort;
  bool ok = inPort.open("/yarp_to_ros/yarp_receiver");
  //yarp.connect("/icubSim/right_arm/state:o",inPort.getName());
  
  /* Setting the ROS node and the port as read only (ROS subscriber) */
  //Node node("/yarp/listener");
  //Port port;
  //port.setReadOnly();
  BufferedPort<moveit_msgs_MoveGroupActionResult> port;
  port.setReadOnly();
  
  /* Checking if the topic/port is available */
  if (!port.open("/move_group/result@/yarp/listener")) return 1;
  
  /* Main cycle to get the planned trajectory and command the robot arm to the desired positions */
  while (true) {
    
    /* Blocking on the read function to get the message and store it on msg variable */
    //Bottle msg;
    moveit_msgs_MoveGroupActionResult* msg = port.read();
    
    int numOfPoints = (int)msg->result.planned_trajectory.joint_trajectory.points.size();
    
    for(int i = 0; i < numOfPoints; i++) {
      /* Get the size of the list of positions */
      int bottleSize = (int)msg->result.planned_trajectory.joint_trajectory.points[i].positions.size();
      
      /* Just some debug to print the point structure */
      printf("\n[DEBUG] Positions for all the joints until the hand (in rads)...\n"); // debug
      printf("[DEBUG] (");
      for(int j = 0; j < bottleSize; j++) {
        printf(" [%f]", msg->result.planned_trajectory.joint_trajectory.points[i].positions[j]);
      }
      printf(" )\n\n");
      /* End of debug */
    }
  }
  
  return 0;
}
