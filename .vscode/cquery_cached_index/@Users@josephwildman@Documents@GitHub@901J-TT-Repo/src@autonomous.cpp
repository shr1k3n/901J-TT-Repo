#include "main.h"
#include "config.hpp"
#include <math.h>
#include <vector>
namespace WheelTracker{
  float wheelrad = 2.75;

  float lencval = 0;
  float rencval = 0;
  float bencval = 0;

  float prevl = 0;
  float prevr = 0;
  float prevb = 0;
  float thetar = 180;//constant
  float theta1;
  float theta0 = 0;
  float thetam;

  float rdis = 10;
  float ldis = 10;
  float bdis=10;

  float dltheta = 0; //change in encoder angle
  float drtheta = 0;
  float dbtheta = 0;

  float dl; //change in distance
  float dr;
  float ds;

  float dtheta;


  std::vector<float> d (3);
  std::vector<float> dtemp (3);
  std::vector <float> d1 (3);

  float rad;
  float angle;
  float currentl;
  float currentr;
  float currentb;

std::vector<float> track(){



    currentl = LeftEncoder.get_value();
    currentr = RightEncoder.get_value();
    currentb = BackEncoder.get_value();

    dltheta = currentl - prevl;
    drtheta = currentr - prevr;
    dbtheta = currentb - prevb;

    //distance traveled by each wheel
    dl = ((dltheta)/360) * 2 *M_PI * wheelrad;
    dr = ((drtheta)/360) * 2 *M_PI * wheelrad;
    ds = ((dbtheta)/360) * 2 *M_PI * wheelrad;

    //update values
    prevl = currentl;
    prevr = currentr;
    prevb = currentb;

    theta1 = thetar + 180*((dl-dr)/(rdis+ldis))/M_PI;//convert angle to degrees and add to initial angle to find new angle

    dtheta = theta1 - theta0; //change in angle

    if(dtheta == 0.0){//if only vertical movement add vertical component dr

      dtemp.at(0) = ds;
      dtemp.at(1) = dr;
    }else{
      dtemp.at(0) = 2 * sin(dtheta/2) * (ds/dtheta + bdis);
      dtemp.at(1) = 2 * sin(dtheta/2) * (dr/dtheta + rdis);


    //calculate average orientation
    thetam = theta0 + dtheta/2;

    //convert position to polar
    angle = atan(dtemp[1] / dtemp[0]);
    rad = sqrt(dtemp[0] * dtemp[0] + dtemp[1] * dtemp[1]);

    angle += -1 * thetam;

    //convert back
    dtemp[0] = rad * cos(angle);
    dtemp[1] = rad * sin(angle);
}
    //add position vector to old one
    for(int i = 0; i < 2; i++){
      d1[i] = d[i] + dtemp[i];
    }

      theta0 = theta1;

      d[0] = d1[0];
      d[1] = d1[1];
      d1[2] = theta0;
      //return new position
      return d1;
    }

}

void measure_jerk(){
  float vel_max = 200*4/60; //inches per s
  float pos = 0;
  float d_pos;
  float vel;
  float vel_prev;
  float a_prev;
  float a;
  float d_a;
  float j_max = 5.0 ;//inch / s^3
  while (true){
    d_pos = RobotPosition[0] - pos;

    a += 0.01*j_max;
    vel += a_prev*0.01;
    pos += vel_prev*0.01;
    vel_prev = vel;
    a_prev = a;
    left_wheel.move_velocity(vel);
    right_wheel.move_velocity(vel);
    left_chain.move_velocity(vel);
    right_chain.move_velocity(vel);

    pros::delay(10);
  }
}

//test
/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {

while(true){
  RobotPosition = WheelTracker::track();
  printf("X: %f\r\n",RobotPosition[0]);
  printf("Y: %f\r\n",RobotPosition[1]);
  printf("THETA: %f\r\n",RobotPosition[2]);
  printf("LEFT ENCODER %d\r\n",LeftEncoder.get_value());
  printf("RIGHT ENCODER %d\r\n",RightEncoder.get_value());
  printf("Back ENCODER %d\r\n",BackEncoder.get_value());
  pros::delay(10);

}


}
