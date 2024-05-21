#include "Files.h"

#include <iostream>
#include <filesystem>
#include <fstream>

#include <spdlog/spdlog.h>

#include "Utils/FileTypes.h"

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

NeuroPipelineFilesystem::NeuroPipelineFilesystem()
{
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

	return pipeline;
}

void NeuroPipelineFilesystem::SavePipeline(std::shared_ptr<Pipeline> pipeline, const std::string& filepath)
{

	std::ofstream file(filepath);

	auto json = PipelineToJSON(pipeline);
	file << json.dump();

	file.close();

	spdlog::info("Pipeline saved : " + filepath);
}

nlohmann::json NeuroPipelineFilesystem::PipelineToJSON(std::shared_ptr<Pipeline> pipeline)
{
	return nlohmann::json();
}

std::shared_ptr<Pipeline> NeuroPipelineFilesystem::JSONToPipeline(nlohmann::json json)
{
	return std::shared_ptr<Pipeline>();
}


