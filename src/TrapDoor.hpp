#ifndef TRAPDOOR_HPP
#define TRAPDOOR_HPP

#include "Basic Control Classes/Motor.hpp"
#include "BlockDetector.hpp"
#include "Basic Control Classes/Piston.hpp"

class TrapDoor
{
    private:
        Pistonf TrapDoor_;
        bool TrapDoorOn_ = false;
        bool SortOn_ = true;
        int TrapDoorDelay = 50;
        BlockDetector BlockDetector_;
    public:
        TrapDoor(Pistonf TrapDoor) : TrapDoor_(TrapDoor) {
            SortOn();
        }

        void InputTick() {
            BlockDetector_.Tick();
        }

        void OutputTick() { 
            if (SortOn_ == true) {
                if (BlockDetector_.GetBadColour() == true && TrapDoorOn_ == false) {
                    TrapDoorOn_= true;
                    TrapDoor_.SetValue(true);
                    TrapDoorDelay = 50;
                }
                if (TrapDoorDelay == 0) {
                        TrapDoorOn_ = false;
                        TrapDoor_.SetValue(false);
                        TrapDoorDelay = -1;
                }
                else if (TrapDoorDelay > 0) {
                    TrapDoorDelay--;
                }
            }
        }

        void SetAllianceAsRed(bool isRed) {
            BlockDetector_.SetAllianceAsRed(isRed);
        }

        void Toggle() {
            if (SortOn_ == false) {
                TrapDoorOn_ = !TrapDoorOn_;
                TrapDoor_.SetValue(TrapDoorOn_);
            }
        }

        void SortOn() {
            BlockDetector_.SortOn();
        }

        void SortOff() {
            BlockDetector_.SortOff();
        }
        void ToggleSort() {
            if (SortOn_ == true) {
                BlockDetector_.SortOff();
                SortOn_ = false;
            }
            else  {
                BlockDetector_.SortOn();
                SortOn_ = true;
            }
        }
};
#endif // TRAPDOOR_HPP