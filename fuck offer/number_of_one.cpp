#include <iostream>

using namespace std;

// #define __tmain main

#ifdef __tmain
#define debug cout
#else
#define debug 0 && cout
#endif

class Solution {
    public:
    int numberOfOne(int n) {
        int counter = 0;
        unsigned long flag = 1;

        while (flag) {
            if (flag & n) {
                counter++;
            }

            flag <<= 1;
            debug << "current flag is: " << flag << endl;
        }

        return counter;
    }

    int numberOfOne2(int n) {
        int counter = 0;
        while (n) {
            n &= (n - 1);
            counter++;
        }

        return counter;
    }
};

int main() {
    Solution sol;

    int res = sol.numberOfOne(8);
    cout << "8" << " number of one is: " << res << endl;

    res = sol.numberOfOne(18);
    cout << "18" << " number of one is: " << res << endl;

    res = sol.numberOfOne2(356);
    cout << "356" << " number of one is: " << res << endl;
}

