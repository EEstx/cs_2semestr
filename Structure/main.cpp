#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

struct Student {
    string surname;
    string name;
    int marks[4];
};

vector<string> split(const string &s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t");
    size_t end = s.find_last_not_of(" \t");
    if (start == string::npos)
        return "";
    else
        return s.substr(start, end - start + 1);
}

int main() {
    vector<Student> students;
    ifstream file("marks.csv");
    if (!file.is_open()) {
        cerr << "Не удалось открыть файл marks.csv" << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {
        vector<string> parts = split(line, ',');
        if (parts.size() != 6) continue;

        Student s;
        s.surname = trim(parts[0]);
        s.name = trim(parts[1]);
        for (int i = 0; i < 4; i++) {
            try {
                s.marks[i] = stoi(trim(parts[2 + i]));
            } catch (...) {
                cerr << "Ошибка чтения оценок для " << s.surname << endl;
                continue;
            }
        }
        students.push_back(s);
    }
    file.close();

    double averages[4] = {0};
    for (const auto& s : students) {
        for (int i = 0; i < 4; i++) {
            averages[i] += s.marks[i];
        }
    }
    for (double &avg : averages) avg /= students.size();

    cout << fixed << setprecision(2);
    cout << "Средний балл по алгебре: " << averages[0] << "\n"
         << "Средний балл по русскому языку: " << averages[1] << "\n"
         << "Средний балл по физике: " << averages[2] << "\n"
         << "Средний балл по истории: " << averages[3] << endl;

    int max_sum = 0;
    for (const auto& s : students) {
        int sum = s.marks[0] + s.marks[1] + s.marks[2] + s.marks[3];
        if (sum > max_sum) max_sum = sum;
    }
    cout << "Максимальная сумма баллов: " << max_sum << endl;

    vector<Student> top_students;
    for (const auto& s : students) {
        int sum = s.marks[0] + s.marks[1] + s.marks[2] + s.marks[3];
        if (sum == max_sum) top_students.push_back(s);
    }

    sort(top_students.begin(), top_students.end(), [](const Student& a, const Student& b) {
        return (a.surname == b.surname) ? (a.name < b.name) : (a.surname < b.surname);
    });

    cout << "Учащиеся с максимальной суммой баллов:\n";
    for (const auto& s : top_students) {
        cout << s.surname << " " << s.name << "\n";
    }

    int count = 0;
    for (const auto& s : students) {
        for (int mark : s.marks) {
            if (mark == 2) {
                count++;
                break;
            }
        }
    }
    cout << "Количество учащихся с хотя бы одной двойкой: " << count << endl;

    return 0;
}