#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Utils/FileTypes.h"
struct File {
	std::string filepath = "";
	std::string filename = "";
	Filetype type = INVALID;
};

struct Directory {
	std::string path = "";
	std::string name = "";
	std::vector<std::shared_ptr<File>> files;
};

struct Experiment {
	std::string path = "";
	std::string name = "";
	std::vector<std::shared_ptr<Directory>> directories;


};

struct Pipeline {
	std::string path = "";
	std::string name = "";

	std::shared_ptr<File> pipe_file;
	std::vector<std::shared_ptr<File>> files;
};

class ExperimentEditor { // : public GUIWindow {
private:
	std::shared_ptr<Experiment> experiment = nullptr;
public:
	ExperimentEditor(std::shared_ptr<Experiment> _experiment);
	int Render();

};
