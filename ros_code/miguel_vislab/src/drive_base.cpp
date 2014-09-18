#include <iostream>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <SDL/SDL.h>
#include <QtCore/QMutex>

#define JOY_DEADBAND 3200
#define JOY_MAX_VALUE 32768

class RobotDriver
{
private:
  //! The node handle we'll be using
  ros::NodeHandle nh_;
  //! We will be publishing to the "/base_controller/command" topic to issue commands
  ros::Publisher cmd_vel_pub_;

  SDL_Joystick * joystick_;
  QMutex joy_mutex_;

public:
  //! ROS node initialization
  RobotDriver(ros::NodeHandle &nh)
  {
    nh_ = nh;
    //set up the publisher for the cmd_vel topic
    cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  }

  //! Loop forever while sending drive commands based on keyboard input
  bool driveKeyboard()
  {
    std::cout << "Type a command and then press enter.  "
      "Use '+' to move forward, 'l' to turn left, "
      "'r' to turn right, '.' to exit.\n";

    //we will be sending commands of type "twist"
    geometry_msgs::Twist base_cmd;

    char cmd[50];
    while(nh_.ok()){

      std::cin.getline(cmd, 50);
      if(cmd[0]!='+' && cmd[0]!='l' && cmd[0]!='r' && cmd[0]!='.')
      {
        std::cout << "unknown command:" << cmd << "\n";
        continue;
      }

      base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;   
      //move forward
      if(cmd[0]=='+'){
        base_cmd.linear.x = 0.25;
      } 
      //turn left (yaw) and drive forward at the same time
      else if(cmd[0]=='l'){
        base_cmd.angular.z = 0.75;
        base_cmd.linear.x = 0.25;
      } 
      //turn right (yaw) and drive forward at the same time
      else if(cmd[0]=='r'){
        base_cmd.angular.z = -0.75;
        base_cmd.linear.x = 0.25;
      } 
      //quit
      else if(cmd[0]=='.'){
        break;
      }
      
      //publish the assembled command
      cmd_vel_pub_.publish(base_cmd);
    }
    return true;
  }

  bool driveJoystick()
  {
    SDL_Event event;

    SDL_Init(SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);

    std::cout << "Configuring your joystick, " << SDL_JoystickName(0) << ", please wait!\n";

    this->joystick_ = SDL_JoystickOpen(0);
    size_t num_axes = SDL_JoystickNumAxes(this->joystick_);

    std::cout << "This joystick has: " << num_axes << " axes!\n";
    this->joy_mutex_.lock();
    // If the joystick isn't there do nothing
    if (!this->joystick_) {
        this->joy_mutex_.unlock();
        return -1;
    }

     while(SDL_WaitEvent(&event) >= 0) {
      SDL_JoystickUpdate();
      int lv_i = SDL_JoystickGetAxis(this->joystick_, 3);
      int av_i = SDL_JoystickGetAxis(this->joystick_, 2);
      this->joy_mutex_.unlock();
      // Deadband
      if (lv_i > -JOY_DEADBAND && lv_i < JOY_DEADBAND) {
          lv_i = 0;
      }
      if (av_i > -JOY_DEADBAND && av_i < JOY_DEADBAND) {
          av_i = 0;
      }
      // Normalize
      double lv = float(lv_i)/float(JOY_MAX_VALUE);
      lv *= -1; // Invert X
      double av = float(av_i)/float(JOY_MAX_VALUE);

      geometry_msgs::Twist base_cmd;

      base_cmd.linear.x = base_cmd.linear.y = base_cmd.angular.z = 0;

      base_cmd.linear.x = lv;
      base_cmd.angular.z = -1 * av;

      cmd_vel_pub_.publish(base_cmd);

      //std::cout << "Axe number 3: " << lv << "!\n";
      //std::cout << "Axe number 2: " << av << "!\n";
    }
  }

};

int main(int argc, char** argv)
{
  //init the ROS node
  ros::init(argc, argv, "robot_driver");
  ros::NodeHandle nh;

  RobotDriver driver(nh);
  //driver.driveKeyboard();
  driver.driveJoystick();
}