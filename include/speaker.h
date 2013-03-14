#ifndef SPEAKER_H_
#define SPEAKER_H_

#include <queue>
#include <memory>
#include <event.h>
#include <listener.h>

// Speaker class (design pattern `opinion`)
//
// Dispatches different Events to Listeners,
// simulates a state-based event handling.
class Speaker
{
    public:
        Speaker() = default;
        Speaker(Speaker &&) = default;
        Speaker(const Speaker &) = default;
        ~Speaker() = default;
        Speaker & operator=(const Speaker &) = default;
        void setListener(Listener *);
        void push(const Event &);
        void pollEvents();

    private:
        std::shared_ptr<Listener> _listener;
        std::queue<Event> _events;
};

#endif
