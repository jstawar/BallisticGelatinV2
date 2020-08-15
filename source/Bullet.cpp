#include "Bullet.h"

#include <cmath>

BulletBall::BulletBall(const Settings &settings)
    : Bullet(settings)
{
    initialize();
}

void BulletBall::initialize()
{
    utilities::Vectors vectors;
    vectors.position = settings.simParams.bulletParams.initialPosition;
    vectors.velocity = settings.simParams.bulletParams.initialVelocity;
    Ball current(vectors, settings.simParams.bulletParams.massBall, settings.simParams.bulletParams.radiusBall);
    balls.push_back(current);

    mass = settings.simParams.bulletParams.massBall;
    calcVelocity();

    // DO NOT ALTER BALL VECTOR CONTAINER AFTER THAT POINT!!!
}

void Bullet::nextFrame()
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

    calcVelocity();
}
