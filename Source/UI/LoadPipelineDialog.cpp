#include "UI/LoadPipelineDialog.h"

#include <QFileDialog.h>
#include <QPushButton.h>
#include <QBoxLayout.h>
#include <Qlabel.h>
#include <QLineEdit.h>
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

#include <spdlog/spdlog.h>
#include <filesystem>

#include "Utils/FileTypes.h"

LoadPipelineDialog::LoadPipelineDialog(QWidget *parent, std::string filepath)
    : QDialog(parent)
{
    setWindowTitle("Load Pipeline");
    resize(500, 100);

    browse_button = new QToolButton();
    browse_button->setText(tr("Browse"));
    connect(browse_button, &QAbstractButton::clicked, this, &LoadPipelineDialog::Browse);

    button_box = new QDialogButtonBox(QDialogButtonBox::Open | QDialogButtonBox::Close);
    connect(button_box, &QDialogButtonBox::accepted, this, &LoadPipelineDialog::OpenFile);
    connect(button_box, &QDialogButtonBox::rejected, this, &LoadPipelineDialog::Cancel);

    headerLabel = new QLabel(tr("Open Pipeline file .pipe"));
    fileNameLabel = new QLabel(tr("Filepath: "));
    fileStatusLabel = new QLabel(tr("No file selected..."));

    fileNameLine = new QLineEdit;
    fileNameLine->setText(tr(filepath.c_str()));
    connect(fileNameLine, &QLineEdit::textEdited, this, &LoadPipelineDialog::Update);


    QHBoxLayout* directoryLayout = new QHBoxLayout(); //Horizontal
    directoryLayout->addWidget(fileNameLabel); // "Filename:"
    directoryLayout->addWidget(fileNameLine);  // "Editable text"
    directoryLayout->addWidget(browse_button); // "Browse"

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(headerLabel);
    mainLayout->addLayout(directoryLayout);
    mainLayout->addWidget(fileStatusLabel);
    mainLayout->addStretch();
    mainLayout->addWidget(button_box);
    setLayout(mainLayout);

    Update();
}

LoadPipelineDialog::~LoadPipelineDialog()
{
}



void LoadPipelineDialog::Update()
{   
    std::string filepath = fileNameLine->text().toStdString();

    if (filepath.size() == 0) {
        fileStatusLabel->setText("");
        return;
    }

    if (!std::filesystem::exists(filepath)) {
        fileStatusLabel->setText("File does not exist...");
        button_box->button(QDialogButtonBox::Open)->setEnabled(false);
        return;
    }

    if (SuffixToFiletype(GetSuffix(filepath)) != Filetype::PIPELINE) {
        fileStatusLabel->setText("Not a .pipe file...");
        button_box->button(QDialogButtonBox::Open)->setEnabled(false);
        return;
    }

    fileStatusLabel->setText("");
    button_box->button(QDialogButtonBox::Open)->setEnabled(true);
    return;
}

void LoadPipelineDialog::Browse()
{
    std::string opening_path = fileNameLine->text().toStdString();
    bool use_preset_path = std::filesystem::exists(opening_path);

    QString filepath = QFileDialog::getOpenFileName(this, 
                                                    "Open Pipeline", 
                                                    use_preset_path ? opening_path.c_str() : "C://");
    if (filepath == "") {
        return;
    }
    fileNameLine->setText(filepath);
    Update();
}


void LoadPipelineDialog::OpenFile()
{
    filepath = fileNameLine->text().toStdString();
    done(LOAD_SUCCESS);
}

void LoadPipelineDialog::Cancel()
{
    done(LOAD_CANCLED);
}

