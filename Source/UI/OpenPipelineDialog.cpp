#include "UI/OpenPipelineDialog.h"
#include "ui_OpenPipelineDialog.h"

#include <QPushButton.h>
OpenPipelineDialog::OpenPipelineDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OpenPipelineDialog)
{
    ui->setupUi(this);
}

OpenPipelineDialog::~OpenPipelineDialog()
{
    delete ui;
}

