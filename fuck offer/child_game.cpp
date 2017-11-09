#include <iostream>

class Solution {
public:
    int childGame(int number, int m) {
        if (number == 1) {
            return 0;
        }

        return (childGame(number - 1, m) + m) % number;
    }
};

int main() {
    Solution sol;
    std::cout << sol.childGame(5, 2) << std::endl;
    std::cout << sol.childGame(4, 3) << std::endl;

    return 0;
}

