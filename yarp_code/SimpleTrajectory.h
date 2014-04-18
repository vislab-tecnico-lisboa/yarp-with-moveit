// This is an automatically generated file.
// Generated from this SimpleTrajectory.msg definition:
//   SimpleJointTrajectoryPoint[] points
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_SimpleTrajectory
#define YARPMSG_TYPE_SimpleTrajectory

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
#include <SimpleJointTrajectoryPoint.h>

class SimpleTrajectory : public yarp::os::Portable {
public:
  yarp::os::Type getType() {
    return yarp::os::Type::byName("SimpleTrajectory");
  }

  std::vector<SimpleJointTrajectoryPoint> points;

  bool read(yarp::os::ConnectionReader& connection) {
    // *** points ***
    int len = connection.expectInt();
    points.resize(len);
    for (int i=0; i<len; i++) {
      if (!points[i].read(connection)) return false;
    }
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    // *** points ***
    connection.appendInt(points.size());
    for (int i=0; i<points.size(); i++) {
      if (!points[i].write(connection)) return false;
    }
    return !connection.isError();
  }
};

#endif
