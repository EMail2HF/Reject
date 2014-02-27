/****************************************************************************
**
**
****************************************************************************/

#include <QApplication>
#include "client.h"
#include <iostream>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Client client;
	
    client.show();

    return client.exec();
    //return app.exec();
}
