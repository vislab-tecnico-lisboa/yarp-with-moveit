#include <yarp/os/all.h>
#include <stdio.h>
#include <stdlib.h>

using namespace yarp::os;

int main(int argc, char *argv[]) {

  Network yarp;
  
  // Make a port called /yarp_to_ros/yarp_receiver to receive the data from the yarp port unknown on the ROSCORE
  // We'll send "Bottles" (a simple nested list container) between these ports
  BufferedPort<Bottle> inPortLeftArm;
  BufferedPort<Bottle> inPortRightArm;
  bool ok = inPortLeftArm.open("/yarp_to_ros/yarp_receiver_publisher_left");
  bool ok_right = inPortRightArm.open("/yarp_to_ros/yarp_receiver_publisher_right");

  // Make a port called   
  Port outPort;
  outPort.setWriteOnly();
  if (!outPort.open("/icub_feedback@/yarp/intermediate")) return 1;
  if (!ok || !ok_right) {
    fprintf(stderr, "Failed to create ports.\n");
    fprintf(stderr, "Maybe you need to start a nameserver (run 'yarpserver')\n");
    return 1;
  }
  
  yarp.connect("/icubSim/left_arm/state:o",inPortLeftArm.getName());
  yarp.connect("/icubSim/right_arm/state:o",inPortRightArm.getName());

  printf("\n\n WAIT FOR JOINT PUBLISHER CONFIGURATION \n\n");
  for(int i = 0; i <= 10; i++) {
    Time::delay(1);
    printf(" %d%%...\n", i*10);
  }
  printf("\n READY TO START PLANNING \n\n");
  
  while(true) {
    Bottle *in = inPortLeftArm.read();
    Bottle *in_right = inPortRightArm.read();
    if (in==NULL) {
      fprintf(stderr, "Failed to read message\n");
      return 1;
    }
    Bottle toSend = Bottle();
    Bottle& data = toSend.addList();
    for(int m = 0; m < 7; m++) {
      data.addDouble(in->get(m).asDouble());
      printf("\n[DEBUG POS] pos[%f]\n", in->get(m).asDouble()); // debug
    }
    for(int m = 0; m < 7; m++) {
      data.addDouble(in_right->get(m).asDouble());
      printf("\n[DEBUG POS] pos[%f]\n", in_right->get(m).asDouble()); // debug
    }
    outPort.write(toSend);
  }
  
  return 0;
}
