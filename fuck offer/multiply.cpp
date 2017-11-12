#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> multiply(vector<int> numbers) {
        int temp = 1;
        
        vector<int> res(numbers.size());
        for (int i = 0; i < numbers.size(); ++i) {
            res[i] = temp;
            temp *= numbers[i];
        }

        for (int temp = 1, i = numbers.size() - 1; i >= 0; --i) {
            res[i] *= temp;
            temp *= numbers[i];
        }

        return res;
    }
};


int main() {
    int a[] = {2, 3, 6};
    vector<int> vec(a, a + 3);

    Solution sol;
    vec = sol.multiply(vec);
    for (auto s : vec) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}

