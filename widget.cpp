#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    _file_explorer = FileExplorer::Instance();
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateScreen()));
    _timer->start(1000);

    connect(ui->addFile,SIGNAL(clicked()),this,SLOT(handleAddFile()));
    connect(ui->lineEdit,SIGNAL(returnPressed()),this,SLOT(handleAddFile()));

    connect(ui->addObserver,SIGNAL(clicked()),this,SLOT(handleAddObserver()));
    connect(ui->lineEdit_2,SIGNAL(returnPressed()),this,SLOT(handleAddObserver()));

    connect(ui->delFile,SIGNAL(clicked()),this,SLOT(handleDelFile()));
    connect(ui->lineEdit_3,SIGNAL(returnPressed()),this,SLOT(handleDelFile()));

    connect(ui->delObserver,SIGNAL(clicked()),this,SLOT(handleDelObserver()));
    connect(ui->lineEdit_5,SIGNAL(returnPressed()),this,SLOT(handleDelObserver()));

    connect(ui->subscribe,SIGNAL(clicked()),this,SLOT(handleSubscribe()));
    connect(ui->lineEdit_7,SIGNAL(returnPressed()),this,SLOT(handleSubscribe()));
    connect(ui->lineEdit_8,SIGNAL(returnPressed()),this,SLOT(handleSubscribe()));

    connect(ui->Unsubscribe,SIGNAL(clicked()),this,SLOT(handleUnsubscribe()));
    connect(ui->lineEdit_10,SIGNAL(returnPressed()),this,SLOT(handleUnsubscribe()));
}

Widget::~Widget()
{
    delete ui;
    delete _timer;
    int size =_file_explorer->size();

    if(size)
        for(int i = 0; i < size; i++)
        {
            _file_explorer->del();
        }

    size = _supervisors.size();
    if(size)
        for(int i = 0; i < size; i++)
        {
            delete _supervisors[0];
            _supervisors.removeFirst();
        }
    //_file_explorer->delInstance();
}

void Widget::updateScreen()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
    if(!_file_explorer->isEmpty())
        for(int i = 0; i < _file_explorer->size(); i++)
        {
            ui->listWidget->addItem(_file_explorer->show(i));
        }
    else
        ui->listWidget->addItem("File vector is empty");
    if(_supervisors.size())
        for(int i = 0; i < _supervisors.size(); i++)
        {
            QString s;
            s.append("[").append(QString::number(i)).append("] ").append(_supervisors[i]->show());
            ui->listWidget_2->addItem(s);
        }
    else
        ui->listWidget_2->addItem("Supervizor vector is empty");
    ui->listWidget->addItem(QString::number(_file_explorer->size()));
    //_file_explorer->check();
}

void Widget::handleAddFile()
{
    _file_explorer->add(ui->lineEdit->text());
}

void Widget::handleAddObserver()
{
    for(int i = 0; i < _supervisors.size(); i++)
        if(_supervisors[i]->getName()==ui->lineEdit_2->text())
            return;
    QFile * file;
    file = new QFile(ui->lineEdit_2->text());
    Supervisor * supervisor;
    supervisor = new Supervisor(file->fileName(), file->size(), file->exists());
    _supervisors.append(supervisor);
    delete file;
}

void Widget::handleSubscribe()
{
    int j = ui->lineEdit_7->text().toInt();
    int i = ui->lineEdit_8->text().toInt();
    if(i>=0 && i < _supervisors.size() && _supervisors.size() > 0)
        if(j>=0 && j < _file_explorer->size() && !_file_explorer->isEmpty())
        {
            _supervisors[i]->changeFile(_file_explorer->getName(j), _file_explorer->getSize(j), _file_explorer->getExitsts(j));
            QObject::connect(_file_explorer, SIGNAL(changed(QString, int, bool)), _supervisors[i], SLOT(update(QString, int, bool)));
        }
}

void Widget::handleUnsubscribe()
{
    int i = ui->lineEdit_10->text().toInt();
    if(i>=0 && i < _supervisors.size() && _supervisors.size() > 0)
    {
        QObject::disconnect(_file_explorer, SIGNAL(changed(QString, int, bool)), _supervisors[i], SLOT(update(QString, int, bool)));
    }
}

void Widget::handleDelObserver()
{
    int i = ui->lineEdit_5->text().toInt();
    if(i>=0 && i < _supervisors.size() && _supervisors.size() > 0)
    {
        _supervisors.removeAt(i);
    }
}

void Widget::handleDelFile()
{
    int i = ui->lineEdit_3->text().toInt();
    if(i>=0 && i < _file_explorer->size() && !_file_explorer->isEmpty())
    {
        _file_explorer->del(i);
    }
}
