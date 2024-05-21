#include <iostream>
#include <memory>

#include <QApplication.h>

#include "NeuroPipeline.h"


int main(int argc, char* argv[]) {

	QApplication qapp(argc, argv);

	std::shared_ptr<NeuroPipeline> application = std::make_shared<NeuroPipeline>();
	application->Run();

	
	return qapp.exec();
}