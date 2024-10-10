#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QWidget>

#include "NeuroPipelineConfig.h"
#include "Pipeline.h"

namespace np {

	class NeuroPipeline : public QMainWindow {

	private:

		config::NeuroPipelineConfig config;
		np::pipeline::Pipeline pipeline;


	public:
		NeuroPipeline(QWidget* parent = nullptr);

		void Initalize(); // Start
		void Shutdown(); // End


	private:

		void Open();
		void Save();
		void SaveAs();
	protected:
		void closeEvent(QCloseEvent* event) override;

	private:
		QAction* openAct;
		QAction* saveAct;
		QAction* saveAsAct;
		QAction* exitAct;
		void CreateActions();

		QMenu* fileMenu;
		QMenu* helpMenu;
		void CreateMenus();
	};


};