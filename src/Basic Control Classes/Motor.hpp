#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "../include/pros/motors.hpp"
#include "../include/pros/motors.h"

//temp
#include "Stick.hpp"


class Motor
{

private:
    int MotorSpeed_;
    int ReverseTimer_ = 0;
    int StalledTimer_ = 0;
    bool Stalled_ = false;

    pros::Motor Motor_;

public:
    Motor(char PortNum)
        : Motor_(PortNum)
    {
    }

    void Tick() {

        if (std::abs(Motor_.get_actual_velocity()) / 1.5 < 30 && std::abs(MotorSpeed_) > 50) {
            StalledTimer_++;
        }
        
        if (StalledTimer_ > 30) {
            ReverseTimer_ = 100;
            StalledTimer_ = 0;
            Stalled_ = true;

        }
        else {
            Stalled_ = false;
        }
        ReverseTimer_--;
    }

    int GetReverseTimer() {
        return ReverseTimer_;
    }


    void SetSpeed(int motorSpeed) {
        // values from -127 to 127
        MotorSpeed_ = motorSpeed;
        Motor_.move(MotorSpeed_);
    }

    void Stop() {
        SetSpeed(0);
    }

    void SetBrakeMode(pros::motor_brake_mode_e brakeMode) {
        Motor_.set_brake_mode(brakeMode);
    }

    bool IsStalled() {
        return Stalled_;
    }
};
#endif  // MOTOR_HPP