#include <gtest/gtest.h>
#include <iostream>
#include <clocale>
#include <locale>
#include <codecvt>
#include <string>
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

std::wstring program(const wchar_t* arr, const std::wstring& del_str) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    size_t len = std::wcslen(arr);
    wchar_t* w_arr = new wchar_t[len + 1];
    std::wmemcpy(w_arr, arr, len + 1);//копирует из многобайтовой строки в широкую

    for (size_t i = 0; i < len; ++i) {
        if (iswdigit(w_arr[i])) {
            delete[] w_arr;
            return L"Неверный ввод: строка содержит цифры.";
        }
    }

    if (del_str.size() != 1 || iswdigit(del_str[0])) {
        delete[] w_arr;
        return L"Неверный ввод: символ для удаления является цифрой.";
    }

    wchar_t w_del = del_str[0];
    removeChar(w_arr, w_del);

    std::wstring result(w_arr);//обратное преобразование
    delete[] w_arr;

    return result;
}

TEST(SampleTest, Example1) {
    const wchar_t arr[] = L"kjgegrопк";
    std::wstring del = L"k";
    EXPECT_EQ(program(arr, del), L"jgegrопк");
}

TEST(SampleTest, InvalidString) {
    const wchar_t arr[] = L"kjgegrопк123";
    std::wstring del = L"k";
    EXPECT_EQ(program(arr, del), L"Неверный ввод: строка содержит цифры.");
}

TEST(SampleTest, InvalidCharToDelete) {
    const wchar_t arr[] = L"kjgegrопк";
    std::wstring del = L"3";
    EXPECT_EQ(program(arr, del), L"Неверный ввод: символ для удаления является цифрой.");
}

TEST(SampleTest, MillionCharactersTest) {
    std::wstring long_string(1000000, L'a');
    std::wstring del = L"a";
    EXPECT_EQ(program(long_string.c_str(), del), L"");
}

TEST(SampleTest, Example5) {
    const wchar_t arr[] = L"привет";
    std::wstring del = L"п";
    EXPECT_EQ(program(arr, del), L"ривет");
}

TEST(SampleTest, Example6) {
    const wchar_t arr[] = L"ляляля";
    std::wstring del = L"я";
    EXPECT_EQ(program(arr, del), L"ллл");
}

TEST(SampleTest, Example7) {
    const wchar_t arr[] = L"рарара";
    std::wstring del = L"х";
    EXPECT_EQ(program(arr, del), L"рарара");
}

TEST(SampleTest, Example8) {
    const wchar_t arr[] = L"meow";
    std::wstring del = L"m";
    EXPECT_EQ(program(arr, del), L"eow");
}

TEST(SampleTest, Example9) {
    const wchar_t arr[] = L"мяу";
    std::wstring del = L"у";
    EXPECT_EQ(program(arr, del), L"мя");
}

TEST(SampleTest, Example10) {
    const wchar_t arr[] = L"ашршаруша";
    std::wstring del = L"е";
    EXPECT_EQ(program(arr, del), L"ашршаруша");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
