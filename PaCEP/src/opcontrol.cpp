#include "main.h"
#include "motorConfig.cpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
 void drive(int left, int right){
	leftFront.move(left);
  leftBack.move(left);
  rightFront.move(right);
  rightBack.move(right);
 }

void intake(void*){
  while (true){
    if(master.get_digital(DIGITAL_L2)){
      intakeLeft.move(1);
      intakeRight.move(-1);
      delay(5);
    }
    if(master.get_digital(DIGITAL_L1)){
      intakeLeft.move(-1);
      intakeRight.move(1);
      delay(5);
    }
  }
}


void trayControl(void*){
struct tray *trayz,pid1;
trayz= &pid1;
trayPID(trayz, 0, 0 ,0);
float error =0;
  bool toggle = false;
  while(true){

    if(master.get_digital(DIGITAL_Y)){
      toggle = !toggle;
      if(toggle){
        tray.move(PIDUpdate(trayz,error,5));
        delay(5);
      } else {
        tray.move(1000);
      }
      while (master.get_digital(DIGITAL_Y)){
        delay(1);
      }
    }
    delay(20);
  }
}

// void arm_control(void*) {
// 	Task arm_t(arm_pid);
// 	bool was_pid;
// 	while (true) {
// 		if (master.get_digital(DIGITAL_B)) {
// 			was_pid = true;
// 			arm_t.resume();
// 			set_arm_pid(2300);
// 		} else if (master.get_digital(DIGITAL_DOWN)) {
// 			was_pid = true;
// 			arm_t.resume();
// 			set_arm_pid(1800);
// 		} else {
// 			if (master.get_digital(DIGITAL_R1)||master.get_digital(DIGITAL_R2)) {
// 				was_pid = false;
// 				set_arm((master.get_digital(DIGITAL_R1)-master.get_digital(DIGITAL_R2))*127);
// 			} else {
// 				if (!was_pid) {
// 					set_arm(0);
// 				}
// 			}
// 		}
//
// 		if (!was_pid) {
// 			arm_t.suspend();
// 		}
//
// 		pros::delay(20);
// 	}
// }

void opcontrol(){
  Task trayControlT(trayControl);
//  Task armControlT(arm_control);
  Task intakeT(intake);
	while (true){
		int linear = master.get_analog(ANALOG_RIGHT_Y);
		int turn = master.get_analog(ANALOG_RIGHT_X);
		int left = linear - turn;
		int right = linear + turn;
		drive(left,right);
		delay(2);
	}
}
