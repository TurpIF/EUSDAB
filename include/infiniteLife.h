#ifndef INFINITE_LIFE_H_
#define INFINITE_LIFE_H_

#include <life.h>

namespace EUSDAB
{
    class InfiniteLife: public Life
    {
        public:
            InfiniteLife(InfiniteLife &&) = default;
            InfiniteLife(const InfiniteLife &) = default;
            InfiniteLife & operator=(const InfiniteLife &) = default;

            InfiniteLife();
            virtual ~InfiniteLife();

            bool isAlive() const;
            Life::Ratio receiveDamage(const Life::Amount &);
            void healDamage(const Life::Amount &);
            virtual Life::Amount amount() const;
            virtual void reset();
    };
}

#endif
