#include "Settings.h"

// Some default parameters - not checked whether physical
// All should be loaded from GUI

Settings::SimulationParameters::SimulationParameters()
{
    // SHIELD
    shieldParams.numXShield = 120;
    shieldParams.numYShield = 120;
    shieldParams.dx = 0.003;
    shieldParams.dy = 0.003;
    shieldParams.massBall = 0.0005;
    // maybe radius dependent on dx and dy? say 2* radius filling 90% of space between?
    // TODO - collision radius and display radius - will look nicer, make it blend. Ball filled with color representing tension (no spring attached - red)
    shieldParams.radiusBall = 0.0005; // has to be smaller than min(dx/2, dy/2) - add checks - TODO
    shieldParams.initialPosition = utilities::VectorXY(0.0, 0.0);
    // TODO - different spring coefficients for different connection/cristalization (more realistic modelling of materials like concrete)
    shieldParams.springParams.springCoefficient = 100000.0;
    shieldParams.springParams.extensionBreakCoefficient = 1.15;
    // TODO - rething the compression break - maybe it's something that is not needed?
    // given the size of the ball and detecting collision - might never be reached?
    shieldParams.springParams.compressionBreakCoefficient = 0.65;

    // BULLET
    bulletParams.massBall = 0.015;
    bulletParams.radiusBall = 0.015;
    // currently not used - only solid ball bullet implemented so far
    bulletParams.springParams.springCoefficient = 100000.0;
    bulletParams.springParams.extensionBreakCoefficient = 1.15;
    bulletParams.springParams.compressionBreakCoefficient = 0.65;

    bulletParams.initialPosition = utilities::VectorXY(-0.02,shieldParams.numYShield * shieldParams.dy / 2.0); // let's start in the middle of the shield
    bulletParams.initialVelocity = utilities::VectorXY(300.0,0.0);
}

Settings::CalculationParameters::CalculationParameters()
    : dt(0.000003),
      gAcc(9.81),
      tMax(0.011),
      halfdt(dt/2.0),
      enableGravity(true), // given the time of simulation it might have a negligible effect
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
    recorderParams.totalSeconds = 15;
    recorderParams.framesPerSecond = 30;
    // this is calculated based on other inputs
    double totalFramesThatWillBeCalced = calcParams.tMax / calcParams.dt;
    recorderParams.captureEveryNth = static_cast<unsigned int>( totalFramesThatWillBeCalced / static_cast<double>(recorderParams.totalSeconds / recorderParams.framesPerSecond) );

    // TODO - calculate density of objects for selected inputs(remember about cristalization differences)
    // TODO - maybe add an option to set density and other params are recalculated?
    // TODO - calculate the Young modulus of material
}
