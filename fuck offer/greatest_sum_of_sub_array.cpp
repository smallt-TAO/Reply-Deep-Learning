#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    int greatestSumOfSubArray(vector<int> number) {
        int res = 0;

        if (number.empty()) {
            return res;
        }

        int sum = 0;
        for (auto n : number) {
            if (sum >= 0) {
                sum += n;
            }
            else {
                sum = n;
            }

            res = max(sum, res);
        }

        return res;
    }
};


int main() {
    int a[] = {2, -3, 4, 5, -2, 6, 9};
    vector<int> vec(a, a + 7);

    Solution sol;
    cout << sol.greatestSumOfSubArray(vec) << endl;

    return 0;
}

