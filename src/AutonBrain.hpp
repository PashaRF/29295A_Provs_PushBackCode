#ifndef AUTONBRAIN_HPP
#define AUTONBRAIN_HPP

#include "Robot.hpp"

class AutonBrain
{

private:

    Robot* Robot_;
   
public:
    AutonBrain(Robot* Robot)
        : Robot_(Robot)
    {

    }

    bool intakeOn = false;
    bool descoreOn = false;
    bool matchLoadOn = false;
    bool doubleParkOn = false;
    bool wingsOn = false;
    bool prerollerOnly = false;
    bool intakeReverseOn = false;
    bool intakeMiddleOn = false;
    void Tick()
    {
        Robot_->InputTick();
        if (intakeMiddleOn) {
            if(prerollerOnly) {
                Robot_->Intake_.PreRollForward();
            }
            else {
                Robot_->Intake_.M_Forward();
            }
        }
        else if (intakeOn) {
            if(prerollerOnly) {
                Robot_->Intake_.PreRollForward();
            }
            else {
                Robot_->Intake_.Forward();
            }
        }
        else if (intakeReverseOn)
            if(prerollerOnly) {
                Robot_->Intake_.PreRollReverse();
            }
            else {
                Robot_->Intake_.Reverse();
            }
        else {
            Robot_->Intake_.Stop();
        }
        if (descoreOn) {
            Robot_->Descore_.Activate();
        }
        else {
            Robot_->Descore_.Deactivate();
        }
        if (matchLoadOn) {
            Robot_->MatchLoad_.Activate();
        }
        else {
            Robot_->MatchLoad_.Deactivate();
        }
         if (wingsOn) {
            Robot_->Wings_.Activate();
        }
        else {
            Robot_->Wings_.Deactivate();
        }
        if (doubleParkOn) {
            Robot_->DoublePark_.Activate();
        }
        else {
            Robot_->DoublePark_.Deactivate();
        }
        Robot_->AutonOutputTick();
    }
    
    void SetAllianceAsRed(bool isRed) {
        Robot_->SetAllianceAsRed(isRed);
    }
};
#endif // AUTONBRAIN_HPP