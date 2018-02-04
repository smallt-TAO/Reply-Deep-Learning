// We observe that a palindrome mirrors around its center. Therefore, a palindrome can be expanded from its center, and there are only 
// 2n-1 such centers.
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    string longestPalindrome(string str) {
        int start = 0;
        int gap = -1;
        for (int i = 0; i < str.size(); ++i) {
            int len1 = expandAroundCenter(str, i, i);
            int len2 = expandAroundCenter(str, i, i + 1);
            int len = max(len1, len2);
            if (len > gap) {
                start = i - (len - 1) / 2;
                gap = len;
            }
        }

        return str.substr(start, gap);
    }

    int expandAroundCenter(string str, int a, int b) {
        int left = a;
        int right = b;
        while (left >= 0 && right < str.size() && str[left] == str[right]) {
            left --;
            right ++;
        }

        return right - left - 1;
    }
};

int main() {
    string str("abddbhui");

    Solution sol;
    cout << sol.longestPalindrome(str) << endl;

    return 0;
}

