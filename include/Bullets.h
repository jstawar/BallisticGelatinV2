#ifndef BULLETS_H
#define BULLETS_H

#include "Bullet.h"

namespace bullets
{

class BulletAK47: public Bullet
{
protected:
    virtual void initialize() override;
public:
    BulletAK47(const Settings &settings);
};

}

#endif // BULLETS_H
