#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
    string convert(string s, int numRows) {
        vector<string> temp(numRows, "");
        string res("");
        int i = 0;
        while (i < s.size()) {
            for (int j = 0; j < numRows; j++) {
                temp[j].push_back(s[i++]);
            }

            for (int j = numRows - 2; j > 0; j--) {
                temp[j].push_back(s[i++]);
            }
        }

        for (auto sa : temp) {
            // cout << sa << endl;
            res += sa;
        }

        return res;
    }
};

int main() {
    string s("asdfghj");

    Solution sol;
    cout << sol.convert(s, 3) << endl;

    return 0;
}

