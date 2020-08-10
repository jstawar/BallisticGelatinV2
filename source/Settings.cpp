#include "Settings.h"

// Some default parameters - not checked whether physical

Settings::SimulationParameters::SimulationParameters()
    : initialBulletPosition(utilities::VectorXY(-0.06,0.5)),
      initialBulletVelocity(utilities::VectorXY(10.0,0.0))
{
    springCoefficient = 500.0;
    numXShield = 5;
    numYShield = 6;
    massShieldBall = 0.0015;
    radiusShieldBall = 0.015;
    massBullet = 0.015;
    radiusBullet = 0.015;
    extensionBreakCoefficient = 1.35;
    compressionBreakCoefficient = 0.65;
    initialShieldPosition = utilities::VectorXY(0.0, 0.0);

    colorMap[0.0] = utilities::Color(1.0, 1.0, 1.0);
    colorMap[0.1] = utilities::Color(0.0, 0.0, 1.0);
    colorMap[0.2] = utilities::Color(0.0, 1.0, 0.0);
    colorMap[0.45] = utilities::Color(1.0, 1.0, 0.0);
    colorMap[0.70] = utilities::Color(1.0, 0.0, 0.0);
}

Settings::CalculationParameters::CalculationParameters()
    : dt(0.001),
      gAcc(9.81),
      tMax(4.0)
{

}

// TODO = initialize it with values from GUI
Settings::Settings(CalculationParameters calcParams, SimulationParameters simParams)
    : calcParams(calcParams),
      simParams(simParams)
{
    // TODO - calculate density of gelatin for selected inputs
    // TODO - maybe add an option to set density and other params are recalculated?
}
