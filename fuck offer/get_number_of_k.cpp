#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int getNumberOfK(std::vector<int> numbers, int k) {
        std::vector<int>::iterator upper, lower;

        upper = std::upper_bound(numbers.begin(), numbers.end(), k);
        lower = std::lower_bound(numbers.begin(), numbers.end(), k);

        return upper - lower;
    }
};

int main() {
    int a[] = {1, 2, 2, 2, 3, 4, 5};
    std::vector<int> vec(a, a + 7);

    Solution sol;
    std::cout << sol.getNumberOfK(vec, 2) << std::endl;

    return 0;
}

