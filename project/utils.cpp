#include "utils.h"

bool validateStringSecond(const wchar_t* arr, int length) {
    for (int i = 0; i < length; i++) {
        if (!iswalnum(arr[i]) && arr[i] != L',' && arr[i] != L'.' && arr[i] != L'+' && arr[i] != L'-') {
            return false;
        }
    }
    return true;
}

void inputStringSecond(wchar_t* arr, wchar_t &el, int &i) {
    i = 0;
    std::wcout << L"Введите строку (максимум 80 символов):\n";
    while ((el = std::getwchar()) != L'\n' && i < 80) {
        arr[i++] = el;
    }
    arr[i] = L'\0';
}


bool validateString(const wchar_t* arr, int length) {
    for (int g = 0; g < length; g++) {
        if (!iswalpha(arr[g]) && arr[g] != L' ') {
            return false;
        }
    }
    return true;
}

void inputArr(wchar_t*& arr, int& size, int& capacity) {
    size = 0;
    capacity = 10;
    arr = new wchar_t[capacity];
    wchar_t el;

    std::wcout << L"Введите строку: \n";
    while ((el = std::getwchar()) != L'\n') {
        if (size == capacity - 1) {
            capacity *= 2;
            wchar_t* newArr = new wchar_t[capacity];
            std::wmemcpy(newArr, arr, size);
            delete[] arr;
            arr = newArr;
        }
        arr[size++] = el;
    }
    arr[size] = L'\0'; 
}

void inputString(wchar_t* arr, wchar_t &el, int &i) {
    i = 0;
    std::wcout << L"Введите строку (максимум 80 символов):\n";
    while ((el = std::getwchar()) != L'\n' && i < 80) {
        arr[i++] = el;
    }
    arr[i] = L'\0';
}
