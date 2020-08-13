#include "Physics.h"

namespace physics
{

utilities::VectorXY gravityForce(double gAcc, double mass)
{
    return gAcc * mass;
}

utilities::VectorXY springForce(double k, double mass, double length, double restLength)
{

}

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


}
