#ifndef INTAKE_HPP
#define INTAKE_HPP

#include "Basic Control Classes/Motor.hpp"
#include "BlockDetector.hpp"

class Intake
{

private:
    Motor PreRoller_;
    Motor Intake_;

    int PreRollerSpeed_;
    int IntakeSpeed_;
    int maxSpeed = 127;

public:
    Intake(Motor PreRoller, Motor Intake)
        : PreRoller_(PreRoller), Intake_(Intake)
    {
        SetIntakeBrakeCoast(); //* flag
    }

    void InputTick() {
        Intake_.Tick();
    }

    void OutputTick() {
        PreRoller_.SetSpeed(PreRollerSpeed_);
        Intake_.SetSpeed(IntakeSpeed_);
        }

    void Forward()
    {
        PreRollerSpeed_ = maxSpeed;
        IntakeSpeed_ = maxSpeed;
    }

    void Reverse()
    {
        PreRollerSpeed_ = -maxSpeed;
        IntakeSpeed_ = -maxSpeed;
    }
    void PreRollForward()
    {
        PreRollerSpeed_ = maxSpeed;
        IntakeSpeed_ = 0;
    }
    void PreRollReverse()
    {
        PreRollerSpeed_ = -maxSpeed;
        IntakeSpeed_ = 0;
    }

    void Stop()
    {
        PreRollerSpeed_ = 0;
        IntakeSpeed_ = 0;
    }

    void ChangePreRollerSpeed(int speed)
    {
        PreRollerSpeed_ = speed;
    }

    void ChangeIntakeSpeed(int speed)
    {
        IntakeSpeed_ = speed;
    }

    void SetIntakeBrakeBrake() {
        Intake_.SetBrakeMode(MOTOR_BRAKE_BRAKE);
    }

    void SetIntakeBrakeCoast() {
        Intake_.SetBrakeMode(MOTOR_BRAKE_COAST);
    }

};
#endif // INTAKE_HPP