#ifndef BLOCKDETECTOR_HPP
#define BLOCKDETECTOR_HPP

#include "Basic Control Classes/OpticalSensor.hpp"

class BlockDetector {
private:
    bool colourSort = true;
    bool allianceColourRed;

    OpticalSensor::BlockType block = OpticalSensor::BlockType::None;

    bool badColour = false;
    int trapDoorTimer = 5;

    OpticalSensor OpticalSensor_;
//  DistanceSensor DistanceSensor_;
    

public:
    BlockDetector() : OpticalSensor_(9) {
        SortOn();
    }

    void Tick() {
        OpticalSensor_.Tick();

        if (!colourSort) return;

        if (trapDoorTimer == 0) {
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
            trapDoorTimer = 5;
            block = OpticalSensor::BlockType::None;
        }
        else {
            trapDoorTimer--;
        }        
    }

    void SortOn() {
        colourSort = true;
        OpticalSensor_.LEDon();
    }
    void SortOff() {
        colourSort = false;
        OpticalSensor_.LEDoff();
    }

    int GetTrapDoorTimer() {
        return trapDoorTimer;
    }

    bool GetBadColour() {
        return badColour;
    }

    void SetAllianceAsRed(bool isRed) {
        allianceColourRed = isRed;
    }
};

#endif  // BLOCKDETECTOR_HPP