#include <iostream>
#include <cmath>

bool equal(double a, double b, double e = 1E-10);
int sign(int a) {
    return a<0 ? -1 : 1;
}

// этот код было сложно писать, во многих местах он путаный
// постарался описать в комментариях, что делает каждая часть кода

class Rational {
    int num, denom, sgn;

public:
    // наибольший общий делитель (НОД)
    static int gcd(int a, int b) {
        // если одно из чисел равно 0, тогда
        // наибольший общий делитель - другое число
        if (a == 0) return b;
        if (b == 0) return a;

        // делаем число а больше, чем b для удобства
        if (b > a) std::swap(a, b);

        // от b до 1 проверяем, делится ли нацело  a на i  и  b на i
        // если делится, тогда i - наибольшее общее делимое
        // начинаем с b, потому что числа a и b должны делиться на НОД без остатка
        for (int i = b; i > 1; --i)
            if (a % i == 0 and b % i == 0)
                return i;
        return 1;
    }
    // наименьший общий множитель (НОК)
    static int lcm(int a, int b) {
        return abs(a * b) / gcd(a, b);
    }
    Rational() : num(0), denom(1), sgn(1) {}

    Rational(int a, int b)
        : num(abs(a)),      // записываем модули числителя
          denom(abs(b)),    // и знаминателя
          // если знаки a и b равны, тогда sgn = 1, иначе sgn = -1
          sgn(sign(a) == sign(b) ? 1 : -1) {

        // если ни числитель, ни знаменатель не равны 0
        // эту дробь можно сократить
        if (a != 0 and b != 0) {
            // получаем наибольший общий делитель
            int gcd = Rational::gcd(num, denom);

            // сокращаем дроби
            num /= gcd;
            denom /= gcd;
        }
    }

    bool operator ==(const Rational& other) const {
        // неопределённые не равны даже себе, поэтому они не равны ничему
        if (isNaN() or other.isNaN()) return false;

        // нули не имеют знак, так что если оба числа нули - они равны
        if (num == 0 and other.num == 0) return true;

        // если знаки не равны, числа не равны
        if (sgn != other.sgn) return false;
        // далее в сравнении учавствуют числа с одинаковым знаком

        // если оба числа - бесконечность, они равны
        if (denom == 0 and other.denom == 0) return true;

        // сравниваем числители и знаминатели
        return num == other.num and denom == other.denom;
    }

    Rational operator -(const Rational& other) const {
        // просто переворачиваем знак и складываем числа
        // потому что a - b = a + (-b)
        Rational copy = other;
        copy.sgn = -copy.sgn;

        return *this + copy;
    }

    Rational operator +(const Rational& other) const {
        // сложение с неопределённостью даёт неопределённость
        if (isNaN() or other.isNaN()) return Rational(0, 0);

        // если оба числа - бесконечности
        if (denom == 0 and other.denom == 0) {
            // если бесконечности направленны в одну сторону (-∞ и -∞, +∞ и +∞),
            // возвращаем любую бесконечность, разницы нет
            if (sgn == other.sgn) return other;

            // значение суммы -∞ и +∞ неопределено
            return Rational(0, 0);
        }
        // если левый операнд - бесконечность, вощвращаем левый операнд
        if (denom == 0) return *this;

        // если правый операнд - бесконечность, возвращаем правый операнд
        if (other.denom == 0) return other;

        // наименьшее общее кратное (НОК)
        int lcm = Rational::lcm(denom, other.denom);

        // чтобы сложить два рациональных числа, нужно отдельно умножить
        // обе дроби так, чтобы знаминатели были равны
        // (привести к общему знаменателю). Знаминатель суммы это НОК
        // Здесь делиться НОК на знаминатель, чтобы получить множитель знаминателя
        int firstNum = num * (lcm / denom);
        int secondNum = other.num * (lcm / other.denom);

        int resultSgn, resultNum;

        // если знаки равны
        if (sgn == other.sgn) {
            // берём знак любого операнда как знак результата, разницы нет
            resultSgn = sgn;

            // числитель результата это сумма новых числителей
            resultNum = firstNum + secondNum;
        } else { // если знаки не равны
            // знак результата это знак большего числа
            resultSgn = firstNum > secondNum ? sgn : other.sgn;

            // числитель - модуль разности новых числителей
            resultNum = abs(firstNum - secondNum);
        }

        Rational result(resultNum, lcm);
        result.sgn = resultSgn;
        return result;
    }

    Rational operator *(const Rational& other) const {
        // создаём новое рациональное, умножая числители и знаминатели соответственно
        // помним, что num и denom положительные числа
        Rational result(num * other.num,
                        denom * other.denom);

        // устанавливаем знак числа, т.к. знак по-умолчанию плюс
        result.sgn = sgn * other.sgn;
        return result;
    }

