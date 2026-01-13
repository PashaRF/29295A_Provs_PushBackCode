#include "main.h"
#include "Robot.hpp"
#include "PashaBrain.hpp"
Robot* robot;
/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

ez::as::auton_selector.autons_add({

//
// -- AUTONS --
//

//{"Drive Test", drive_test},
//{"Turn Test", turn_test},
// {"Drive+Turn", drive_and_turn_test},
// {"Speed Test",wait_until_change_speed},
 {"Swing Test", swing_test},

//{"fullWP_RR", fullWP_RR},
// {"Block9_RR", Block9_RR},
//{"Skills1", Skills1},

//
// -- AUTONS --
//

   });
  
  ez::as::initialize();
  // Ensure Robot is declared and the header is included
  // Add this at the top of the file if not already present:
  // #include "Robot.h"
  robot = new Robot();
  master.rumble(robot->DriveTrain_.DriveTrain_.Chassis_.drive_imu_calibrated() ? "." : "---");
}

#pragma region software mush

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

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
robot->DriveTrain_.Reset();

  robot->DriveTrain_.DriveTrain_.Chassis_.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency
  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Simplifies printing tracker values to the brain screen
 */
void screen_print_tracker(ez::tracking_wheel *tracker, std::string name, int line) {
  std::string tracker_value = "", tracker_width = "";
  // Check if the tracker exists
  if (tracker != nullptr) {
    tracker_value = name + " tracker: " + util::to_string_with_precision(tracker->get());             // Make text for the tracker value
    tracker_width = "  width: " + util::to_string_with_precision(tracker->distance_to_center_get());  // Make text for the distance to center
  }
  ez::screen_print(tracker_value + tracker_width, line);  // Print final tracker text
}


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

 #pragma endregion

void opcontrol() {
  robot->IsAutonomous = false;
  PashaBrain brain(robot);
  robot->DriveTrain_.DriveTrain_.Chassis_.drive_brake_set(MOTOR_BRAKE_COAST);
  robot->SetAllianceAsRed(false);

  while (true) {
    brain.Tick();

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculati
  }
}