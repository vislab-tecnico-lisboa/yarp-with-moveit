#include <yarp/os/all.h>
#include <stdio.h>
#include <stdlib.h>
#include <SimpleJointTrajectoryPoint.h>
#include <SimpleTrajectory.h>
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
  yarp.connect("/icubSim/right_arm/state:o",inPort.getName());
  
  /* Preparing a set of configuration parameters */
  Property options;
  options.put("device", "remote_controlboard");
  options.put("local", "/test/client");           //local port names
  options.put("remote", "/icubSim/right_arm");    //where we connect to
  
  /* Creating the PolyDriver */
  PolyDriver robotDevice(options);
  if (!robotDevice.isValid()) {
    printf("Device not available.  Here are the known devices:\n");
    printf("%s", Drivers::factory().toString().c_str());
    return 1;
  }
  
  /* Set pointers to the interfaces needed (position control) */
  //miguel IPositionControl *pos;
  //miguel robotDevice.view(pos);

  IControlMode2     *modArm;
  IPositionDirect   *posArm;
  robotDevice.view(modArm);
  robotDevice.view(posArm);
  
  /* Check if pointers to the interfaces are valid */
  //miguel if (pos==0) {
    //miguel printf("Error getting IPositionControl interface.\n");
    //miguel return 1;
  //miguel }
   
  /* Get the number of joints available on the left_arm */
  int jnts = 0;
  //miguel pos->getAxes(&jnts);
  posArm->getAxes(&jnts);
  printf("\n[DEBUG] Number of joints: %d...\n\n", jnts); // debug
  
  /* Creating and resizing the vectors needed to interact with the interfaces */
  Vector tmp;
  Vector command_position;
  tmp.resize(jnts);
  command_position.resize(jnts);
    
  /* Setting the acceleration of each joint (here 50 degrees/sec^2) */
  int i;
  for (i = 0; i < jnts; i++) {
    tmp[i] = 0.0;
  }
  //miguel pos->setRefAccelerations(tmp.data());
  
  for (i = 0; i < jnts; i++) {
    tmp[i] = 0.0;
  }
  //miguel pos->setRefSpeeds(tmp.data());

  VectorOf<int> modes;
  VectorOf<int> jointsToSet;
  jointsToSet.resize(16);

  for(int k = 0; k < jnts; k++) {
    jointsToSet[k] = k;
    modes.push_back(VOCAB_CM_POSITION_DIRECT);
  }
  modArm->setControlModes(jointsToSet.size(),jointsToSet.getFirst(),modes.getFirst());
  
  /* Setting the ROS node and the port as read only (ROS subscriber) */
  Node node("/yarp/listener");
  //Port port;
  //port.setReadOnly();
  BufferedPort<SimpleTrajectory> port;
  port.setReadOnly();
  
  /* Checking if the topic/port is available */
  if (!port.open("/left_arm_planned_trajectory@/yarp/listener")) return 1;
  
  BufferedPort<SimpleTrajectory> velocityPort;
  velocityPort.setReadOnly();
  
  /* Checking if the topic/port is available */
  if (!velocityPort.open("/left_arm_planned_velocity@/yarp/listener")) return 1;
  
  /* Main cycle to get the planned trajectory and command the robot arm to the desired positions */
  while (true) {
    
    /* Blocking on the read function to get the message and store it on msg variable */
    //Bottle msg;
    SimpleTrajectory* msg = port.read();
    SimpleTrajectory* msgVelocity = velocityPort.read();
    //if (!port.read(msg)) continue;
    
    int numOfPoints = (int)msg->points.size();
    
    for(i = 0; i < numOfPoints; i++) {
      /* Get the size of the list of positions */
      int bottleSize = (int)msg->points[i].positions.size();
      
      /* Just some debug to print the point structure */
      printf("\n[DEBUG] Positions for all the joints until the hand (in rads)...\n"); // debug
      printf("[DEBUG] (");
      for(int j = 0; j < bottleSize; j++) {
        printf(" [%f]", msg->points[i].positions[j]);
      }
      printf(" )\n\n");
      /* End of debug */
      
      /* Just some debug to print the point structure */
      printf("\n[DEBUG] Velocities for all the joints until the hand (in rads/s)...\n"); // debug
      printf("[DEBUG] (");
      for(int j = 0; j < bottleSize; j++) {
        printf(" [%f]", msgVelocity->points[i].positions[j]);
      }
      printf(" )\n\n");
      /* End of debug */
      
      /* Populate the vector with the desired position of each joint */
      for(int j = 0; j < bottleSize; j++) {
        command_position[j] = msg->points[i].positions[j] * (180/PI);
        //if(i == 0) {
          //tmp[j] = 200.0;
        //} else {
          //tmp[j] = msgVelocity->points[i].positions[j] * (180/PI) * 2;
        //}
      }
      //pos->setRefSpeeds(tmp.data());
      /* Positions of the joints that compose the hand are hardcoded */
      command_position[7] = 59.000989;
      command_position[8] = 20.000335;
      command_position[9] = 20.000335;
      command_position[10] = 20.000335;
      command_position[11] = 10.000168;
      command_position[12] = 10.000168;
      command_position[13] = 10.000168;
      command_position[14] = 10.000168;
      command_position[15] = 10.000168;
      
      Bottle *in = inPort.read();
      for(int j = 0; j < 7; j++) {
        double current = in->get(j).asDouble();
        double velocity = abs((command_position[j] - current)) * 6;
        if(velocity > 80)
          velocity = 80;
        if(velocity == 0)
          velocity = 5;
        printf("Velocity joint number %d: [%f]\n", j, velocity);
        tmp[j] = velocity;
      }
      for (int j = 7; j < jnts; j++) {
        tmp[j] = 0.0;
      }
      //miguel pos->setRefSpeeds(tmp.data());
      /* Moving the joints to the desired positions */
      //miguel bool ok = pos->positionMove(command_position.data());
      bool ok = posArm->setPositions(jointsToSet.size(),jointsToSet.getFirst(),command_position.data());
      bool done=false;
      
      Time::delay(0.1);
      /* Waiting for the movement to be completed */
      //miguel if(i == numOfPoints -1) {
        //miguel while(!done) {
        //Bottle *in = inPort.read();
        //done = true;
        //for(int m = 0; m < 6; m++) {
          //double posToCheck = in->get(m).asDouble();
          //if(!(posToCheck < (command_position[m] + 1) && posToCheck > (command_position[m] - 1))) {
            //done = false;
          //}
        //}
        //miguel pos->checkMotionDone(&done);
        //miguel Time::delay(0.2);
        //miguel }
      //miguel }
      if(done)
        printf("\n\n MOTION TRAJECTORY COMPLETED \n\n");
    }
  }
  
  return 0;
}
