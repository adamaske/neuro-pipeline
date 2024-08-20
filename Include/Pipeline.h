#pragma once

#include <memory>
#include <string>
#include <fstream>

#include <qfiledialog.h>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <limits>
#include <iostream>
namespace np {
	namespace pipeline {

		class Pipeline {
		private:

		public:
			std::string name;
			std::string filepath;
		};

		inline nlohmann::json EncodeJSON(const Pipeline& pipeline)
		{
			nlohmann::json json;
			json["name"] = pipeline.name;
			json["filepath"] = pipeline.filepath;
			return json;
		}

		inline Pipeline DecodeJSON(nlohmann::json json)
		{
			Pipeline pipeline;
			pipeline.name = json["name"];
			pipeline.filepath = json["filepath"];
			return pipeline;
		}

		// Only reads at a filepath, decodes pipeline and returns
		inline Pipeline Read(const std::filesystem::path& path) {

			std::ifstream file(path);
			nlohmann::json json = nlohmann::json::parse(file);
			auto pipeline = np::pipeline::DecodeJSON(json);

			return pipeline;
		}

		//Only writes an encoded pipeline to a filepath, doesnt care about anything else
		inline Pipeline Write(const np::pipeline::Pipeline& pipeline, const std::filesystem::path& path) {
			std::ofstream file(path);

			auto json = np::pipeline::EncodeJSON(pipeline);
			auto dump = json.dump().c_str();
			
			if (!file.write(dump, sizeof(dump))) {

			}
			file.close();
			return pipeline;
		}

		
		// Should check for valid addresses 
		inline void Save(const np::pipeline::Pipeline& pipeline) {
			auto path = std::filesystem::path(pipeline.filepath);

			//Only allow writing if the filepath is legal
			Write(pipeline, path);
		}

		//
		inline void SaveAs(const np::pipeline::Pipeline& pipeline) {
			QString filepath = QFileDialog::getSaveFileName(nullptr, "Save Pipeline", pipeline.filepath.c_str());
			Write(pipeline, filepath.toStdString());
		}


		inline bool IsPipeline(const std::filesystem::path& path) {
			if (!std::filesystem::exists(path)) {
				spdlog::info("Path does not exist : ", path.generic_string());
				return false;
			}
			if (!std::filesystem::is_regular_file(path)) {
				spdlog::info("Path does not lead to a file : ", path.generic_string());
				return false;
			}
			if (path.extension() != "exe") {
				return false;
			}
			return true;
		}
	}
}