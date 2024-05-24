#pragma once

#include "Event.h"
#include "EventType.h"

class Tool;

class BuyToolEvent : public Event
{
public:
	BuyToolEvent(const Tool& toolToBuy);

	inline EventType GetEventType() const override { return EventType::BUY_TOOL; };
	const Tool& GetToolToBuy() const;

private:
	const Tool& m_toolToBuy;
};