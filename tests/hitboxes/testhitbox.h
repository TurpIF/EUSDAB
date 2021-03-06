#ifndef TEST_PHYSICS_H_
#define TEST_PHYSICS_H_

#include <SFML/Graphics/RectangleShape.hpp>
#include <application.h>
#include <physics/config.h>

namespace EUSDAB
{
    class HitboxTest: public Application
    {
        public:
            HitboxTest() = delete;
            HitboxTest(HitboxTest &&) = delete;
            HitboxTest(const HitboxTest &) = delete;
            HitboxTest & operator=(const HitboxTest &) = delete;

            HitboxTest(sf::RenderWindow &);
            ~HitboxTest();

        protected:
            void render();
            void update();
            void updateRectangles();

        private:
            typedef sf::RectangleShape Rectangle;
            typedef std::vector<Rectangle> RectangleList;
            Physics::Hitbox _hitbox1, _hitbox2;
            RectangleList _rectList1, _rectList2;
            Rectangle _globalRect1, _globalRect2;
    };
}

#endif
