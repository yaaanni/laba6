#include <gtest/gtest.h>
#include "utils.h"
#include <iostream>
#include <clocale>
#include <locale>
#include <codecvt>
#include <string>
#include <cwchar>

void swapWordsCompletely(wchar_t*& str1, wchar_t*& str2) {
    wchar_t* temp = str1;
    str1 = str2;
    str2 = temp;
}

void swapOddEvenWords(wchar_t** words, int wordCount) {
    for (int i = 0; i < wordCount - 1; i += 2) {
        swapWordsCompletely(words[i], words[i + 1]);
    }
}

void resizeWordsArray(wchar_t**& words, int*& wordCapacities, int& maxWords) {
    int newMaxWords = maxWords * 2; 
    wchar_t** newWords = new wchar_t*[newMaxWords];
    int* newWordCapacities = new int[newMaxWords];

    for (int i = 0; i < maxWords; ++i) {
        newWords[i] = words[i];
        newWordCapacities[i] = wordCapacities[i];
    }

    for (int i = maxWords; i < newMaxWords; ++i) {
        newWordCapacities[i] = 30; 
        newWords[i] = new wchar_t[newWordCapacities[i]];
    }

    delete[] words;
    delete[] wordCapacities;

    words = newWords;
    wordCapacities = newWordCapacities;
    maxWords = newMaxWords;
}

std::wstring program(const char* arr) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    size_t len = std::mbstowcs(nullptr, arr, 0);
    if (len == static_cast<size_t>(-1)) {
        return L"Ошибка преобразования строки.";
    }

    wchar_t* w_arr = new wchar_t[len + 1];
    std::mbstowcs(w_arr, arr, len + 1);

    for (size_t i = 0; i < len; ++i) {
        if (iswdigit(w_arr[i])) {
            delete[] w_arr;
            return L"Текст может содержать только буквы и пробелы. Повторите ввод:";
        }
    }

    int maxWords = 20; 
    wchar_t** words = new wchar_t*[maxWords];
    int* wordCapacities = new int[maxWords]; 
    for (int i = 0; i < maxWords; ++i) {
        wordCapacities[i] = 30; 
        words[i] = new wchar_t[wordCapacities[i]];
    }

    int wordIndex = 0;
    int charIndex = 0;
    for (int i = 0; w_arr[i] != L'\0'; ++i) {
        if (w_arr[i] != L' ') {
            if (charIndex == wordCapacities[wordIndex]) {
                wordCapacities[wordIndex] *= 2;
                wchar_t* newWordArr = new wchar_t[wordCapacities[wordIndex]];
                std::wmemcpy(newWordArr, words[wordIndex], charIndex);
                delete[] words[wordIndex];
                words[wordIndex] = newWordArr;
            }
            words[wordIndex][charIndex++] = w_arr[i];
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

    swapOddEvenWords(words, wordCount);

    std::wstring result;
    for (int i = 0; i < wordCount; ++i) {
        result += words[i];
        if (i < wordCount - 1) {
            result += L" ";
        }
    }

    delete[] w_arr;
    for (int i = 0; i < maxWords; ++i) {
        delete[] words[i];
    }
    delete[] words;
    delete[] wordCapacities;

    return result;
}

TEST(SampleTest, Example10) {
    const char arr[] = "пока привет";
    EXPECT_EQ(program(arr), L"привет пока");
}

TEST(SampleTest, InvalidInput) {
    const char arr[] = "пока привет 123";
    EXPECT_EQ(program(arr), L"Текст может содержать только буквы и пробелы. Повторите ввод:");
}

TEST(SampleTest, EmptyString) {
    const char arr[] = "";
    EXPECT_EQ(program(arr), L"");
}

TEST(SampleTest, SingleElement) {
    const char arr[] = "a";
    EXPECT_EQ(program(arr), L"a");
}

TEST(SampleTest, OnlySpaces) {
    const char arr[] = "     ";
    EXPECT_EQ(program(arr), L"     ");
}

TEST(SampleTest, test4) {
    const char arr[] = "колодец машина бутерброд гайка";
    EXPECT_EQ(program(arr), L"машина колодец гайка бутерброд");
}

TEST(SampleTest, test3) {
    const char arr[] = "колодец машина бутерброд";
    EXPECT_EQ(program(arr), L"машина колодец бутерброд");
}

TEST(SampleTest, vanyayana) {
    const char arr[] = "Ваня Яна";
    EXPECT_EQ(program(arr), L"Яна Ваня");
}

TEST(SampleTest, test1) {
    const char arr[] = "hello world";
    EXPECT_EQ(program(arr), L"world hello");
}

// Тест на строку с миллионом пробелов
TEST(SampleTest, MillionSpaces) {
    std::string long_string(1000000, ' ');
    EXPECT_EQ(program(long_string.c_str()), std::wstring(1000000, L' '));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
