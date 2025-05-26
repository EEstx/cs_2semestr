#include <iostream>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

struct MaxResults {
    int exact5 = INT_MIN;    // Для задачи 1
    int upTo5 = INT_MIN;     // Для задачи 2
    int over5 = INT_MIN;     // Для задачи 3
};

MaxResults processData(const string& filename) {
    ifstream file(filename);
    int n;
    if (!(file >> n) || n <= 5) {
        cerr << "Invalid input" << endl;
        exit(1);
    }

    MaxResults result;
    queue<int> last5;        // Хранит последние 5 элементов для задачи 2
    int maxPrev = INT_MIN;    // Максимум из элементов старше 5 секунд
    int pos = 0;             // Текущая позиция

    int current;
    while (file >> current) {
        pos++;

        // Задача 1: ровно 5 секунд разницы
        if (pos > 5) {
            int prev = last5.front();
            result.exact5 = max(result.exact5, prev + current);
        }

        // Задача 2: не более 5 секунд разницы
        if (!last5.empty()) {
            int localMax = current + last5.back(); // Проверяем с последним в очереди
            result.upTo5 = max(result.upTo5, localMax);
        }

        // Задача 3: более 5 секунд разницы
        if (maxPrev != INT_MIN) {
            result.over5 = max(result.over5, current + maxPrev);
        }

        // Обновляем историю для следующих итераций
        if (pos > 5) {
            maxPrev = max(maxPrev, last5.front());
            last5.pop();
        }

        last5.push(current);
    }

    return result;
}

int main() {
    MaxResults res = processData("queue.dat");
    cout << "1. Максимальная сумма (разница 5 сек): " << res.exact5 << endl;
    cout << "2. Максимальная сумма (разница ≤5 сек): " << res.upTo5 << endl;
    cout << "3. Максимальная сумма (разница >5 сек): " << res.over5 << endl;
    return 0;
}