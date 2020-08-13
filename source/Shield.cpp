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
        balls[i].getVectors().acceleration.y -= settings.calcParams.gAcc;
    }
    // get all the forces from springs
    springConnections->nextFrame();

    // new velocity and position
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        balls[i].getVectors().velocity.x += 1.0/2.0 * settings.calcParams.dt * balls[i].getAcceleration().x;
        balls[i].getVectors().velocity.y += 1.0/2.0 * settings.calcParams.dt * balls[i].getAcceleration().y;

        balls[i].getVectors().position.x += balls[i].getVelocity().x * settings.calcParams.dt;
        balls[i].getVectors().position.y += balls[i].getVelocity().y * settings.calcParams.dt;
    }
}

void Shield::initialize()
{
    // TODO check if any > 0 - in GUI disabled
    double dx = 1.0/settings.simParams.numXShield;
    double dy = 1.0/settings.simParams.numYShield;

    double current_x = 0.0;
    double current_y = 0.0;

    balls.reserve( settings.simParams.numXShield * settings.simParams.numYShield );

    for(unsigned int i = 0 ; i < settings.simParams.numYShield ; i++)
    {
        current_y = i * dy;
        for(unsigned int j = 0 ; j < settings.simParams.numXShield ; j++)
        {
            current_x = j * dx;
            // TODO - random small displacements etc.
            utilities::VectorXY position(current_x, current_y);
            utilities::Vectors vectors(position, utilities::VectorXY(0.0, -1.0), utilities::VectorXY(0.0, 0.0) );
            Ball ball(vectors, settings.simParams.massShieldBall, settings.simParams.radiusShieldBall);
            balls.push_back(ball);
        }
    }


    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        balls[i].getVectors().position.translate(settings.simParams.initialShieldPosition);
    }

    springConnections = new SpringConnections(settings, balls);
}
