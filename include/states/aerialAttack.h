#ifndef AERIALATTACK_H_
#define AERIALATTACK_H_

#include <states/baseState.h>

namespace CharacterStates
{
    class AerialAttack: public CharacterState
    {
        public:
            AerialAttack(Character &);
            AerialAttack(const AerialAttack &);
            AerialAttack(AerialAttack &&);
            virtual ~AerialAttack();
            AerialAttack & operator=(const AerialAttack &);
            virtual void enter();
            virtual void leave();
            virtual void update();
    };
}

#endif
