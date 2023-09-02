#include "include/Database.h"
#include "include/UI.h"
#include "include/MenuPrinter.h"


Database db;

int main()
{
    #ifdef _WIN32
        system("chcp 1251");
    #endif

    useMenu(drawMenu, menuInputHandler);

    return 0;
}

