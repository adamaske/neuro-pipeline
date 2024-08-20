#include "NeuroPipeline.h"

#include <iostream>
#include <string>
#include <QFileDialog.h>
#include <spdlog/spdlog.h>

#include "UI/LoadPipelineDialog.h"
#include "UI/SavePipelineDialog.h"


void np::NeuroPipeline::Initalize() 
{
	spdlog::info("Welcome to NeuroPipeline " +
		std::to_string(PROJECT_VERSION_MAJOR) + "." +
		std::to_string(PROJECT_VERSION_MINOR) + "!");

	config = np::config::ReadConfig(NP_CONFIG_FILEPATH);
	spdlog::info("config loaded : {}", NP_CONFIG_FILEPATH);

	pipeline = np::pipeline::Read(config.last_pipeline_filepath);
	spdlog::info("pipeline loaded : {}", pipeline.filepath);

	spdlog::info("Intialization completed...");

	Run();
}

void np::NeuroPipeline::Run() {
	main_window = new MainWindow();
	main_window->show();

	spdlog::info("main loop...");
}

void np::NeuroPipeline::Shutdown()
{
	config.last_pipeline_filepath = pipeline.filepath;
	np::config::WriteConfig(config);

}

int np::NeuroPipeline::PromptSavePipeline()
{
	SavePipelineDialog* save = new SavePipelineDialog(pipeline);
	int saved = save->exec();

	if (saved == SAVE_CANCELED) {
		return 0;
	}
	
	return 1;
}

int np::NeuroPipeline::PromptLoadPipeline()
{

	//if (pipeline) { //If we already have a pipeline loaded, save current pipeline
	//	int saved = PromptSavePipeline();
	//	if (saved == 0) { //If user cancled save (X button) then we want to cancel loading prompt aswell.
	//		return 0;
	//	}
	//}
	//LoadPipelineDialog* load = new LoadPipelineDialog(nullptr,
	//	pipeline ? pipeline->filepath :
	//	(config.last_pipeline_filepath.size() > 0 ?
	//		config.last_pipeline_filepath : ""));
	//
	//int loaded = load->exec();
	//if (loaded == LOAD_CANCLED) {
	//	return 0;
	//}
	//
	//pipeline = filesystem->LoadPipeline(load->filepath);
	//return 1;
	return 0;
}


