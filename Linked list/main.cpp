#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "list.h"
using namespace std;

// Helper function to remove leading zeros
string remove_leading_zeros(const string& s) {
    if (s.empty()) return "0";
    size_t start = s.find_first_not_of('0');
    if (start == string::npos) {
        return "0";
    }
    return s.substr(start);
}

// Convert string to list of 9-digit blocks
list string_to_list(string s) {
    s = remove_leading_zeros(s);
    list lst;
    if (s == "0") {
        add(lst, 0);
        return lst;
    }

    int len = s.length();
    int i = len;
    while (i > 0) {
        int start_index = (i - 9 >= 0) ? i - 9 : 0;
        string block_str = s.substr(start_index, i - start_index);
        long long block_val = stoll(block_str);
        add(lst, block_val);
        i -= 9;
    }
    return lst;
}

// Add two lists representing long numbers
list add_lists(const list& a, const list& b) {
    list result;
    if (a.border == nullptr && b.border == nullptr) {
        add(result, 0);
        return result;
    }

    long long carry = 0;
    list_elem* pa = a.border;
    list_elem* pb = b.border;
    bool a_finished = (a.border == nullptr);
    bool b_finished = (b.border == nullptr);

    while (!a_finished || !b_finished || carry) {
        long long val_a = 0;
        if (!a_finished) {
            val_a = pa->value;
            pa = pa->next;
            if (pa == a.border) {
                a_finished = true;
            }
        }

        long long val_b = 0;
        if (!b_finished) {
            val_b = pb->value;
            pb = pb->next;
            if (pb == b.border) {
                b_finished = true;
            }
        }

        long long total = val_a + val_b + carry;
        carry = total / 1000000000LL;
        long long block = total % 1000000000LL;
        add(result, block);
    }

    return result;
}

// Print the number stored in the list
void print_number(const list& lst) {
    if (lst.border == nullptr) {
        cout << 0;
        return;
    }

    vector<long long> blocks;
    list_elem* start = lst.border->prev;
    list_elem* curr = start;
    do {
        blocks.push_back(curr->value);
        curr = curr->prev;
    } while (curr != start);

    // Output the most significant block without leading zeros
    cout << blocks[0];

    // Output subsequent blocks with leading zeros
    for (int i = 1; i < blocks.size(); i++) {
        cout << setfill('0') << setw(9) << blocks[i];
    }
}

int main() {
    string num1, num2;
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter second number: ";
    cin >> num2;

    list list1 = string_to_list(num1);
    list list2 = string_to_list(num2);

    list result = add_lists(list1, list2);

    cout << "Result: ";
    print_number(result);
    cout << endl;

    clear(list1);
    clear(list2);
    clear(result);

    return 0;
}