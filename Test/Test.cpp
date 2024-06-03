#include "Windows.h"
#include <iostream> //библ ввода/вывода
#include <string>
using namespace std;

typedef bool (*CheckFunction)(const char*, const char*);

int main() {
    SetConsoleCP(1251);
    setlocale(LC_ALL, "Russian");
    string inputStr;
    string inputChars;

    HINSTANCE load = LoadLibrary(L"DynamicLib.dll");
    if (load == NULL) {
        cerr << "Не удалось загрузить динамическую библиотеку" << endl;
        return EXIT_FAILURE;
    }

    CheckFunction checkFunction = (CheckFunction)GetProcAddress(load, "checkFunction");
    if (!checkFunction) {
        cerr << "Не удалось найти функцию" << endl;
        FreeLibrary(load);
        return EXIT_FAILURE;
    }

    string inputString;
    string charactersToFind;

    cout << "Введите строку: ";
    getline(std::cin, inputString);

    cout << "Введите символы для поиска: ";
    getline(std::cin, charactersToFind);

    bool result = checkFunction(inputString.c_str(), charactersToFind.c_str());

    cout << "Результат: " << (result ? "true" : "false") << endl;

    FreeLibrary(load);

    return EXIT_SUCCESS;
}