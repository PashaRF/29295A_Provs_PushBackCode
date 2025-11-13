#pragma once

void default_constants();
void testAuton(); //foward and back
void driveAuton(); //forward, back, turn
void turnAuton(); //turning only
void  fullWP_RR(); // solo win point
void Block9_RR();

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void motion_chaining();
void combining_movements();
void interfered_example();
void odom_drive_example();
void odom_pure_pursuit_example();
void odom_pure_pursuit_wait_until_example();
void odom_boomerang_example();
void odom_boomerang_injected_pure_pursuit_example();
void measure_offsets();