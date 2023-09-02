#include <iostream>
#include <iomanip>
#include "../include/UI.h"
#include "../include/MenuPrinter.h"
#include "../include/Database.h"

using std::cout;
using std::cin;

extern Database db;


bool isPosNum(const std::string& str)
{
    if (str.empty())
        return false;

    for (auto chr : str)
        if (!isdigit(chr))
            return false;
    
    return true;
}

void printMsg(const std::string& msg)
{
    cout << msg;
    while (!getchar());
}

void printHeader()
{
    cout << std::setw(10) << "Имя" << std::setw(10) << "X" << std::setw(10) << "Y" << std::setw(15) << "Тип" << std::setw(20) << "Время создания" << "\n\n";
}

void printObjF(const Object& obj)
{
    cout << std::setw(10) << obj._name << std::setw(10) << obj._x << std::setw(10) << obj._y << std::setw(15) << obj._type << std::setw(20) << obj._time << '\n';
}

bool openDB()
{
    std::string fileName;

    CLS;
    cout << "Введите имя файла: ";
    std::getline(cin, fileName);

    return db.open(fileName);
}

void addObject(Object& obj)
{
    std::string buf;

    bool isGood = true;
    do {
        CLS;
        cout << "Введите имя объекта: ";
        std::getline(cin, obj._name);
        isGood = checkString(obj._name);
        if (!isGood)
            printMsg("Должны отсутствовать пробелы...\n");
    } while (!isGood);

    do {
        CLS;
        cout << "Введите координату X: ";
        std::getline(cin, buf);
        isGood = checkIfFloat(buf);
        if (!isGood)
            printMsg("Некорректный ввод...\n");
    } while (!isGood);
    obj._x = std::atof(buf.c_str());

    do {
        CLS;
        cout << "Введите координату Y: ";
        std::getline(cin, buf);
        isGood = checkIfFloat(buf);
        if (!isGood)
            printMsg("Некорректный ввод...\n");
    } while (!isGood);
    obj._y = std::atof(buf.c_str());

    do {
        CLS;
        cout << "Введите тип объекта: ";
        std::getline(cin, obj._type);
        isGood = checkString(obj._type);
        if (!isGood)
            printMsg("Должны отсутствовать пробелы...\n");
    } while (!isGood);
}

void printTrailer(bool isEmpty)
{
    if (!isEmpty)
        printMsg("\n\nКонец...");
    else
        printMsg("\n\nНе найдено ни одного объекта...");
}

void printObjects(Database& db)
{
    auto& list = db.getObjectList();

    printHeader();
    for (auto& obj : list)
    {
        printObjF(obj);
    }

    printTrailer(list.empty());
}

void printSet(const ObjectGroup &list)
{
    printHeader();

    for (auto& obj : list)
    {
        printObjF(*obj);
    }

    printTrailer(list.empty());
}

void printGrouppedByDistance(Database& db, double d)
{
    const auto list = db.groupByDistance(d);

    for (auto& pair : list)
    {
        cout << std::setw(9) << pair.first << " : ";
        printObjF(*pair.second);
    }

    printTrailer(list.empty());
}

void printGrouppedByName(Database& db, const std::regex& regex)
{
    const auto list = db.groupByName(regex);
    printSet(list);
}

void printGrouppedByTime(Database& db, time_t t2, time_t t1 = 0)
{
    const auto list = db.groupByTime(t2, t1);
    printSet(list);
}

void printGrouppedByType(Database& db, const std::string& type)
{
    const auto list = db.groupByType(type);
    printSet(list);
}



void useMenu(void (*drawMenuFunc)(), int (*inputHandlerFunc)(int choice))
{
    std::string str;
    int _choice = 0;

    while (true)
    {
        drawMenuFunc();
        std::getline(cin, str);

        if (!isPosNum(str))
        {
            printMsg("Некорректный ввод...\n");
        }
        else
        {
            _choice = atoi(str.c_str());
            if (inputHandlerFunc(_choice) < 0)
                return;
        }
    }
}

int menuInputHandler(int choice)
{
    switch (choice)
    {
    case (int)MainMenu::OpenFile:
        if (!openDB())
        {
            printMsg("Невозможно открыть такой файл...\n");
        }
        else
        {
            useMenu(drawDbMenu, dbMenuInputHandler);
        }
        break;

    case (int)MainMenu::Exit:
        return -1;

    default:
        printMsg("Выберете действие из списка...\n");
        break;
    }

    return 0;
}

int distanceSortMenuInputHandler(int choice)
{
    CLS;
    switch (choice)
    {
    case (int)DistanceSortMenu::_100:
        printGrouppedByDistance(db, 100);
        break;
    
    case (int)DistanceSortMenu::_1000:
        printGrouppedByDistance(db, 1000);
        break;

    case (int)DistanceSortMenu::_10000:
        printGrouppedByDistance(db, 10000);
        break;

    case (int)DistanceSortMenu::_FAR:
        printGrouppedByDistance(db, 1000000.);
        break;

    case (int)DistanceSortMenu::_Exit:
        return -1;

    default:
        printMsg("Выберете действие из списка...\n");
        break;
    }

    return 0;
}

