// This is an automatically generated file.
// Generated from this SimpleTrajectory.msg definition:
//   SimpleJointTrajectoryPoint[] points
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_SimpleTrajectory
#define YARPMSG_TYPE_SimpleTrajectory

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include "SimpleJointTrajectoryPoint.h"

class SimpleTrajectory : public yarp::os::idl::WirePortable {
public:
  std::vector<SimpleJointTrajectoryPoint> points;

  SimpleTrajectory() {
  }

  bool readBare(yarp::os::ConnectionReader& connection) {
    // *** points ***
    int len = connection.expectInt();
    points.resize(len);
    for (int i=0; i<len; i++) {
      if (!points[i].read(connection)) return false;
    }
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(1)) return false;

    // *** points ***
    if (connection.expectInt()!=BOTTLE_TAG_LIST) return false;
    int len = connection.expectInt();
    points.resize(len);
    for (int i=0; i<len; i++) {
      if (!points[i].read(connection)) return false;
    }
    return !connection.isError();
  }

  bool read(yarp::os::ConnectionReader& connection) {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) {
    // *** points ***
    connection.appendInt(points.size());
    for (size_t i=0; i<points.size(); i++) {
      if (!points[i].write(connection)) return false;
    }
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(1);

    // *** points ***
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(points.size());
    for (size_t i=0; i<points.size(); i++) {
      if (!points[i].write(connection)) return false;
    }
    connection.convertTextMode();
    return !connection.isError();
  }

  bool write(yarp::os::ConnectionWriter& connection) {
    if (connection.isBareMode()) return writeBare(connection);
    return writeBottle(connection);
  }

  // This class will serialize ROS style or YARP style depending on protocol.
  // If you need to force a serialization style, use one of these classes:
  typedef yarp::os::idl::BareStyle<SimpleTrajectory> rosStyle;
  typedef yarp::os::idl::BottleStyle<SimpleTrajectory> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "SimpleJointTrajectoryPoint[] points\n\
\n================================================================================\n\
MSG: miguel_vislab/SimpleJointTrajectoryPoint\n\
float64[] positions\n\
";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() {
    yarp::os::Type typ = yarp::os::Type::byName("miguel_vislab/SimpleTrajectory","miguel_vislab/SimpleTrajectory");
    typ.addProperty("md5sum",yarp::os::Value("51a1216f17171544823c1508aabe5993"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif
