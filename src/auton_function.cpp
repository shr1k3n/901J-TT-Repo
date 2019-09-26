#include "main.h"
#include "config.hpp"
#include "auton_function.h"

const int LIFTGEARRATIO = 7;

/*
void liftpid(int targetDegree, int maxvel){
  left_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  right_lift.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
  const double degreeGoal = (targetDegree*LIFTGEARRATIO);

  bool goalMet = false;
  int targetVelocity = 0;
  double currentPosition = 0;
  double followPosition = 0;
  double error = 0;
  double previous_error = degreeGoal;
  double kP = 0.8;
  double kI = 0.0025;
  double kD = 0.001;
  double diff = 0;
  double integral = 0;
  double derivative = 0;
  if (targetDegree < 0) {maxvel *= -1;}
  right_lift.tare_position();
  left_lift.tare_position();


  while(!goalMet){
    currentPosition = left_lift.get_positon();
    followPosition = right_lift.get_position();
    diff = currentPosition - followPosition;
    error = degreeGoal - currentPosition;

    if (std::abs(error) < 100){
      integral += error;
    }

    derivative = error - previous_error;
    previous_error = error;

    targetVelocity = kP*error + kI*integral + kD*derivative;

    if (targetVelocity > maxVelocity){
      targetVelocity = maxVelocity;
    }

    left_lift.move_velocity(targetVelocity);
    right_lift.move_velocity(targetVelocity + diff);

    if (std::abs(error) < 4){
      goalMet = true;
  }

  pros::delay(10);
  }
  right_lift.move_velocity(0);
  left_lift.move_velocity(0);
}
*/
void slewRateControl(pros::Motor *motor, int targetVelocity, int increment){
  int currentVelocity = motor->get_target_velocity();
  if (targetVelocity != 0){
    if (currentVelocity != targetVelocity){
      if (targetVelocity > currentVelocity){
        currentVelocity += increment;
      } else if (targetVelocity < currentVelocity){
        currentVelocity -= increment;
      }
      if (std::abs(currentVelocity) > std::abs(targetVelocity)){
        currentVelocity = targetVelocity;
      }
    }
  } else {
    currentVelocity = targetVelocity;
  }
  motor->move_velocity(currentVelocity);
}