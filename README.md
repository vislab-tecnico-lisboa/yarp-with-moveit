# yarp-with-moveit

Just some modules to help and complement the usage of yarp and moveit

## Compile yarp-code

    $ cd yarp-code
    $ mkdir build
    $ cd build
    $ cmake ..

Done! You can call the executables now...

## Compile ros-code

    $ mv ros-code/miguel_vislab /wherever/your/catkin/workspace/is/src
    $ cd /wherever/your/catkin/workspace/is/
    $ catkin_make

You might have some dependencies that are not installed, besides that this should be it!

## Forget about the old_code

New is always best, so... don't care about it too much. It's just some old set of modules that I wasn't sure I would use again.
