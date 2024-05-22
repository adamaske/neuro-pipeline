#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAction>
#include <QApplication>
#include <QLibraryInfo>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE

class Assistant;
class TextEdit;
class NeuroPipeline;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    //Q_OBJECT

private:
    Ui::MainWindow *ui;

    NeuroPipeline* neuro_pipeline = nullptr;

    QMenu* fileMenu;
    QMenu* helpMenu;
public:
    explicit MainWindow(QWidget *parent = nullptr, NeuroPipeline* np = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent* event) override;

private:
    void Open();

    void CreateActions();
    void CreateMenus();

//Actions
    QAction* assistantAct;
    QAction* clearAct;
    QAction* openAct;
    QAction* exitAct;
    QAction* aboutAct;
    QAction* aboutQtAct; 

};

#endif // MAINWINDOW_H
