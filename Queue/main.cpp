#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

vector<int> readData(const string& filename) {
    ifstream file(filename);
    vector<int> data;
    int n, num;
    if (file >> n) {
        for (int i = 0; i < n; ++i) {
            if (file >> num) {
                data.push_back(num);
            }
        }
    }
    return data;
}

// Задача 1: Ровно 5 секунд разницы (индексы i и i+5)
int findMaxSumExact5(const vector<int>& data) {
    int maxSum = INT_MIN;
    for (int i = 0; i < static_cast<int>(data.size()) - 5; ++i) {
        maxSum = max(maxSum, data[i] + data[i + 5]);
    }
    return maxSum;
}

// Задача 2: Не более 5 секунд (индексы i и j, где 1 ≤ j-i ≤ 5)
int findMaxSumUpTo5(const vector<int>& data) {
    int maxSum = INT_MIN;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = i + 1; j <= min(i + 5, static_cast<int>(data.size()) - 1); ++j) {
            maxSum = max(maxSum, data[i] + data[j]);
        }
    }
    return maxSum;
}

// Задача 3: Более 5 секунд (индексы i и j, где j-i > 5)
int findMaxSumOver5(const vector<int>& data) {
    int maxSum = INT_MIN;
    for (int i = 0; i < data.size(); ++i) {
        for (int j = i + 6; j < data.size(); ++j) {
            maxSum = max(maxSum, data[i] + data[j]);
        }
    }
    return maxSum;
}

int main() {
    vector<int> data = readData("queue.dat");
    if (data.size() <= 5) {
        cerr << "Ошибка: недостаточно данных (N ≤ 5)" << endl;
        return 1;
    }

    cout << "1. Максимальная сумма (разница 5 сек): " << findMaxSumExact5(data) << endl;
    cout << "2. Максимальная сумма (разница ≤5 сек): " << findMaxSumUpTo5(data) << endl;
    cout << "3. Максимальная сумма (разница >5 сек): " << findMaxSumOver5(data) << endl;

    return 0;
}