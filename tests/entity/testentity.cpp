#include "testentity.h"
#include <string>
#include <iostream>
#include <sstream>
#include <list>
#include <stdexcept>
#include <cassert>
#include <entityparser.h>
#include <state.h>
#include <input/joystickmapping.h>
#include <input/keyboardmapping.h>
#include <physics/world.h>
#include <SFML/Window/Joystick.hpp>
#include <percentageLife.h>
#include <infiniteLife.h>
#include <boost/lexical_cast.hpp>


namespace EUSDAB
{
int id = 0;
std::vector<Entity *> players;
    template <typename Container>
        static Input::Mapping * initPlayerEntities(Container & cont)
    {
        static auto loadEntity = [] (const std::string & name)
        {
            static EntityParser entityParser("../../assets/entities");
            Entity * e = entityParser.loadEntity(name, false);
            if (e == nullptr)
            {
                throw std::runtime_error("Rick Hard entity wasn't loaded");
            }
            typedef unsigned int Size;
            static auto h = [](const Size & v)
            {
                return static_cast<Physics::Unit>(v) 
                    / static_cast<Physics::Unit>(2);
            };
            e->position() = Physics::Vector2(h(500 + id * 500), h(0));
            std::cout << "Id " << id << std::endl;
            e->setName(e->name());// + " " + boost::lexical_cast<std::string>(id));
            id++;

            e->setLife(new PercentageLife(0, 999));
            return e;
        };

        // Type used by sf::Joystic
        typedef unsigned int Size;

        // Number of players before joystick adding
        auto old_size = cont.size();

        // Players
        //std::vector<Entity *> players;
        auto addPlayer = [&] (Entity * e)
        {
            cont.push_back(e);
            players.push_back(e);
        };

        std::vector<std::string> entityList = {{
            "rickhard", "poney", "panda"
        }};

        for (Size i = 0; sf::Joystick::isConnected(i); i++)
        {
            std::cout << "Charging entity..." << std::endl;
            addPlayer(loadEntity(entityList[i % entityList.size()]));
        }

        if (cont.size() == old_size)
        {
            std::cout << "No joysticks detected, using keyboard mapping"
                << std::endl;
            addPlayer(loadEntity("rickhard"));
            return new Input::KeyboardMapping(players.begin(), players.end());
        }
        else
        {
            std::cout << "Nb players : " << players.size() << std::endl;
            return new Input::JoystickMapping(players.begin(), players.end());
        }
    }

    static Entity * makeMapEntity(sf::RenderWindow & window)
    {
        EntityParser entityParser("../../assets/entities");
        Entity * map = entityParser.loadEntity("map_bazar", true);
        if (map == nullptr)
        {
            throw std::runtime_error("Map entity wasn't loaded");
        }

        // Shorten halfwidth / halfheight
        typedef unsigned int Size;
        static auto h = [](const Size & v)
        {
            return static_cast<Physics::Unit>(v) 
                / static_cast<Physics::Unit>(2);
        };

        // Move map to center of window to start with
        sf::Vector2<Size> size = window.getSize();
        map->position() = Physics::Vector2(h(size.x), h(size.y));

        // Map is not gravitable
        map->gravitable() = false;

        //Map f***** life
        map->setLife(new InfiniteLife());

        return map;
    }

    Physics::World * makePhysicsWorld()
    {
        using namespace Physics;
        return new World(AABB(0, 0, 600, 480), Vector2(0, 0.35f));
    }

    EntityTest::EntityTest(sf::RenderWindow & window):
        Application(window), _entityList(), _music()
    {
        // Map
        _entityList.push_back(makeMapEntity(window));

        auto nbNonPlayers = _entityList.size();

        std::cout << "Nb non player = " << nbNonPlayers << std::endl;

        // Players
        Input::Mapping * mapping = initPlayerEntities(_entityList);

        // Input
        _input = new Input::Controller(_entityList.begin(), _entityList.end(), mapping);

        // Physics
        Physics::World * world = makePhysicsWorld();
        _physics = new Physics::Controller(*_input, world);
        _physics->addEntity(_entityList.begin(), _entityList.end());

        _physics->addPlayer(players.begin(), players.end());

        // Graphics
        auto playersBegin = _entityList.begin() + nbNonPlayers;
        _graphics = new Graphics::Controller(_window,
                playersBegin, _entityList.end(), world, false);
        _graphics->addEntity(_entityList.begin(), playersBegin);

        if (!_music.openFromFile("../../assets/audio/musics/bazar.ogg"))
            throw std::runtime_error("Map's music wasn't loaded");
        _music.setLoop(true);
        _music.play();

    }

    EntityTest::~EntityTest()
    {
        delete _input;
        delete _physics;
        delete _graphics;
        for (Entity * e : _entityList)
        {
            delete e;
        }
    }

    void EntityTest::event()
    {
        sf::Event e;
        while (_window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                _window.close();
            }
            else
            {
                _input->pushEvent(e);
            }
        }
        _input->nextFrame();
    }

    void EntityTest::update()
    {
        _physics->update();
        _input->update();
    }

    void EntityTest::render()
    {
        _graphics->draw();
    }
}
