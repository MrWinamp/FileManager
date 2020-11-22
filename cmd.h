#ifndef CMD_H
#define CMD_H

#include <QObject>
#include <QString>
#include <string>
#include <QFile>
#include <QTimer>
#include <QTime>
#include "iostream"
#include <QTextStream>
#include <conio.h>
#include <fileexplorer.h>
#include <supervisor.h>

class cmd : public QObject
{
    Q_OBJECT
    QTimer *_timer;
    FileExplorer * _file_explorer;
    QVector<Supervisor *> _supervisors;

public:
    explicit cmd(QObject *parent = nullptr);
    ~cmd();
    void in();
    void out();

public slots:
    void updateScreen();

};

#endif // CMD_H
