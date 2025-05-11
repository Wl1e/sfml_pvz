#pragma once

#include <SFML/Window/Event.hpp>
#include <functional>
#include <unordered_map>

namespace demo {

using handler = std::function<void(const sf::Event&)>;

class EventHandler
{
public:
    EventHandler() = default;
    ~EventHandler() = default;
    void setEvent(const sf::Event& event, handler func)
    {
        m_funcs[event] = std::move(func);
    }
    void delEvent(const sf::Event& event)
    {
        m_funcs.erase(event);
    }
    bool hasEvent(const sf::Event& event)
    {
        return m_funcs.count(event) != 0;
    }
    void call(const sf::Event& event)
    {
        if(!hasEvent(event)) {
            // log error
            return;
        }
        m_funcs[event](event);
    }

private:
    std::unordered_map<sf::Event, handler> m_funcs;
};

} // namespace demo