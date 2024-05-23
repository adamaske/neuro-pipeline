#include "NeuroPipeline.h"

#include <iostream>
#include <string>
#include <QFileDialog.h>
#include <spdlog/spdlog.h>

#include "UI/LoadPipelineDialog.h"
#include "UI/SavePipelineDialog.h"

#define NP_CONFIG_FILEPATH "C:/dev/NeuroPipeline/Resources/neuro_config.np"

void NeuroPipeline::Initalize()
{
	spdlog::info("NeuroPipeline " +
		std::to_string(PROJECT_VERSION_MAJOR) + "." +
		std::to_string(PROJECT_VERSION_MINOR));

	filesystem = std::make_shared<NeuroPipelineFilesystem>();
	config = filesystem->LoadConfigFile(NP_CONFIG_FILEPATH);
	
	int loaded = PromptLoadPipeline();
	if (!loaded) {
		spdlog::error("No Pipeline loaded... Exiting...");
		return;
	}

	LaunchMainWindow();

	Run();
}

void NeuroPipeline::Run() {

	spdlog::info("Main Loop");
	
}

void NeuroPipeline::Shutdown()
{
	if (config && pipeline) {
		config->last_pipeline_filepath = pipeline->filepath;
	}

	filesystem->SaveConfigFile(config, NP_CONFIG_FILEPATH);

	delete main_window;

	spdlog::info("Closed");
}

void NeuroPipeline::LaunchMainWindow()
{
	main_window = new MainWindow(nullptr, this);
	main_window->show();
}
int NeuroPipeline::PromptSavePipeline()
{
	SavePipelineDialog* save = new SavePipelineDialog(pipeline, filesystem);
	int saved = save->exec();

	if (saved == SAVE_CANCELED) {
		return 0;
	}
	
	return 1;
}

int NeuroPipeline::PromptLoadPipeline()
{
	if (pipeline) { //If we already have a pipeline loaded, save current pipeline
		int saved = PromptSavePipeline();
		if (saved == 0) { //If user cancled save (X button) then we want to cancel loading prompt aswell.
			return 0;
		}
	}
	LoadPipelineDialog* load = new LoadPipelineDialog(nullptr,
		pipeline ? pipeline->filepath :
		(config ? config->last_pipeline_filepath : ""));

	int loaded = load->exec();
	if (loaded == LOAD_CANCLED) {
		return 0;
	}

	pipeline = filesystem->LoadPipeline(load->filepath);
	return 1;
}


void NeuroPipeline::SaveCurrentPipeline()
{
	filesystem->SavePipeline(pipeline, pipeline->filepath);
}

void NeuroPipeline::SaveCurrentPipelineAs()
{
	filesystem->SavePipelineAs(pipeline);
}

void NeuroPipeline::SetPipeline(std::shared_ptr<Pipeline> _pipeline)
{
	pipeline = _pipeline;
}


