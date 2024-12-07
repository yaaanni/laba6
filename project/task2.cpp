#include "task2.h"
#include "utils.h"
#include <iostream>
#include <clocale>
#include <cwchar>
#include <limits>

void removeChar(wchar_t* arr, wchar_t del) {
    int j = 0;
    for (int i = 0; arr[i] != L'\0'; i++) {
        if (arr[i] != del) {
            arr[j++] = arr[i];
        }
    }
    arr[j] = L'\0';
}

void Task2::execute() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t* arr = nullptr;
    int size = 0;
    int capacity = 0;
    wchar_t delStr[3];
    wchar_t del;

    while (true) {
        std::wcout << L"Введите символ, который нужно убрать из текста:\n";
        std::wcin.getline(delStr, 3);

        if (wcslen(delStr) == 1 && iswalpha(delStr[0])) {
            del = delStr[0];
            break;
        } else {
            std::wcout << L"Пожалуйста, введите одну букву.\n";
            std::wcin.clear(); // очистка флагов ошибок
            std::wcin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка ввода
        }
    }

    inputArr(arr, size, capacity);

    std::wcout << L"Введенный текст: " << arr << '\n';

    while (!validateString(arr, size)) {
        std::wcout << L"Текст может содержать только буквы. Повторите ввод:\n";
        delete[] arr;
        arr = nullptr;
        size = 0;
        inputArr(arr, size, capacity);
    }

    removeChar(arr, del);

    std::wcout << L"Текст после удаления символа '" << del << "':\n" << arr << '\n';

    delete[] arr;
}
