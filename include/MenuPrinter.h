#pragma once

#ifdef _WIN32
    #define CLS system("cls")
#endif


enum class MainMenu
{
    OpenFile = 1,
    Exit
};

enum class DbMenu
{
    ReadFile = 1,
    AddObject,
    GroupBy,
    SaveToFile,
    Exit
};

enum class GroupByMenu
{
    Distance = 1,
    Name,
    Time,
    Type,
    Exit
};

enum class DistanceSortMenu
{
    _100 = 1,
    _1000,
    _10000,
    _FAR,
    _Exit
};

enum class TimeSortMenu
{
    Today = 1,
    Yesterday,
    Week,
    Month,
    Year,
    Earlier,
    Exit
};

enum class NameSortMenu
{
    Any = 1,
    Other,
    Exit
};

enum class TypeSortMenu
{
    Any = 1,
    Other,
    Exit
};


void drawMenu();
void drawDbMenu();
void drawGroupByMenu();
void drawDistanceSortMenu();
void drawTimeSortMenu();
void drawNameSortMenu();
void drawTypeSortMenu();