#include "Windows.h"
#include <iostream> //���� �����/������
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
        cerr << "�� ������� ��������� ������������ ����������" << endl;
        return EXIT_FAILURE;
    }

    CheckFunction checkFunction = (CheckFunction)GetProcAddress(load, "checkFunction");
    if (!checkFunction) {
        cerr << "�� ������� ����� �������" << endl;
        FreeLibrary(load);
        return EXIT_FAILURE;
    }

    string inputString;
    string charactersToFind;

    cout << "������� ������: ";
    getline(std::cin, inputString);

    cout << "������� ������� ��� ������: ";
    getline(std::cin, charactersToFind);

    bool result = checkFunction(inputString.c_str(), charactersToFind.c_str());

    cout << "���������: " << (result ? "true" : "false") << endl;

    FreeLibrary(load);

    return EXIT_SUCCESS;
}