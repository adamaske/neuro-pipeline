#pragma once
#include <memory>

#include "Files.h"
#include "UI/MainWindow.h"

class NeuroPipeline {
private:
	std::shared_ptr<NeuroPipelineFilesystem> filesystem = nullptr;

	std::shared_ptr<Pipeline> pipeline = nullptr;

	MainWindow* main_window = nullptr;
public:
	void Initalize();

	void Run();

	void Shutdown();

	void LoadPipeline();

	void LoadExperiment();
	void CreateExperiment();

	void LaunchMainWindow();
};