    Rational operator /(const Rational& other) const {
        // создаём новое рациональное, перевернув второй операнд
        // и умножив числители и знаминатели соответственно
        // помним, что num и denom положительные числа
        auto result = Rational(num * other.denom,
                               denom * other.numerator());

        // устанавливаем знак числа, т.к. знак по-умолчанию плюс
        result.sgn = sgn * other.sgn;
        return result;
    }

    operator double() const {
        // делим числитель на знаминатель и умножаем на знак (1 или -1)
        return sgn * num / double(denom);
    }

    operator bool() const {
        // Возвращает false, если число является нулём.
        // Если число бесконечность или неопределённость,
        // или другое, возвращается true
        return num != 0 or denom == 0;
    }

    int numerator() const {
        return num;
    }

    int denominator() const {
        return denom;
    }

    bool isNaN() const {
        // дробь 0/0 является неопределённостью
        return num == 0 and denom == 0;
    }
};

int main()
{
    if (Rational::gcd(91, 65) == 13 &&
        Rational::gcd(10, 3) == 1 &&
        Rational::gcd(-10, 3) == 1 &&
        Rational::gcd(10, -3) == 1 &&
        Rational::gcd(-10, -3) == 1 &&
        Rational::gcd(30, 10) == 10 &&
        Rational::gcd(10, 30) == 10 &&
        Rational::gcd(0, 10) == 10 &&
        Rational::gcd(10, 0) == 10) std::cout << "gcd test passed\n";
    else std::cout << "gcd test failed\n";

    if (!Rational(22, 0).isNaN() &&
        !Rational(22, 9).isNaN() &&
        !Rational(0, 9).isNaN() &&
        !Rational(-22, 9).isNaN() &&
        !Rational(-22, 0).isNaN() &&
        Rational(0, 0).isNaN()
        ) std::cout << "isNaN test passed\n";
    else std::cout << "isNaN test failed\n";

    if (Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 0) == Rational(9, 0) &&
        !(Rational(22, 0) == Rational(22, 9)) &&
        !(Rational(22, 0) == Rational(-22, 9)) &&
        !(Rational(22, 0) == Rational(-22, 0)) &&
        !(Rational(22, 0) == Rational(0, 9)) &&
        !(Rational(22, 0) == Rational(0, 0)) &&

        Rational(22, 9) == Rational(22, 9) &&
        Rational(22, 9) == Rational(-22, -9) &&
        Rational(22, 9) == Rational(110, 45) &&
        Rational(22, 9) == Rational(-110, -45) &&
        !(Rational(22, 9) == Rational(-22, 9)) &&
        !(Rational(22, 9) == Rational(22, -9)) &&
        !(Rational(22, 9) == Rational(9, 22)) &&
        !(Rational(22, 9) == Rational(22, 0)) &&
        !(Rational(22, 9) == Rational(-22, 0)) &&
        !(Rational(22, 9) == Rational(0, 9)) &&
        !(Rational(22, 9) == Rational(0, 0)) &&

        Rational(0, 1) == Rational(0, 1) &&
        Rational(0, 1) == Rational(0, 9)  &&
        Rational(0, 1) == Rational(0, -9)  &&
        !(Rational(0, 1) == Rational(22, 9))  &&
        !(Rational(0, 1) == Rational(-22, 9))  &&
        !(Rational(0, 1) == Rational(22, 0)) &&
        !(Rational(0, 1) == Rational(-22, 0)) &&
        !(Rational(0, 1) == Rational(0, 0)) &&

        Rational(-22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) == Rational(22, -9) &&
        Rational(-22, 9) == Rational(-110, 45) &&
        Rational(-22, 9) == Rational(110, -45) &&
        !(Rational(-22, 9) == Rational(-22, -9)) &&
        !(Rational(-22, 9) == Rational(22, 9)) &&
        !(Rational(-22, 9) == Rational(9, -22)) &&
        !(Rational(-22, 9) == Rational(22, 0)) &&
        !(Rational(-22, 9) == Rational(-22, 0)) &&
        !(Rational(-22, 9) == Rational(0, 9)) &&
        !(Rational(-22, 9) == Rational(0, 0)) &&

        Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) == Rational(-9, 0) &&
        !(Rational(-22, 0) == Rational(22, 9)) &&
        !(Rational(-22, 0) == Rational(-22, 9)) &&
        !(Rational(-22, 0) == Rational(22, 0)) &&
        !(Rational(-22, 0) == Rational(0, 9)) &&
        !(Rational(-22, 0) == Rational(0, 0)) &&

        !(Rational(0, 0) == Rational(0, 0))
        ) std::cout << "Equality test passed\n";
    else std::cout << "Equality test failed\n";

    if (Rational(22, 0) + Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 9) + Rational(22, 0) == Rational(22, 0) &&
        Rational(0, 9) + Rational(22, 0) == Rational(22, 0) &&
        Rational(-22, 9) + Rational(22, 0) == Rational(22, 0) &&
        (Rational(-22, 0) + Rational(22, 0)).isNaN() &&

        Rational(22, 0) + Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) + Rational(22, 9) == Rational(44, 9) &&
        Rational(0, 9) + Rational(22, 9) == Rational(22, 9) &&
        Rational(-22, 9) + Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 0) + Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) + Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) + Rational(0, 1) == Rational(22, 9) &&
        Rational(0, 9) + Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) + Rational(0, 1) == Rational(-22, 9) &&
        Rational(-22, 0) + Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) + Rational(-22, 9) == Rational(22, 0) &&
        Rational(22, 9) + Rational(-22, 9) == Rational(0, 9) &&
        Rational(0, 9) + Rational(-22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) + Rational(-22, 9) == Rational(-44, 9) &&
        Rational(-22, 0) + Rational(-22, 9) == Rational(-22, 0) &&

        (Rational(22, 0) + Rational(-22, 0)).isNaN() &&
        Rational(22, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(0, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 9) + Rational(-22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) + Rational(-22, 0) == Rational(-22, 0) &&

        (Rational(22, 0) + Rational(0, 0)).isNaN() &&
        (Rational(22, 9) + Rational(0, 0)).isNaN() &&
        (Rational(0, 9) + Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) + Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) + Rational(0, 0)).isNaN()
       ) std::cout << "Summation test passed\n";
    else std::cout << "Summation test failed\n";

    if ((Rational(22, 0) - Rational(22, 0)).isNaN() &&
        Rational(22, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(0, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 9) - Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) - Rational(22, 0) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) - Rational(22, 9) == Rational(0, 9) &&
        Rational(0, 9) - Rational(22, 9) == Rational(-22, 9) &&
        Rational(-22, 9) - Rational(22, 9) == Rational(-44, 9) &&
        Rational(-22, 0) - Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) - Rational(0, 1) == Rational(22, 9) &&
        Rational(0, 9) - Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) - Rational(0, 1) == Rational(-22, 9) &&
        Rational(-22, 0) - Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(-22, 9) == Rational(22, 0) &&
        Rational(22, 9) - Rational(-22, 9) == Rational(44, 9) &&
        Rational(0, 9) - Rational(-22, 9) == Rational(22, 9) &&
        Rational(-22, 9) - Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 0) - Rational(-22, 9) == Rational(-22, 0) &&

        Rational(22, 0) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(22, 9) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(0, 9) - Rational(-22, 0) == Rational(22, 0) &&
        Rational(-22, 9) - Rational(-22, 0) == Rational(22, 0) &&
        (Rational(-22, 0) - Rational(-22, 0)).isNaN() &&

        (Rational(22, 0) - Rational(0, 0)).isNaN() &&
        (Rational(22, 9) - Rational(0, 0)).isNaN() &&
        (Rational(0, 9) - Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) - Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) - Rational(0, 0)).isNaN()
        ) std::cout << "Subtraction test passed\n";
    else std::cout << "Subtraction test failed\n";

    if (Rational(22, 0) * Rational(22, 0) == Rational(22, 0) &&
        Rational(22, 9) * Rational(22, 0) == Rational(22, 0) &&
        (Rational(0, 9) * Rational(22, 0)).isNaN() &&
        Rational(-22, 9) * Rational(22, 0) == Rational(-22, 0) &&
        Rational(-22, 0) * Rational(22, 0) == Rational(-22, 0) &&

        Rational(22, 0) * Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) * Rational(22, 9) == Rational(22*22, 9*9) &&
        Rational(0, 9) * Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(22, 9) == Rational(-22*22, 9*9) &&
        Rational(-22, 0) * Rational(22, 9) == Rational(-22, 0) &&

        (Rational(22, 0) * Rational(0, 1)).isNaN() &&
        Rational(22, 9) * Rational(0, 1) == Rational(0, 9) &&
        Rational(0, 9) * Rational(0, 1) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(0, 1) == Rational(0, 9) &&
        (Rational(-22, 0) * Rational(0, 1)).isNaN() &&

        Rational(22, 0) * Rational(-22, 9) == Rational(-22, 0) &&
        Rational(22, 9) * Rational(-22, 9) == Rational(-22*22, 9*9) &&
        Rational(0, 9) * Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 9) * Rational(-22, 9) == Rational(22*22, 9*9) &&
        Rational(-22, 0) * Rational(-22, 9) == Rational(22, 0) &&

        Rational(22, 0) * Rational(-22, 0) == Rational(-22, 0) &&
        Rational(22, 9) * Rational(-22, 0) == Rational(-22, 0) &&
        (Rational(0, 9) * Rational(-22, 0)).isNaN() &&
        Rational(-22, 9) * Rational(-22, 0) == Rational(22, 0) &&
        Rational(-22, 0) * Rational(-22, 0) == Rational(22, 0) &&

        (Rational(22, 0) * Rational(0, 0)).isNaN() &&
        (Rational(22, 9) * Rational(0, 0)).isNaN() &&
        (Rational(0, 9) * Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) * Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) * Rational(0, 0)).isNaN()
        ) std::cout << "Multiplication test passed\n";
    else std::cout << "Multiplication test failed\n";

    if ((Rational(22, 0) / Rational(22, 0)).isNaN() &&
        Rational(22, 9) / Rational(22, 0) == Rational(0, 9) &&
        Rational(0, 9) / Rational(22, 0) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(22, 0) == Rational(0, 9) &&
        (Rational(-22, 0) / Rational(22, 0)).isNaN() &&

        Rational(22, 0) / Rational(22, 9) == Rational(22, 0) &&
        Rational(22, 9) / Rational(22, 9) == Rational(9, 9) &&
        Rational(0, 9) / Rational(22, 9) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(22, 9) == Rational(-9, 9) &&
        Rational(-22, 0) / Rational(22, 9) == Rational(-22, 0) &&

        Rational(22, 0) / Rational(0, 1) == Rational(22, 0) &&
        Rational(22, 9) / Rational(0, 1) == Rational(22, 0) &&
        (Rational(0, 9) / Rational(0, 1)).isNaN() &&
        Rational(-22, 9) / Rational(0, 1) == Rational(-22, 0) &&
        Rational(-22, 0) / Rational(0, 1) == Rational(-22, 0) &&

        Rational(22, 0) / Rational(-22, 9) == Rational(-22, 0) &&
        Rational(22, 9) / Rational(-22, 9) == Rational(-9, 9) &&
        Rational(0, 9) / Rational(-22, 9) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(-22, 9) == Rational(9, 9) &&
        Rational(-22, 0) / Rational(-22, 9) == Rational(22, 0) &&

        (Rational(22, 0) / Rational(-22, 0)).isNaN() &&
        Rational(22, 9) / Rational(-22, 0) == Rational(0, 9) &&
        Rational(0, 9) / Rational(-22, 0) == Rational(0, 9) &&
        Rational(-22, 9) / Rational(-22, 0) == Rational(0, 9) &&
        (Rational(-22, 0) / Rational(-22, 0)).isNaN() &&

        (Rational(22, 0) / Rational(0, 0)).isNaN() &&
        (Rational(22, 9) / Rational(0, 0)).isNaN() &&
        (Rational(0, 9) / Rational(0, 0)).isNaN() &&
        (Rational(-22, 9) / Rational(0, 0)).isNaN() &&
        (Rational(-22, 0) / Rational(0, 0)).isNaN()
        ) std::cout << "Division test passed\n";
    else std::cout << "Division test failed\n";

    if (equal(Rational(-22, -9), 22/9.0) &&
        equal(Rational(-9, -9), 1) &&
        equal(Rational(-6, -9), 6/9.0) &&
        equal(Rational(0, -9), 0) &&
        equal(Rational(6, -9), -6/9.0) &&
        equal(Rational(9, -9), -1) &&
        equal(Rational(22, -9), -22/9.0) &&
        std::isinf((double)Rational(-9, 0)) &&
        std::isnan((double)Rational(0, 0)) &&
        std::isinf((double)Rational(9, 0)) &&
        equal(Rational(-22, 9), -22/9.0) &&
        equal(Rational(-9, 9), -1) &&
        equal(Rational(-6, 9), -6/9.0) &&
        equal(Rational(0, 9), 0) &&
        equal(Rational(6, 9), 6/9.0) &&
        equal(Rational(9, 9), 1) &&
        equal(Rational(22, 9), 22/9.0)) std::cout << "Conversion to double test passed\n";
    else std::cout << "Conversion to double test failed\n";

    if (Rational(-22, -9) &&
        Rational(-9, -9) &&
        Rational(-6, -9) &&
        !Rational(0, -9) &&
        Rational(6, -9) &&
        Rational(9, -9) &&
        Rational(22, -9) &&
        Rational(-9, 0) &&
        Rational(0, 0) &&
        Rational(9, 0) &&
        Rational(-22, 9) &&
        Rational(-9, 9) &&
        Rational(-6, 9) &&
        !Rational(0, 9) &&
        Rational(6, 9) &&
        Rational(9, 9) &&
        Rational(22, 9)) std::cout << "Conversion to bool test passed\n";
    else std::cout << "Conversion to bool test failed\n";
}

bool equal(double a, double b, double e) {
    if (-e < a - b && a - b < e) return true;
    else return false;
}
