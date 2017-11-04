#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Solution {
public:
    static bool compare(const string &str1, const string &str2) {
        return str1 + str2 < str2 + str1;
    }

    string printMinNumber(vector<int> numbers) {
        if (numbers.empty()) {
            cout << "No number in vector" << endl;
        }
        vector<string> str;
        for (auto n : numbers) {
            str.push_back(to_string(n));
        }

        sort(str.begin(), str.end(), compare);

        string res = accumulate(str.begin(), str.end(), string(""));
        return res;
    }
};

int main() {
    int a[] = {233, 32, 342, 322};
    vector<int> vec(a, a + 4);

    Solution sol;
    cout << sol.printMinNumber(vec) << endl;

    return 0;
}
        
