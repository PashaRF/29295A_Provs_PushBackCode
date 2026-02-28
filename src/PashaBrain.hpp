#ifndef PASHABRAIN_HPP
#define PASHABRAIN_HPP

#include "Robot.hpp"
#include "PashaController.hpp"

class PashaBrain
{

private:

    Robot* Robot_;
    PashaController Controller_;

    //piston boolean values
    bool DeScoreOn_ = false;
    bool MatchLoadOn_ = false;
    bool MiddleGoalOn_ = false;
    bool BlockHolderOn_ = false;

public:
    PashaBrain(Robot* Robot)
        : Robot_(Robot), Controller_()

    {

    }
    void Vibrate() {
        Controller_.Vibrate();
    }
    void Tick()
    {
        //inputs 
        Controller_.Tick();
        Robot_->InputTick();

        //assign drivetrain values
        Robot_->DriveTrain_.SetLeftStickValue(Controller_.LeftY_.GetPosition());
        Robot_->DriveTrain_.SetRightStickValue(Controller_.RightX_.GetPosition());

        //
        //intake
        //
        if (Controller_.R1_.IsPressed()) {
            Robot_->Intake_.Reverse();
        }
        else if (Controller_.R2_.IsPressed()) {
            Robot_->Intake_.Forward();
        }
        else {
            Robot_->Intake_.Stop();
        }

        //
        //pistons
        //

        if (Controller_.Down_.WasTapped()) { //switch to right (broken?)
            MiddleGoalOn_ = !MiddleGoalOn_;
            if (MiddleGoalOn_) {
                BlockHolderOn_ = false;
            }
        }
        if (Controller_.L1_.WasTapped()) {
            MatchLoadOn_ = !MatchLoadOn_;
        }
        if (Controller_.L2_.WasTapped()) {
            DeScoreOn_ = !DeScoreOn_;
        }
        if (Controller_.Y_.WasTapped()) {
            BlockHolderOn_ = !BlockHolderOn_;
        }
        if (Controller_.Up_.WasTapped()) {
            Robot_->HalfSpeed = !Robot_->HalfSpeed;
            Controller_.Vibrate();
        }

        Robot_->Descore_.SetValue(DeScoreOn_);
        Robot_->MatchLoad_.SetValue(MatchLoadOn_);
        Robot_->MiddleGoal_.SetValue(MiddleGoalOn_);
        Robot_->BlockHolder_.SetValue(BlockHolderOn_);
        Robot_->OutputTick();
    }
};
#endif // MATTHEWBRAIN_HPP