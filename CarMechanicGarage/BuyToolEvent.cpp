#include "BuyToolEvent.h"
#include "EventType.h"

BuyToolEvent::BuyToolEvent(const Tool& toolToBuy)
    : m_toolToBuy(toolToBuy)
{
}

const Tool& BuyToolEvent::GetToolToBuy() const
{
    return m_toolToBuy;
}
