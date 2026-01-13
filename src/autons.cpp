#include "main.h"
#include "AutonBrain.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
int DRIVE_SPEED =110;
int TURN_SPEED = 90;
const int SWING_SPEED = 110;

extern Robot* robot;
AutonBrain* brain;

void brainTick() {
  while (robot->IsAutonomous) {
    brain->Tick();
    pros::delay(ez::util::DELAY_TIME);
  }
}

#pragma region Auton Tests 
void drive_test() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
}

void turn_test() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  ch->pid_turn_set(90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
}

///
// Combining Turn + Drive
///
void drive_and_turn_test() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_drive_set(-24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position
  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);
  
  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_until(6_in);
  brain->matchLoadOn = true;
  ch->pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  ch->pid_drive_set(-24, 30);
  ch->pid_wait_until(-6_in);
  brain->matchLoadOn = false;
  ch->pid_speed_max_set(DRIVE_SPEED);  
  ch->pid_wait_quick_chain();
}

void swing_test() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  ch->pid_swing_set(ez::LEFT_SWING, 45, SWING_SPEED, 45);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED, 45);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 45, SWING_SPEED, 45);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::LEFT_SWING, 0, SWING_SPEED, 45);
  ch->pid_wait_quick_chain();
}

#pragma endregion
#pragma region Prerebuild Autons
void fullWP_RR() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  TURN_SPEED = 60;
  DRIVE_SPEED = 60;

  brain->descoreOn = true;
  ch->pid_drive_set(17, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  //brain -> intakeMiddleOn = true;
  brain-> intakeOn = true;
  brain->matchLoadOn = true;

  ch->pid_drive_set(12, DRIVE_SPEED);
  ch->pid_wait();
  pros::delay(20);

  ch->pid_turn_set(-55, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = false;
  brain->intakeOn = false;
//  brain -> intakeMiddleOn = false;

  ch->pid_drive_set(10, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeReverseOn = true;
  pros::delay(1200);
 // pros::delay(2500);
  brain->intakeReverseOn = false;
  brain->descoreOn = false;

  ch->pid_drive_set(-11.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(-100, TURN_SPEED);
  ch->pid_wait_quick_chain();

  brain->intakeOn = true;
  ch->pid_drive_set(36, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = true;

  ch->pid_drive_set(10.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
 // brain->prerollerOnly = true;

  ch->pid_turn_set(-144, TURN_SPEED);
  ch->pid_wait_quick_chain();
//  brain->prerollerOnly = false;

  ch->pid_drive_set(-13.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(900);
  brain->intakeOn = false;

  ch->pid_drive_set(43, DRIVE_SPEED);
  ch->pid_wait_quick_chain();

  ch->pid_turn_set(169, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain -> intakeOn = true;
  brain -> descoreOn = true;
  ch->pid_drive_set(14, 105);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(3, 120);
  ch->pid_wait();
  pros::delay(100); 
  brain ->intakeOn = false;
  brain-> descoreOn = false;
  ch->pid_drive_set(-28.5, 127);
  brain->intakeOn = true;
} 

void Block9_RR() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  TURN_SPEED = 60;
  DRIVE_SPEED = 60;

  brain->descoreOn = true;
  ch->pid_drive_set(17, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain -> intakeOn = true;
  brain->matchLoadOn = true;

  ch->pid_drive_set(11.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain ();
  ch->pid_turn_set(-120, TURN_SPEED);
  ch->pid_wait_quick_chain();
 // brain-> prerollerOnly = true;
  ch->pid_drive_set(31, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-172, TURN_SPEED);
  ch->pid_wait_quick_chain();
 // brain-> prerollerOnly = false;
  ch->pid_drive_set(13, 110);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(4.5, 120);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(4, 105);
  ch->pid_wait_quick_chain();
  pros::delay(1050);
  brain ->intakeOn = false;
  brain -> descoreOn = false;
  ch->pid_turn_set(-169, TURN_SPEED); //turning left
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-28.5, 127);
  ch->pid_wait();
  brain->intakeOn = true;
} 

void Skills1() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  TURN_SPEED = 65;
  DRIVE_SPEED = 65;
  
  brain->intakeOn = true;
  brain->descoreOn = true;
  brain->matchLoadOn = true;

  ch->pid_drive_set(29, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(90, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(72, DRIVE_SPEED); //moves into matchload 1
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-5, DRIVE_SPEED); 
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-10, DRIVE_SPEED); //away from wall
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(90, TURN_SPEED); 
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-85, DRIVE_SPEED); //long run 1
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(0, TURN_SPEED); 
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(10, DRIVE_SPEED); 
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  ch->pid_turn_set(-90, TURN_SPEED); //facing goal
  ch->pid_wait_quick_chain();

  brain->descoreOn = false;
  ch->pid_drive_set(-9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;  //score on goal
  pros::delay(3000);
  ch->pid_drive_set(12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->descoreOn = true;

  ch->pid_drive_set(75, DRIVE_SPEED); //intakes from loader
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-16,  DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false; 
  ch->pid_drive_set(-12,  DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->descoreOn = false; 
  brain->intakeOn = true; //finish filling long goal 1
  pros::delay(3000);
  ch->pid_drive_set(9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(180, TURN_SPEED); //facing towards other side of arena
  ch->pid_wait_quick_chain();
  brain->descoreOn = true;

  ch->pid_drive_set(90, DRIVE_SPEED); //long run 2
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-91, TURN_SPEED); 
  ch->pid_wait_quick_chain(); 

  ch->pid_drive_set(75, DRIVE_SPEED); //moves into matchload 3
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-5, DRIVE_SPEED); 
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(180, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-10, DRIVE_SPEED); //away from wall
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-90, TURN_SPEED); 
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-85, DRIVE_SPEED); //long run 3
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(180, TURN_SPEED); 
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(11, DRIVE_SPEED); 
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  ch->pid_turn_set(90, TURN_SPEED); //facing goal
  ch->pid_wait_quick_chain();

  brain->descoreOn = false;
  ch->pid_drive_set(-9, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;  //score on goal
  pros::delay(3000);
  ch->pid_drive_set(12, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->descoreOn = true;

  ch->pid_drive_set(75, DRIVE_SPEED); //intakes from loader 4
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-16,  DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false; 
  ch->pid_drive_set(-12,  DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->descoreOn = false; 
  brain->intakeOn = true; //finish filling long goal 2
  pros::delay(3000);
  ch->pid_drive_set(12,  DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(30, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = false;
  brain->intakeReverseOn = true;
  ch->pid_drive_set(32, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(40, 110);
  ch->pid_wait_quick_chain();
  pros::delay(1000);
  ch->pid_turn_set(-90, 120);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(180, 120);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(90, 120);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(0, 120);
  ch->pid_wait_quick_chain();
  #pragma endregion
}
// . . .
// Make your own autonomous functions here!
// . . .