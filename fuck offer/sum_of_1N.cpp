#include <iostream>

class Solution {
public:
    int sumRecursion(int n) {
        int ans = n;

        n && (ans += sumRecursion(n - 1));
        return ans;
    }
};

int main() {
    Solution sol;
    std::cout << sol.sumRecursion(5) << std::endl;
    std::cout << sol.sumRecursion(78) << std::endl;

    return 0;
}

