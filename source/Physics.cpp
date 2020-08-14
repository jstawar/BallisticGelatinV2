#include "Physics.h"

namespace physics
{

void Collision::groundCheck(Ball &ball)
{
    if( ball.getPosition().y - ball.getRadius() < 0.0 )
    {
        ball.getVectors().position.y = ball.getRadius();  // TODO - this is just for tests
        ball.getVectors().velocity.y = -ball.getVelocity().y;
    }
}

void Collision::collision(Ball &ball1, Ball &ball2)
{
    x21 = ball2.getPosition().x - ball1.getPosition().x;
    y21 = ball2.getPosition().y - ball1.getPosition().y;
    r12 = ball1.getRadius() + ball2.getRadius();

    d = sqrt(x21*x21 + y21*y21);
    if ( d <= r12)
    {
       m21 = ball2.getMass()/ball1.getMass();
       vx21 = ball2.getVelocity().x - ball1.getVelocity().x;
       vy21 = ball2.getVelocity().y - ball1.getVelocity().y;
       gammav = atan2( -vy21, -vx21 );
       gammaxy = atan2( y21, x21 );
       dgamma = gammaxy-gammav;
       if( dgamma > pi2 )
          dgamma = dgamma - pi2;
       else if ( dgamma < -pi2 )
          dgamma = dgamma + pi2;
       dr = d * sin( dgamma ) / r12;
       alpha = asin( dr );
       a = tan( gammav + alpha );
       dvx2 = -2.0 * ( vx21 + a * vy21) /( ( 1.0 + a * a ) * ( 1.0 + m21 ) );
       ball2.getVectors().velocity.x += dvx2;
       ball2.getVectors().velocity.y += a * dvx2;
       ball1.getVectors().velocity.x -= m21 * dvx2;
       ball1.getVectors().velocity.y -= m21 * a * dvx2;
    }
}

OptimisedCollisions::OptimisedCollisions(const Settings &settings, unsigned int numBuckets)
    : settings(settings),
      numBuckets(numBuckets),
      dl(1.0/static_cast<double>(numBuckets))
{
    buckets = new std::vector<Ball*>*[numBuckets];
    for(unsigned int i = 0 ; i < numBuckets ; i++ )
    {
        buckets[i] = new std::vector<Ball*>[numBuckets];
    }
}

void OptimisedCollisions::addBalls(std::vector<Ball> &balls)
{
    for(unsigned int i = 0 ; i < balls.size() ; i++)
    {
        ballsPointers.push_back( &balls[i] );
    }
}

void OptimisedCollisions::fillBuckets()
{
    // first clear all the buckets
    for(unsigned int i = 0 ; i < numBuckets ; i++)
    {
        for(unsigned int j = 0 ; j < numBuckets ; j++)
        {
            buckets[i][j].clear();
        }
    }

    // fill buckets
    unsigned int bucketX = 0;
    unsigned int bucketY = 0;
    for(unsigned int i = 0 ; i < ballsPointers.size() ; i++)
    {
        Ball *current = ballsPointers[i];
        if( current->getPosition().x < 0 )
        {
            bucketX = 0;
        }
        else
        {
            bucketX = static_cast<unsigned int>(current->getPosition().x / dl);
            if(bucketX >= numBuckets)
                bucketX = numBuckets - 1;
        }
        if( current->getPosition().y < 0 )
        {
            bucketX = 0;
        }
        else
        {
            bucketY = static_cast<unsigned int>(current->getPosition().y / dl);
            if(bucketY >= numBuckets)
                bucketY = numBuckets - 1;
        }

        buckets[bucketX][bucketY].push_back(ballsPointers[i]);
    }
}

void OptimisedCollisions::nextFrame()
{
    // first we have to fill buckets
    fillBuckets();

    //next collisions inside a bucket and with surrounding buckets
    for(unsigned int i = 0 ; i < numBuckets ; i++)
    {
        for(unsigned int j = 0 ; j < numBuckets ; j++)
        {
            // inside a bucket
            std::vector<Ball*> &currentBucket = buckets[j][i];
            for(unsigned n = 0 ; n < currentBucket.size() ; n++)
            {
                for(unsigned m = n+1 ; m < currentBucket.size() ; m++)
                {
                    collision.collision( *currentBucket[n], *currentBucket[m] );
                }

                // ground check only for those in the lowest bucket
                if(settings.calcParams.checkForGround && j == 0)
                {
                    collision.groundCheck(*currentBucket[n]);
                }
            }
            // next right
            if( j < numBuckets - 1 )
            {
                std::vector<Ball*> &currentBucketNextRight = buckets[j+1][i];
                for(unsigned n = 0 ; n < currentBucket.size() ; n++)
                {
                    for(unsigned m = 0 ; m < currentBucketNextRight.size() ; m++)
                    {
                        collision.collision( *currentBucket[n], *currentBucketNextRight[m] );
                    }
                }
            }
            // next up
            if( i < numBuckets - 1 )
            {
                std::vector<Ball*> &currentBucketNextRight = buckets[j][i+1];
                for(unsigned n = 0 ; n < currentBucket.size() ; n++)
                {
                    for(unsigned m = 0 ; m < currentBucketNextRight.size() ; m++)
                    {
                        collision.collision( *currentBucket[n], *currentBucketNextRight[m] );
                    }
                }
            }
            // next right-up
            if( i < numBuckets - 1 && j < numBuckets - 1 )
            {
                std::vector<Ball*> &currentBucketNextRight = buckets[j+1][i+1];
                for(unsigned n = 0 ; n < currentBucket.size() ; n++)
                {
                    for(unsigned m = 0 ; m < currentBucketNextRight.size() ; m++)
                    {
                        collision.collision( *currentBucket[n], *currentBucketNextRight[m] );
                    }
                }
            }
        }
    }
}

}
