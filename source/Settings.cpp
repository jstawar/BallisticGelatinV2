#include "Settings.h"

// Some default parameters - not checked whether physical

Settings::SimulationParameters::SimulationParameters()
{
    shieldParams.numXShield = 50;
    shieldParams.numYShield = 75;
    shieldParams.dx = 0.01;
    shieldParams.dy = 0.01;
    shieldParams.massBall = 0.0005;
    shieldParams.radiusBall = 0.0025;
    shieldParams.initialPosition = utilities::VectorXY(0.0, 0.0);
    shieldParams.springParams.springCoefficient = 100000.0;
    shieldParams.springParams.extensionBreakCoefficient = 1.15;
    shieldParams.springParams.compressionBreakCoefficient = 0.65;

    bulletParams.massBall = 0.015;
    bulletParams.radiusBall = 0.015;
    bulletParams.springParams.springCoefficient = 100000.0;
    bulletParams.springParams.extensionBreakCoefficient = 1.15;
    bulletParams.springParams.compressionBreakCoefficient = 0.65;
    bulletParams.initialPosition = utilities::VectorXY(-0.06,0.5);
    bulletParams.initialVelocity = utilities::VectorXY(300.0,0.0);
}

Settings::CalculationParameters::CalculationParameters()
    : dt(0.000003),
      gAcc(9.81),
      tMax(0.05),
      enableGravity(true),
      checkForGround(false)
{
    colorMap[0.0] = utilities::Color(1.0, 1.0, 1.0);
    colorMap[0.1] = utilities::Color(0.0, 0.0, 1.0);
    colorMap[0.2] = utilities::Color(0.0, 1.0, 0.0);
    colorMap[0.45] = utilities::Color(1.0, 1.0, 0.0);
    colorMap[0.70] = utilities::Color(1.0, 0.0, 0.0);
}

// TODO = initialize it with values from GUI
Settings::Settings(CalculationParameters calcParams, SimulationParameters simParams)
    : calcParams(calcParams),
      simParams(simParams)
{
    // TODO - calculate density of gelatin for selected inputs
    // TODO - maybe add an option to set density and other params are recalculated?
}
