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
    bool intakeReverseOn = false;
    void Tick()
    {
        Robot_->InputTick();
        if (intakeReverseOn) {
            Robot_->Intake_.Reverse();
        }
        else if (intakeOn) { 
            Robot_->Intake_.Forward();
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
        Robot_->AutonOutputTick();
    }
    
    void SetAllianceAsRed(bool isRed) {
        Robot_->SetAllianceAsRed(isRed);
    }
};
#endif // AUTONBRAIN_HPP