#include "utils.h"
#include <limits>

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



    //task1
    void Task::task1() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t el;
    wchar_t arr[81];
    wchar_t result[81];
    int i = 0;

    inputStringSecond(arr, el, i);

    while (i >= 80 || !validateStringSecond(arr, i)) {
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
//task2
void Task::task2() {
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
            std::wcin.clear(); 
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

//task3
void Task::task3() {
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int size = 0;
    int capacity = 0;
    wchar_t* arr = nullptr;

    inputArr(arr, size, capacity);

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
}



//task2
void Task::removeChar(wchar_t* arr, wchar_t del) {
    int j = 0;
    for (int i = 0; arr[i] != L'\0'; i++) {
        if (arr[i] != del) {
            arr[j++] = arr[i];
        }
    }
    arr[j] = L'\0';
}
//task3
// Функция для обмена местами двух строк полностью
void Task::swapWordsCompletely(wchar_t*& str1, wchar_t*& str2) {
    wchar_t* temp = str1;
    str1 = str2;
    str2 = temp;
}

// Функция для обмена нечетных и четных слов
void Task::swapOddEvenWords(wchar_t** words, int wordCount) {
    for (int i = 0; i < wordCount - 1; i += 2) {
        swapWordsCompletely(words[i], words[i + 1]);
    }
}

// Функция для увеличения размера массива слов
void Task::resizeWordsArray(wchar_t**& words, int*& wordCapacities, int& maxWords) {
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