#include "task1.h"
#include "utils.h"
#include <iostream>
#include <clocale>

void Task1::execute() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t el;
    wchar_t arr[81];
    wchar_t result[81];
    int i = 0;

    inputStringSecond(arr, el, i);

    while (i > 80 || !validateStringSecond(arr, i)) {
        std::wcout << L"Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n";
        inputStringSecond(arr, el, i);
    }

    std::wcout << L"Вы ввели:\n" << arr << '\n';

    int j = 0;
    for (int k = 0; k < i; k++) {
        if (iswdigit(arr[k])) {
            result[j++] = arr[k];
        }
    }
    result[j] = L'\0';

    std::wcout << L"Строка, представляющая целое число:\n" << result << '\n';
}
