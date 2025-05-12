// list.h (дополнено)
#pragma once
#include <string>
using namespace std;

struct list_elem {
    string value;
    list_elem* next = nullptr;
};

bool contains(const list_elem* list, const string& value); // Новая функция
void add(list_elem*& list, string value);
bool insert(list_elem*& list, string value, int position);
// Остальные объявления функций остаются без изменений