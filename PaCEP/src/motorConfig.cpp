#include "motor.hpp"
#include "main.h"

Controller master(CONTROLLER_MASTER);

Motor leftBack(1);
Motor leftFront(2);
Motor rightBack(3,true);
Motor rightFront(4,true);

Motor tray(5,MOTOR_GEARSET_36,true);
Motor intakeLeft(6);
Motor intakeRight(7,true);
Motor arm(8,MOTOR_GEARSET_36,true);

int sgn(float a) {
  if(a>0)
    return 1;
  else if(a<0)
    return -1;
  return 0;
}

// struct tray{
//   float kP, kI, kD;
//   float cError, pError;
//   float i, d;
//   float maxI;
//   float maxOut;
// };
//
// int trayPID(struct tray* pid, float kP, float kI, float kD){
//   pid->kP = kP;
//   pid->kI = kI;
//   pid->kD = kD;
//
//   pid->pError = 0;
//   pid->i = 0;
//   pid->d = 0;
//   pid->cError = 0;
//
//   pid->maxI = 0;
//   pid->maxOut = 0;
//
//   return 0;
// }
//
// float PIDUpdate(struct tray* pid, float error, float dT)
// {
//   pid->cError = error;
//   pid->i += error*dT;
//   pid->d = (error-pid->pError)/dT;
//   pid->pError = error;
//
//   if(pid->maxI != 0){
//     pid->i = abs(pid->i)>pid->maxI ? sgn(pid->i)*pid->maxI : pid->i;
//   }
//
//   float returnValue = (pid->cError*pid->kP)+(pid->i*pid->kI)+(pid->d*pid->kD);
//
//   if(pid-> maxOut != 0){
//     returnValue = abs(returnValue)>pid->maxOut ? sgn(returnValue)*pid->maxOut : returnValue;
//   }
// }

void
set_tray(int input) {
  tray.move(input);
}

void
set_arm(int input) {
  arm.move(input);
}

int t_target;
void set_tray_pid(int input) {
  t_target = input;
}
void tray_pid(void*) {
	while (true) {
		set_tray((t_target-tray.get_position())*0.5);
		pros::delay(20);
	}
}

int a_target;
void set_arm_pid(int input) {
  a_target = input;
}
void arm_pid(void*) {
  while (true) {
    set_arm((a_target-arm.get_position())*0.5);
    pros::delay(20);
  }
}
