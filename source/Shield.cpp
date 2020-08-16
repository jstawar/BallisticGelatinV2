#include "Shield.h"

Shield::Shield(const Settings &settings)
    : settings(settings)
{
    initialize();
}

void Shield::nextFrame()
{
    // TODO - move to some integrator class so wil be generic
    // http://physics.ucsc.edu/~peter/242/leapfrog.pdf
    // http://cvarin.github.io/CSci-Survival-Guide/leapfrog.html
    // let's zero all the accelerations and add gravity
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        balls[i].getVectors().acceleration.clear();
        if( settings.calcParams.enableGravity )
            balls[i].getVectors().acceleration.y -= settings.calcParams.gAcc;
    }
    // get all the forces from springs
    if(springConnections)
        springConnections->nextFrame();

    // new velocity and position - leapfrog algorithm
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        balls[i].getVectors().velocity.x += settings.calcParams.halfdt * balls[i].getAcceleration().x;
        balls[i].getVectors().velocity.y += settings.calcParams.halfdt * balls[i].getAcceleration().y;

        balls[i].getVectors().position.x += balls[i].getVelocity().x * settings.calcParams.dt;
        balls[i].getVectors().position.y += balls[i].getVelocity().y * settings.calcParams.dt;
    }
}

void Shield::initialize()
{
    // TODO check if any > 0 - in GUI disabled
    double dx = settings.simParams.shieldParams.dx; // 1.0/settings.simParams.shieldParams.numXShield;
    double dy = settings.simParams.shieldParams.dy; // 1.0/settings.simParams.shieldParams.numYShield;

    double current_x = 0.0;
    double current_y = 0.0;

    balls.reserve( settings.simParams.shieldParams.numXShield * settings.simParams.shieldParams.numYShield );

    // starting in point (0, 0)
    for(unsigned int i = 0 ; i < settings.simParams.shieldParams.numYShield ; i++)
    {
        current_y = i * dy;
        for(unsigned int j = 0 ; j < settings.simParams.shieldParams.numXShield ; j++)
        {
            current_x = j * dx;
            // TODO - random small displacements etc.?
            utilities::VectorXY position(current_x, current_y);
            utilities::Vectors vectors(position, utilities::VectorXY(0.0, -1.0), utilities::VectorXY(0.0, 0.0) );
            Ball ball(vectors, settings.simParams.shieldParams.massBall, settings.simParams.shieldParams.radiusBall);
            balls.push_back(ball);
        }
    }

    // translate to the desired position
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        balls[i].getVectors().position.translate(settings.simParams.shieldParams.initialPosition);
    }

    springConnections = nullptr;
    if(settings.simParams.shieldParams.hasSpings)
        springConnections = new SpringConnections(settings, balls);

    // DO NOT ALTER BALL VECTOR CONTAINER AFTER THAT POINT!!!
}
