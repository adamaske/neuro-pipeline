#include "UI/MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog.h>

#include <spdlog/spdlog.h>

#include "UI/LoadPipelineDialog.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{

    setWindowTitle("NeuroPipeline");
    resize(800, 600);

    CreateActions();
    CreateMenus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    spdlog::info("Closed");
    //neuro_pipeline->Shutdown();
}

void MainWindow::Open()
{
    spdlog::info("Open");
    //neuro_pipeline->PromptLoadPipeline();
}

void MainWindow::Save()
{
    spdlog::info("Save");
    //neuro_pipeline->SaveCurrentPipeline();
}

void MainWindow::SaveAs()
{
    spdlog::info("Save As");
    //neuro_pipeline->SaveCurrentPipelineAs();
}

void MainWindow::CreateActions()
{
    openAct = new QAction(tr("&Open Pipeline..."), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::Open);

    saveAct = new QAction(tr("&Save..."), this);
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::Save);

    saveAsAct = new QAction(tr("&Save As..."), this);
    saveAsAct->setShortcut(QKeySequence::SaveAs);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::SaveAs);

    exitAct = new QAction(tr("&Exit..."), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::CreateMenus()
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
