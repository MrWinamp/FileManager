#ifndef SUPERVISOR_H
#define SUPERVISOR_H

#include <QObject>
#include <QString>
#include <string>
#include <QFile>
#include <QTimer>
#include <QTime>
#include "iostream"
#include <QTextStream>
#include <conio.h>

class Supervisor : public QObject
{
    Q_OBJECT

    QString _name;
    int _size;
    bool _exists;

public:
    explicit Supervisor(QObject *parent = nullptr);
    Supervisor(QString name, int size, bool exists);
    ~Supervisor();
    QString show();
    QString getName();
    void changeFile(QString name, int size, bool exists);

public slots:
    void update(QString name, int size, bool exists);
};

#endif // SUPERVISOR_H
