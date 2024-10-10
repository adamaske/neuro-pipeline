#include <QApplication>
#include "NeuroPipeline.h"

int main(int argc, char* argv[]) {
	QApplication qapp(argc, argv);

	np::NeuroPipeline np;
	np.show();

	return qapp.exec();
}