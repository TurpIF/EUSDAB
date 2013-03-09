//-----------------run.cpp
#include <run.h>
#include <character.h>
#include <joystickState.h>

Run::Run(Character & c, float speed, DirectionX dirX, DirectionY dirY) :
    CharacterState(c, dirX, dirY)
{
    if(isDirection(Right))
    {
        _motion.x = speed;
        _motion.y = 0.f;
    }
    else
    {
        _motion.x = -speed;
        _motion.y = 0.f;
    }
}

Run::~Run()
{
}

void Run::enter()
{
    CharacterState::enter();
}

void Run::update(const JoystickState & j)
{
    CharacterState::update(j);
    if (j.axisPosition(_character.joystickId(), JoystickState::Axis::X) * _motion.x == 0)
    {
        if (isDirection(Right))
        {
            _character.state(CharacterState::IdleRight);
        }
        else
        {
            _character.state(CharacterState::IdleLeft);
        }
    }
    else if (j.axisPosition(_character.joystickId(), JoystickState::Axis::X) * _motion.x < 0)
    {
        if(isDirection(Left))
        {
            _character.state(CharacterState::RunRight);
        }
        else
        {
            _character.state(CharacterState::RunLeft);
        }
    }
    else
    {
        _character.move(_motion);
        /*if (j.isButtonFront(_character.joystickId(),BUTTON_A)) 
        {
            if (isDirection(Left))
            {
                _character.state(CharacterState::AttackLeft);
            }
            else
            {
                _character.state(CharacterState::AttackRight);
            }
        }
        else if (j.isButtonFront(_character.joystickId(), BUTTON_B))
        {
            if (isDirection(Left))
            {
                _character.state(CharacterState::SpecialLeft);
            }
            else
            {
                _character.state(CharacterState::SpecialRight);
            }
        }*/
    }
}

void Run::leave()
{
}
