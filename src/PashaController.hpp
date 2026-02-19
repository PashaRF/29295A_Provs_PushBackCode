#ifndef PASHACONTROLLER_HPP
#define PASHACONTROLLER_HPP

#define PROS_USE_SIMPLE_NAMES

#include <math.h>
#include <list>

#include "../include/pros/misc.hpp"

#include "Basic Control Classes/Stick.hpp"
#include "Basic Control Classes/HoldButton.hpp"
#include "Basic Control Classes/ToggleButton.hpp"
#include "Basic Control Classes/TapButton.hpp"


class PashaController
{

public:

    Stick LeftX_;
    Stick LeftY_;
    Stick RightX_;
    Stick RightY_;

    HoldButton R1_;
    HoldButton R2_;
    TapButton L1_;
    TapButton L2_;

    ToggleButton A_;
    TapButton B_;
    TapButton X_;
    TapButton Y_;

    TapButton Up_;
    TapButton Down_;
    TapButton Left_;
    HoldButton Right_; //ahhh

public:
    PashaController() :
        LeftX_(ANALOG_LEFT_X),
        LeftY_(ANALOG_LEFT_Y),
        RightX_(ANALOG_RIGHT_X),
        RightY_(ANALOG_RIGHT_Y),

        R1_(DIGITAL_R1),
        R2_(DIGITAL_R2),
        L1_(DIGITAL_L1),
        L2_(DIGITAL_L2),

        A_(DIGITAL_A),
        B_(DIGITAL_B),
        X_(DIGITAL_X),
        Y_(DIGITAL_Y),

        Up_(DIGITAL_UP),
        Down_(DIGITAL_DOWN),
        Left_(DIGITAL_LEFT),
        Right_(DIGITAL_RIGHT)
    {

    }

    void Tick()
    {
        LeftX_.Tick();
        LeftY_.Tick();
        RightX_.Tick();
        RightY_.Tick();

        R1_.Tick();
        R2_.Tick();
        L1_.Tick();
        L2_.Tick();

        A_.Tick();
        B_.Tick();
        X_.Tick();
        Y_.Tick();

        Up_.Tick();
        Down_.Tick();
        Left_.Tick();
        Right_.Tick();
    }

    void Vibrate() {
        master.rumble("-.");
    }
};

#endif // PASHACONTROLLER_HPP