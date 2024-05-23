#include "UI/MainWindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog.h>

#include <spdlog/spdlog.h>

#include "UI/LoadPipelineDialog.h"
#include "NeuroPipeline.h"

MainWindow::MainWindow(QWidget* parent, NeuroPipeline* np)
    : QMainWindow(parent), neuro_pipeline(np)
    , ui(new Ui::MainWindow)   
{
    ui->setupUi(this);

    setWindowTitle("NeuroPipeline");
    resize(800, 600);

    CreateActions();
    CreateMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    neuro_pipeline->Shutdown();
}

void MainWindow::Open()
{
    neuro_pipeline->PromptLoadPipeline();
}

void MainWindow::Save()
{
    neuro_pipeline->SaveCurrentPipeline();
}

void MainWindow::SaveAs()
{
    neuro_pipeline->SaveCurrentPipelineAs();
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
