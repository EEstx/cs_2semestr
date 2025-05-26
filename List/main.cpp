#include <iostream>
#include <fstream>
#include "list.h"

using namespace std;
void show_list(list_elem* lst) {
	auto curr = lst;
	cout << "Состав списка:" << endl;
	int i = 0;
	while (curr) {
		cout << ++i << ". " << curr->value << endl;
		curr = curr->next;
	}
	cout << endl;
}
int main() {
	setlocale(LC_ALL, "");

	ifstream f("students.txt");
	if (f) {
		list_elem* lst = nullptr;
		while (!f.eof()) {
			string product;
			getline(f, product);
			add(lst, product);
		}
		f.close();
		// Ввывод содержания списка
		show_list(lst);
		auto curr = lst;
		list_elem* lst_403 = nullptr;
		list_elem* lst_404 = nullptr;
		while (curr) {
			string value = curr->value;
			int pos = value.find(" ");
			if (value.substr(0, pos) == "05-403")
				addSort(lst_403, value);
			else
				addSort(lst_404, value);
			curr = curr->next;
		}
		show_list(lst_403);
		show_list(lst_404);
	}
	else {
		cout << "Списка нет." << endl;
	}
    return 0;
}