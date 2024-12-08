#include <iostream>
#include <map>
#include "MyContainer.h" // Подключаем кастомный контейнер

// Функция для вычисления факториала
int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

int main() {
    setlocale(LC_ALL, "Russian");

    // 1) Создание экземпляра std::map<int, int>
    std::map<int, int> standardMap;

    // 2) Заполнение 10 элементами, где ключ – это число от 0 до 9, а значение – факториал ключа
    for (int i = 0; i < 10; ++i) {
        standardMap[i] = factorial(i);
    }

    // 3) Создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
    std::map<int, int, std::less<int>, CustomAllocator<std::pair<const int, int>>> customMap;

    // 4) Заполнение 10 элементами, где ключ – это число от 0 до 9, а значение – факториал ключа
    for (int i = 0; i < 10; ++i) {
        customMap[i] = factorial(i);
    }

    // 5) Вывод на экран всех значений (ключ и значение разделены пробелом)
    std::cout << "Стандартная карта:" << std::endl;
    for (const auto& pair : standardMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    std::cout << "\nКастомная карта:" << std::endl;
    for (const auto& pair : customMap) {
        std::cout << pair.first << " " << pair.second << std::endl;
    }

    // 6) Создание экземпляра своего контейнера для хранения значений типа int
    MyContainer<int> myContainer;

    // 7) Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i) {
        myContainer.push_back(i);
    }

    // 8) Создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором, ограниченным 10 элементами
    MyContainer<int, CustomAllocator<int>> customContainer;

    // 9) Заполнение 10 элементами от 0 до 9
    for (int i = 0; i < 10; ++i) {
        customContainer.push_back(i);
    }

    // 10) Вывод на экран всех значений, хранящихся в контейнере
    std::cout << "\nМой контейнер:" << std::endl;
    for (auto it = myContainer.begin(); it != myContainer.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Кастомный контейнер:" << std::endl;
    for (auto it = customContainer.begin(); it != customContainer.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
