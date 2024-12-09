#include <gtest/gtest.h>
#include <iostream>
#include <clocale>
#include <locale>
#include <string>

// Функция для обработки строки изначально работающая с wchar_t
std::wstring program(const wchar_t* arr) {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    wchar_t result[81];
    int j = 0;

    if (wcslen(arr) > 80) {
        return L"Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n";
    }

    size_t len = wcslen(arr);
    wchar_t* w_arr = new wchar_t[len + 1];
    wmemcpy(w_arr, arr, len + 1);

    for (size_t k = 0; k < len; k++) {
        if (!iswalnum(w_arr[k]) && w_arr[k] != L',' && w_arr[k] != L'.' && w_arr[k] != L'+' && w_arr[k] != L'-') {
            delete[] w_arr;
            return L"Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n";
        }
        if (iswdigit(w_arr[k])) {
            result[j++] = w_arr[k];
        }
    }
    result[j] = L'\0';

    delete[] w_arr;

    return std::wstring(result);
}

TEST(SampleTest, Example) {
    const wchar_t arr[] = L"a";
    EXPECT_EQ(program(arr), L"");
}

TEST(SampleTest, Example2) {
    const wchar_t arr[] = L"szexrdcfgvhbjnkmxrdcftvygbhunjsxrdfcvgbhjsxrdcftvgbhjnxsrdcftvgybxrdcftvvvvvvvvvvvvvvvvvvvvvdrxrrrcrdxrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrkmcijefvijvnrvnnfrnfjnfjvnvjnnjvnjndjnfjnjnvjnvjndjvjndjvndjdnjnjdnnvjn";
    EXPECT_EQ(program(arr), L"Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n");
}

TEST(SampleTest, InvalidCharacters) {
    const wchar_t arr[] = L"abc!@#";
    EXPECT_EQ(program(arr), L"Строка принимает буквы, цифры, запятые, точки, знаки + и -, и не более 80 символов.\n");
}

TEST(SampleTest, Example3) {
    const wchar_t arr[] = L"a3";
    EXPECT_EQ(program(arr), L"3");
}

TEST(SampleTest, Example4) {
    const wchar_t arr[] = L"ajgtee234hi";
    EXPECT_EQ(program(arr), L"234");
}

TEST(SampleTest, Example5) {
    const wchar_t arr[] = L"a++-345";
    EXPECT_EQ(program(arr), L"345");
}

TEST(SampleTest, Exampl7) {
    const wchar_t arr[] = L"a++пуккукпк-345";
    EXPECT_EQ(program(arr), L"345");
}

TEST(SampleTest, Example8) {
    const wchar_t arr[] = L"09809авовыв";
    EXPECT_EQ(program(arr), L"09809");
}

TEST(SampleTest, Example9) {
    const wchar_t arr[] = L"тотыо7вриырви7";
    EXPECT_EQ(program(arr), L"77");
}

TEST(SampleTest, Example10) {
    const wchar_t arr[] = L"kjgegrопк1";
    EXPECT_EQ(program(arr), L"1");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
