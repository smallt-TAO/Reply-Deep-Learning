#include <iostream>

using namespace std;

class Solution {
    public:
    double powerNormal(double base, int exponent) {
        if (exponent == 0) {
            return 1;
        }
        else if (exponent == 1) {
            return base;
        }

        double res = 1;
        double temp = base;

        while (exponent) {
            if (exponent & 1) {
                res *= temp;
            }
            temp *= temp;
            exponent >>= 1;
        }

        return res;
    }

    double powerNormal2(double base, int exponent) {
        if (exponent == 0) {
            return 1;
        }
        else if (exponent == 1) {
            return base;
        }

        double res = powerNormal2(base, exponent >> 1);
        res *= res;

        if (exponent & 1) {
            res *= base;
        }

        return res;
    }

};

int main() {
    Solution sol;
    double res = sol.powerNormal(2.3, 4);
    cout << "powerNormal(2.3, 4) " << res << endl;

    res = sol.powerNormal2(2.3, 4);
    cout << "powerNormal(2.3, 4) " << res << endl;
}
