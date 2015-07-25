#include <yarp/os/all.h>
#include <stdio.h>
#include <stdlib.h>

using namespace yarp::os;

int main(int argc, char *argv[]) {

	Network yarp;

  BufferedPort<Bottle> vizzyHeadReceiver;
  BufferedPort<Bottle> vizzyTorsoReceiver;
  BufferedPort<Bottle> vizzyLeftArmReceiver;
  BufferedPort<Bottle> vizzyRightArmReceiver;
  
  bool headOk = vizzyHeadReceiver.open("/vizzy_joint_publisher/head_receiver");
  bool torsoOk = vizzyTorsoReceiver.open("/vizzy_joint_publisher/torso_receiver");
  bool leftArmOk = vizzyLeftArmReceiver.open("/vizzy_joint_publisher/left_arm_receiver");
  bool rightArmOk = vizzyRightArmReceiver.open("/vizzy_joint_publisher/right_arm_receiver");

  Port outputPort;
  outputPort.setWriteOnly();
  bool outputOk = outputPort.open("/vizzy_joint_states@/yarp/vizzy_joint_publisher");

  if(!headOk || !torsoOk || !leftArmOk || !rightArmOk || !outputOk) {
    fprintf(stderr, "Failed to create ports.\n");
    fprintf(stderr, "Maybe you need to start a nameserver (run 'yarpserver').\n");
    return 1;
  }

  printf("\n\n WAIT FOR JOINT PUBLISHER CONFIGURATION \n\n");
  for(int i = 0; i <= 10; i++) {
    Time::delay(2);
    printf(" %d%%...\n", i*10);
  }
  printf("\n READY TO START PLANNING \n\n");

  yarp.connect("/vizzySim/head/state:o", vizzyHeadReceiver.getName());
  yarp.connect("/vizzySim/torso/state:o", vizzyTorsoReceiver.getName());
  yarp.connect("/vizzySim/left_arm/state:o", vizzyLeftArmReceiver.getName());
  yarp.connect("/vizzySim/right_arm/state:o", vizzyRightArmReceiver.getName());

  while(true){
  	Bottle *headReading = vizzyHeadReceiver.read();
  	Bottle *torsoReading = vizzyTorsoReceiver.read();
  	Bottle *leftArmReading = vizzyLeftArmReceiver.read();
  	Bottle *rightArmReading = vizzyRightArmReceiver.read();

  	if (headReading == NULL || torsoReading == NULL || leftArmReading == NULL || rightArmReading == NULL) {
      fprintf(stderr, "Failed to read message from at least one of the ports.\n");
      return 1;
    }

    Bottle bottleToSend = Bottle();
    Bottle& listOnBottle = bottleToSend.addList();

    for(int i = 0; i < headReading->size(); i++) {
    	listOnBottle.addDouble(headReading->get(i).asDouble());
      printf("\n[DEBUG POS] pos[%f]\n", headReading->get(i).asDouble()); // debug
    }
    for(int i = 0; i < torsoReading->size(); i++) {
    	listOnBottle.addDouble(torsoReading->get(i).asDouble());
      printf("\n[DEBUG POS] pos[%f]\n", torsoReading->get(i).asDouble()); // debug
    }
    for(int i = 0; i < leftArmReading->size(); i++) {
    	listOnBottle.addDouble(leftArmReading->get(i).asDouble());
      printf("\n[DEBUG POS] pos[%f]\n", leftArmReading->get(i).asDouble()); // debug
    }
    for(int i = 0; i < rightArmReading->size(); i++) {
    	listOnBottle.addDouble(rightArmReading->get(i).asDouble());
      printf("\n[DEBUG POS] pos[%f]\n", rightArmReading->get(i).asDouble()); // debug
    }

    outputPort.write(bottleToSend);
  }

  return 0;
}