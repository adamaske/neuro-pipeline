#pragma once

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include "Pipeline.h"

class NeuroPipelineFilesystem {
private:

public:
	NeuroPipelineFilesystem();
	
	std::shared_ptr<Pipeline> LoadPipeline(const std::string& filepath);
	void SavePipeline(std::shared_ptr<Pipeline> pipeline, const std::string& filepath);

	nlohmann::json PipelineToJSON(std::shared_ptr<Pipeline> pipeline);
	std::shared_ptr<Pipeline> JSONToPipeline(nlohmann::json json);
};