#include <iostream>

class Solution {
public:
    std::string reverseSentence(std::string str) {
        if (str.size() == 0) {
            return "";
        }

        std::string res = "", temp = "";
        for (auto s : str) {
            if (s == ' ') {
                res = temp + " " + res;
                temp = "";
            }
            else {
                temp += s;
            }
        }

        res = temp + " " + res;

        return res;
    }
};

int main() {
    std::string str("this is samlltao");

    Solution sol;
    std::cout << sol.reverseSentence(str) << std::endl;

    return 0;
}

