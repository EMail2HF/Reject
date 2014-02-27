/****************************************************************************
**
**
****************************************************************************/

#include <QtGui>
#include <string>
#include <iostream>
#include "client.h"



//! [0]
Client::Client(QWidget *parent)
    : QDialog(parent)
{
//! [0]
    fileLable1_ = new QLabel(tr("File&1:"));
    fileLabel2_ = new QLabel(tr("File&2:"));


    fileEdit1_ = new QLineEdit;
    fileEdit2_ = new QLineEdit;
    //fileEdit2_->setValidator(new QIntValidator(1, 65535, this));

    fileLable1_->setBuddy(fileEdit1_);
    fileLabel2_->setBuddy(fileEdit2_);


    chooseButton1_ = new QPushButton(tr("&Choose"));
    chooseButton1_->setDefault(true);
   // chooseButton1_->setEnabled(false);

    chooseButton2_ = new QPushButton(tr("C&hoose"));

    processButton_ = new QPushButton(tr("&Process"));
    processButton_->setEnabled(false);
    processButton_->setToolTip(QString("click to Reject Duplicates"));



    connect(fileEdit1_, SIGNAL(textChanged(QString)),
            this, SLOT(enableProcessButton()));
    connect(fileEdit2_, SIGNAL(textChanged(QString)),
            this, SLOT(enableProcessButton()));
    connect(chooseButton1_, SIGNAL(clicked()),
            this, SLOT(choose1_handler()));
    connect(chooseButton2_, SIGNAL(clicked()), this, SLOT(choose2_handler()));
     connect(processButton_, SIGNAL(clicked()), this, SLOT(process_handler()));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(fileLable1_, 0, 0);
    mainLayout->addWidget(fileEdit1_, 0, 1);
     mainLayout->addWidget(chooseButton1_, 0, 2);

    mainLayout->addWidget(fileLabel2_, 1, 0);
    mainLayout->addWidget(fileEdit2_, 1, 1);
    mainLayout->addWidget(chooseButton2_, 1, 2);
    mainLayout->addWidget(processButton_, 2, 2);

    setLayout(mainLayout);

    setWindowTitle(tr("Reject Duplicates"));

    resize(QSize(500,100));

    fileEdit1_->setFocus();

    QIcon icon(QString("res/qt.png"));

    setWindowIcon(icon);

#ifdef Q_OS_SYMBIAN
    isDefaultIapSet = false;
#endif
//! [5]
}
Client::~Client()
{
}
void Client::choose1_handler()
{
    QFileDialog dialog(this);
     dialog.setFileMode(QFileDialog::AnyFile);
    QStringList fileNames;
    if (dialog.exec())
    {
        fileNames = dialog.selectedFiles();
        QString filepath = dialog.directory().absolutePath();
        std::cout<<"filepath ="<<filepath.toStdString()<<std::endl;
    }
    if(fileNames.size())
    {
        QString fileName =fileNames[0];
        fileEdit1_->setText(fileName);

    }

}
void Client::choose2_handler()
{
    QFileDialog dialog(this);
     dialog.setFileMode(QFileDialog::AnyFile);
    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();

    if(fileNames.size())
    {
        QString fileName =fileNames[0];
        fileEdit2_->setText(fileName);
    }
}

void Client::process_handler()
{
    processButton_->setEnabled(false);
    chooseButton1_->setEnabled(false);
    chooseButton2_->setEnabled(false);

    std::string filename1 = fileEdit1_->text().toStdString();

    std::string filename2 = fileEdit2_->text().toStdString();

   
    processData_.DataProcess(filename1.c_str(),filename2.c_str());

    chooseButton1_->setEnabled(true);
    chooseButton2_->setEnabled(true);
    processButton_->setEnabled(true);
}




void Client::enableProcessButton()
{
    processButton_->setEnabled(!fileEdit1_->text().isEmpty()
                                 && !fileEdit2_->text().isEmpty());
}
