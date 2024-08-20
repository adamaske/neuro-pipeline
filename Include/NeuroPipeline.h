#pragma once
#include <memory>

#include "UI/MainWindow.h"

#include "NeuroPipelineConfig.h"

#include "Pipeline.h"

#include "Robot.h"

namespace np {

	class NeuroPipeline {
	private:
		config::NeuroPipelineConfig config;
		np::pipeline::Pipeline pipeline;

		bool pipeline_loaded = 0;

		MainWindow* main_window = nullptr;

		np::sim::Robot robot;
	public:
		void Initalize(); // Start
		void Run(); // Main loop
		void Shutdown(); // End

		int PromptSavePipeline();
		int PromptLoadPipeline();
	};


};