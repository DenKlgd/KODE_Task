#include "../include/MenuPrinter.h"
#include <iostream>


using std::cout;
using std::cin;


void drawMenu()
{
    CLS;
    cout << "Выберете действие:\n\n";
    cout << (int)MainMenu::OpenFile << ") Открыть файл\n";
    cout << (int)MainMenu::Exit << ") Выйти\n\n";
    cout << "Ваш выбор: ";
}

void drawDbMenu()
{
    CLS;
    cout << "Выберете действие:\n\n";
    cout << (int)DbMenu::ReadFile << ") Просмотр файла\n";
    cout << (int)DbMenu::AddObject << ") Добавить объект\n";
    cout << (int)DbMenu::GroupBy << ") Группировать\n";
    cout << (int)DbMenu::SaveToFile << ") Сохранить изменения\n";
    cout << (int)DbMenu::Exit << ") Выйти\n\n";
    cout << "Ваш выбор: ";
}

void drawGroupByMenu()
{
    CLS;
    cout << "Группировка:\n\n";
    cout << (int)GroupByMenu::Distance << ") по расстоянию\n";
    cout << (int)GroupByMenu::Name << ") по имени\n";
    cout << (int)GroupByMenu::Time << ") по времени\n";
    cout << (int)GroupByMenu::Type << ") по типу\n";
    cout << (int)GroupByMenu::Exit << ") Назад\n\n";
    cout << "Ваш выбор: ";
}

void drawDistanceSortMenu()
{
    CLS;
    cout << "Группировка по расстоянию:\n\n";
    cout << (int)DistanceSortMenu::_100 << ") До 100 ед.\n";
    cout << (int)DistanceSortMenu::_1000 << ") До 1000 ед.\n";
    cout << (int)DistanceSortMenu::_10000 << ") До 10000 ед.\n";
    cout << (int)DistanceSortMenu::_FAR << ") Слишком далеко\n";
    cout << (int)DistanceSortMenu::_Exit << ") Назад\n\n";
    cout << "Ваш выбор: ";
}

void drawTimeSortMenu()
{
    CLS;
    cout << "Группировка по времени:\n\n";
    cout << (int)TimeSortMenu::Today << ") Сегодня\n";
    cout << (int)TimeSortMenu::Yesterday << ") Вчера\n";
    cout << (int)TimeSortMenu::Week << ") На этой неделе\n";
    cout << (int)TimeSortMenu::Month << ") В этом месяце\n";
    cout << (int)TimeSortMenu::Year << ") В этом году\n";
    cout << (int)TimeSortMenu::Earlier << ") Ранее\n";
    cout << (int)TimeSortMenu::Exit << ") Назад\n\n";
    cout << "Ваш выбор: ";
}

void drawNameSortMenu()
{
    CLS;
    cout << "Группировка по имени:\n\n";
    cout << (int)NameSortMenu::Any << ") Произвольный символ\n";
    cout << (int)NameSortMenu::Other << ") A - Z | 0 - 9 | спецсимвол\n";
    cout << (int)NameSortMenu::Exit << ") Назад\n\n";
    cout << "Ваш выбор: ";
}

void drawTypeSortMenu()
{
    CLS;
    cout << "Группировка по типу:\n\n";
    cout << (int)TypeSortMenu::Any << ") Указать тип\n";
    cout << (int)TypeSortMenu::Other << ") Разное (тип <= N)\n";
    cout << (int)TypeSortMenu::Exit << ") Назад\n\n";
    cout << "Ваш выбор: ";
}
