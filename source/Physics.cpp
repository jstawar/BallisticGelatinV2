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

void Collision::groundCheck(Ball &ball, bool frame) // TODO - this frame bool passing is quite ugly, maybe Ball should store a reference?
{
    if( ball.getPosition(frame).getY() - ball.getRadius() < 0.0 )
    {
        ball.getVectors(frame).position.setY(ball.getRadius());  // TODO - this is just for tests
        ball.getVectors(frame).velocity.setY( -ball.getVelocity(frame).getY() );
    }
}

void Collision::collision(Ball &ball1, Ball &ball2, bool frame)
{
    x21 = ball2.getPosition(frame).getX() - ball1.getPosition(frame).getX();
    y21 = ball2.getPosition(frame).getY() - ball1.getPosition(frame).getY();
    r12 = ball1.getRadius() + ball2.getRadius();

    d = sqrt(x21*x21 + y21*y21);
    if ( d <= r12)
    {
       m21 = ball2.getMass()/ball1.getMass();
       vx21 = ball2.getVelocity(frame).getX() - ball1.getVelocity(frame).getX();
       vy21 = ball2.getVelocity(frame).getY() - ball1.getVelocity(frame).getY();
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
       ball2.getVectors(frame).velocity.setX( ball2.getVelocity(frame).getX() + dvx2 );
       ball2.getVectors(frame).velocity.setY( ball2.getVelocity(frame).getY() + a * dvx2 );
       ball1.getVectors(frame).velocity.setX( ball1.getVelocity(frame).getX() - m21 * dvx2 );
       ball1.getVectors(frame).velocity.setY( ball1.getVelocity(frame).getY() - m21 * a * dvx2 );

       // TODO basically it's that.. I think I'll add some interfaces to Vector to make it more friendly
       //ball2.velocity.x += dvx2;
       //ball2.velocity.y += a*dvx2;
       //ball1.velocity.x -= m21*dvx2;
       //ball1.velocity.y -= a*m21*dvx2;
    }
}


}
