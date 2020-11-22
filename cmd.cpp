#include "cmd.h"

cmd::cmd(QObject *parent) : QObject(parent)
{
    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(updateScreen()));
    _timer->start(1000);
    _file_explorer = FileExplorer::Instance();
}
cmd::~cmd()
{
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

}

void cmd::in()
{
    if(kbhit()){
        _timer->stop();
        QString command;
        QTextStream cin(stdin);
        cin >> command;
        if(command == "exit")
        {
            cout << "Press Enter to exit" << endl;
            exit(0);
        }
        else if(command == "addf")
        {
            cout << "Enter name of file: ";
            cin >> command;
            _file_explorer->add(command);
        }
        else if(command == "adds")
        {
            cout << "Enter name of file: ";
            cin >> command;
            QFile * file;
            file = new QFile(command);
            Supervisor *supervisor;
            supervisor = new Supervisor(file->fileName(), file->size(), file->exists());
            _supervisors.append(supervisor);
            delete file;
        }
        else if(command == "connect")
        {
            cout << "Enter index supervisor: ";
            cin >> command;
            int i = command.toInt();
            if(i>=0 && i < _supervisors.size() && _supervisors.size() > 0)
                {
                cout << "Enter index file: ";
                cin >> command;
                int j = command.toInt();
                if(j>=0 && j < _file_explorer->size() && !_file_explorer->isEmpty())
                {
                    _supervisors[i]->changeFile(_file_explorer->getName(j), _file_explorer->getSize(j), _file_explorer->getExitsts(j));
                    QObject::connect(_file_explorer, SIGNAL(changed(QString, int, bool)), _supervisors[i], SLOT(update(QString, int, bool)));
                }
                else
                {
                    system("cls");
                    cout << "Invalid index" << endl;
                    cout << "Press Enter to continue : ";
                    getch();
                }
            }
            else
            {
                system("cls");
                cout << "Invalid index" << endl;
                cout << "Press Enter to continue : ";
                getch();
            }
        }
        else if(command == "disconnect")
        {
            cout << "Enter index supervisor: ";
            cin >> command;
            int i = command.toInt();
            if(i>=0 && i < _supervisors.size() && _supervisors.size() > 0)
            {
                QObject::disconnect(_file_explorer, SIGNAL(changed(QString, int, bool)), _supervisors[i], SLOT(update(QString, int, bool)));
            }
            else
            {
                system("cls");
                cout << "Invalid index" << endl;
                cout << "Press Enter to continue : ";
                getch();
            }
        }
        else if(command == "rmall")
        {
            int size =_file_explorer->size();
            if(size)
                for(int i = 0; i < size; i++)
                {
                    _file_explorer->del();
                }
            size = _supervisors.size();
            if(size)
                for(int i = 0; i < size; i++)
                    _supervisors.removeFirst();
        }
        else if(command == "rmf")
        {
            cout << "Enter index: ";
            cin >> command;
            int i = command.toInt();
            if(i>=0 && i < _file_explorer->size() && !_file_explorer->isEmpty())
            {
                _file_explorer->del(i);
            }
            else
            {
                system("cls");
                cout << "Invalid index" << endl;
                cout << "Press Enter to continue : ";
                getch();
            }
        }
        else if(command == "rms")
        {
            cout << "Enter index: ";
            cin >> command;
            int i = command.toInt();
            if(i>=0 && i < _supervisors.size() && _supervisors.size() > 0)
            {
                _supervisors.removeAt(i);
            }
            else
            {
                system("cls");
                cout << "Invalid index" << endl;
                cout << "Press Enter to continue : ";
                getch();
            };
        }
        else if(command == "write")
        {
            cout << "Enter index: ";
            cin >> command;
            int i = command.toInt();
            cout << "Enter text: ";
            if(i>=0 && i < _file_explorer->size() && !_file_explorer->isEmpty())
            {
                QTextStream in(stdin);
                cout << "Enter text: ";
                _file_explorer->write(i, in.readLine());
            }
            else
            {
                system("cls");
                cout << "Invalid index" << endl;
                cout << "Press Enter to continue : ";
                getch();
            }
        }
        else if(command == "read")
        {
            cout << "Enter index: ";
            cin >> command;
            int i = command.toInt();
            if(i>=0 && i < _file_explorer->size() && !_file_explorer->isEmpty())
            {
                QTextStream out(stdout);
                out << _file_explorer->read(i) << endl;
                cout << "Press Enter to continue : ";
                getch();
            }
            else
            {
                system("cls");
                cout << "Invalid index" << endl;
                cout << "Press Enter to continue : ";
                getch();
            }
        }
        else if(command == "help")
        {
            system("cls");
            cout << "Enter addf to add file" << endl;
            cout << "Enter adds to add supervisor" << endl;
            cout << "Enter rmf to remove [i] file" << endl;
            cout << "Enter rms to remove [i] supervisor" << endl;
            cout << "Enter rmall to remove all files and supervisors" << endl;
            cout << "Enter exit to exit from programm" << endl;
            cout << "Enter write to write to [i] file" << endl;
            cout << "Enter read to read [i] file" << endl;
            cout << "Enter connect to connect" << endl;
            cout << "Enter disconnect to disconnect" << endl;
            cout << "Press Enter to continue : ";
            getch();
        }
    }
}

void cmd::out()
{
    system("cls");
    QTextStream out(stdout);
    out << "Supervisors:" << endl;
    if(_supervisors.size())
        for(int i = 0; i < _supervisors.size(); i++)
        {
            out << "[" << i << "] " << _supervisors[i]->show() << endl;
        }
    else
        out << "Supervizor vector is empty";
    out << endl << "Files:" << endl;
    if(!_file_explorer->isEmpty())
        for(int i = 0; i < _file_explorer->size(); i++)
        {
            out <<_file_explorer->show(i) << endl;
        }
    else
        out << "File vector is empty" << endl;
    out << ">> ";
}

void cmd::updateScreen()
{
    in();
    out();
    _timer->start(1000);
}
