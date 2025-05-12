#include <iostream>
#include <string>

using namespace std;

struct StackElem {
    char bracketType;
    int position;
    StackElem* next;
};

void push(StackElem*& top, char bracket, int pos) {
    StackElem* newElem = new StackElem;
    newElem->bracketType = bracket;
    newElem->position = pos;
    newElem->next = top;
    top = newElem;
}

StackElem pop(StackElem*& top) {
    StackElem elem;
    if (top) {
        elem.bracketType = top->bracketType;
        elem.position = top->position;
        StackElem* temp = top;
        top = top->next;
        delete temp;
    }
    return elem;
}

bool isMatching(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}') ||
           (open == '<' && close == '>');
}

void checkBrackets(const string& expr) {
    StackElem* stack = nullptr;
    for (int i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (c == '(' || c == '[' || c == '{' || c == '<') {
            push(stack, c, i);
        } else if (c == ')' || c == ']' || c == '}' || c == '>') {
            if (!stack) {
                cout << "Лишняя закрывающая скобка на позиции: " << i << endl;
                return;
            }
            StackElem lastOpen = pop(stack);
            if (!isMatching(lastOpen.bracketType, c)) {
                cout << "Несоответствие скобок: " 
                     << lastOpen.position << " и " << i << endl;
                return;
            }
        }
    }
    if (stack) {
        StackElem extra = pop(stack);
        cout << "Лишняя открывающая скобка на позиции: " << extra.position << endl;
    } else {
        cout << "Скобки расставлены верно!" << endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    string expr;
    cout << "Введите выражение: ";
    getline(cin, expr);
    checkBrackets(expr);
    return 0;
}