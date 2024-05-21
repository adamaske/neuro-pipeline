#ifndef OPENPIPELINEDIALOG_H
#define OPENPIPELINEDIALOG_H

#include <QDialog>

namespace Ui {
class OpenPipelineDialog;
}

class OpenPipelineDialog : public QDialog
{
    //Q_OBJECT

public:
    explicit OpenPipelineDialog(QWidget *parent = nullptr);
    ~OpenPipelineDialog();

private:
    Ui::OpenPipelineDialog *ui;
};

#endif // OPENPIPELINEDIALOG_H
