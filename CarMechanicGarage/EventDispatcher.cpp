#include "EventDispatcher.h"
#include "Event.h"
#include "EventType.h"

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::DispatchEvent(const Event& eventToDispatch)
{
	const auto& listenerIterator = m_listeners.find(eventToDispatch.GetEventType());
	if (listenerIterator != m_listeners.end() && listenerIterator->second != nullptr)
	{
		listenerIterator->second(eventToDispatch);
	}
}

void EventDispatcher::SubscribeToEvent(EventListener listener, EventType type)
{
	m_listeners[type] = listener;
}

void EventDispatcher::UnsubscribeFromEvent(EventType type)
{
	m_listeners.erase(type);
}
