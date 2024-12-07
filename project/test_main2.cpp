#include <gtest/gtest.h>
#include "task1.h"
#include "utils.h"
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

std::string program(const char* arr, const std::string& del_str) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    // Преобразование строки в широкую строку
    size_t len = std::mbstowcs(nullptr, arr, 0);
    if (len == static_cast<size_t>(-1)) {
        return "Ошибка преобразования строки.";
    }

    wchar_t* w_arr = new wchar_t[len + 1];
    std::mbstowcs(w_arr, arr, len + 1);

    // Проверка на наличие цифр в широкой строке
    for (size_t i = 0; i < len; ++i) {
        if (iswdigit(w_arr[i])) {
            delete[] w_arr;
            return "Неверный ввод: строка содержит цифры.";
        }
    }

    // Преобразование символа для удаления в широкий символ
    wchar_t w_del;
    size_t del_len = std::mbstowcs(&w_del, del_str.c_str(), del_str.size());
    if (del_len != 1 || iswdigit(w_del)) {
        delete[] w_arr;
        return "Неверный ввод: символ для удаления является цифрой.";
    }

    // Удаление символа из строки
    removeChar(w_arr, w_del);

    // Преобразование широкой строки обратно в std::string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string result = converter.to_bytes(w_arr);

    delete[] w_arr;

    return result;
}

TEST(SampleTest, Example1) {
    const char arr[] = "kjgegrопк";
    std::string del = "k";
    EXPECT_EQ(program(arr, del), "jgegrопк");
}

TEST(SampleTest, InvalidString) {
    const char arr[] = "kjgegrопк123";
    std::string del = "k";
    EXPECT_EQ(program(arr, del), "Неверный ввод: строка содержит цифры.");
}

TEST(SampleTest, InvalidCharToDelete) {
    const char arr[] = "kjgegrопк";
    std::string del = "3";
    EXPECT_EQ(program(arr, del), "Неверный ввод: символ для удаления является цифрой.");
}

TEST(SampleTest, MillionCharactersTest) {
    std::string long_string(1000000, 'a');
    std::string del = "a";
    EXPECT_EQ(program(long_string.c_str(), del), "");
}

TEST(SampleTest, Example5) {
    const char arr[] = "привет";
    std::string del = "п";
    EXPECT_EQ(program(arr, del), "ривет");
}

TEST(SampleTest, Example6) {
    const char arr[] = "ляляля";
    std::string del = "я";
    EXPECT_EQ(program(arr, del), "ллл");
}

TEST(SampleTest, Example7) {
    const char arr[] = "рарара";
    std::string del = "х";
    EXPECT_EQ(program(arr, del), "рарара");
}

TEST(SampleTest, Example8) {
    const char arr[] = "meow";
    std::string del = "m";
    EXPECT_EQ(program(arr, del), "eow");
}

TEST(SampleTest, Example9) {
    const char arr[] = "мяу";
    std::string del = "у";
    EXPECT_EQ(program(arr, del), "мя");
}

TEST(SampleTest, Example10) {
    const char arr[] = "ашршаруша";
    std::string del = "е";
    EXPECT_EQ(program(arr, del), "ашршаруша");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
