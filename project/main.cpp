#include <iostream>
#include <limits>
#include <locale>
#include "task1.h"
#include "task2.h"
#include "task3.h"

int menu() {
    std::wcout << L"Выберите интересующий пункт меню: \n";
    std::wcout << L"1. Кто выполнил задание\n";
    std::wcout << L"2. Результат программы\n";
    std::wcout << L"3. Суть задания\n";
    std::wcout << L"4. Выход из программы\n";
    std::wcout << L"5. Вариант\n";
    std::wcout << L">>>\n";
    int n;
    while (!(std::wcin >> n) || (std::wcin.peek() != '\n')) {
        std::wcin.clear();
        std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::wcout << L"Введите значение повторно: ";
    }
    return n;
}

void program(int choice) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Очистка ввода
    std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    switch (choice) {
        case 1: {
            Task1 task1;
            task1.execute();
            break;
        }
        case 2: {
            Task2 task2;
            task2.execute();
            break;
        }
        case 3: {
            Task3 task3;
            task3.execute();
            break;
        }
        default:
            std::wcout << L"Неверный выбор!" << std::endl;
            break;
    }
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    std::wcout.imbue(std::locale("ru_RU.UTF-8"));

    while (true) {
        int number = menu();
        if (number == 1) {
            std::wcout << L"Попова Яна\n";
        } else if (number == 2) {
            int choice;
            std::wcout << L"Выберите задание:\n";
            std::wcout << L"1. Выделить подстроку, соответствующую записи целого числа\n";
            std::wcout << L"2. Удалить указанный символ везде, где он встречается\n";
            std::wcout << L"3. Менять местами все четные и нечетные слова\n";
            std::wcin >> choice;

            program(choice);
        } else if (number == 3) {
            std::wcout << L"Сделать 3 задания\n";
        } else if (number == 4) {
            std::wcout << L"Выход выполнен успешно!\n";
            return 0;
        } else if (number == 5) {
            std::wcout << L"Вариант: 6\n";
        } else {
            std::wcout << L"Неверно ввели значение, попробуйте еще раз: \n";
            continue;
        }
        std::wcout << L">>>\n";
    }
}
