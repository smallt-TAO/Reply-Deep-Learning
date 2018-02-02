#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    public:
    vector<int> twoSum(vector<int>& array, int target) {
        vector<int> res;
        unordered_map<int, int> temp;

        for (int i = 0; i < array.size(); ++i) {
            // Found in map, return them.
            if (temp.find(target - array[i]) != temp.end()) {
                res.push_back(temp[target - array[i]]);
                res.push_back(i);
                return res;
                }
            // Number is NOT found, put it in the unordered_map.
            temp[array[i]] = i;
        }
    return res;
    }
};

int main() {
    int a[] = {2, 3, 4, 5};
    vector<int> arr(a, a + 4);

    Solution sol;
    vector<int> res = sol.twoSum(arr, 7);

    // print the result.
    for (auto a : res) {
        cout << a << " ";
    }
    cout << endl;

    return 0;
}

