#include "Simulation.h"

Simulation::Simulation(const Settings &settings)
    : shield(new Shield(settings)), // TODO - selected from settings (ShieldFactory)
      bullet(new BulletBall(settings)), // TODO - this should be selected from settings (add BulletFactory)
      optimisedCollisions(settings, 10),
      frameNum(0),
      totalBalls(0)
{
    if( shield )
    {
        optimisedCollisions.addBalls(shield->getBalls());
        totalBalls += shield->getBalls().size();
    }
    if( bullet )
    {
        optimisedCollisions.addBalls(bullet->getBalls());
        totalBalls += bullet->getBalls().size();
    }
}

void Simulation::nextFrame()
{
    // TODO - this requires testing what comes first
    // integration and forces part
    if( bullet )
        bullet->nextFrame();
    if( shield )
        shield->nextFrame();

    optimisedCollisions.nextFrame();

    // update to next - this comes last for sure
    frameNum++;
}

void Simulation::countActiveConnections()
{

}

