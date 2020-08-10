#include "Simulation.h"

Simulation::Simulation(const Settings &settings)
    : shield(settings),
      bullet(new BulletBall(settings)),
      frameForBalls(false),
      frameNum(0)
{

}

void Simulation::nextFrame()
{
  //  collision.groundCheck(bulletBall);

    // integration and forces part
    bullet->nextFrame(frameForBalls);
    shield.nextFrame(frameForBalls);

    std::vector<Ball> &bulletBall = bullet->getBalls();
    std::vector<Ball> &shieldBalls = shield.getBalls();
    // In - Shield collision detecion - very inefficeint
    // TODO - in-shield collision can have it's own collision class - then one division is ommited per calc
    // same for in-bullet and bullet-shield collsion - initialized in constructor
    for(unsigned int i = 0 ; i < shieldBalls.size() ; i++)
    {
        for(unsigned int j = i+1 ; j < shieldBalls.size() ; j++)
        {
            collisions.collision(shieldBalls[i], shieldBalls[j], frameForBalls);
        }
        // Bullet to Shield collision detection
        for(unsigned int k = 0; k < bulletBall.size() ; k++)
        {
            collisions.collision(bulletBall[k], shieldBalls[i], frameForBalls);
        }

        collisions.groundCheck(shieldBalls[i], frameForBalls);
    }

    // update to next - this comes last for sure
    frameForBalls = !frameForBalls;
    frameNum++;
}
