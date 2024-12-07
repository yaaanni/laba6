#include <gtest/gtest.h>
#include "task1.h"
#include "utils.h"
#include <iostream>
#include <clocale>
#include <locale>
#include <codecvt>
#include <string>

std::string program(const char* arr) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t result[81];
    int j = 0;

    if (strlen(arr) > 80) {
        return "Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n";
    }

    size_t len = std::mbstowcs(nullptr, arr, 0);
    wchar_t* w_arr = new wchar_t[len + 1];
    std::mbstowcs(w_arr, arr, len + 1);

    for (size_t k = 0; k < len; k++) {
        if (!iswalnum(w_arr[k]) && w_arr[k] != L',' && w_arr[k] != L'.' && w_arr[k] != L'+' && w_arr[k] != L'-') {
            delete[] w_arr;
            return "Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n";
        }
        if (iswdigit(w_arr[k])) {
            result[j++] = w_arr[k];
        }
    }
    result[j] = L'\0';

    delete[] w_arr;

    // Преобразование wstring в string
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    return converter.to_bytes(result);
}

TEST(SampleTest, Example) {
    const char arr[] = "a";
    EXPECT_EQ(program(arr), "");
}

TEST(SampleTest, Example2) {
    const char arr[] = "szexrdcfgvhbjnkmxrdcftvygbhunjsxrdfcvgbhjsxrdcftvgbhjnxsrdcftvgybxrdcftvvvvvvvvvvvvvvvvvvvvvdrxrrrcrdxrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrkmcijefvijvnrvnnfrnfjnfjvnvjnnjvnjndjnfjnjnvjnvjndjvjndjvndjdnjnjdnnvjn";
    EXPECT_EQ(program(arr), "Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n");
}

TEST(SampleTest, InvalidCharacters) {
    const char arr[] = "abc!@#";
    EXPECT_EQ(program(arr), "Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n");
}

TEST(SampleTest, Example3) {
    const char arr[] = "a3";
    EXPECT_EQ(program(arr), "3");
}

TEST(SampleTest, Example4) {
    const char arr[] = "ajgtee234hi";
    EXPECT_EQ(program(arr), "234");
}

TEST(SampleTest, Example5) {
    const char arr[] = "a++-345";
    EXPECT_EQ(program(arr), "345");
}

TEST(SampleTest, Exampl7) {
    const char arr[] = "a++пуккукпк-345";
    EXPECT_EQ(program(arr), "345");
}

TEST(SampleTest, Example8) {
    const char arr[] = "09809авовыв";
    EXPECT_EQ(program(arr), "09809");
}

TEST(SampleTest, Example9) {
    const char arr[] = "тотыо7вриырви7";
    EXPECT_EQ(program(arr), "77");
}

TEST(SampleTest, Example10) {
    const char arr[] = "kjgegrопк1";
    EXPECT_EQ(program(arr), "1");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
