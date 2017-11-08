#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    std::string leftRotateString(std::string str, int k) {
        if (str.size() == 0) {
            return "";
        }

        k %= str.size();

        reverse(str, 0, k - 1);
        reverse(str, k, str.size() - 1);
        reverse(str, 0, str.size() - 1);

        return str;
    }

    void reverse(std::string &str, int start, int end) {
        while (start < end) {
            std::swap(str[start], str[end]);
            start++;
            end--;
        }
    }
};

int main() {
    std::string str("smalltao");

    Solution sol;
    std::cout << sol.leftRotateString(str, 3) << std::endl;

    return 0;
}

