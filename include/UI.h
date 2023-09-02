#pragma once

void useMenu(void (*drawMenuFunc)(), int (*inputHandlerFunc)(int choice));
int menuInputHandler(int choice);
int dbMenuInputHandler(int choice);
int groupByMenuHandler(int choice);
