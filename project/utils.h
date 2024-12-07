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

#endif // UTILS_H
