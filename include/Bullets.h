#ifndef BULLETS_H
#define BULLETS_H

#include "Bullet.h"

namespace bullets
{

class BulletAK47: public Bullet
{
public:
    BulletAK47(const Settings &settings);
    virtual void initialize() override;
    virtual void nextFrame(bool frame) override
    {
        // TODO
    }
};

}

#endif // BULLETS_H
