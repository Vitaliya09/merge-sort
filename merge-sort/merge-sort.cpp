#include "merge-sort.hpp"
#include <memory>

List::List(std::initializer_list<int> list) {
    // Задание №1: сделать список из list
    ListElement* tail = nullptr;
    for (auto number : list) {
        if (tail == nullptr) {
            // Создаем первый элемент списка в head
            head = std::make_unique<ListElement>(number);
            tail = head.get();
        } else {
            // Создаем элемент списка в tail->next
            tail->next = std::make_unique<ListElement>(number);
            tail = tail->next.get();
        }
    }
}

auto merge(List a, List b) noexcept -> List {
    // Слияние двух упорядоченных списков
    List result;
    ListElement* tail = nullptr; // должен указывать на последний элемент списка result

    while (a.head && b.head) {
        ListElement* smaller;
        if (a.head->value <= b.head->value) {
            // Берем элемент из списка a
            smaller = a.head.release();
            a.head = std::move(smaller->next);
        } else {
            // Берем элемент из списка b
            smaller = b.head.release();
            b.head = std::move(smaller->next);
        }

        if (result.head == nullptr) {
            // Создаем первый элемент списка result
            result.head = std::unique_ptr<ListElement>(smaller);
            tail = result.head.get();
        } else {
            // Добавляем элемент в конец списка result
            tail->next = std::unique_ptr<ListElement>(smaller);
            tail = tail->next.get();
        }
    }

    // Переносим оставшийся список в конец result
    tail->next = (a.head) ? std::move(a.head) : std::move(b.head);
    return result;
}

auto mergesort(List& list) noexcept -> void {
    // Сортировка слиянием
    if (!list.head || !list.head->next) {
        // Базовый случай: список пуст или содержит один элемент
        return;
    }

    // 1. Определяем середину списка (см. ветку list-algo семинаров)
    ListElement* middle = nullptr;
    ListElement* slow = list.head.get();
    ListElement* fast = list.head->next.get();

    while (fast && fast->next) {
        slow = slow->next.get();
        fast = fast->next->next.get();
    }

    // 2. Переносим вторую половину в новый список
    List second;
    second.head = std::move(slow->next);
    slow->next = nullptr;

    // 3. Для каждой половины запускаем mergesort
    mergesort(list);
    mergesort(second);

    // 4. Делаем merge от результатов, не забыв std::move в аргументах,
    // присваивая результат в list
    list = merge(std::move(list), std::move(second));
}
