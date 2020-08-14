#include "Settings.h"

// Some default parameters - not checked whether physical

Settings::SimulationParameters::SimulationParameters()
    : initialBulletPosition(utilities::VectorXY(-0.06,0.5)),
      initialBulletVelocity(utilities::VectorXY(300.0,0.0))
{
    springCoefficient = 100000.0;
    numXShield = 100;
    numYShield = 100;
    massShieldBall = 0.0005;
    radiusShieldBall = 0.002;
    massBullet = 0.015;
    radiusBullet = 0.015;
    extensionBreakCoefficient = 1.15;
    compressionBreakCoefficient = 0.65;
    initialShieldPosition = utilities::VectorXY(0.0, 0.01);

    colorMap[0.0] = utilities::Color(1.0, 1.0, 1.0);
    colorMap[0.1] = utilities::Color(0.0, 0.0, 1.0);
    colorMap[0.2] = utilities::Color(0.0, 1.0, 0.0);
    colorMap[0.45] = utilities::Color(1.0, 1.0, 0.0);
    colorMap[0.70] = utilities::Color(1.0, 0.0, 0.0);
}

Settings::CalculationParameters::CalculationParameters()
    : dt(0.000003),
      gAcc(9.81),
      tMax(4.0),
      enableGravity(true),
      checkForGround(false)
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
