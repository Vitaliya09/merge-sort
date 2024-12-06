#include "merge-sort.hpp"
#include <iostream>

// Функция для вывода списка
void print_list(List const& list) {
    auto* current = list.head.get();
    while (current) {
        std::cout << current->value << " ";
        current = current->next.get();
    }
    std::cout << std::endl;
}

int main() {
    // Тестирование конструктора
    List list1{3, 1, 4, 1, 5};
    std::cout << "Исходный список 1: ";
    print_list(list1);

    List list2{9, 2, 6, 5, 3};
    std::cout << "Исходный список 2: ";
    print_list(list2);

    // Тестирование слияния
    List merged = merge(std::move(list1), std::move(list2));
    std::cout << "Результат слияния: ";
    print_list(merged);

    // Тестирование сортировки
    List unsorted{3, 1, 4, 1, 5, 9, 2, 6, 5, 3};
    std::cout << "Несортированный список: ";
    print_list(unsorted);

    mergesort(unsorted);
    std::cout << "Сортированный список: ";
    print_list(unsorted);

    return 0;
}
