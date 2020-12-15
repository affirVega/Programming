#include <iostream>
#include "logger.hpp"

int main()
{
    // Создаётся объект класса логгер
    logger out;
    
    // Создаётся лябмда-функция, принимающая текущий уровень логирования
    // и сообщение, которое необходимо вывести. Оно выводит в std::cout
    // сообщение и новую строку.
    auto to_stdout = [](log_level level, std::string msg)
    {
        if (level > log_level::none)
            std::cout << msg << std::endl; // может быть std::flush
    };
    
    // В класс логгера добавляем 2 вывода (в stdout)
    out.add_output(to_stdout);
    out.add_output(to_stdout);
    
    // Выводим текстовое сообщение
    out << "I love my mom";
};
