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
    vectors.position = settings.simParams.initialBulletPosition;
    vectors.velocity = settings.simParams.initialBulletVelocity;
    Ball current(vectors, settings.simParams.massBullet, settings.simParams.radiusBullet);
    balls.push_back(current);

    mass = settings.simParams.massBullet;
    calcVelocity();
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
        balls[i].getVectors().acceleration.y -= settings.calcParams.gAcc;
    }
    // get all the forces from springs
    if (springConnections)
        springConnections->nextFrame();

    // new velocity and position
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        balls[i].getVectors().velocity.x += 1.0/2.0 * settings.calcParams.dt * balls[i].getAcceleration().x;
        balls[i].getVectors().velocity.y += 1.0/2.0 * settings.calcParams.dt * balls[i].getAcceleration().y;

        balls[i].getVectors().position.x += balls[i].getVelocity().x * settings.calcParams.dt;
        balls[i].getVectors().position.y += balls[i].getVelocity().y * settings.calcParams.dt;
    }

    calcVelocity();
}
