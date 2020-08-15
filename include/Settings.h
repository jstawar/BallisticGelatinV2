#ifndef SETTINGS_H
#define SETTINGS_H

#include "Utilities.h"
#include <map>

// TODO - maybe make it a singleton class
// TODO - move bullet/shield stuff to bullet/shield settings etc.
// TODO - and ofc const correctness and getters/setters

struct Settings
{
    struct CalculationParameters
    {
        double dt; // [s]
        double gAcc; // [m/s^2]
        double tMax; // [s]
        bool enableGravity;
        bool checkForGround;
        std::map<double,utilities::Color> colorMap;
        CalculationParameters();
    };
    struct SpringParameters
    {
        double extensionBreakCoefficient; // [] but > 1.0 TODO - add checks
        double compressionBreakCoefficient; // [] but < 1.0
        double springCoefficient; // [N/m]
    };
    struct ShieldParameters
    {
        unsigned int numXShield; // []
        unsigned int numYShield;  // []
        double massBall; // [kg]
        double radiusBall; // [m]
        SpringParameters springParams;
        utilities::VectorXY initialPosition; // [m]
    };
    struct BulletParameters
    {
        double massBall; // [kg]
        double radiusBall; // [m]
        SpringParameters springParams;
        utilities::VectorXY initialPosition; // [m]
        utilities::VectorXY initialVelocity; // [m/s]
    };
    struct SimulationParameters
    {
        ShieldParameters shieldParams;
        BulletParameters bulletParams;
        SimulationParameters();
    };

    CalculationParameters calcParams;
    SimulationParameters simParams;

    Settings(CalculationParameters calcParams, SimulationParameters simParams);
};

#endif // SETTINGS_H
