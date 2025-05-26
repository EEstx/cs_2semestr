#include <iostream>
#include <string>
using namespace std;

struct bracket_stack_elem {
    char type;
    int pos;
    bracket_stack_elem* next;
};

void push(bracket_stack_elem*& top, char type, int pos) {
    bracket_stack_elem* new_elem = new bracket_stack_elem;
    new_elem->type = type;
    new_elem->pos = pos;
    new_elem->next = top;
    top = new_elem;
}

bool pop(bracket_stack_elem*& top, bracket_stack_elem& elem) {
    if (top == nullptr) {
        return false;
    }
    elem = *top;
    bracket_stack_elem* old_top = top;
    top = top->next;
    delete old_top;
    return true;
}

void clearStack(bracket_stack_elem*& top) {
    while (top != nullptr) {
        bracket_stack_elem* temp = top;
        top = top->next;
        delete temp;
    }
}

bool isMatching(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '[' && close == ']') return true;
    if (open == '{' && close == '}') return true;
    if (open == '<' && close == '>') return true;
    return false;
}

void checkBrackets(const string& expr) {
    bracket_stack_elem* stack = nullptr;
    for (int i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{' || c == '<') {
            push(stack, c, i);
        } else if (c == ')' || c == ']' || c == '}' || c == '>') {
            bracket_stack_elem popped;
            if (!pop(stack, popped)) {
                cout << "Лишняя закрывающая скобка '" << c << "' на позиции " << i << endl;
                clearStack(stack);
                return;
            } else {
                if (!isMatching(popped.type, c)) {
                    cout << "Несоответствие скобок: '" << popped.type << "' на позиции " << popped.pos << " и '" << c << "' на позиции " << i << endl;
                    clearStack(stack);
                    return;
                }
            }
        }
    }
    bracket_stack_elem remaining;
    if (pop(stack, remaining)) {
        cout << "Лишняя открывающая скобка '" << remaining.type << "' на позиции " << remaining.pos << endl;
        clearStack(stack);
    } else {
        cout << "Скобки расставлены правильно" << endl;
    }
}

int main() {
    string expr;
    cout << "Введите выражение для проверки скобок: ";
    getline(cin, expr);
    checkBrackets(expr);
    return 0;
}