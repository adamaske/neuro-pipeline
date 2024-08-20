#pragma once
#include <nlohmann/json.hpp>

#define PROJECT_NAME "NeuroPipeline"

#define PROJECT_VERSION_MAJOR 0
#define PROJECT_VERSION_MINOR 1

#define RESOUCES_DIRECTORY "C:/dev/NeuroPipeline/Resources"

#define NP_CONFIG_FILEPATH "C:/dev/NeuroPipeline/Resources/neuro_config.np"
#include <filesystem>
#include <string>
#include <fstream>

namespace np {
	namespace config {

		struct NeuroPipelineConfig {
			std::string last_pipeline_filepath = "C:/dev/NeuroPipeline/Resources/Experiment_01/test.pipe";

		};

		inline nlohmann::json EncodeJSON(const NeuroPipelineConfig& config)
		{
			nlohmann::json json;

			json["last_pipeline_filepath"] = config.last_pipeline_filepath;

			return json;
		}

		inline NeuroPipelineConfig DecodeJSON(nlohmann::json json)
		{
			NeuroPipelineConfig config;

			config.last_pipeline_filepath = json["last_pipeline_filepath"];

			return config;
		}

		inline void WriteConfig(const NeuroPipelineConfig& config) {
			auto path = std::filesystem::path(NP_CONFIG_FILEPATH);
			std::ofstream file(path.c_str());

			auto json = EncodeJSON(config);
			file << json.dump();

			file.close();
		}

		inline NeuroPipelineConfig ReadConfig(std::string filepath) {
			auto path = std::filesystem::path(NP_CONFIG_FILEPATH);
			std::ifstream file(path.c_str());

			auto json = nlohmann::json::parse(file);

			file.close();

			auto config = DecodeJSON(json);
			return config;
		}

	}
}

