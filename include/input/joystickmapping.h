#ifndef INPUT_JOYSTICK_MAPPING_H
#define INPUT_JOYSTICK_MAPPING_H

#include <input/mapping.h>
#include <input/event.h>
#include <map>
#include <string>

namespace EUSDAB
{
    namespace Input
    {
        class JoystickMapping: public Mapping
        {
            
            public:
                typedef unsigned int JoystickInput;

                enum Button: JoystickInput
                {
                    A, B,
                    X, Y,
                    LB, RB,
                    LStick, RStick,
                    Back, Start, Menu
                };

                enum Axis: JoystickInput
                {
                    LStickUp, LStickDown,
                    LStickRight, LStickLeft,
                    RStickUp, RStickDown,
                    RStickRight, RStickLeft,
                    DPadUp, DPadDown,
                    DPadRight, DPadLeft,
                    LTrigger, RTrigger,
                    None
                };

                JoystickMapping() = delete;
                JoystickMapping(JoystickMapping &&) = default;
                JoystickMapping(JoystickMapping const &) = delete;
                JoystickMapping & operator=(JoystickMapping const &) = delete;

                template <typename InputIter>
                    JoystickMapping(InputIter begin, InputIter end):
                    Mapping(begin, end), _mappings()
                {
                    initMappings();
                }

                ~JoystickMapping();

                // Event-based input, mapping SFML events to
                //  EUSDAB events, using a predefined mapping
                void pushEvent(sf::Event const & event);

                // Continuous input using the same mapping
                //  as for the event-based version
                void update();

            protected:
                // Setup the mappings (ugly s**t)
                void initMappings();

                // SFML Joystick axis -> EUSDAB Joystick axis
                Axis sfAxisToAxis(sf::Joystick::Axis const &, float);

                // EUSDAB Joystick axis -> SFML Joystick axis
                sf::Joystick::Axis axisToSfAxis(Axis const &);

                // Return if the given axis event is in the "dead" zone,
                //  that is if it should be considered as at rest
                bool isInDeadZone(Axis const &, float);

            private:
                struct PlayerMapping
                {
                    typedef JoystickMapping::Axis Axis;

                    Speaker * player;
                    std::map<int, Event::Id> btnMapping;
                    std::map<Axis, Event::Id> axisMapping;
                };

                std::vector<PlayerMapping *> _mappings;
        };
    }
}

#endif
