#pragma once
#include <memory>
#include <string>

#include <nlohmann/json.hpp>

class Pipeline {

public:
	std::string name;
	std::string filepath;

};


inline nlohmann::json PipelineToJSON(std::shared_ptr<Pipeline> pipeline)
{
	nlohmann::json json;
	json["name"] = pipeline->name;

	json["filepath"] = pipeline->filepath;

	return json;
}

inline std::shared_ptr<Pipeline> JSONToPipeline(nlohmann::json json)
{
	std::shared_ptr<Pipeline> pipeline = std::make_shared<Pipeline>();

	pipeline->name = json["name"];
	pipeline->filepath = json["filepath"];

	return pipeline;
}