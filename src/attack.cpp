#include <attack.h>

namespace EUSDAB {
    
    Attack::Attack(): _direction(), _damage(0)
    {
    }    

    Attack::~Attack()
    {
    }

    void Attack::setDirection(float x, float y)
    {
        _direction.x = x;
        _direction.y = y;
    }

    Physics::Vector2T<float> Attack::direction()
    {
        return _direction;
    }

    void Attack::setDamage(Life::Amount const & amount)
    {
        _damage = amount;
    }

    Life::Amount Attack::damage()
    {
        return _damage;
    }
}

