#include <iostream>

using namespace std;

class Solution {
public:
    int numberOfOneBetween1N(int n) {
        int count = 0;

        long i = 1;
        long current, before, after;

        while ((n / i)) {
            current = (n / i) % 10;
            after = n - (n / i) * i;
            before = n / (i * 10);

            cout << before << current << after << endl;

            if (current > 1) {
                count += (before + 1) * i;
            }
            else if (current == 0) {
                count += before * i;
            }
            else if (current == 1) {
                count += before * i + after + 1;
            }

            i *= 10;
        }

        return count;
    }
};

int main() {
    Solution sol;
    cout << sol.numberOfOneBetween1N(345) << endl;

    return 0;
}



