#ifndef SAVEPIPELINEDIALOG_H
#define SAVEPIPELINEDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QToolButton;
class QTreeWidget;
class QLineEdit;
QT_END_NAMESPACE

#include <memory>
#include "Pipeline.h"
#include "Files.h"

#define SAVE_AS_PIPELINE 2
#define SAVE_PIPELINE 1
#define DONT_SAVE_PIPELINE 0
#define SAVE_CANCELED -1

class SavePipelineDialog : public QDialog
{
    //Q_OBJECT

public:
    SavePipelineDialog(std::shared_ptr<Pipeline> _pipeline, 
        std::shared_ptr<NeuroPipelineFilesystem> _filesystem);
    ~SavePipelineDialog();

    std::string filepath = "C:/";
    std::shared_ptr<Pipeline> pipeline;
    std::shared_ptr<NeuroPipelineFilesystem> filesystem;
private:

    QToolButton* save_button       = nullptr;
    QToolButton* save_as_button    = nullptr;
    QToolButton* no_save_button = nullptr;
    QDialogButtonBox* button_box   = nullptr;

    QLabel* prompt_label = nullptr;
    
    QLineEdit* fileNameLine = nullptr;

    void Save();
    void SaveAs();
    void DontSave();
    void Cancel();

};

#endif // SAVEPIPELINEDIALOG_H