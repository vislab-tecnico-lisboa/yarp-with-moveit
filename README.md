# yarp-with-moveit

Integration between iCub YARP and ROS MoveIt! for the execution of the planned trajectories by the robot simulator

## Environment

All the functionality was tested on machines configured with:

+ Ubuntu 12.04 LTS
+ ROS Hydro (install it [here](http://wiki.ros.org/hydro/Installation/Ubuntu))
+ YARP 2.3.62.1

## Prerequisites

This package is a complement to the iCub MoveIt! planning, so, in order to run the modules from this package, you should be able to run with no problems [this repository](https://github.com/vislab-tecnico-lisboa/icub-moveit).

After concluding that you can start following the next instructions.

## Download and Setup

Open a terminal and navigate to the folder where you want to download the package.

Now, run:

    git clone https://github.com/vislab-tecnico-lisboa/yarp-with-moveit.git

After completing the download, you should execute some instructions to setup your environment:

    cd [Path to the downloaded folder]/yarp_code
    mkdir build

And now, to finish your setup, you will have to create a catkin workspace to compile and run the ROS modules, run:

    mkdir -p [Choose a location for your catkin workspace]
    cd [Path to your catkin workspace]/src
    catkin_init_workspace
    cd [Path to your catkin workspace]
    catkin_make
    sudo gedit ~/.bashrc

At the end of the file, add the following lines:

    source [Path to your catkin workspace]/devel/setup.bash
    export ROS_PACKAGE_PATH=[Path to your catkin workspace]:$ROS_PACKAGE_PATH

Save the file and run:

    source .bashrc
    cp -a [Path to the downloaded folder]/ros_code/miguel_vislab/ [Path to your catkin workspace]/src/
