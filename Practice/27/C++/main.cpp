#include <iostream>

template <class T>
struct linklist_item
{
    T val;
    linklist_item *next = nullptr;
    
    /*
    void push_back(linklist_item &item)
    {
        linklist_item *temp = *this;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = &item;
    }*/
    
    void insert(linklist_item &item)
    {
        item.next = this.next;
        this.next = &item;
    }
};


int main()
{
    int64_t n;
    std::cout << "Введите число n: " << std::flush;
    std::cin >> n;
    
    int value;
    std::cout << "Введите n чисел, разделённые пробелом:\n> " << std::flush;
    std::cin >> value;
    linklist_item<int64_t> head = {value};
    
    for (int64_t i = 1; i < n; ++i)
    {
        std::cin >> value;
        linklist_item<int64_t> *item;
        for (int j = 0, item = &head;
            j < 5;
            ++j)
        {
            if (value > item->value)
            {
                linklist_item<int64_t> temp = {value};
                temp.insert(*item);
                if (item == &head)
                {
                    head = temp;
                }
                break;
            }
            else if (item->next == nullptr)
            {
                break;
            }
            else
            {
                item = item->next;
            }
        }
        
        for (int j = 0, item = &head; j < 5; ++j)
        {
            if (item->next != nullptr)
            {
                std::cout << item->value << ' ';
            }
            else
            {
                break;
            }
        }
        std::cout << std::endl;
    }
}
