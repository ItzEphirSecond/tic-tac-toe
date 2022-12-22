#include <iostream>
#include "Application.h"

int main()
{
    // русский
    std::setlocale(LC_ALL, "Russian");

    // создаем экземпл€р класса Application
    Application app = Application();

    // пока игра не остановилась
    while (!app.isStopped())
    {
        // обновл€ть игру
        app.Update();
    }
}