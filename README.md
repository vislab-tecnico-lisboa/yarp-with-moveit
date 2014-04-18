# yarp-with-moveit

Integration between iCub YARP and ROS MoveIt! for the execution of the planned trajectories by the robot simulator

## Environment

All the functionality was tested on machines configured with:

+ Ubuntu 12.04 LTS
+ ROS Hydro (install it [here](http://wiki.ros.org/hydro/Installation/Ubuntu))
+ YARP 2.3.62.1

## Prerequisites

This package is a complement to the iCub MoveIt! planning, so, in order to run the modules from this package, you should be able to run with no problems [this repository](https://github.com/vislab-tecnico-lisboa/icub-moveit).

Compile YARP with the following flags enabled:

+ CREATE_OPTIONAL_CARRIERS
+ CREATE_IDLS
+ ENABLE_yarpcar_tcpros_carrier
+ ENABLE_yarpcar_rossrv_carrier
+ ENABLE_yarpcar_xmlrpc_carrier
+ ENABLE_yarpidl_rosmsg

Make sure your YARP namespace is not /root or /ros. You can change it with:

    yarp namespace /icub

You can choose another name instead of /icub (just remember not choosing /root or /ros).

You will need to have xterm installed:

    sudo apt-get install xterm

After concluding that you can start following the next instructions.

## Download and Setup

Open a terminal and navigate to the folder where you want to download the package.

Now, run:

    git clone https://github.com/vislab-tecnico-lisboa/yarp-with-moveit.git

After completing the download, you should execute some instructions to setup your environment:

    cd [Path to the downloaded folder]/yarp_code
    mkdir build

And now, to finish your setup, you will have to create a catkin workspace to compile and run the ROS modules:

    mkdir -p [Choose a location for your catkin workspace]/ros_yarp/src
    cd [Path to your catkin workspace]/src
    catkin_init_workspace
    cd [Path to your catkin workspace]
    catkin_make
    sudo gedit ~/.bashrc

At the end of the file, add the following lines:

    export ROS_PACKAGE_PATH=[Path to your catkin workspace]:$ROS_PACKAGE_PATH
    source [Path to your catkin workspace]/devel/setup.bash

Save the file and run:

    source ~/.bashrc
    cp -a [Path to the downloaded folder]/ros_code/miguel_vislab/ [Path to your catkin workspace]/src/

## Compilation

You have to compile both the ROS and YARP code:

    cd [Path to your catkin workspace]
    catkin_make
    cd [Path to the downloaded folder]/yarp_code/build
    cmake ..
    make

## Running

As mentioned on the prerequisites section you should be able to run the other repository with no problems to work with these modules.

If you have followed everything as stated in here, you should now be able to run all the modules!

Open a terminal:

    roscore

Open another terminal:

    yarpserver --ros

Open another terminal:

    iCub_SIM

Open another terminal:

    cd [Path to the downloaded folder]/yarp_code
    sh run_planner.sh

This last command will open 7 different xterm windows. Give them time to initialize everything. You will know that everything is ready to work when the xterm window running the command `roslaunch icub_moveit functional.launch` stabilizes and shows a green message.

Now you can open a new terminal and publish, to a rostopic, a desired position for the end effector:

    rostopic pub /pose_to_achieve miguel_vislab/FinalPosition "{xp: 0.0, yp: 0.0, zp: 0.0, xo: 0.0, yo: 0.0, zo: 0.0, wo: 0.0}"

Choose whatever values you want to achieve.

For now this code is working with the iCub_SIM but it is easy to change it to interact with the real robot. Will add some configuration files to select the one to interact with.
