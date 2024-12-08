#include <iostream>
#include <map>
#include "MyContainer.h" // ���������� ��������� ���������

// ������� ��� ���������� ����������
int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // 1) �������� ���������� std::map<int, int>
    std::map<int, int> standardMap;

    // 2) ���������� 10 ����������, ��� ���� � ��� ����� �� 0 �� 9, � �������� � ��������� �����
    for (int i = 0; i < 10; ++i) {
        standardMap[i] = factorial(i);
    }

    // 3) �������� ���������� std::map<int, int> � ����� �����������, ������������ 10 ����������
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> customMap;

    // 4) ���������� 10 ����������, ��� ���� � ��� ����� �� 0 �� 9, � �������� � ��������� �����
    for (int i = 0; i < 10; ++i) {
        customMap[i] = factorial(i);
    }

    // 5) ����� �� ����� ���� �������� (���� � �������� ��������� ��������)
    std::cout << "����������� �����:" << std::endl;
    for (const auto& pair : standardMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << "\n��������� �����:" << std::endl;
    for (const auto& pair : customMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    // 6) �������� ���������� ������ ���������� ��� �������� �������� ���� int
    MyContainer<int> myContainer;

    // 7) ���������� 10 ���������� �� 0 �� 9
    for (int i = 0; i < 10; ++i) {
        myContainer.push_back(i);
    }

    // 8) �������� ���������� ������ ���������� ��� �������� �������� ���� int � ����� �����������, ������������ 10 ����������
    MyContainer<int, CustomAllocator<int>> customContainer;

    // 9) ���������� 10 ���������� �� 0 �� 9
    for (int i = 0; i < 10; ++i) {
        customContainer.push_back(i);
    }

    // 10) ����� �� ����� ���� ��������, ���������� � ����������
    std::cout << "\n��� ���������:" << std::endl;
    for (auto it = myContainer.begin(); it != myContainer.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "��������� ���������:" << std::endl;
    for (auto it = customContainer.begin(); it != customContainer.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
