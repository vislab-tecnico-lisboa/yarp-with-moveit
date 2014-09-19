#include <iostream>

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <SDL/SDL.h>

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
  int cancelButton, pauseButton, upDownAxe, leftRightAxe;

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

    if(SDL_JoystickName(0) == NULL) {
      std::cout << "\nI'm sorry but I couldn't find any joystick, please try again or contact the developer at miguelaragao91@gmail.com, thank you :)\n\n";
      return -1;
    } else {
      std::cout << "\nI just found a joystick with the name, " << SDL_JoystickName(0) << ", please wait while opening it... ";
      cancelButton = pauseButton = upDownAxe = leftRightAxe = -1;
    }

    this->joystick_ = SDL_JoystickOpen(0);

    std::cout << "Success!\n\nNow it is time to configure your joystick's buttons and axes, please complete the following instructions:\n";
    // If the joystick isn't there do nothing
    if (!this->joystick_) {
        std::cout << "\n\n\n\nI'm sorry but I couldn't connect and open your joystick, please try again or contact the developer at miguelaragao91@gmail.com, thank you :)\n\n";
        return -1;
    }

    int numButtons = SDL_JoystickNumButtons(this->joystick_);
    std::cout << "- Press the button you want to define as the cancel button:\n";
    while(SDL_WaitEvent(&event) >= 0) {
      SDL_JoystickUpdate();
      for(int i = 0; i < numButtons; i++) {
        if(SDL_JoystickGetButton(this->joystick_, i) == 1) {
          std::cout << "\nThank you, please wait while setting it...\n";
          cancelButton = i;
          ros::Duration d = ros::Duration(1);
          d.sleep();
          std::cout << "Success! You can now cancel execution at any time by pressing the cancel button.\n";
          break;
        }
      }
      if(cancelButton != -1)
        break;
      ros::Duration d = ros::Duration(0.1);
      d.sleep();
    }

    size_t num_axes = SDL_JoystickNumAxes(this->joystick_);
    std::cout << "\n\n- Move the axis you want to define as the axis for forward and backward movements:\n";
    while(SDL_WaitEvent(&event) >= 0) {
      SDL_JoystickUpdate();
      int button = SDL_JoystickGetButton(this->joystick_, cancelButton);
      if(button == 1) {
        SDL_JoystickClose(0);
        std::cout << "\n\nTurning your joystick off, please wait...\n";
        geometry_msgs::Twist close_cmd;
        close_cmd.linear.x = close_cmd.linear.y = close_cmd.angular.z = 0;
        cmd_vel_pub_.publish(close_cmd);
        ros::Duration d = ros::Duration(1);
        d.sleep();
        std::cout << "\nJoystick was properly turned off, closing now!\n\n";
        return -1;
      }
      for(int i = 0; i < numButtons; i++) {
        if(SDL_JoystickGetAxis(this->joystick_, i) != 0 && SDL_JoystickGetAxis(this->joystick_, i) != -0) {
          std::cout << "\nThank you, please wait while setting it...\n";
          upDownAxe = i;
          ros::Duration d = ros::Duration(1);
          d.sleep();
          std::cout << "Success!\n";
          break;
        }
      }
      if(upDownAxe != -1)
        break;
      ros::Duration d = ros::Duration(0.1);
      d.sleep();
    }

    std::cout << "\n\n- Move the axis you want to define as the axis for left and right movements:\n";
    while(SDL_WaitEvent(&event) >= 0) {
      SDL_JoystickUpdate();
      int button = SDL_JoystickGetButton(this->joystick_, cancelButton);
      if(button == 1) {
        SDL_JoystickClose(0);
        std::cout << "\n\nTurning your joystick off, please wait...\n";
        geometry_msgs::Twist close_cmd;
        close_cmd.linear.x = close_cmd.linear.y = close_cmd.angular.z = 0;
        cmd_vel_pub_.publish(close_cmd);
        ros::Duration d = ros::Duration(1);
        d.sleep();
        std::cout << "\nJoystick was properly turned off, closing now!\n\n";
        return -1;
      }
      for(int i = 0; i < numButtons; i++) {
        if(SDL_JoystickGetAxis(this->joystick_, i) != 0 && SDL_JoystickGetAxis(this->joystick_, i) != -0) {
          std::cout << "\nThank you, please wait while setting it...\n";
          leftRightAxe = i;
          ros::Duration d = ros::Duration(1);
          d.sleep();
          std::cout << "Success!\n";
          break;
        }
      }
      if(leftRightAxe != -1)
        break;
      ros::Duration d = ros::Duration(0.1);
      d.sleep();
    }

    while(SDL_WaitEvent(&event) >= 0) {
      SDL_JoystickUpdate();
      int button = SDL_JoystickGetButton(this->joystick_, cancelButton);
      if(button == 1) {
        SDL_JoystickClose(0);
        std::cout << "\n\nTurning your joystick off, please wait...\n";
        geometry_msgs::Twist close_cmd;
        close_cmd.linear.x = close_cmd.linear.y = close_cmd.angular.z = 0;
        cmd_vel_pub_.publish(close_cmd);
        ros::Duration d = ros::Duration(1);
        d.sleep();
        std::cout << "\nJoystick was properly turned off, closing now!\n\n";
        return -1;
      }
      int lv_i = SDL_JoystickGetAxis(this->joystick_, upDownAxe);
      int av_i = SDL_JoystickGetAxis(this->joystick_, leftRightAxe);
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

      ros::Duration d = ros::Duration(0.1);
      d.sleep();
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