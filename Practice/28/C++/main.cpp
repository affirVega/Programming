#include <iostream>
#include <map>
#include <string>

void print_factors(const std::map<unsigned int, unsigned int>& factors)
{
    bool not_first = false;
    for (const auto& pair : factors)
    {
        std::cout << (not_first
                        ? "*"
                        : (not_first = true, ""))
                  << pair.first;
        
        if (pair.second > 1)
        {
            std::cout << '^' << pair.second;
            /*
            for (char digit : std::to_string(pair.second))
            {
                switch (digit)
                {
                    case '0': std::cout << "⁰"; break;
                    case '1': std::cout << "¹"; break;
                    case '2': std::cout << "²"; break;
                    case '3': std::cout << "³"; break;
                    case '4': std::cout << "⁴"; break;
                    case '5': std::cout << "⁵"; break;
                    case '6': std::cout << "⁶"; break;
                    case '7': std::cout << "⁷"; break;
                    case '8': std::cout << "⁸"; break;
                    case '9': std::cout << "⁹"; break;
                    default:                    break;
                }
            }
            */
        }
    }
}

void factorization(unsigned int n)
{
    // минимальное значение, делимость на которое будем проверять,
    // т.к. все числа делятся на 1 без остатка.
    const int min_divisor = 2;
    
    std::map<unsigned int, unsigned int> factors;
    
    for (unsigned int i = min_divisor; n == 0 || i <= n; ++i)
    {
        if (n % i == 0)
        {
            n /= i;
            ++factors[i];
            
            i = min_divisor;
        }
    }
    
    print_factors(factors);
}

int main()
{
    unsigned int num;
    std::cin >> num;
    factorization(num);
}
