#include "testPainter.h"
#include <stdexcept>
#include <iostream>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <texturemanager.h>
#include <movement.h>
#include <state.h>

namespace EUSDAB
{
    PainterTest::PainterTest(sf::RenderWindow & window):
        Application(window), _entityParser(), _painter(window)
    {
        _entity = _entityParser.loadEntity("../../assets/entities/rickhard");
        if (_entity == nullptr)
        {
            throw std::runtime_error("Entity wasn't loaded");
        }
        std::cout << "Loaded Entity " << _entity->name() << std::endl;
        _painter.addEntity(_entity);

        auto setupAnimation = [] (Animation * a)
        {
            std::cout << "Setting up animation :" << std::endl;
            constexpr float sX = 50, sY = 50;
            std::cout << "- moving sprite to (" << sX << ", " 
                << sY << ")" << std::endl;
            a->sprite().setPosition(sX, sY);
            std::cout << "Animation FPI = " << a->fpi() << std::endl;
        };
        setupAnimation(_entity->state()->animation());
    }

    PainterTest::~PainterTest()
    {
        delete _entity;
    }

    void PainterTest::event()
    {
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (e.type == sf::Event::KeyPressed)
            {
                if (e.key.code == sf::Keyboard::A)
                {
                    std::cout << "Adding entity "
                        << _entity->name() << std::endl;
                    _painter.addEntity(_entity);
                }
                else if (e.key.code == sf::Keyboard::Z)
                {
                    std::cout << "Removing entity "
                        << _entity->name() << std::endl;
                    _painter.removeEntity(_entity);
                }
                else if (e.key.code == sf::Keyboard::Space)
                {
                    Animation * a = _entity->state()->animation();
                    a->setPaused(1 - a->paused());
                    std::cout << "Toggling animation pause" << std::endl;
                }
                else if (e.key.code == sf::Keyboard::Right)
                {
                    Movement mvt = _entity->state()->movement();
                    Movement new_mvt;
                    if (mvt.flag() & Movement::Idle)
                    {
                        std::cout << "Setting state to Walk" << std::endl;
                        new_mvt.setFlag(Movement::Walk | Movement::Right);
                        _entity->setState(new_mvt);
                    }
                }
                else if (e.key.code == sf::Keyboard::Left)
                {
                    Movement mvt = _entity->state()->movement();
                    Movement new_mvt;
                    if (mvt.flag() & Movement::Idle || true)
                    {
                        std::cout << "Setting state to Walk" << std::endl;
                        new_mvt.setFlag(Movement::Run | Movement::Left);
                        _entity->setState(new_mvt);
                    }
                }
            }
        }
    }

    void PainterTest::update()
    {
        _entity->state()->onNextFrame();
    }

    void PainterTest::render()
    {
        _painter.draw();
    }
}
