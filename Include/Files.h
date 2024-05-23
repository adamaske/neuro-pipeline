#pragma once

#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

#include "Pipeline.h"

#include "Config.h"


class NeuroPipelineFilesystem {
private:

public:
	NeuroPipelineFilesystem();

	void SavePipeline(std::shared_ptr<Pipeline> pipeline, const std::string& filepath);
	void SavePipelineAs(std::shared_ptr<Pipeline> pipeline);
	std::shared_ptr<Pipeline> LoadPipeline(const std::string& filepath);

	void SaveConfigFile(std::shared_ptr<NeuroPipelineConfig> config, const std::string& filepath);
	std::shared_ptr<NeuroPipelineConfig> LoadConfigFile(const std::string& filepath);

	nlohmann::json ConfigToJSON(std::shared_ptr<NeuroPipelineConfig> config);
	std::shared_ptr<NeuroPipelineConfig> JSONToConfig(nlohmann::json json);
};