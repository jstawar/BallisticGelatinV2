#include "Settings.h"

// Some default parameters - not checked whether physical
// All should be loaded from GUI

Settings::SimulationParameters::SimulationParameters()
{
    // SHIELD
    shieldParams.numXShield = 120;
    shieldParams.numYShield = 120;
    shieldParams.totalBalls = shieldParams.numXShield * shieldParams.numYShield;
    shieldParams.dx = 0.0035;
    shieldParams.dy = 0.0035;
    shieldParams.xL = shieldParams.numXShield * shieldParams.dx;
    shieldParams.yL = shieldParams.numYShield * shieldParams.dy;
    shieldParams.massBall = 0.0001;
    shieldParams.mass = shieldParams.massBall * shieldParams.totalBalls;
    // TODO - collision radius and display radius - will look nicer, make it blend. Ball filled with color representing tension (no spring attached - red)
    shieldParams.fillingPercentage = 0.6;
    shieldParams.radiusBall = std::min( shieldParams.dx, shieldParams.dy ) * shieldParams.fillingPercentage / 2.0; // TODO - filling from GUI
    // now we can calculate the densities
    shieldParams.densityArea = shieldParams.mass / (shieldParams.xL * shieldParams.yL);
    shieldParams.densityVolume = shieldParams.densityArea / ( 2.0 * shieldParams.radiusBall ) * shieldParams.fillingPercentage;
    shieldParams.initialPosition = utilities::VectorXY(0.0, 0.0);
    // TODO - different spring coefficients for different connection/cristalization (more realistic modelling of materials like concrete)
    shieldParams.hasSpings = true;
    shieldParams.springParams.springCoefficient = 1000000.0;
    shieldParams.springParams.extensionBreakCoefficient = 1.15;
    // TODO - rethink the compression break - maybe it's something that is not needed?
    // given the size of the ball and detecting collision - might never be reached?
    shieldParams.springParams.compressionBreakCoefficient = 0.65;

    // BULLET
    bulletParams.massBall = 0.008;
    bulletParams.radiusBall = 0.00381;
    // currently not used - only solid ball bullet implemented so far
    bulletParams.springParams.springCoefficient = 100000.0;
    bulletParams.springParams.extensionBreakCoefficient = 1.15;
    bulletParams.springParams.compressionBreakCoefficient = 0.65;

    bulletParams.initialPosition = utilities::VectorXY(-0.02,shieldParams.numYShield * shieldParams.dy / 2.0); // let's start in the middle of the shield
    bulletParams.initialVelocity = utilities::VectorXY(715.0,0.0);
}

Settings::CalculationParameters::CalculationParameters()
    : dt(0.000003),
      gAcc(9.81),
      tMax(0.025),
      halfdt(dt/2.0),
      enableGravity(true), // given the time of simulation it might have a negligible effect
      checkForGround(true)
{
    // set colors for values [-1, 1]
    colorMap[-1.0] = utilities::Color(1.0, 0.0, 1.0);
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
    recorderParams.fileName = "/Users/jakubstawarczyk/renders/test"; // TODO - from GUI location and fileName
    recorderParams.record = false;
    recorderParams.streamOnTheFly = true;
    recorderParams.saveFirstFrameNthTimes = 30;
    // this is calculated based on other inputs
    double totalFramesThatWillBeCalced = calcParams.tMax / calcParams.dt;
    // TODO - fix that rounding error that makes animation longer than expected ( 8.2 is rounded to 8 so more frames are captured)
    recorderParams.captureEveryNth = static_cast<unsigned int>( totalFramesThatWillBeCalced / static_cast<double>(recorderParams.totalSeconds * recorderParams.framesPerSecond) );

    // TODO - calculate density of objects for selected inputs(remember about cristalization differences)
    // TODO - maybe add an option to set density and other params are recalculated?
    // TODO - calculate the Young modulus of material
}
