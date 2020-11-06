#include <QCoreApplication>
#include <fileexplorer.h>
#include <supervisor.h>
#include <QObject>
#include <cmd.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    cmd c;
    return a.exec();
}
