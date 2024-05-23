#pragma once
#include "UI/SavePipelineDialog.h"

#include <QToolButton.h>
#include <QDialogButtonBox.h>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

SavePipelineDialog::SavePipelineDialog(std::shared_ptr<Pipeline> _pipeline,
    std::shared_ptr<NeuroPipelineFilesystem> _filesystem)
{
    pipeline = _pipeline;
    filesystem = _filesystem;

    setWindowTitle("Save Pipeline");
    resize(400, 50);

    prompt_label = new QLabel();
    prompt_label->setText(tr("Do you want to save current Pipeline?"));

    save_button = new QToolButton();
    save_button->setText(tr("Save"));
    connect(save_button, &QAbstractButton::clicked, this, &SavePipelineDialog::Save);

    save_as_button = new QToolButton();
    save_as_button->setText(tr("Save As"));
    connect(save_as_button, &QAbstractButton::clicked, this, &SavePipelineDialog::SaveAs);

    no_save_button = new QToolButton();
    no_save_button->setText(tr("Don't Save"));
    connect(no_save_button, &QAbstractButton::clicked, this, &SavePipelineDialog::DontSave);

    button_box = new QDialogButtonBox();
    button_box->addButton(save_button, QDialogButtonBox::ActionRole);
    button_box->addButton(save_as_button, QDialogButtonBox::ActionRole);
    button_box->addButton(no_save_button, QDialogButtonBox::ActionRole);

    //LAYOUT 
    QHBoxLayout* box_layout = new QHBoxLayout(); //Horizontal
    
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(prompt_label);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(button_box);
    mainLayout->addStretch();
    setLayout(mainLayout);

}

SavePipelineDialog::~SavePipelineDialog()
{
}

void SavePipelineDialog::Save()
{
    filesystem->SavePipeline(pipeline, pipeline->filepath);
    done(SAVE_PIPELINE);
}

void SavePipelineDialog::SaveAs()
{
    filesystem->SavePipelineAs(pipeline);
    done(SAVE_AS_PIPELINE);
}

void SavePipelineDialog::DontSave()
{
    done(DONT_SAVE_PIPELINE);
}

void SavePipelineDialog::Cancel()
{
    done(SAVE_CANCELED);
}
