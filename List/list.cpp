// list.cpp (модифицированные функции)
#include "list.h"

// Проверка наличия элемента в списке
bool contains(const list_elem* list, const string& value) {
    const list_elem* curr = list;
    while (curr != nullptr) {
        if (curr->value == value) return true;
        curr = curr->next;
    }
    return false;
}

// Модифицированная функция add
void add(list_elem*& list, string value) {
    if (contains(list, value)) return; // Пропуск дубликата
    auto new_el = new list_elem;
    new_el->value = value;
    list_elem* curr = list;
    while (curr && curr->next) {
        curr = curr->next;
    }
    if (curr) curr->next = new_el;
    else list = new_el;
}

// Модифицированная функция insert
bool insert(list_elem*& list, string value, int position) {
    if (contains(list, value)) return false; // Дубликат не вставляется
    if (position < 0 || position > count(list)) return false;
    auto new_el = new list_elem;
    new_el->value = value;
    if (position == 0) {
        new_el->next = list;
        list = new_el;
        return true;
    }
    auto curr = list;
    int i = 1;
    while (i++ < position && curr->next) {
        curr = curr->next;
    }
    new_el->next = curr->next;
    curr->next = new_el;
    return true;
}


// main.cpp (пример вызова)
int main() {
    list_elem* myList = nullptr;
    add(myList, "Иванов");
    add(myList, "Петров");
    insert(myList, "Иванов", 1); // Не будет вставлен (дубликат)
    insert(myList, "Сидоров", 2); // Успешная вставка
    // ...
    clear(myList);
    return 0;
}

// Остальные функции остаются без изменений