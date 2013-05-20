#include <states/jump.h>
#include <iostream>

namespace EUSDAB
{
    namespace States
    {
        Jump::Jump():
            State()
        {
        }

        Jump::~Jump()
        {
        }

        void Jump::onUp(const Event & e)
        {
            State::onUp(e);
            if (e.edge == Event::RisingEdge)
            {
                if (entity()->canJump()&&entity()->jumpPossible())
                {
                    switchState(Movement::Jump | _mvt.direction());
                }
            }
        }

        void Jump::onDown(const Event & e)
        {
            State::onDown(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Falling | _mvt.direction());
                entity()->setJumpPossible(true);
            }
        }

        void Jump::onGround(const Event & e)
        {
            State::onGround(e);
            if (e.edge == Event::RisingEdge)
            {
                switchState(Movement::Idle | _mvt.direction());
                entity()->setJumpPossible(true);
                entity()->setNbrJump(entity()->nbrJumpMax());
            }
        }

        void Jump::onLeft(const Event & e)
        {
            State::onLeft(e);

            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                onChangeSide(Movement::Jump | Movement::Left);
                setNextStateAnimationFrameToCurrentFrame();
            }
            else
            {
                //switchState(Movement::Jump | Movement::Idle | Movement::Left);
            }
        }

        void Jump::onRight(const Event & e)
        {
            State::onRight(e);

            if (e.edge == Event::RisingEdge || e.edge == Event::ContinuousEdge)
            {
                onChangeSide(Movement::Jump | Movement::Right);
                setNextStateAnimationFrameToCurrentFrame();
            }
            else
            {
                //switchState(Movement::Jump | Movement::Idle | Movement::Right);
            }
        }

        void Jump::onNextFrame()
        {
            State::onNextFrame();

            // Shorten code !
            using Physics::Unit;

            if (_transform.velocity().y < 0)
            {
                switchState(Movement::Falling | _mvt.direction());
                entity()->setJumpPossible(true);
            }
            
            if (_transform.velocity().y < _jumpValue / 2)
            {
                _entity->setJumpPossible(true);
            }
        }
        
       
        
        void Jump::onEnter()
        {
            // TODO add vertical impulse

            _animation->setPaused(false);
            _entity->setJumpPossible(false);
            _entity->setNbrJump(entity()->nbrJump()-1);
            
            _transform.velocity().y = 4;
        }
        
        

        void Jump::onAnimationEnd()
        {
            _animation->setPaused();
            _animation->explicitAdvance(-1);
        }

        void Jump::setNextStateAnimationFrameToCurrentFrame() const
        {
            // Continue animation from current frame in next state
            State * s = _entity->state();
            if (s == nullptr) { return; }

            Animation * a = s->animation();
            if (a == nullptr) { return; }
            a->setCurrentFrame(_animation->currentFrame());
        }
        
        void Jump::onMiddleOfJump()
        {
        
        }
        
        
        void Jump::onJumpEnd()
        {
        
        }
    }
}
