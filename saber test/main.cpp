#define _CRT_SECURE_NO_WARNINGS                                     // Отключаем предупреждения, чтобы использовать strcpy()              
#include <iostream> 
#include <stack>
#include <bitset>
#include <cmath>
#include <cstring>


void ConvertToBinary(int num, int bit) {
    // Локальные переменные.
    std::stack<int> binNumberStck;                                  // Создаём стэк, потому что из него будет удобнее доставать числа (поскольку порядок обратный).
    int  bitTmp = bit;                                              // Переменная для итерации, чтобы заполнить стэк.
    int* binNumberArr = new int[bit] {0};
    // Проверка числа.
    bool isNegative = (num < 0 ? num *= -1, true : false);          // Проверяем отрицательное ли число.   

    // Служебная информация
    std::cout << "\t\tDEC TO BIN:"
        << std::endl;
    std::cout << "Original number: \t\t"
        << (isNegative ? -num : num) << std::endl;
    std::cout << "Number is: \t\t\t"
        << (isNegative ? "Negative(-)" : "Positive(+)")
        << std::endl;

    // Перевод в классическую двоичную запись.
    while (bitTmp != 0) {                                           // Пушим в стэк пока не закончится количество бит, указанных пользователем.
        if (num > 0) {                                              // Пушим по этому условию,
            binNumberStck.push(num % 2);                            // пока не закончится
            num /= 2;                                               // десятичное число.
        }
        else
            binNumberStck.push(0);                                  // Пушим нули на оставшие биты.
        bitTmp--;
    }

    // Заполнение массива двоичным числом.
    for (int i = 0; i < bit; i++) {
        if (isNegative)
            binNumberArr[i] = abs(binNumberStck.top() - 1);         // Переводим в обратный код для отрицательных чисел.
        else
            binNumberArr[i] = binNumberStck.top();                  // Для положительных чисел - записываем данные из стэка в массив.
        binNumberStck.pop();
    }

    // Переводим в дополнительный код.
    if (isNegative) {                                               // (Для отрицательных чисел)
        binNumberArr[bit - 1]++;                                    // Прибавляем единицу
        for (int i = bit - 1; i > 0; i--) {                         // Поскольку массив типа int,
            if (binNumberArr[i] == 2) {                             // Ловим переполнение когда значение == 2.
                binNumberArr[i] = 0;
                binNumberArr[i - 1]++;
            }
        }
    }

    // Вывод двоичного числа
    std::cout << "Bin number: \t\t\t";
    for (int j = 0; j < bit; j++) {
        std::cout << binNumberArr[j];
    }
    std::cout << std::endl;

    delete[] binNumberArr;                                          //Очищаем выделенную память
}


void RemoveDups(char* str) {
    // Локальные переменные.
    char* tmpStr = new char[strlen(str)] {'\0'};                    // Создаём временный массив, для хранения  символов.
    int tmpIter = 0;                                                // Переменная для итерирования по временному массиву.
    // Служебная информация
    std::cout << "\t\tREMOVING DUPLICATES:"
        << std::endl;
    std::cout << "Original string: \t\t"
        << str << std::endl;

    // Основной цикл
    for (int i = 0; i <= int(strlen(str)); i++) {
        if (str[i] == ' ' && str[i] != '\0') {                      // Записываем левый символ во временный массив,
            tmpStr[tmpIter] = str[i - 1];                           // После того как встретили пробел,
            tmpStr[tmpIter + 1] = ' ';                              // Ставим пробел в новый массив для разделения.
            tmpIter += 2;
        }
        else if (str[i] == '\0') {                                  // Если встречаем символ конца строки,
            tmpStr[tmpIter] = str[i - 1];                           // Просто записываем левый символ от этого символа.
            break;
        }
    }

    strcpy(str, tmpStr);                                            // Копируем значения из временного массива в оригинальный
    delete[] tmpStr;                                                // Очищаем выделенную память
}


int main()
{
    // Удаление дубликатов
    char data[] = "A BB CCC LLL OOO LLL";
    RemoveDups(data);
    std::cout << "Modified string: \t\t"
        << data << std::endl;

    // Перевод в двоичную систему,
    // работает и для отрицательных чисел/
    ConvertToBinary(-1337322, 32);                                  // Первое число в функции - десятичное значение, 
                                                                    // второе - количество бит для отображения (по аналогии с bitset).
    std::cout << "bitset check: \t\t\t" << std::bitset<32>(-1337322) << std::endl;
    ConvertToBinary(777555, 32);
    std::cout << "bitset check: \t\t\t" << std::bitset<32>(777555) << std::endl;
}


//Артемьев Илья Сергеевич
//17.11.2022
//Примерно затрачено времени:
//на первую задачу        - 2ч
//на вторую               - 4ч
//*на форматирование кода - 1ч