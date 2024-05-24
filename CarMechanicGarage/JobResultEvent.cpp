#include "JobResultEvent.h"


JobResultEvent::JobResultEvent(bool isJobSuccessful, const std::map<const Tool*, int>& usedTools)
	:	m_isJobSuccessful(isJobSuccessful),
		m_usedTools(usedTools)
{
}

JobResultEvent::~JobResultEvent()
{
}
