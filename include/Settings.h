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
        CalculationParameters();
    };
    struct SimulationParameters
    {
        unsigned int numXShield; // []
        unsigned int numYShield;  // []
        double massShieldBall; // [kg]
        double radiusShieldBall; // [m]
        double massBullet; // [kg]
        double radiusBullet; // [m]
        double extensionBreakCoefficient; // [] but > 1.0 TODO - add checks
        double compressionBreakCoefficient; // [] but < 1.0
        double springCoefficient; // [N/m]
        utilities::VectorXY initialShieldPosition; // [m]
        utilities::VectorXY initialBulletPosition; // [m]
        utilities::VectorXY initialBulletVelocity; // [m/s]
        std::map<double,utilities::Color> colorMap;
        SimulationParameters();
    };

    CalculationParameters calcParams;
    SimulationParameters simParams;

    Settings(CalculationParameters calcParams, SimulationParameters simParams);
};

#endif // SETTINGS_H
