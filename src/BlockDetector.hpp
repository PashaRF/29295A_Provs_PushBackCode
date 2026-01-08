#ifndef BLOCKDETECTOR_HPP
#define BLOCKDETECTOR_HPP

#include "Basic Control Classes/OpticalSensor.hpp"

class BlockDetector {
private:
    bool colourSort = true;
    bool allianceColourRed;

    OpticalSensor::BlockType block = OpticalSensor::BlockType::None;

    bool badColour = false;
    int timer = 5;

    OpticalSensor OpticalSensor_;

public:
    BlockDetector() : OpticalSensor_(9) {
        SortOn();
    }

    void InputTick() {
        OpticalSensor_.Tick();

        if (!colourSort) return;

        if (timer == 0) {
            block = OpticalSensor_.GetBlock();
            switch (block)
            {
            case OpticalSensor::BlockType::Blue:
                badColour = !allianceColourRed;
                break;
            case OpticalSensor::BlockType::Red:
                badColour = allianceColourRed;
                break;
            default:
                badColour = false;
                break;
            } 
            timer = 5;
            block = OpticalSensor::BlockType::None;
        }
        else {
            timer--;
        }        
    }

    void OutputTick() {

    }

    void SortOn() {
        colourSort = true;
        OpticalSensor_.LEDon();
    }
    void SortOff() {
        colourSort = false;
        OpticalSensor_.LEDoff();
    }

    int GetTimer() {
        return timer;
    }

    bool GetBadColour() {
        return badColour;
    }

    void SetAllianceAsRed(bool isRed) {
        allianceColourRed = isRed;
    }
};

#endif  // BLOCKDETECTOR_HPP