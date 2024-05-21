#include "NeuroPipeline.h"

#include <spdlog/spdlog.h>
#include "Config.h"

#include <iostream>
#include <string>

void NeuroPipeline::Initalize()
{
	spdlog::info("NeuroPipeline " +
		std::to_string(PROJECT_VERSION_MAJOR) + "." +
		std::to_string(PROJECT_VERSION_MINOR));

	filesystem = std::make_shared<NeuroPipelineFilesystem>();

	LoadPipeline();
}

void NeuroPipeline::Run() {
	Initalize();

	if (!pipeline) {
		spdlog::info("No pipeline loaded...");
		return;
	}
	
	//Probe user input 

	//Talk to python server

	//
}

void NeuroPipeline::LoadPipeline()
{
	std::cout << "Enter location of .pipe file :";
	std::string location;
	std::getline(std::cin, location);

	pipeline = filesystem->LoadPipeline(location);
	if (!pipeline) {
		spdlog::error("No .pipe file found...");
		return;
	}
}

void NeuroPipeline::LoadExperiment()
{
}

void NeuroPipeline::CreateExperiment()
{

}


