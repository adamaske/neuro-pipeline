#include <iostream>
#include <memory>
#include "NeuroPipeline.h"

#include <QApplication>
#include "MainWindow.h"
int main(int argc, char* argv[]) {

	//std::shared_ptr<NeuroPipeline> application = std::make_shared<NeuroPipeline>();
	//application->Run();
	QApplication app(argc, argv);

	MainWindow* main_window = new MainWindow();
	main_window->show();

	
	return app.exec();
}