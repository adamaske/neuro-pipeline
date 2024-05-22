#include "UI/MainWindow.h"
#include "ui_MainWindow.h"

#include "UI/OpenPipelineDialog.h"
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

}

void MainWindow::Open()
{
    neuro_pipeline->LoadPipeline();
}

void MainWindow::CreateActions()
{
    openAct = new QAction(tr("&Open Pipeline..."), this);
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::Open);

    exitAct = new QAction(tr("&Exit..."), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void MainWindow::CreateMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    menuBar()->addMenu(fileMenu);
}
