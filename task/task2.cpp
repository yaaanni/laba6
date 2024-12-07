#include <iostream>
#include <clocale> 
#include <cwchar>  

void inputArr(wchar_t* &arr, int &size, int &capacity) {
    size = 0;
    capacity = 10;
    arr = new wchar_t[capacity];
    wchar_t el;

    std::wcout << L"Введите текст:\n";
    while ((el = std::getwchar()) != L'\n') {
        if (size == capacity) {
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

void removeChar(wchar_t* arr, wchar_t del) {
    int j = 0;
    for (int i = 0; arr[i] != L'\0'; i++) {
        if (arr[i] != del) {
            arr[j++] = arr[i];
        }
    }
    arr[j] = L'\0';
}

bool validateString(const wchar_t* arr, int length) {
    for (int g = 0; g < length; g++) {
        if (!iswalpha(arr[g])) {
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8"); 

    wchar_t* arr = nullptr;
    int size = 0;
    int capacity = 0;
    wchar_t delStr[2];
    wchar_t del;

    while (true) {
        std::wcout << L"Введите символ, который нужно убрать из текста:\n";
        std::wcin.getline(delStr, 2); 

        if (wcslen(delStr) == 1 && iswalpha(delStr[0])) {
            del = delStr[0];
            break; 
        } else {
            std::wcout << L"Пожалуйста, введите одну букву.\n";
        }
    }

    inputArr(arr, size, capacity);

    std::wcout << L"Введенный текст: " << arr << '\n';

    while (!validateString(arr, size)) {
        std::wcout << L"Текст может содержать только буквы:\n";
        delete[] arr; 
        arr = nullptr;
        size = 0;
        inputArr(arr, size, capacity);
    }

    removeChar(arr, del);

    std::wcout << L"Текст после удаления символа '" << del << "':\n" << arr << '\n';

    delete[] arr; 

    return 0;
}