int nameSortMenuInputHandler(int choice)
{
    switch (choice)
    {
    case (int)NameSortMenu::Any:
    {
        std::string input;

        do {
            CLS;
            cout << "Укажите символ для группировки: ";
            std::getline(cin, input);
        } while (input.length() != 1);
        
        CLS;
        std::regex regex(std::string("^") + toUpper(input[0]));
        printGrouppedByName(db, regex);
        break;
    }

    case (int)NameSortMenu::Other:
    {
        CLS;
        std::regex regex("^[^А-Яа-я]");
        printGrouppedByName(db, regex);
        break;
    }

    case (int)NameSortMenu::Exit:
        return -1;

    default:
        printMsg("Выберете действие из списка...\n");
        break;
    }

    return 0;
}

int timeSortMenuInputHandler(int choice)
{
    constexpr size_t day = 60 * 60 * 24; 
    CLS;

    switch (choice)
    {
    case (int)TimeSortMenu::Today:
        printGrouppedByTime(db, day);
        break;

    case (int)TimeSortMenu::Yesterday:
        printGrouppedByTime(db, day * 2, day);
        break;

    case (int)TimeSortMenu::Week:
        printGrouppedByTime(db, day * 7);
        break;

    case (int)TimeSortMenu::Month:
        printGrouppedByTime(db, day * 30);
        break;

    case (int)TimeSortMenu::Year:
        printGrouppedByTime(db, day * 365);
        break;

    case (int)TimeSortMenu::Earlier:
        printGrouppedByTime(db, time(0), day * 365);
        break;

    case (int)TimeSortMenu::Exit:
        return -1;

    default:
        printMsg("Выберете действие из списка...\n");
        break;
    }

    return 0;
}

int typeSortMenuInputHandler(int choice)
{
    std::string input;

    switch (choice)
    {
    case (int)TypeSortMenu::Any:
    {
        do {
            CLS;
            cout << "Укажите тип для группировки: ";
            std::getline(cin, input);
        } while (!input.length());
        
        CLS;
        printGrouppedByType(db, input);
        break;
    }

    case (int)TypeSortMenu::Other:
    {
        do {
            CLS;
            cout << "Укажите максимальное число объектов каждого типа: ";
            std::getline(cin, input);
        } while (!isPosNum(input));
        
        CLS;
        printSet(db.groupByTypeNotMoreN(std::atoi(input.c_str())));
        break;
    }

    case (int)TypeSortMenu::Exit:
        return -1;

    default:
        printMsg("Выберете действие из списка...\n");
        break;
    }

    return 0;
}

int dbMenuInputHandler(int choice)
{
    switch (choice)
    {
    case (int)DbMenu::ReadFile:
    {
        CLS;
        printObjects(db);
        break;
    }

    case (int)DbMenu::AddObject:
    {
        Object obj;
        addObject(obj);
        if (!db.addObject(obj))
        {
            printMsg("Ошибка добавления объекта в файл...");
            return -1;
        }
        printMsg("Объект успешно добавлен...");
        break;
    }

    case (int)DbMenu::DelObject:
    {
        std::string input;
        CLS;
        cout << "Укажите имя объекта для удаления: ";
        std::getline(cin, input);
        cout << "\nБыло удалено объектов: " << db.removeObjectByName(input) << "\n\n";
        printMsg("Нажмите любую клавишу...");
        break;
    }

    case (int)DbMenu::GroupBy:
        useMenu(drawGroupByMenu, groupByMenuHandler);
        break;

    case (int)DbMenu::SaveToFile:
        CLS;
        if (db.save())
            printMsg("Файл успешно сохранен...");
        else
            printMsg("Ошибка сохранения файла...");
        break;

    case (int)DbMenu::Exit:
        return -1;

    default:
        printMsg("Выберете действие из списка...\n");
        break;
    }

    return 0;
}

int groupByMenuHandler(int choice)
{
    switch (choice)
    {
    case (int)GroupByMenu::Distance:
        useMenu(drawDistanceSortMenu, distanceSortMenuInputHandler);
        break;
    case (int)GroupByMenu::Name:
        useMenu(drawNameSortMenu, nameSortMenuInputHandler);
        break;
    case (int)GroupByMenu::Time:
        useMenu(drawTimeSortMenu, timeSortMenuInputHandler);
        break;
    case (int)GroupByMenu::Type:
        useMenu(drawTypeSortMenu, typeSortMenuInputHandler);
        break;
    case (int)GroupByMenu::Exit:
        return -1;
    default:
        printMsg("Выберете действие из списка...\n");
        break;
    }

    return 0;
}