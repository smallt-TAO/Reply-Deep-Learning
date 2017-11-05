#include <iostream>
#include <cstring>

using namespace std;
// debug
// #define __tmain main
#ifdef __tmain
#define debug cout
#else
#define debug 0 && cout
#endif

class Solution {
protected:
    int count[256];

public:
    int firstNotRepeatingChar(string str) {
        if (str.size() == 0) {
            return -1;
        }

        memset(count, '\0', sizeof(count));

        for (auto s : str) {
            count[(int)s]++;
        }
        debug << count[(int)'a'] << endl;
         
        for (int i = 0; i < str.size(); ++i) {
            if (count[(int)str[i]] == 1) {
                return i;
            }

        }
    }
};

int main() {
    string str = "abdad";

    Solution sol;
    int res = sol.firstNotRepeatingChar(str);
    cout << res << endl;

    return 0;
}

