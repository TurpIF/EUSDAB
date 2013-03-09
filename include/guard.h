#ifndef GUARD_H_
#define GUARD_H_

#include <characterState.h>

class Guard: public CharacterState
{
    public:
        Guard(Character &);
        Guard(const Guard &);
        Guard(Guard &&);
        virtual ~Guard();
        Guard & operator=(const Guard &);
        virtual void enter();
        virtual void leave();
        virtual void update();
};

#endif
