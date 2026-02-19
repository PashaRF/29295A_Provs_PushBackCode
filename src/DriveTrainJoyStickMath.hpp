#ifndef DRIVETRAINCURVEJOYSTICKMATH_HPP
#define DRIVETRAINCURVEJOYSTICKMATH_HPP

#include <math.h>

#include "Basic Control Classes/Stick.hpp"
#include "Basic Control Classes/HoldButton.hpp"
#include "DriveTrain.hpp"

class DriveTrainCurveJoystickMath
{

private:
    double power;
    double powerC;
    double turn;
    double turnC;

    bool HalfSpeed = false;

    // input curve constants
    float pCurve = 0.5;       // curve for fwd/back
    float tCoefficient = 1.2; // curve for turn
    float tCurve = 0.4;       // coefficient for turn

public:
    DriveTrain DriveTrain_;

public:
    DriveTrainCurveJoystickMath()
    {
    }

    void InputTick()
    {
        // calculates power curve for joystick
        powerC = ((1 - pCurve) * power) + ((pCurve * pow(power, 3)) / 16129); // 16129 is 127^2
        // modelled after https://www.desmos.com/calculator/asjs86sdpy

        //calculates curve
        //turnC = turn * tCoefficient;
        turnC = tCoefficient * ((1 - tCurve) * turn) + ((tCurve * pow(turn, 3)) / 16129); // 16129 is 127^2

        if (HalfSpeed)
        {
            powerC *= 0.55;
        }

        //assigns motor speeds
        DriveTrain_.setLeftSpeed(powerC + turnC);
        DriveTrain_.setRightSpeed(powerC - turnC);
    }

    void OutputTick() {
        DriveTrain_.OutputTick();
    }

    void SetLeftStickValue(int value) {
        power = value;
    }
    void SetRightStickValue(int value) {
        turn = value;
    }
    void SetHalfSpeedValue(bool value) {
        HalfSpeed = value;
    }

    void Reset() {
        DriveTrain_.Chassis_.pid_targets_reset();                // Resets PID targets to 0
        DriveTrain_.Chassis_.drive_imu_reset();                  // Reset gyro position to 0
        DriveTrain_.Chassis_.drive_sensor_reset();
    }

};

#endif // DRIVETRAINCURVEJOYSTICKMATH_HPP