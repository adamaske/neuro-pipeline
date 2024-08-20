#include <iostream>
#include <memory>


#include <QApplication>

#include "NeuroPipeline.h"
#include <filesystem>
#include <source_location>

int main(int argc, char* argv[]) {

	std::cout << __FILE__ << '\n';
	std::cout << std::source_location::current().file_name() << '\n'; // requires C++20

	return 0;
	QApplication qapp(argc, argv);
	
	np::NeuroPipeline np;
	np.Initalize();


	return qapp.exec();
}