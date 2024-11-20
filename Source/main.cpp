#include <QApplication>
#include "NeuroPipeline.h"

#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
	QApplication qapp(argc, argv);

	np::NeuroPipeline np;
	np.show();

	return qapp.exec();
}