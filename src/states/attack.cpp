#include <states/attack.h>
#include <character.h>

namespace CharacterStates
{
    Attack::Attack(Character & c, DirectionX dirX, DirectionY dirY, const unsigned int duration):
        BaseState(c, dirX, dirY), _countDown(duration)
    {
    }

    Attack::~Attack()
    {
    }

    void Attack::enter()
    {
        BaseState::enter();
    }

    void Attack::update()
    {
        BaseState::update();
        if (--_countDown == 0)
        {
            if (isDirection(Right))
            {
                _character.state(IdleRight);
            }
            else
            {
                _character.state(IdleLeft);
            }
        }
    }

    void Attack::leave()
    {
        BaseState::leave();
    }
}
