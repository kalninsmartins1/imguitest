#pragma once

#include <map>

class JobList;
class Job;
class EventDispatcher;
class Event;
class Tool;

class JobListTab
{
public:
	JobListTab(const JobList& jobList, EventDispatcher& eventDispatcher);
	~JobListTab();

	void Draw();

private:
	void DrawJob(const Job& job, int jobIndex);
	void DrawJobAttemptedPopup();

	void OnAcceptJobResultEvent(const Event& genericEvent);

private:
	bool m_isShowingJobAttemptedPopup;
	bool m_isLastJobSuccessful;

	const JobList& m_jobList;
	const std::map<const Tool*, int>* m_toolsUsedForLastJob;
	EventDispatcher& m_eventDispatcher;	
};