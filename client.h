/****************************************************************************
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include "processdata.h"

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QIcon;
QT_END_NAMESPACE

//! [0]
class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);
    virtual ~Client();
private slots:
    void choose1_handler();
    void choose2_handler();
    void process_handler();


    void enableProcessButton();

private:
    QLabel *fileLable1_;
    QLabel *fileLabel2_;
    QLineEdit *fileEdit1_;
    QLineEdit *fileEdit2_;
    QLabel *statusLabel;
    QPushButton *chooseButton1_;
    QPushButton *chooseButton2_;
    QPushButton * processButton_;

    QIcon       * appIcon_;

    ProcessData processData_;

#ifdef Q_OS_SYMBIAN
    bool isDefaultIapSet;
#endif
};
//! [0]

#endif
