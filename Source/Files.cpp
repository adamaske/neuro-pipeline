#include "Files.h"

#include <iostream>
#include <filesystem>
#include <fstream>
#include <QFileDialog.h>
#include <spdlog/spdlog.h>

#include "Utils/FileTypes.h"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

NeuroPipelineFilesystem::NeuroPipelineFilesystem()
{
}

void NeuroPipelineFilesystem::SavePipeline(std::shared_ptr<Pipeline> pipeline, const std::string& filepath)
{
	std::ofstream file(filepath);

	pipeline->filepath = filepath;
	auto json = PipelineToJSON(pipeline);
	file << json.dump();
	file.close();

	spdlog::info("Pipeline saved : " + filepath);
}

void NeuroPipelineFilesystem::SavePipelineAs(std::shared_ptr<Pipeline> pipeline)
{
	QString filepath = QFileDialog::getSaveFileName(nullptr, "Save Pipeline", pipeline->filepath.c_str());
	SavePipeline(pipeline, filepath.toStdString());
}

std::shared_ptr<Pipeline> NeuroPipelineFilesystem::LoadPipeline(const std::string& filepath)
{	//File exists and is a .pipe file
	auto entry = std::filesystem::directory_entry(filepath);
	if (!std::filesystem::exists(entry)) {
		spdlog::error("File does not exist : " + filepath);
		return nullptr;
	}
	if (std::filesystem::is_directory(entry)) {
		spdlog::error("Is directory : " + filepath);
		return nullptr;
	}

	std::string name = entry.path().filename().string();
	std::string suffix = GetSuffix(name);
	Filetype type = SuffixToFiletype(suffix);

	if (type != Filetype::PIPELINE) { //File exists and is a .pipe so we can load it
		spdlog::error("Not a PIPELINE file : " + FiletypeToString(type));
		return nullptr;
	}

	std::ifstream file(filepath);
	nlohmann::json json = nlohmann::json::parse(file);
	std::shared_ptr<Pipeline> pipeline = JSONToPipeline(json);
	pipeline->filepath = filepath;

	return pipeline;
}



void NeuroPipelineFilesystem::SaveConfigFile(std::shared_ptr<NeuroPipelineConfig> config, const std::string& filepath)
{
	spdlog::info("Saving Config...");

	std::ofstream file(filepath);

	auto json = ConfigToJSON(config);
	file << json.dump();

	file.close();

}

std::shared_ptr<NeuroPipelineConfig> NeuroPipelineFilesystem::LoadConfigFile(const std::string& filepath)
{
	spdlog::info("Loading Config...");

	std::ifstream file(filepath);

	auto json = nlohmann::json::parse(file);

	std::shared_ptr<NeuroPipelineConfig> config = JSONToConfig(json);

	return config;
}

nlohmann::json NeuroPipelineFilesystem::ConfigToJSON(std::shared_ptr<NeuroPipelineConfig> config)
{
	nlohmann::json json;

	json["last_pipeline_filepath"] = config->last_pipeline_filepath;

	return json;
}

std::shared_ptr<NeuroPipelineConfig> NeuroPipelineFilesystem::JSONToConfig(nlohmann::json json)
{
	std::shared_ptr<NeuroPipelineConfig> config = std::make_shared<NeuroPipelineConfig>();

	config->last_pipeline_filepath = json["last_pipeline_filepath"];

	return config;
}


