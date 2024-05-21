#include "Files.h"

#include <iostream>
#include <filesystem>
#include <spdlog/spdlog.h>
#include <fstream>


using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

NeuroPipelineFilesystem::NeuroPipelineFilesystem()
{
}

std::shared_ptr<Pipeline> NeuroPipelineFilesystem::LoadPipeline(const std::string& filepath)
{	//File exists and is a .pipe file
	auto entry = std::filesystem::directory_entry(filepath);
	if (!std::filesystem::exists(entry) ) {
		spdlog::error("File does not exist : " + filepath);
		return nullptr;
	}

	if (std::filesystem::is_directory(filepath)) { //Search through files to find .pipe

		for (auto const& entry : std::filesystem::directory_iterator(filepath)) {

			std::string name = entry.path().filename().string();
			std::string suffix = GetSuffix(name);
			Filetype type = SuffixToFiletype(suffix);
			if (type == Filetype::PIPELINE) {
				
				break;
			}
		}


		spdlog::error("File is directory, no PIPELINE file found: " + filepath);
		return nullptr;
	}
	


	std::string name = entry.path().filename().string();
	std::string suffix = GetSuffix(name);
	Filetype type = SuffixToFiletype(suffix);

	if (type == Filetype::PIPELINE) { //File exists and is a .pipe so we can load it

	}
	return std::shared_ptr<Pipeline>();
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

void NeuroPipelineFilesystem::UpdateFilesystem()
{
	for (auto directory : directories) {
		directory->files.clear();
	}
	directories.clear();

	std::shared_ptr<Directory> last;
	for (const auto& directory_entry : recursive_directory_iterator("tesdf")) {
		std::string path = directory_entry.path().string();
		std::string name = directory_entry.path().filename().string();

		if (!std::filesystem::is_directory(path)) {
			continue;
		}

		last = std::make_shared<Directory>();
		last->path = path;
		last->name = name;
		directories.push_back(last);
		
	}
}

void NeuroPipelineFilesystem::Print()
{
	spdlog::info("Filesystem :");

	for (auto experiment : experiments) {
		PrintExperiment(experiment);
	}

}

void NeuroPipelineFilesystem::AppendDirectory(std::shared_ptr<Experiment> experiment, const std::string& folder_path)
{
	if (!std::filesystem::is_directory(folder_path)) {
		spdlog::error("DIRECTORY NOT FOUND : " + folder_path);
		return;
	}

	auto directory_entry = std::filesystem::directory_entry(folder_path);
	
	std::shared_ptr<Directory> directory = std::make_shared<Directory>();
	directory->path = directory_entry.path().string();
	directory->name = directory_entry.path().filename().string();
	
	experiment->directories.push_back(directory);

	spdlog::info("Directory added to  " + experiment->name + " : " + directory->name);
}

void NeuroPipelineFilesystem::ParseDirectory(std::shared_ptr<Directory> directory)
{
	auto path = directory->path;
	//Go thorugh folders and look for experiments
	if (!std::filesystem::is_directory(path)) {
		spdlog::error("DIRECTORY NOT FOUND : " + path);
		return;
	}

	for (const auto& directory_entry : recursive_directory_iterator(path)) {
		
	}
}

std::shared_ptr<Experiment> NeuroPipelineFilesystem::CreateExperiment(const std::string& name, const std::string& folder_path)
{
	std::shared_ptr<Experiment> experiment = std::make_shared<Experiment>();

	if (!std::filesystem::exists(folder_path)) {
		std::filesystem::create_directory(folder_path);
		spdlog::info("Created directory for " + name + ": " + folder_path);
	}

	experiment->name = name;
	experiment->path = folder_path + "/" + name + FiletypeToSuffix(Filetype::EXPERIMENT);

	experiments.push_back(experiment);

	SaveExperiment(experiment);

	return experiment;
}

void NeuroPipelineFilesystem::SaveExperiment(std::shared_ptr<Experiment> experiment)
{
	auto name = experiment->name;
	auto path = experiment->path;

	std::ofstream file;
	if (!std::filesystem::exists(path)) {
		file.open(path);
		if (!file.is_open()) {
			spdlog::error("File not open : " + path);
			return;
		}
	}

	//TODO : JSON IMPLEMENTATION

	file << name << std::endl;
	file << path << std::endl;

	//TODO : Serialize Directory paths

	file.close();

	spdlog::info("Created .expr file : " + experiment->path);
}

std::shared_ptr<Experiment> NeuroPipelineFilesystem::LoadExperiment(const std::string& file_path)
{
	if (!std::filesystem::exists(file_path)) {
		spdlog::error("File does not exist : " + file_path);
		return nullptr;
	}
	if (std::filesystem::is_directory(file_path)) {
		spdlog::error("Filepath is a directory : " + file_path);
		return nullptr;
	}
	
	return nullptr;
}

void NeuroPipelineFilesystem::DeleteExperiment(const std::string& expriment_file_path)
{
	//Is there an expr file here ? 

}

void NeuroPipelineFilesystem::PrintExperiment(std::shared_ptr<Experiment> experiment)
{
	spdlog::info("|- " +experiment->name);

	for (auto dir : experiment->directories) {
		spdlog::info("|---> " + dir->name);
		for (auto file : dir->files) {
			spdlog::info("|------> " + file->filename);
		}
	}

}

