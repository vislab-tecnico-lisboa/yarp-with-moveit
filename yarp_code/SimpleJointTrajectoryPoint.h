// This is an automatically generated file.
// Generated from this SimpleJointTrajectoryPoint.msg definition:
//   float64[] positions
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_SimpleJointTrajectoryPoint
#define YARPMSG_TYPE_SimpleJointTrajectoryPoint

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>

class SimpleJointTrajectoryPoint : public yarp::os::idl::WirePortable {
public:
  std::vector<yarp::os::NetFloat64> positions;

  SimpleJointTrajectoryPoint() {
  }

  bool readBare(yarp::os::ConnectionReader& connection) {
    // *** positions ***
    int len = connection.expectInt();
    positions.resize(len);
    if (!connection.expectBlock((char*)&positions[0],sizeof(yarp::os::NetFloat64)*len)) return false;
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(1)) return false;

    // *** positions ***
    if (connection.expectInt()!=(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE)) return false;
    int len = connection.expectInt();
    positions.resize(len);
    for (size_t i=0; i<len; i++) {
      positions[i] = (yarp::os::NetFloat64)connection.expectDouble();
    }
    return !connection.isError();
  }

  bool read(yarp::os::ConnectionReader& connection) {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) {
    // *** positions ***
    connection.appendInt(positions.size());
    connection.appendExternalBlock((char*)&positions[0],sizeof(yarp::os::NetFloat64)*positions.size());
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(1);

    // *** positions ***
    connection.appendInt(BOTTLE_TAG_LIST|BOTTLE_TAG_DOUBLE);
    connection.appendInt(positions.size());
    for (size_t i=0; i<positions.size(); i++) {
      connection.appendDouble((double)positions[i]);
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
  typedef yarp::os::idl::BareStyle<SimpleJointTrajectoryPoint> rosStyle;
  typedef yarp::os::idl::BottleStyle<SimpleJointTrajectoryPoint> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "float64[] positions\n\
";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() {
    yarp::os::Type typ = yarp::os::Type::byName("miguel_vislab/SimpleJointTrajectoryPoint","miguel_vislab/SimpleJointTrajectoryPoint");
    typ.addProperty("md5sum",yarp::os::Value("3b33cf2d1f9005e741ee291d519b97ee"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif
