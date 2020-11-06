#include "supervisor.h"

void Supervisor::update(QString name, int size, bool exists)
{
    if(_name == name)
    {
        if(exists)
            _exists = true;
        else
            {
                _exists = false;
                _size = 0;
                return;
            }
        _size = size;
    }
}

void Supervisor::changeFile(QString name, int size, bool exists)
{
    _name = name;
    _size = size;
    _exists = exists;
}

Supervisor::Supervisor(QObject *parent) : QObject(parent)
{

}

Supervisor::Supervisor(QString name, int size, bool exists)
{
    _name = name;
    _size = size;
    _exists = exists;
}

QString Supervisor::show()
{
    QString text;
    QTextStream out(&text);
    if(_exists)
    {
        out << "File exists, name is " << _name << ", size = " << _size;
        return text;
    }
    else
    {
        out << "File does not exists, name is " << _name << ", size = " << _size;
        return text;
    }
}

Supervisor::~Supervisor()
{

}
