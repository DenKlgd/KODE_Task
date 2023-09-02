#include "include/Database.h"
#include "include/UI.h"
#include "include/MenuPrinter.h"


Database db;

int main()
{
    system("chcp 1251");

    useMenu(drawMenu, menuInputHandler);

    return 0;
}

