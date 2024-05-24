#pragma once

class Event;

class EventListener
{
public:
	EventListener();
	virtual ~EventListener();

	virtual void Handle(const Event& eventToHandle) = 0;

};