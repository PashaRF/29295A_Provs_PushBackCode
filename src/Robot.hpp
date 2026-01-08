#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "../include/pros/adi.h"

#include "Basic Control Classes/Piston.hpp"
#include "Intake.hpp"
#include "DriveTrainJoystickMath.hpp"

class Robot
{

public:
    Pistonf Descore_;
    Pistonf MatchLoad_;
    BlockDetector BlockDetector_;

    Intake Intake_;

    DriveTrainCurveJoystickMath DriveTrain_;

    bool IsAutonomous = false;
    bool HalfSpeed = false;

public:
    Robot()
        : Descore_('A'),
          MatchLoad_('B'),
          Intake_(Motor(12), Motor(-14)),
          DriveTrain_()
          //optical in 19, distance in 17

    {
        BlockDetector_.SortOn();
    }

    void InputTick()
    {
        Intake_.InputTick();
        BlockDetector_.InputTick();
        DriveTrain_.SetHalfSpeedValue(HalfSpeed);
        DriveTrain_.InputTick();
    }

    void OutputTick() {
        Intake_.OutputTick();
        DriveTrain_.OutputTick();
    }

    void AutonOutputTick() {
        Intake_.OutputTick();
        BlockDetector_.OutputTick();
    }

    void SetAllianceAsRed(bool isRed) {
        BlockDetector_.SetAllianceAsRed(isRed);
    }
};


#endif // ROBOT_HPP