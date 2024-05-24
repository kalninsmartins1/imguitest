#include "HelpTab.h"
#include "imgui.h"

HelpTab::HelpTab()
{
}

HelpTab::~HelpTab()
{
}

void HelpTab::Draw()
{
	ImGui::Text("Hello Player!");

	ImGui::NewLine();

	ImGui::Text("You are about to lead your own Car Mechanic Garage.");
	ImGui::Text("In order to be successful you should :");
	ImGui::Text("   - keep an eye on your money.");
	ImGui::Text("   - always have a set of Tools in your inventory.");
	ImGui::Text("   - finish Jobs to earn Money which you can spend in the Shop.");
	
	ImGui::NewLine();

	ImGui::Text("Inventory - your amount of Money and your available Tools.");
	ImGui::Text("Jobs - a list of available Jobs.");
	ImGui::Text("Shop - a list of all available Tools and their Price.");
}
