#include <states/walk.h>

namespace EUSDAB
{
    namespace States
    {
        Walk::Walk():
            State()
        {
        }

        Walk::~Walk()
        {
        }

        void Walk::onUp(const Event & e)
        {
            State::onUp(e);
        }

        void Walk::onDown(const Event & e)
        {
            State::onDown(e);
        }

        void Walk::onLeft(const Event & e)
        {
            State::onLeft(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Run | Movement::Left);
            }
            else
            {
                switchState(Movement::Idle | Movement::Left);
            }
        }

        void Walk::onRight(const Event & e)
        {
            State::onRight(e);
            if ((e.edge == Event::RisingEdge)||(e.edge == Event::ContinuousEdge))
            {
                switchState(Movement::Run | Movement::Right);
            }
            else
            {
                switchState(Movement::Idle | Movement::Right);
            }
        }

        void Walk::onNextFrame()
        {
            State::onNextFrame();
        }
    }
}