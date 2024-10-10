#include "NeuroPipeline.h"

#include <iostream>
#include <string>
#include <QFileDialog.h>
#include <spdlog/spdlog.h>

#include "UI/SavePipelineDialog.h"
#include "UI/LoadPipelineDialog.h"

np::NeuroPipeline::NeuroPipeline(QWidget* parent) : QMainWindow(parent)
{
	Initalize();
}

void np::NeuroPipeline::Initalize()
{
	setWindowTitle("NeuroPipeline");
	resize(1200, 800);

	spdlog::info("Welcome to NeuroPipeline " +
		std::to_string(PROJECT_VERSION_MAJOR) + "." +
		std::to_string(PROJECT_VERSION_MINOR) + "!");

// Open Config
	config = np::config::ReadConfig(NP_CONFIG_FILEPATH);
	spdlog::info("config loaded : {}", NP_CONFIG_FILEPATH);

// Open previous Pipeline
	//pipeline = np::pipeline::Read(config.last_pipeline_filepath);
	//spdlog::info("pipeline loaded : {}", pipeline.filepath);

	CreateActions();
	CreateMenus();

	spdlog::info("Intialization completed...");
}


void np::NeuroPipeline::Shutdown()
{
	config.last_pipeline_filepath = pipeline.filepath;
	np::config::WriteConfig(config);

	spdlog::info("Shutdown...");
}

void np::NeuroPipeline::Open()
{
	spdlog::info("Open");

	bool pl = np::pipeline::ValidPipeline(pipeline);
	if (pl) { // Save prior to opening a new one
		auto saveDialog = new SavePipelineDialog(pipeline);
		int saved = saveDialog->exec();
		if (saved == SAVE_CANCELED) { // If this was cancled, dont open a new either
			spdlog::info("Open Pipeline Canceled...");
			return;
		}
	}

	LoadPipelineDialog* load = new LoadPipelineDialog(nullptr,
		pl ? pipeline.filepath :
		(	config.last_pipeline_filepath.size() > 0 ?
				config.last_pipeline_filepath : ""));
	
	int loaded = load->exec();
	if (loaded == LOAD_CANCLED) {
		return;
	}
	
	pipeline = np::pipeline::Read(load->filepath);

}

void np::NeuroPipeline::Save()
{
	spdlog::info("Save");
	//SavePipelineDialog* save = new SavePipelineDialog(pipeline);
	//int saved = save->exec();
	//
	//if (saved == SAVE_CANCELED) {
	//	return;
	//}
	//
	//return;
}

void np::NeuroPipeline::SaveAs()
{
	spdlog::info("Save As");

}

void np::NeuroPipeline::closeEvent(QCloseEvent* event)
{
	Shutdown();
}


void np::NeuroPipeline::CreateActions()
{
	openAct = new QAction(tr("&Open Pipeline..."), this);
	openAct->setShortcut(QKeySequence::Open);
	connect(openAct, &QAction::triggered, this, &NeuroPipeline::Open);

	saveAct = new QAction(tr("&Save..."), this);
	saveAct->setShortcut(QKeySequence::Save);
	connect(saveAct, &QAction::triggered, this, &NeuroPipeline::Save);

	saveAsAct = new QAction(tr("&Save As..."), this);
	saveAsAct->setShortcut(QKeySequence::SaveAs);
	connect(saveAsAct, &QAction::triggered, this, &NeuroPipeline::SaveAs);

	exitAct = new QAction(tr("&Exit..."), this);
	exitAct->setShortcuts(QKeySequence::Quit);
	connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void np::NeuroPipeline::CreateMenus()
{
	fileMenu = new QMenu(tr("&File"), this);
	fileMenu->addAction(openAct);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAct);
	fileMenu->addSeparator();
	fileMenu->addAction(saveAsAct);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAct);

	menuBar()->addMenu(fileMenu);
}
