#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QObject>
#include <QString>
#include <string>
#include <QFile>
#include <QTimer>
#include <QTime>
#include "iostream"
#include <QTextStream>
#include <conio.h>

using namespace std;

class FileExplorer : public QObject
{
    Q_OBJECT

    QVector<QFile *> _vec;
    QVector<int> _size;
    QVector<bool> _exists;
    QTimer * _timer;

public:
    explicit FileExplorer(QObject *parent = nullptr);
    ~FileExplorer();
    void add(QString name);
    void del();
    void del(int i);
    bool isEmpty();
    QString show(int i);
    int size();
    QString getName(int i);
    int getSize(int i);
    bool getExitsts(int i);
    bool write(int i, QString text);
    QString read(int i);
signals:
    void changed(QString name, int size, bool exists);

public slots:
    void check();
};

#endif // FILEEXPLORER_H
