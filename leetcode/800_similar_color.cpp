#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string similarRGB(string color) {
        string res = "#";
        for (int i = 1; i < 7; i+=2) {
            res += help(color.substr(i, 2));
        }

        return res;
    }

    string help(string a) {
        vector<char> flag = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
        int pre = 0;
        for (auto c : a) {
            if (c - '0' > 10) pre = (c - 'a' + 10) + pre * 16;
            if (c - '0' < 10) pre = (c - '0') + pre * 16;
        }

        int min = 255;
        string res;
        for (int i = 0; i < flag.size(); i++) {
            int cur = (flag[i] - '0' > 10) ? (flag[i] - 'a' + 10) : (flag[i] - '0');
            int curcur = cur * 16 + cur;
            if (min > abs(curcur - pre)) {
                min = abs(curcur - pre);
                string temp("");
                temp.push_back(flag[i]);
                temp.push_back(flag[i]);
                res = temp;
            }
        }
        return res;
    }
};

int main() {
    string a = "#09f166";
    Solution sol;
    cout << sol.similarRGB(a) << endl;

    return 0;
}

