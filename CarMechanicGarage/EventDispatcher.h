#pragma once

#include <vector>
#include <map>
#include <functional>

class Event;
enum class EventType;

using EventListener = std::function<void(const Event&)>;

class EventDispatcher
{
public:
	EventDispatcher();
	~EventDispatcher();

	void DispatchEvent(const Event& eventToDispatch);
	void SubscribeToEvent(EventListener listener, EventType type);
	void UnsubscribeFromEvent(EventType type);

private:
	std::map<EventType, EventListener> m_listeners;
};