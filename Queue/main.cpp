#include <iostream>
#include <fstream>
#include <climits>
#include <queue>

using namespace std;

struct MaxResults {
    int exact5 = INT_MIN;
    int upTo5 = INT_MIN;
    int over5 = INT_MIN;
};

MaxResults processData(const string& filename) {
    ifstream file(filename);
    int n;
    if (!(file >> n) || n <= 5) {
        cerr << "Invalid input" << endl;
        exit(1);
    }

    MaxResults result;
    queue<int> last5;
    int maxPrev = INT_MIN;
    int pos = 0;

    int current;
    while (file >> current) {
        pos++;

        if (pos > 5) {
            int prev = last5.front();
            result.exact5 = max(result.exact5, prev + current);
        }

        if (!last5.empty()) {
            int localMax = current + last5.back();
            result.upTo5 = max(result.upTo5, localMax);
        }

        if (maxPrev != INT_MIN) {
            result.over5 = max(result.over5, current + maxPrev);
        }

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