#pragma once

#include "Event.h"
#include "EventType.h"

class Tool;

class ToolBoughtEvent: public Event
{
public:
	ToolBoughtEvent(const Tool& boughtTool);
	~ToolBoughtEvent();

	inline EventType GetEventType() const override { return EventType::TOOL_BOUGHT; }
	inline const Tool& GetBoughtTool() const { return m_boughtTool; }

private:
	const Tool& m_boughtTool;
};
