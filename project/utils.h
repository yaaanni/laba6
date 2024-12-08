#ifndef UTILS_H
#define UTILS_H

#include <cwchar>
#include <iostream>
#include <cwctype>

void inputStringSecond(wchar_t* arr, wchar_t &el, int &i);
bool validateStringSecond(const wchar_t* arr, int length);
bool validateString(const wchar_t* arr, int length);
void inputArr(wchar_t*& arr, int& size, int& capacity);
void inputString(wchar_t* arr, wchar_t &el, int &i);

class Task {
public:
    void task1();
    void task2();
    void task3();

private:
    void removeChar(wchar_t* arr, wchar_t del);
    void swapWordsCompletely(wchar_t*& str1, wchar_t*& str2);
    void swapOddEvenWords(wchar_t** words, int wordCount);
    void resizeWordsArray(wchar_t**& words, int*& wordCapacities, int& maxWords);
};

#endif // UTILS_H
