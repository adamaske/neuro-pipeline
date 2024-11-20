#pragma once
#include <filesystem>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

#define PROJECT_NAME "NeuroPipeline"

#define PROJECT_VERSION_MAJOR 0
#define PROJECT_VERSION_MINOR 1


#define RESOURCES_PATH "../lib/Resources"
#define CONFIG_PATH "../lib/Resources/neuro_config.np"

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
			auto path = std::filesystem::path(CONFIG_PATH);
			std::ofstream file(path.c_str());

			auto json = EncodeJSON(config);
			file << json.dump();

			file.close();
		}

		inline NeuroPipelineConfig ReadConfig(const std::filesystem::path& path) {
			std::ifstream file(path);

			auto json = nlohmann::json::parse(file);
			auto config = DecodeJSON(json);

			file.close();

			return config;
		}



	}
}

