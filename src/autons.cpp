#include "main.h"
#include "AutonBrain.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
int DRIVE_SPEED = 90;
int TURN_SPEED = 90;
const int SWING_SPEED = 90;

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
  for (int i; i<7; i++) {
  ch->pid_drive_set(24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  //ch->pid_drive_set(12, DRIVE_SPEED);
  //ch->pid_wait();
  ch->pid_drive_set(-24, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  //ch->pid_wait();
  }
}

void turn_test() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(false);

  ch->pid_turn_set(90, TURN_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(-45, TURN_SPEED);
  ch->pid_wait();
  ch->pid_turn_set(0, TURN_SPEED);
  ch->pid_wait();
}

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

  ch->pid_swing_set(ez::LEFT_SWING, 45, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::LEFT_SWING, -45, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, -45, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::LEFT_SWING, 0, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 45, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::LEFT_SWING, 0, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
}

#pragma endregion
#pragma region S-Bot Autons
void SoloAWP() {
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

void _7Block() {
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

void Skills() {
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

#pragma region Provs Autons
void SkillsProvs() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  brain->intakeOn = true;
//  brain->blockHolderOn = true;
  ch->pid_drive_set(24.5, 60);
  ch->pid_wait_until(10_in);
  ch->pid_speed_max_set(DRIVE_SPEED);
  brain->intakeOn = false;              // intakes mid block 1
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-95, TURN_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  ch->pid_drive_set(-18, DRIVE_SPEED);
  ch->pid_wait_until(-15_in);
  brain->middleGoalOn = true;
  ch->pid_wait_quick_chain();
  pros::delay(2000);                    // score on middle goal
  ch->pid_drive_set(46, DRIVE_SPEED);
  ch->pid_wait_until(30_in);
  brain->middleGoalOn = false;
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-145, TURN_SPEED);   // bad angle >:(
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = true;
  ch->pid_drive_set(12.5, DRIVE_SPEED);   // enter matchload 1
  ch->pid_wait_quick_chain();
  pros::delay(2000);   
  ch->pid_swing_set(ez::LEFT_SWING, -178, SWING_SPEED, 15); //175
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, -146, SWING_SPEED, 55);
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = false;
  brain->intakeOn = false;
  ch->pid_drive_set(-51, DRIVE_SPEED);   // moves down corridor 
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 35, SWING_SPEED, -12);
  ch->pid_wait_quick_chain(); 
  ch->pid_drive_set(-8, DRIVE_SPEED);    
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  brain->blockHolderOn = true;
  pros::delay(3000);                    // scores on long goal 1
 // ch->pid_turn_set(34, TURN_SPEED);   
 // ch->pid_wait_quick_chain();
  ch->pid_drive_set(27.5, DRIVE_SPEED);
  brain->matchLoadOn = true;
  ch->pid_wait_until(7_in);
  brain->blockHolderOn = false;
  ch->pid_wait_quick_chain();
  pros::delay(2000);                    // intakes from matchload 2
 // ch->pid_turn_set(34, TURN_SPEED);   
 // ch->pid_wait_quick_chain();
  ch->pid_drive_set(-30, DRIVE_SPEED);   
  ch->pid_wait_until(-20_in);
  brain->blockHolderOn = true;
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = false;
  pros::delay(3000);                    // fills long goal 1
  brain->intakeOn = false;
  brain->blockHolderOn = false;
  ch->pid_swing_set(ez::LEFT_SWING, 115, SWING_SPEED, 55);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  brain->blockHolderOn = false;
  ch->pid_drive_set(60, 105);
  ch->pid_wait_until(40_in);
  ch->pid_speed_max_set(45);   
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-18, 50);         // aligns with park barrier 
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
}

