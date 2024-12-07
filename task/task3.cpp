#include <iostream>
#include <clocale>
#include <cwchar>

bool validateString(const wchar_t* arr, int length) {
    for (int g = 0; g < length; g++) {
        if (!iswalpha(arr[g]) && arr[g] != L' ') {
            return false;
        }
    }
    return true;
}

// Функция для обмена местами двух строк полностью
void swapWordsCompletely(wchar_t*& str1, wchar_t*& str2) {
    wchar_t* temp = str1;
    str1 = str2;
    str2 = temp;
}

// Функция для обмена нечетных и четных слов
void swapOddEvenWords(wchar_t** words, int wordCount) {
    for (int i = 0; i < wordCount - 1; i += 2) {
        swapWordsCompletely(words[i], words[i + 1]);
    }
}

// Функция для ввода строки произвольной длины
void inputArr(wchar_t*& arr, int& size, int& capacity) {
    size = 0;
    capacity = 10;
    arr = new wchar_t[capacity];
    wchar_t el;
    std::wcout << L"Введите строку: \n";
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
    arr[size] = L'\0'; // Завершение строки
}

// Функция для увеличения размера массива слов
void resizeWordsArray(wchar_t**& words, int*& wordCapacities, int& maxWords) {
    int newMaxWords = maxWords * 2; // Увеличиваем размер массива в два раза
    wchar_t** newWords = new wchar_t*[newMaxWords];
    int* newWordCapacities = new int[newMaxWords];

    for (int i = 0; i < maxWords; ++i) {
        newWords[i] = words[i];
        newWordCapacities[i] = wordCapacities[i];
    }

    for (int i = maxWords; i < newMaxWords; ++i) {
        newWordCapacities[i] = 30; // Новый начальный размер для каждого слова - 30 символов
        newWords[i] = new wchar_t[newWordCapacities[i]];
    }

    delete[] words;
    delete[] wordCapacities;

    words = newWords;
    wordCapacities = newWordCapacities;
    maxWords = newMaxWords;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int size = 0;
    int capacity = 0;
    wchar_t* arr = nullptr;

    // Ввод строки
    inputArr(arr, size, capacity);

    // Проверка строки на корректность
    while (!validateString(arr, size)) {
        std::wcout << L"Текст может содержать только буквы и пробелы. Повторите ввод:\n";
        delete[] arr;
        inputArr(arr, size, capacity);
    }

    // Выделение памяти для хранения слов
    int maxWords = 20; // Начальный размер
    wchar_t** words = new wchar_t*[maxWords];
    int* wordCapacities = new int[maxWords]; // Для хранения текущих размеров массивов слов
    for (int i = 0; i < maxWords; ++i) {
        wordCapacities[i] = 30; // Начальный размер для каждого слова - 30 символов
        words[i] = new wchar_t[wordCapacities[i]];
    }

    int wordIndex = 0;
    int charIndex = 0;
    for (int i = 0; arr[i] != L'\0'; ++i) {
        if (arr[i] != L' ') {
            if (charIndex == wordCapacities[wordIndex]) {
                wordCapacities[wordIndex] *= 2;
                wchar_t* newWordArr = new wchar_t[wordCapacities[wordIndex]];
                std::wmemcpy(newWordArr, words[wordIndex], charIndex);
                delete[] words[wordIndex];
                words[wordIndex] = newWordArr;
            }
            words[wordIndex][charIndex++] = arr[i];
        } else {
            words[wordIndex][charIndex] = L'\0';
            wordIndex++;
            charIndex = 0;

            if (wordIndex == maxWords) {
                resizeWordsArray(words, wordCapacities, maxWords);
            }
        }
    }
    words[wordIndex][charIndex] = L'\0';
    int wordCount = wordIndex + 1;

    // Обмен нечетных и четных слов
    swapOddEvenWords(words, wordCount);

    // Вывод результата
    std::wcout << L"Результат:\n";
    for (int i = 0; i < wordCount; ++i) {
        std::wcout << words[i] << L" ";
    }
    std::wcout << std::endl;

    // Освобождение памяти
    delete[] arr;
    for (int i = 0; i < maxWords; ++i) {
        delete[] words[i];
    }
    delete[] words;
    delete[] wordCapacities;

    return 0;
}
