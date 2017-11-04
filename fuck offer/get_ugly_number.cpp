#include <iostream>

using namespace std;

class Solution {
protected:
    int ugly[1000];
    int min(int a, int b, int c) {
        int temp = a < b ? a : b;

        return temp < c ? temp : c;
    }

public:
    int getUglyNumber(int k) {
        ugly[0] = 1;
        int index = 1;
        int index2 = 0, index3 = 0, index5 = 0;

        while (index < k) {
            int temp = min(ugly[index2] * 2,
                              ugly[index3] * 3,
                              ugly[index5] * 5);
            if (temp == ugly[index2] * 2) {
                ++index2;
            }
            if (temp == ugly[index3] * 3) {
                ++index3;
            }
            if (temp == ugly[index5] * 5) {
                ++index5;
            }

            ugly[index++] = temp;

        }

        return ugly[k - 1];
    }
};

int main() {
    Solution sol;

    cout << sol.getUglyNumber(1) << endl;
    cout << sol.getUglyNumber(2) << endl;
    cout << sol.getUglyNumber(20) << endl;

    return 0;
}

