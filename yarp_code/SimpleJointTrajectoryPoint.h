// This is an automatically generated file.
// Generated from this SimpleJointTrajectoryPoint.msg definition:
//   [miguel_vislab/SimpleJointTrajectoryPoint]:
//   float64[] positions
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_SimpleJointTrajectoryPoint
#define YARPMSG_TYPE_SimpleJointTrajectoryPoint

#include <string>
#include <vector>
#include <yarp/os/Portable.h>
#include <yarp/os/ConstString.h>
#include <yarp/os/NetInt16.h>
#include <yarp/os/NetUint16.h>
#include <yarp/os/NetInt32.h>
#include <yarp/os/NetUint32.h>
#include <yarp/os/NetInt64.h>
#include <yarp/os/NetUint64.h>
#include <yarp/os/NetFloat32.h>
#include <yarp/os/NetFloat64.h>

class SimpleJointTrajectoryPoint : public yarp::os::Portable {
public:
  yarp::os::Type getType() {
    return yarp::os::Type::byName("SimpleJointTrajectoryPoint");
  }

  std::vector<yarp::os::NetFloat64> positions;

  bool read(yarp::os::ConnectionReader& connection) {
    // *** positions ***
    int len = connection.expectInt();
    positions.resize(len);
    if (!connection.expectBlock((char*)&positions[0],sizeof(yarp::os::NetFloat64)*len)) return false;
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    // *** positions ***
    connection.appendInt(positions.size());
    connection.appendExternalBlock((char*)&positions[0],sizeof(yarp::os::NetFloat64)*positions.size());
    return !connection.isError();
  }
};

#endif
