#include <iostream>
#include <clocale> 
#include <cwctype>

void inputString(wchar_t* arr, wchar_t &el, int &i) {
    i = 0; 
    std::wcout << L"Введите строку (максимум 80 символов):\n";
    while ((el = std::getwchar()) != L'\n' && i < 80) {
        arr[i++] = el;
    }
    arr[i] = L'\0';
}

bool validateString(const wchar_t* arr, int length) {
    for (int g = 0; g < length; g++) {
        if (!(iswalnum(arr[g]) || arr[g] == L'.' || arr[g] == L',' || arr[g] == L'+' || arr[g] == L'-')) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); 

    wchar_t el;
    wchar_t arr[81];
    wchar_t result[81];
    int i = 0;

    inputString(arr, el, i);

    while (i > 80 || !validateString(arr, i)) {
        std::wcout << L"Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n";
        inputString(arr, el, i);
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

    return 0;
}