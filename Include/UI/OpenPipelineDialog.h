#ifndef OPENPIPELINEDIALOG_H
#define OPENPIPELINEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QToolButton;
class QTreeWidget;
QT_END_NAMESPACE

namespace Ui {
class OpenPipelineDialog;
}

class OpenPipelineDialog : public QDialog
{
    //Q_OBJECT

public:
    explicit OpenPipelineDialog(QWidget *parent = nullptr);
    ~OpenPipelineDialog();

    std::string filepath = "C:/";
private:
    Ui::OpenPipelineDialog *ui;

    QToolButton* browse_button;
    QDialogButtonBox* button_box;

    void CreateButtons();

    void Browse();
    void OpenFile();
};

#endif // OPENPIPELINEDIALOG_H
