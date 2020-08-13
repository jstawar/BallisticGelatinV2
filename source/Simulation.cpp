#include "Simulation.h"

Simulation::Simulation(const Settings &settings)
    : shield(new Shield(settings)), // TODO - selected from settings (ShieldFactory)
      bullet(new bullets::BulletAK47(settings)), // TODO - this should be selected from settings (add BulletFactory)
      frameNum(0)
{

}

void Simulation::nextFrame()
{
    // TODO - this requires testing what comes first
    // integration and forces part
    if( bullet )
        bullet->nextFrame();
    if( shield )
        shield->nextFrame();

    if( shield )
    {
        std::vector<Ball> &shieldBalls = shield->getBalls();
        // In - Shield collision detecion - very inefficeint
        // TODO - in-shield collision can have it's own collision class - then one division is ommited per calc
        // same for in-bullet and bullet-shield collsion - initialized in constructor
        for(unsigned int i = 0 ; i < shieldBalls.size() ; i++)
        {
            for(unsigned int j = i+1 ; j < shieldBalls.size() ; j++)
            {
                collisions.collision(shieldBalls[i], shieldBalls[j]);
            }
            if( bullet )
            {
                // Bullet to Shield collision detection
                std::vector<Ball> &bulletBall = bullet->getBalls();
                for(unsigned int k = 0; k < bulletBall.size() ; k++)
                {
                    collisions.collision(bulletBall[k], shieldBalls[i]);
                }
            }

            collisions.groundCheck(shieldBalls[i]);
        }
    }

    // TODO - we can also check bullet for ground

    // update to next - this comes last for sure
    frameNum++;
}