void SoloProvs() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 100;

  brain->intakeOn = true;
  brain->blockHolderOn = false;
  brain->matchLoadOn = true;
  ch->pid_drive_set(29, DRIVE_SPEED);   
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(90, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(5, DRIVE_SPEED);   
  ch->pid_wait_quick_chain();
  pros::delay(600);                   // emptys match load 1
  ch->pid_drive_set(-30, DRIVE_SPEED); 
  ch->pid_wait_until(-20_in);  
  brain->blockHolderOn = true;
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = false;
  pros::delay(1250);                    // fills long goal 1
  brain-> blockHolderOn = false;
  ch->pid_swing_set(ez::LEFT_SWING, 235, SWING_SPEED, 5);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 180, SWING_SPEED, 38);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(31, DRIVE_SPEED); 
  ch->pid_wait_until(16_in);
  brain->intakeOn = false;
  brain->matchLoadOn = true;
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(140, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-17.5, DRIVE_SPEED);  
  ch->pid_wait_until(-11_in); 
  brain->intakeOn = true;
  brain->middleGoalOn = true;
  ch->pid_wait_quick_chain();
  pros::delay(1000);                  // scores middle goal
  brain->middleGoalOn = false;
  ch->pid_drive_set(48.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(95, TURN_SPEED); // 92
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(7.5, DRIVE_SPEED);   // enter matchload 2
  ch->pid_wait_quick_chain();
  pros::delay(400);
  ch->pid_drive_set(-29, DRIVE_SPEED);   
  ch->pid_wait_until(-20_in);
  brain->blockHolderOn = true;
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = false;
}

void SixThreeProvs() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 100;

  brain->intakeOn = true;
  brain->blockHolderOn = false;
  ch->pid_drive_set(20, DRIVE_SPEED);
  ch->pid_wait_until(6_in);
  brain->matchLoadOn = true;
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-15, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  brain->matchLoadOn = false;
  ch->pid_drive_set(25.5, DRIVE_SPEED);
  ch->pid_wait_until(18_in);
  brain->matchLoadOn = true;
  ch->pid_wait();
  ch->pid_drive_set(-31.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-60, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(33, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-145, TURN_SPEED);   
  ch->pid_wait_quick_chain();
   /* ch->pid_swing_set(ez::RIGHT_SWING, -37, SWING_SPEED, 35);
  ch->pid_wait(); 
  brain->matchLoadOn = true;
  pros::delay(350);
  ch->pid_turn_set(-55, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 40, SWING_SPEED, 30);
  ch->pid_wait_quick_chain();
  ch->pid_swing_set(ez::RIGHT_SWING, 225, SWING_SPEED, 26);
  ch->pid_wait_quick_chain();
  /*
  ch->pid_drive_set(8, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->blockHolderOn = true;
  pros::delay(1300);                    // scores long goal
  brain->blockHolderOn = false;
  ch->pid_drive_set(27.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(650);
  ch->pid_drive_set(7.5, DRIVE_SPEED);   // enter matchload 
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-105, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  ch->pid_drive_set(-48.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = true;
  brain->middleGoalOn = true;
  pros::delay(1600);                      // scores middle goal
  ch->pid_drive_set(-37.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->intakeOn = false;
  brain->middleGoalOn = false;
  ch->pid_turn_set(-150, TURN_SPEED);    // aligns to goal
  ch->pid_wait_quick_chain();
  brain->middleGoalOn = false;
  brain->descoreOn = true;
  ch->pid_drive_set(-12, 50);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-130, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  */
}

void SixPushProvs() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 100;

  brain->intakeOn = true;
  brain->blockHolderOn = false;
  ch->pid_drive_set(20, DRIVE_SPEED);
  ch->pid_wait_until(9_in);
  brain->matchLoadOn = true;
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-105, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  /*
  ch->pid_drive_set(20, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-150, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(8, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  pros::delay(700);
  ch->pid_drive_set(-27.5, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
  brain->blockHolderOn = false;
  pros::delay(1600);
  ch->pid_swing_set(ez::RIGHT_SWING, 30, SWING_SPEED, 35);
  ch->pid_wait_quick_chain();
  ch->pid_drive_set(-12, 50);
  ch->pid_wait_quick_chain();
  ch->pid_turn_set(-130, TURN_SPEED);   
  ch->pid_wait_quick_chain();
  */
}

void SwingTest() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 100;

  brain->intakeOn = true;
  brain->blockHolderOn = false;
  ch->pid_swing_set(ez::RIGHT_SWING, 90, SWING_SPEED, 50);
  ch->pid_wait_quick_chain();
}

void OffLineProvs() {
  Drive* ch = &robot->DriveTrain_.DriveTrain_.Chassis_;
  robot->IsAutonomous = true;
  brain = new AutonBrain(robot);
  pros::Task tickTask(brainTick);
  brain->SetAllianceAsRed(true);
  ch->slew_drive_set(true);

  DRIVE_SPEED = 100;

  ch->pid_drive_set(6, DRIVE_SPEED);
  ch->pid_wait_quick_chain();
}

#pragma endregion
// . . .
// Make your own autonomous functions here!
// . . .