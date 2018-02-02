// Given a string, find the length of the longest substring without repeating characters.
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> charTemp(256, -1);
        int res = 0;
        int start = -1;

        for (int i = 0; i < s.size(); ++i) {
            if (charTemp[s[i]] > start) {
                start = charTemp[s[i]];
            }
            charTemp[s[i]] = i;
            res = max(res, i - start);
        }

        return res;
    }
};

int main() {
    string s("abdabd");

    Solution sol;
    cout << sol.lengthOfLongestSubstring(s) << endl;

    return 0;
}

