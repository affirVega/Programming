
#include <string>
#include <vector>

// Различные уровни логгирования
enum log_level
{
    none,   	// Ничего не выводить

    error,  	// Выводить только ошибки
    warning,	// Выводить ошибки и предупреждения
    info,   	// Выводить всё выше и информацию для пользователя
    debug   	// Выводить всё выше и информацию для отладки
};

struct logger
{
private:
    // внутренний объект, являющийся представлением объекта, в который необходимо
    // вывести информацию.
    struct log_output
    {
        // Переменная-указатель на функцию, которая будет вызываться для вывода
        void(*push)(log_level level, std::string msg);
        
        // Конструктор, принимающий функцию, принимающая уровень логгирования и
        // строку, и присваивающая её переменной push
        log_output(void(func)(log_level, std::string))
        { 
            push = func;
        }
    };

private:
    // массив из обхектов вывода
    std::vector<log_output> _outputs;
    // текущий уровень
    log_level _current_level;

public:
    // Функция для добавления места, куда нужно логгировать.
    void add_output(void(func)(log_level, std::string));
    
    // Функция для вывода строки в место, куда нужно логгировать
    void push(const std::string& msg);
    
    // push(), только через оператор
    logger& operator << (std::string msg)
    {
        this->push(msg);
    }
    
    // Конструктор, принимающий уровень логгирования
    logger(log_level level = info);
    
    // Пустой деструктор
    ~logger() {
    }
};

void logger::push(const std::string& msg)
{
    for (auto& output : _outputs)
        output.push(_current_level, msg);
}

void logger::add_output(void(func)(log_level, std::string))
{
    _outputs.push_back({func});
}

logger::logger(log_level level)
{
    _current_level = level;
}
