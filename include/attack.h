#ifndef ATTACK_H_
#define ATTACK_H_

#include <entity.h>
#include <life.h>

namespace EUSDAB
{
    class Entity;
    class Attack
    {
        public:
            Attack(Attack &&) = default;
            Attack(Attack const &) = delete;
            Attack & operator=(Attack const &) = delete;

            Attack();
            virtual ~Attack();

            virtual void onAttack(Entity * entity) = 0;
            void setDirection(float x, float y);
            Physics::Vector2T<float> direction();
            void setDamage(Life::Amount const & amount);
            Life::Amount const & damage();


        private:
            Physics::Vector2T<float> _direction;
            Life::Amount _damage;
    };
}

#endif //ATTACK_H_
