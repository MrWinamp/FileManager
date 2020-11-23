#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
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

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void in();
    void out();

private slots:
    void handleAddFile();
    void handleAddObserver();
    void handleDelFile();
    void handleDelObserver();
    void handleSubscribe();
    void handleUnsubscribe();
    void updateScreen();

private:
    QTimer *_timer;
    Ui::Widget *ui;
    FileExplorer * _file_explorer;
    QVector<Supervisor *> _supervisors;
};
#endif // WIDGET_H
