#pragma once
#include "main.h"
#ifndef MOTOR_HPP
#define MOTOR_HPP

extern Controller master;
extern Motor leftBack;
extern Motor leftFront;
extern Motor rightBack;
extern Motor rightFront;
extern Motor tray;
extern Motor intakeLeft;
extern Motor intakeRight;
extern Motor arm;
int trayPID(struct tray* pid, float kP, float kI, float kD);
float PIDUpdate(struct tray* pid, float error, float dT);

#endif
