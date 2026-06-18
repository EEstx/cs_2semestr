#include "list.h" 
#include <math.h>
#define EPS 1e-15

void add(list_elem*& border, long long value) {
    auto new_el = new list_elem;
    new_el->value = value;
    if (!border) {
        border = new_el;
        new_el->next = border;
        new_el->prev = border;
        return;
    }

    auto last = border->prev;
    border->prev = new_el;
    new_el->next = border;
    new_el->prev = last;
    last->next = new_el;
}

void add(list& lst, long long value) {
    add(lst.border, value);
}

void clear(list& lst) {
    if (lst.border == nullptr) {
        return;
    }
    list_elem* curr = lst.border;
    do {
        list_elem* next = curr->next;
        delete curr;
        curr = next;
    } while (curr != lst.border);
    lst.border = nullptr;
}
