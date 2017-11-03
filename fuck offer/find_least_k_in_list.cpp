#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int partition(vector<int> &number, int i, int j) {
        int left = i;
        int right = j;
        int flag = number[i];

        while (left < right) {
            while (left < right && number[right] >= flag) {
                right--;
            }

            if (left < right) {
                number[left++] = number[right];
            }

            while (left < right && number[left] < flag) {
                left++;
            }

            if (left < right) {
                number[right--] = number[left];
            }
        }

        number[left] = flag;

        return left;
    }

    int findLeastKNum(vector<int> &number, int left, int right, int k) {
        int targetIndex = partition(number, left, right);

        if (targetIndex < k) {
            return findLeastKNum(number, targetIndex + 1, right, k);
        }
        else if (targetIndex > k) {
            return findLeastKNum(number, left, targetIndex - 1, k);
        }
        else {
            return number[targetIndex];
        }
    }

};

int main() {
    int a[] = {3, 4, 1, 2, 7};
    vector<int> vec(a, a + 5);

    Solution sol;
    cout << sol.partition(vec, 0, 4) << endl;
    for (auto v : vec) {
        cout << v << " ";
    }
    cout << endl;

    cout << sol.findLeastKNum(vec, 0, 4, 3) << endl;

    return 0;
}
