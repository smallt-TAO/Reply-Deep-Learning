#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        int res = -1;
        
        for (auto s : str) {
            if (res == -1) {
                res = s - '0';
            }
            else {
                res = res * 10 + (s - '0');
            }
        }

        return res;
    }
};

int main() {
    string temp("23523423");
    Solution sol;
    cout << sol.myAtoi(temp) << endl;

    return 0;
}
