#pragma once

#include <memory>
#include "Files.h"

class NeuroPipeline {
private:
	std::shared_ptr<NeuroPipelineFilesystem> filesystem = nullptr;

	std::shared_ptr<Pipeline> pipeline = nullptr;
public:
	void Initalize();
	void Run();

	void LoadPipeline();

	void LoadExperiment();
	void CreateExperiment();

};