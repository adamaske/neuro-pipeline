#include "UI/OpenPipelineDialog.h"
#include "ui_OpenPipelineDialog.h"

#include <qfiledialog.h>
#include <QPushButton.h>
#include <qboxlayout.h>
#include <qlabel.h>

#include <spdlog/spdlog.h>

#include <QComboBox>
#include <QDialogButtonBox>
#include <QDir>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QRegularExpression>
#include <QToolButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>


OpenPipelineDialog::OpenPipelineDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::OpenPipelineDialog)
{
    ui->setupUi(this);

    setWindowTitle("NeuroPipeline - Open Pipeline");
    
    CreateButtons();

    QHBoxLayout* directoryLayout = new QHBoxLayout();
    directoryLayout->addWidget(browse_button);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(directoryLayout);
    mainLayout->addStretch();
    mainLayout->addWidget(button_box);
    setLayout(mainLayout);
    //QString file_name = QFileDialog::getOpenFileName(this, "Open Pipeline", "C://");

    //Create OK and Close Button
}

OpenPipelineDialog::~OpenPipelineDialog()
{
    delete ui;
}

void OpenPipelineDialog::CreateButtons()
{
    browse_button = new QToolButton();
    browse_button->setText(tr("..."));
    connect(browse_button, &QAbstractButton::clicked, this, &OpenPipelineDialog::Browse);

    button_box = new QDialogButtonBox(QDialogButtonBox::Open | QDialogButtonBox::Close);

    connect(button_box, &QDialogButtonBox::accepted, this, &OpenPipelineDialog::OpenFile);
    connect(button_box, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

void OpenPipelineDialog::Browse()
{
    filepath = QFileDialog::getOpenFileName(this, "Open Pipeline", "C://").toStdString();
}

void OpenPipelineDialog::OpenFile()
{
    
    close();
}

