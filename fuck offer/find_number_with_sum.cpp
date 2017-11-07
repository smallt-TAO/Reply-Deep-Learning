#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findNumberWithSum(vector<int> array, int target) {
        vector<int> res;

        if (array.size() < 2) {
            return res;
        }

        int start = 0;
        int end = array.size() - 1;
        int temp;

        while (start < end) {
            temp = array[start] + array[end];
            if (temp == target) {
                res.push_back(array[start]);
                res.push_back(array[end]);
                break;
            }
            else if (temp < target) {
                start++;
            }
            else {
                end--;
            }
        }

        return res;
    }
};

int main() {
    int a[] = {2, 3, 5, 9};
    vector<int> res(a, a + 4);

    Solution sol;
    vector<int> re = sol.findNumberWithSum(res, 8);
    for (auto r : re) {
        cout << r << " ";
    }
    cout << endl;

    return 0;
}


