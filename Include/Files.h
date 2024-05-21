#pragma once

#include "Experiment.h"
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>

class NeuroPipelineFilesystem {
private:
	std::vector<std::shared_ptr<File>> files;
	std::vector<std::shared_ptr<Directory>> directories;
	std::vector<std::shared_ptr<Experiment>> experiments;

	std::shared_ptr<Pipeline> pipeline;
public:
	NeuroPipelineFilesystem();
	
	std::shared_ptr<Pipeline> LoadPipeline(const std::string& filepath);
	void SavePipeline(std::shared_ptr<Pipeline> pipeline, const std::string& filepath);

	nlohmann::json PipelineToJSON(std::shared_ptr<Pipeline> pipeline);
	std::shared_ptr<Pipeline> JSONToPipeline(nlohmann::json json);

	void UpdateFilesystem();
	void Print();

	void AppendDirectory(std::shared_ptr<Experiment> experiment, const std::string& folder_path);
	void ParseDirectory(std::shared_ptr<Directory> directory);

	std::shared_ptr<Experiment> CreateExperiment(const std::string& name, const std::string& folder_path);
	void SaveExperiment(std::shared_ptr<Experiment> experiment);
	std::shared_ptr<Experiment> LoadExperiment(const std::string& folder_path);
	void DeleteExperiment(const std::string& expriment_file_path);
	void PrintExperiment(std::shared_ptr<Experiment> experiment);
};