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
    bool prerollerOnly_ = false;
    //arm timer 
    /*
    int ZeroTimer = 0;
    int DescoreWaitAmount = 500;
    int DescoreIntervalTimer = DescoreWaitAmount;
    int DownPressedAmount = 0;
    bool VibrateOnce = false; */

public:
    PashaBrain(Robot* Robot)
        : Robot_(Robot), Controller_()

    {
        /*
        Controller_.Y_.setValue(true);
        Robot_->Intake_.SetArmDocked(false);
        Robot_->Arm_.Zero();
        Robot_->Arm_.SetTarget(Arm::DOCK);

        MogoOn_ = Robot_->Mogo_.GetValue(); */
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
            Robot_->Intake_.PreRollForward();
        }
        else if (Controller_.R2_.IsPressed()) {
            Robot_->Intake_.PreRollReverse();
        }
        else if (Controller_.L1_.IsPressed()) {
            Robot_->Intake_.Forward();
        }
        else if (Controller_.L2_.IsPressed()) {
            Robot_->Intake_.Reverse();
        }
        else {
            Robot_->Intake_.Stop();
        }
        if (Controller_.Y_.WasTapped()) {
            MatchLoadOn_ = !MatchLoadOn_; 
        }

        #pragma region Arm Control - Disabled
        //
        //arm
        //
        /*
        
        if (Controller_.Left_.IsPressed()) {
            ZeroTimer++;

            if (ZeroTimer > 50) {
                Robot_->Arm_.Zero();
                Controller_.Vibrate();
                ZeroTimer = 0;

                Controller_.L1_.SetPressed(0);
                Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 4)); 
            } 
        }

        if (Controller_.Down_.WasTapped()) { /*
            if (Robot_->Arm_.GetState() > 4) {
                if (Robot_->Arm_.GetState() == 10) {
                    Robot_->Arm_.SetTarget((Arm::State)(10));
                } else {
                    Robot_->Arm_.SetTarget((Arm::State)(Robot_->Arm_.GetState() + 1));
                }
                
                DownPressedAmount++;
            } else {
                Robot_->Arm_.MoveDown();
            } 
        }

        if (Controller_.Up_.WasTapped()) { /*
            if (Robot_->Arm_.GetState() > 5) {
                Robot_->Arm_.SetTarget((Arm::State)(Robot_->Arm_.GetState() - 1));
                DownPressedAmount--;
            } else {
                Robot_->Arm_.MoveUp(); 
            }
        }

        if (Controller_.Right_.WasTapped()) { /*
            if (Robot_->Arm_.GetState() == Arm::LOAD) {
                Controller_.L1_.SetPressed(0);
            }
            else {
                Controller_.L1_.SetPressed(1);
            }

            Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 4));
            Robot_->Arm_.ManualTakeoverSet(false); 
        }

        if (Controller_.L1_.IsHeld()) { /*
            Robot_->Arm_.SetTarget((Arm::State)(Controller_.L1_.TimesPressed() % 4));
            Robot_->Arm_.ManualTakeoverSet(false);
            Robot_->Intake_.SetHookBrakeCoast();
        } else {
            Robot_->Intake_.SetHookBrakeBrake(); 
        }

        if (Controller_.X_.WasTapped()) { /*
            if (DescoreIntervalTimer < DescoreWaitAmount) {
                DownPressedAmount++;

                if (DownPressedAmount > 5) {
                    DownPressedAmount = 5;
                } else if (DownPressedAmount < 0) {
                    DownPressedAmount = 0;
                }

                Robot_->Arm_.SetTarget((Arm::State)(5 + DownPressedAmount));
                master.rumble(".");
            } else {
                Robot_->Arm_.SetTarget(Arm::DESCORE1);
                DownPressedAmount = 0;
            }
            
            Controller_.L1_.SetPressed(3);
            Robot_->Arm_.ManualTakeoverSet(false);
            DescoreIntervalTimer = 0;
            VibrateOnce = false;
            
        }
            
        DescoreIntervalTimer++;

        if (DescoreIntervalTimer > DescoreWaitAmount && !VibrateOnce) { 
            Controller_.Vibrate();
            VibrateOnce = true;
        }
            */
        #pragma endregion
        //
        //pistons
        //
        if (Controller_.B_.WasTapped()) {
            DeScoreOn_ = !DeScoreOn_;
        }
        if (Controller_.Up_.WasTapped()) {
            Robot_->HalfSpeed = !Robot_->HalfSpeed; // if we need half speed for some reason
            Controller_.Vibrate();
        }

        Robot_->Descore_.SetValue(DeScoreOn_);
        Robot_->MatchLoad_.SetValue(MatchLoadOn_);
        Robot_->OutputTick();
    }
};
#endif // MATTHEWBRAIN_HPP