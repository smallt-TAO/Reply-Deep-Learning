#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int gapInVector(vector<int> numbers) {
        int mi = numbers[0];
        int res = 0;

        for (int i = 1; i < numbers.size(); ++i) {
            res = max(res, numbers[i] - mi);
            mi = min(mi, numbers[i]);
        }

        return res;
    }
};

int main() {
    int a[] = {2, 3, 6, 34, 89};
    vector<int> vec(a, a + 5);

    Solution sol;
    cout << sol.gapInVector(vec) << endl;

    return 0;
}

