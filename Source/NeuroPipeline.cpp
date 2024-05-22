#include "NeuroPipeline.h"

#include <iostream>
#include <string>
#include <spdlog/spdlog.h>

#include "Config.h"

#include "UI/MainWindow.h"
#include "UI/OpenPipelineDialog.h"

void NeuroPipeline::Initalize()
{
	spdlog::info("NeuroPipeline " +
		std::to_string(PROJECT_VERSION_MAJOR) + "." +
		std::to_string(PROJECT_VERSION_MINOR));

	spdlog::info("Initalizing...");

	filesystem = std::make_shared<NeuroPipelineFilesystem>();

	LaunchMainWindow();

	//LoadPipeline();
}

void NeuroPipeline::Run() {
	Initalize();

	
}

void NeuroPipeline::Shutdown()
{

	delete main_window;
}

void NeuroPipeline::LoadPipeline()
{
	spdlog::info("Loading Pipeline...");
	OpenPipelineDialog* dialog = new OpenPipelineDialog(main_window);

	int result = dialog->exec();
	spdlog::info("Pipeline file : " + dialog->filepath);

	delete dialog;
}

void NeuroPipeline::LoadExperiment()
{
}

void NeuroPipeline::CreateExperiment()
{

}

void NeuroPipeline::LaunchMainWindow()
{
	main_window = new MainWindow(nullptr, this);
	main_window->show();

	spdlog::info("Main Window Created");
}


