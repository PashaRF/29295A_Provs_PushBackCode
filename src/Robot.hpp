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
     Pistonf BlockHolder_;
     Pistonf MiddleGoal_;
    BlockDetector BlockDetector_;

    Intake Intake_;

    DriveTrainCurveJoystickMath DriveTrain_;

    bool IsAutonomous = false;
    bool HalfSpeed = false;

public:
    Robot()
        : Descore_('C'),
          MatchLoad_('D'),
          BlockHolder_('A'),
          MiddleGoal_('B'),
          Intake_(Motor(12), Motor(-15)),
          DriveTrain_()
          //imu in 10
          //optical in 9, distance in ____

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