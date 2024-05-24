#include "JobListTab.h"
#include "imgui.h"
#include "JobList.h"
#include "Job.h"
#include "Vehicle.h"
#include "EventDispatcher.h"
#include "AcceptJobEvent.h"
#include "JobResultEvent.h"

static constexpr const char* JOB_ATTEMPTED_POPUP_NAME = "Accept Result";
static const ImVec2 POPUP_SIZE(300.f, 200.f);

JobListTab::JobListTab(const JobList& jobList, EventDispatcher& eventDispatcher)
	:	m_isShowingJobAttemptedPopup(false),
		m_isLastJobSuccessful(false),
		m_jobList(jobList),
		m_toolsUsedForLastJob(nullptr),
		m_eventDispatcher(eventDispatcher)	
{
	m_eventDispatcher.SubscribeToEvent(std::bind(&JobListTab::OnAcceptJobResultEvent, this, std::placeholders::_1), 
		EventType::ACCEPT_JOB_RESULT);
}

JobListTab::~JobListTab()
{
	m_eventDispatcher.UnsubscribeFromEvent(EventType::ACCEPT_JOB_RESULT);
}

void JobListTab::Draw()
{	
	const std::map<int, std::unique_ptr<Job>>& jobs = m_jobList.GetAvailableJobs();
	for (const auto& jobIterator : jobs)
	{
		const Job* job = jobIterator.second.get();
		if (job != nullptr)
		{
			DrawJob(*job, jobIterator.first);		
		}
	}
	if (m_isShowingJobAttemptedPopup)
	{
		DrawJobAttemptedPopup();
	}
}

void JobListTab::DrawJob(const Job& job, int jobIndex)
{
	const Malfunction& malfunction = job.GetMalfunction();
	ImGui::Text("  - Vehicle type: [%s] Malfunction: [%s]",
		job.GetVehicleType().c_str(), malfunction.GetName().c_str());
	ImGui::SameLine();
	ImGui::PushID(jobIndex);
	bool isButtonPressed = ImGui::Button("Accept");
	ImGui::PopID();

	ImGui::Text("    Needed tools: ");
	const std::vector<Tool*>& tools = job.GetNeededTools();
	for (const Tool* tool : tools)
	{
		if (tool != nullptr)
		{
			ImGui::Text("	-  %s", tool->GetName().c_str());
		}
	}

	ImGui::Text("    Money reward: %d$", job.GetMoneyRewardAmount());
	ImGui::NewLine();

	if (isButtonPressed)
	{
		AcceptJobEvent acceptJobEvent(jobIndex);
		m_eventDispatcher.DispatchEvent(acceptJobEvent);
	}
}

void JobListTab::DrawJobAttemptedPopup()
{
	ImGui::SetNextWindowSize(POPUP_SIZE);
	if (ImGui::BeginPopupModal(JOB_ATTEMPTED_POPUP_NAME))
	{
		if (m_isLastJobSuccessful)
		{
			ImGui::Text("Job succeeded");
		}
		else
		{
			ImGui::Text("Job failed");
		}

		ImGui::NewLine();
		ImGui::Text("Current tool damage counter: ");
		if (m_toolsUsedForLastJob != nullptr)
		{
			std::map<const Tool*, int> usedTools = *m_toolsUsedForLastJob;
			for (const auto& toolsIterator : usedTools)
			{
				const Tool* usedTool = toolsIterator.first;
				if (usedTool != nullptr)
				{
					ImGui::Text("  - %s x%d", usedTool->GetName().c_str(), toolsIterator.second);
				}
			}
		}
		ImGui::NewLine();
		if (ImGui::Button("Close"))
		{
			ImGui::CloseCurrentPopup();
			m_isShowingJobAttemptedPopup = false;
		}
		ImGui::EndPopup();
	}
}

void JobListTab::OnAcceptJobResultEvent(const Event& genericEvent)
{
	if (genericEvent.GetEventType() == EventType::ACCEPT_JOB_RESULT)
	{
		const JobResultEvent& jobResultEvent = static_cast<const JobResultEvent&>(genericEvent);
		m_isLastJobSuccessful = jobResultEvent.IsJobSuccessful();
		m_toolsUsedForLastJob = &jobResultEvent.GetUsedTools();
		m_isShowingJobAttemptedPopup = true;
		ImGui::OpenPopup(JOB_ATTEMPTED_POPUP_NAME);
	}	
}
