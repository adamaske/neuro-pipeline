#include <iostream>
#include <memory>


#include <QApplication>

#include "NeuroPipeline.h"
#include <filesystem>
#include <source_location>

//std::cout << std::source_location::current().file_name() << std::endl; // requires C++20
int main(int argc, char* argv[]) {
	QApplication qapp(argc, argv);
	
	np::NeuroPipeline np;
	np.Initalize();


	return qapp.exec();
}