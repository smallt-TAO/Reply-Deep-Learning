#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void reOrderArray(vector<int> &vec) {
        vector<int> temp;

        for (int i = 0; i < vec.size(); ) {
            if (vec[i] % 2 == 0) {
                temp.push_back(vec[i]);
                vec.erase(vec.begin() + i);
            }
            else {
                ++i;
            }
        }

        for (auto a : temp) {
            vec.push_back(a);
        }
    }
};

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7};
    vector<int> vec(a, a + 7);

    Solution sol;
    sol.reOrderArray(vec);

    for (auto a : vec) {
        cout << a << " ";
    }
    cout << endl;
}

