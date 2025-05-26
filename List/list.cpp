#include "list.h"


void addSort(list_elem*& list, string value) 
{
	auto new_el = new list_elem;
	new_el->value = value;
	list_elem* curr = list;
	while (curr && curr->next && value > curr->next->value) {
		curr = curr->next;
	}
	if (curr) {
		if (value > curr->value) {
			new_el->next = curr->next;
			curr->next = new_el;
		}
		else {
			new_el->next = curr;
			list = new_el;
		}
	}
	else list = new_el;
}


bool get(const list_elem* list, int position, string& result)
{
	if (position < 0 || position >= count(list)) return false;
	if (position == 0) {
		result = list->value;
		return true;
	}
	auto curr = list->next;
	auto i = 1;
	while (i++ < position && curr->next) {
		curr = curr->next;
	}
	result = curr->value;
	return true;
}

int count(const list_elem* list)
{
	if (!list) return 0;
	auto curr = list;
	int i = 1;
	while (curr->next) {
		curr = curr->next;
		i++;
	}
	return i;
}

bool remove(list_elem*& list, int position)
{
	if (position < 0 || position >= count(list)) return false;
	if (position == 0) {
		auto old = list;
		list = list->next;
		delete old;
		return true;
	}
	auto curr = list;
	auto i = 0;
	while (++i < position && curr->next) {
		curr = curr->next;
	}
	auto old = curr->next;
	if (curr->next) curr->next = curr->next->next;
	delete old;
	return true;
}

void clear(list_elem*& list)
{
	auto curr = list;
	while (curr) {
		auto rem = curr;
		curr = curr->next;
		delete rem;
	}
	list = nullptr;
}

// ДОБАВИЛ

void add(list_elem*& list, string value)
{
    // Проверка на существование значения
    list_elem* curr_check = list;
    while (curr_check != nullptr) {
        if (curr_check->value == value) {
            return; // Значение уже существует, не добавляем
        }
        curr_check = curr_check->next;
    }

    auto new_el = new list_elem;
    new_el->value = value;
    list_elem* curr = list;
    while (curr && curr->next) {
        curr = curr->next;
    }
    if (curr) curr->next = new_el;
    else list = new_el;
}

bool insert(list_elem*& list, string value, int position)
{
    // Проверка на существование значения
    list_elem* curr_check = list;
    while (curr_check != nullptr) {
        if (curr_check->value == value) {
            return false; // Значение уже существует
        }
        curr_check = curr_check->next;
    }

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