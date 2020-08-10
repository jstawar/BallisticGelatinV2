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
    calcVelocity(false);
}

void BulletBall::nextFrame(bool frame)
{
   // double newX = balls[0].getVectors(frame).position.getX() + balls[0].getVectors(frame).velocity.getX() * settings.calcParams.dt;
  //  balls[0].getVectors(!frame).position.setX(newX);
  //  double newY = balls[0].getVectors(frame).position.getY() + balls[0].getVectors(frame).velocity.getY() * settings.calcParams.dt;
  //  balls[0].getVectors(!frame).position.setY(newY);

    // this guy has only gravity
    utilities::VectorXY gravityForce(0.0, -settings.calcParams.gAcc); // = physics::gravityForce(settings.calcParams.gAcc,mass);

    calcVelocity(!frame);

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

BulletAK47::BulletAK47(const Settings &settings)
    : Bullet(settings)
{
    initialize();
}

// TODO

void BulletAK47::initialize()
{
    unsigned int nX = 10;
    unsigned int nY = 11;

    double radius = 0.002;
    double dx = 0.02;
    double dy = 0.02;
    double y0 = -1.0 * (dy * (nY-1)/2.0);
    double x0 = 0.0;
    double mass = 0.01;

    for(unsigned int i = 0 ; i < nY ; i++)
    {
        for(unsigned int j = 0 ; j < nX ; j++)
        {
            utilities::Vectors vectors;
            vectors.position.setX(x0 + dx * j);
            vectors.position.setY(y0 + dy * i);
            Ball current(vectors, mass, radius);
            balls.push_back(current);
        }
    }

  /*  unsigned int nXtip = 15;
    double xMaxTip = 0.25;
    x0 = dx * nX;
    dx = xMaxTip / nXtip;
    y0 = dy * (nY - 1) / 2.0;

    for(unsigned int i = 0; i < nXtip ; i++)
    {
        utilities::Vectors vectors;
        double x = x0 + dx * i;
        vectors.position.setX(x);
        double y = sqrt( pow(x/4, 2.0) -  );
        vectors.position.setY(y0);
        Ball current(vectors, mass, radius);
        balls.push_back(current);
    }
*/

    // TODO
    // we are considering only cross-section in our simulation by we should count all the hypothetical shperes that represent 3D bullet?
    // Symmetry is on our favour but we need to know how many balls can be stoed in certain wolume (given the simples cristalization - cube mesh)

}
