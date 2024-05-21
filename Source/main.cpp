#include <iostream>
#include <memory>
#include "NeuroPipeline.h"

int main(int argc, char** argv) {

	std::shared_ptr<NeuroPipeline> application = std::make_shared<NeuroPipeline>();
	application->Run();

	return 1;
}