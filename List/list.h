#pragma once
#include <string>
using namespace std;

struct list_elem
{
	string value;
	list_elem* next = nullptr;
};

void add(list_elem*& list, string value);
bool insert(list_elem*& list, string value, int position);
bool get(const list_elem* list, int position, string& result);
int count(const list_elem* list);
bool remove(list_elem*& list, int position);
void clear(list_elem*& list);
void addSort(list_elem*& list, string value);
