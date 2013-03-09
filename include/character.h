#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <map>
#include <entity.h>
#include <characterState.h>

class Character: public Entity
{
    public:
        Character();
        Character(const Character &);
        Character(Character &&);
        virtual ~Character();
        Character & operator=(const Character &);
        void update(const Input &);
        void render(Graphics::Target &, Graphics::Transformation);
        void addState(CharacterState::Id, CharacterState *);
        void state(CharacterState::Id id);

        std::string const & _name();
        void name(std::string const &);
        int damage();
        void damage(int);
        unsigned int joystickId();
        void joystickId(unsigned int);

    private:
        CharacterState * _currentState;
        std::map<CharacterState::Id, CharacterState *> _states;
        std::string _name;
        int _damage;
        unsigned int _joystickId;
};

#endif // CHARACTER_H_
