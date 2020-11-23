#include "fileexplorer.h"

QString FileExplorer::show(int i){
    if(isEmpty())
    {
        return "Is empty";
    }
    else
    {
        QString *text;
        text = new QString;
        QTextStream out(text);
        if(_vec[i]->exists())
        {
            out << "File[" << i << "] exists, name is " << _vec[i]->fileName() << ", size = " << _size[i];
            return *text;
        }
        else
        {
            out << "File[" << i << "] does not exists, name is " << _vec[i]->fileName() << ", size = " << _size[i];
            return *text;
        }
    }
}

bool FileExplorer::isEmpty(){
    if(_vec.size()==0)
        return true;
    return false;
}

void FileExplorer::del()
{
    if(!isEmpty())
    {
        delete _vec[_vec.size()-1];
        _vec.remove(_vec.size()-1);
        _size.remove(_size.size()-1);
        _exists.remove(_exists.size()-1);
    }
}

void FileExplorer::del(int i)
{
    if(!isEmpty())
        if(i >= 0 && i < _vec.size())
        {
            delete _vec[i];
            _vec.remove(i);
            _size.remove(i);
            _exists.remove(i);
        }
}

void FileExplorer::add(QString name){
    for(int i = 0; i < _vec.size(); i++)
        if(_instance->getName(i)==name)
            return;
    QFile * file;
    file = new QFile(name);
    file->open(QFile::WriteOnly | QFile::Text);
    file->close();
    _vec.append(file);
    _size.append(file->size());
    _exists.append(file->exists());
}

FileExplorer::FileExplorer(QObject *parent) : QObject(parent)
{
}

FileExplorer * FileExplorer::_instance = 0;
QTimer * FileExplorer::_timer = 0;

FileExplorer * FileExplorer::Instance()
{
    if(_instance == 0)
    {
        _instance = new FileExplorer;
        _timer = new QTimer(_instance);
        connect(_timer, SIGNAL(timeout()), _instance, SLOT(check()));
        _timer->start(1000);
    }
    return _instance;
}

void FileExplorer::check()
{
    bool flag;
    for(int i = 0; i < _vec.size(); i++)
    {
        flag = true;
        if(_vec[i]->size() != _size[i])
        {
            _size[i] = _vec[i]->size();
            emit changed(_vec[i]->fileName(), _vec[i]->size(), _vec[i]->exists());
            flag = false;
        }
        if(_vec[i]->exists() != _exists[i])
        {
            if(flag)
                emit changed(_vec[i]->fileName(), _vec[i]->size(), _vec[i]->exists());
            _exists[i] = _vec[i]->exists();
        }
    }
}

FileExplorer::~FileExplorer()
{
delete _timer;
delete _instance;
int size =_vec.size();
if(size)
    for(int i = 0; i < size; i++)
        del();
}

int FileExplorer::size()
{
    return _vec.size();
}

QString FileExplorer::getName(int i)
{
    if(!isEmpty())
    {
        if(i >= 0 && i < _vec.size())
        {
            return _vec[i]->fileName();
        }
        else
            return "Invalid index";
    }
    else
            return "Vector is empty";
}

int FileExplorer::getSize(int i)
{
    if(!isEmpty())
    {
        if(i >= 0 && i < _vec.size())
        {
            return _vec[i]->size();
        }
        else
            return -1;
    }
    else
            return -2;
}

bool FileExplorer::getExitsts(int i)
{
    if(!isEmpty())
    {
        if(i >= 0 && i < _vec.size())
        {
            return _vec[i]->exists();
        }
        else
            return false;
    }
    else
            return false;
}

bool FileExplorer::write(int i, QString text)
{
    if(!isEmpty())
    {
        if(i >= 0 && i < _vec.size())
        {
            _vec[i]->open(QFile::WriteOnly | QFile::Text);
            QTextStream out(_vec[i]);
            out << text;
            _vec[i]->flush();
            _vec[i]->close();
            return true;
        }
        else
            return false;
    }
    else
            return false;
}

QString FileExplorer::read(int i)
{
    if(!isEmpty())
    {
        if(i >= 0 && i < _vec.size())
        {
            _vec[i]->open(QIODevice::ReadOnly);
            QTextStream in(_vec[i]);
            QString text;
            system("cls");
            text = in.readLine();
            _vec[i]->close();
            return text;
        }
        else
            return "Invalid index";
    }
    else
            return "Vector is empty";
}
