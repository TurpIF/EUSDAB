#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <set>
#include <physics/config.h>
#include <movement.h>
#include <input/speaker.h>
//#include <attack.h>

// TODO move this in a separate header
namespace std
{
    template <typename T>
        struct hash_ptr
    {
        size_t operator()(const T * x) const
        {
            return x != nullptr ? hash<T>()(*x) : 0;
        }
    };

    template <typename T>
        struct less_ptr
    {
        bool operator()(const T * l, const T * r) const
        {
            return l != nullptr && r != nullptr ? less<T>()(*l, *r) : false;
        }
    };
}

namespace EUSDAB
{
    // Forward declarations
    class State;

    // TODO physics module should be moved either in a 
    //   component or in state, using delegation afterwards.
    class Entity: public Input::Speaker
    {
        public:
            Entity(Entity &&) = default;
            Entity(Entity const &) = delete;
            Entity & operator=(Entity const &) = delete;

            Entity();
            virtual ~Entity();

            // General

            // Get/Set the Entity's name
            std::string name() const;
            void setName(const std::string &);

            // Attack module

            // Get/Set the attack
            //const Attack & attack() const;
            //void setAttack(Attack *);

            // Actually attack another entity
            void attack(Entity *); // FIXME const ? 

            // State module

            // Get the Entity's state directly
            State * state() const;
            // ...or by lookup by movement
            State * state(const Movement &) const;

            // Set the Entity's state directly
            void setState(State *);
            // ...or by lookup by movement (throws an 
            //   std::runtime_error if the given ID 
            //   isn't defined by an associated state). 
            void setState(const Movement &);

            // Add a new state to the Entity, identified
            //   by its movement (throws an std::runtime_error
            //   if the state's ID is already associated to another
            //   state).
            void addState(State *);

        protected:
            // General
            std::string _name;

            // Attack TODO
            //Attack * _attack;

            // State
            State * _current;
            std::set<State *, std::less_ptr<State>> _states;
    };
}

#endif
