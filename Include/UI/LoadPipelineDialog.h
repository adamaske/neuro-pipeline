#pragma once
#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QToolButton;
class QTreeWidget;
class QLineEdit;
QT_END_NAMESPACE

#define LOAD_SUCCESS 1
#define LOAD_CANCLED -1

class LoadPipelineDialog : public QDialog
{
    //Q_OBJECT

public:
    explicit LoadPipelineDialog(QWidget *parent = nullptr, std::string filepath = "");
    ~LoadPipelineDialog();

    std::string filepath = "C:/";
private:

    QToolButton* browse_button;
    QDialogButtonBox* button_box;

    QLabel* headerLabel;
    QLabel* fileNameLabel;
    QLabel* fileStatusLabel;

    QLineEdit* fileNameLine;

    void Update();
    void Browse();
    void OpenFile();
    void Cancel();
};

