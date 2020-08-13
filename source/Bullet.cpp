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

void BulletBall::nextFrame()
{
   // double newX = balls[0].getVectors(frame).position.getX() + balls[0].getVectors(frame).velocity.getX() * settings.calcParams.dt;
  //  balls[0].getVectors(!frame).position.setX(newX);
  //  double newY = balls[0].getVectors(frame).position.getY() + balls[0].getVectors(frame).velocity.getY() * settings.calcParams.dt;
  //  balls[0].getVectors(!frame).position.setY(newY);

    // this guy has only gravity
    utilities::VectorXY gravityForce(0.0, -settings.calcParams.gAcc); // = physics::gravityForce(settings.calcParams.gAcc,mass);

    calcVelocity();

    // KILL ME
    /*
    k1v.x = force.x / mass * dt;
    k1v.y = force.y / mass * dt;

    k1x.x = velocity.x * dt;
    k1x.y = velocity.y * dt;

    k2v.x = force.x / mass * dt;
    k2v.y = force.y / mass * dt;

    k2x.x = (velocity.x + k1v.x / 2.0) * dt;
    k2x.y = (velocity.y + k1v.x / 2.0) * dt;

    k3v.x = force.x / mass * dt;
    k3v.y = force.y / mass * dt;

    k3x.x = (velocity.x + k2v.x / 2.0) * dt;
    k3x.y = (velocity.y + k2v.x / 2.0) * dt;

    k4v.x = force.x / mass * dt;
    k4v.y = force.y / mass * dt;

    k4x.x = (velocity.x + k3v.x) * dt;
    k4x.y = (velocity.y + k3v.x) * dt;

    velocity.x += 1.0/6.0 * (k1v.x + 2.0 * k2v.x + 2.0 * k3v.x + k4v.x);
    velocity.y += 1.0/6.0 * (k1v.y + 2.0 * k2v.y + 2.0 * k3v.y + k4v.y);

    position.x += 1.0/6.0 * (k1x.x + 2.0 * k2x.x + 2.0 * k3x.x + k4x.x);
    position.y += 1.0/6.0 * (k1x.y + 2.0 * k2x.y + 2.0 * k3x.y + k4x.y);
    */
}
