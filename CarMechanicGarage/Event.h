#pragma once

enum class EventType;

class Event
{
public:
	virtual ~Event();

	virtual EventType GetEventType() const = 0;	
};