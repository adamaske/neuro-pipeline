#pragma once

#include <memory>
#include <string>
#include <fstream>

#include <qfiledialog.h>

#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

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

		//Only writes an encoded pipeline to a filepath, doesnt care about anything else
		Pipeline Write(const np::pipeline::Pipeline& pipeline, const std::filesystem::path& path) {
			std::ofstream file(path);

			auto json = np::pipeline::EncodeJSON(pipeline);
			file << json.dump();

			file.close();

			auto pl = DecodeJSON(json); //ReMOVE THIS
			return pl;
		}

		// Only reads at a filepath, decodes pipeline and returns
		Pipeline Read(const std::filesystem::path& path) {
			std::ifstream file(path);
			nlohmann::json json = nlohmann::json::parse(file);
			auto pipeline = np::pipeline::DecodeJSON(json);

			return pipeline;
		}

		// Should check for valid addresses 
		void Save(const np::pipeline::Pipeline& pipeline) {
			auto path = std::filesystem::path(pipeline.filepath);

			//Only allow writing if the filepath is legal
			Write(pipeline, path);
		}

		//
		void SaveAs(const np::pipeline::Pipeline& pipeline) {
			QString filepath = QFileDialog::getSaveFileName(nullptr, "Save Pipeline", pipeline.filepath.c_str());
			Write(pipeline, filepath.toStdString());
		}

		Pipeline Load(const std::filesystem::path& path) {
			Pipeline p = { };
			return p;
		}

		bool IsPipeline(const std::filesystem::path& path) {
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