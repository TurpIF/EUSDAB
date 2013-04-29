#include <state.h>
#include <entity.h>
#include <stdexcept>

namespace EUSDAB
{
    State::State(Entity * entity, const Movement & mvt):
        _entity(entity),
        _mvt(mvt),
        _animation()
    {
    }

    State::~State()
    {
    }

    Entity * State::entity() const
    {
        return _entity;
    }
    
    void State::setEntity(Entity * e)
    {
        _entity = e;
    }

    void State::switchState(const Movement & id)
    {
        State * s = _entity->state(id);
        if (s == nullptr)
        {
            throw std::runtime_error("Undefined State");
        }
        _entity->setState(s);
    }

    Movement State::movement() const
    {
        return _mvt;
    }

    void State::setMovement(const Movement & mvt)
    {
        _mvt = mvt;
    }

    Animation & State::animation()
    {
        return _animation;
    }

    const Animation & State::animation() const
    {
        return _animation;
    }
}
