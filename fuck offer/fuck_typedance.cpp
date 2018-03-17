#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
    bool fuck(string s, vector<string>& dict) {
        vector<bool> flag(s.size() + 1, false);

        for (int i = 1; i <= s.size(); i++) {
            for (int j = 0; j < i; j++) {
                if (flag[i - j] && 
                    vector<string>::iterator find(dict.begin(), dict.end(), s.substr(i-j-1, i-1)) != dict.end())
                    flag[i] = true;
            }
        }

        return flag[s.size()];
    }
};

