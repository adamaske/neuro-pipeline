#pragma once
#include <memory>

#include "UI/MainWindow.h"

#include "Config.h"

#include "Files.h"
#include "Pipeline.h"



class NeuroPipeline {
private:
	std::shared_ptr<NeuroPipelineFilesystem> filesystem = nullptr;

	std::shared_ptr<NeuroPipelineConfig> config = nullptr;

	std::shared_ptr<Pipeline> pipeline = nullptr;

	MainWindow* main_window = nullptr;
public:
	void Initalize(); // Start
	void Run(); // Main loop
	void Shutdown(); // End

	void LaunchMainWindow();

	int PromptSavePipeline();
	int PromptLoadPipeline();

	void SaveCurrentPipeline();
	void SaveCurrentPipelineAs();

	void SetPipeline(std::shared_ptr<Pipeline> _pipeline);
};