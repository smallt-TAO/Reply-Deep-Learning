#include <iostream>
#include <vector>

using namespace std;
#define INT_MAX 0x7fffffff

class Solution {
public:
    int minInRotateArray(vector<int> rotateArray) {
        if (rotateArray.size() == 0) {
            return 0;
        }

        int res = INT_MAX;
        
        for (int i = 0; i < rotateArray.size(); ++i) {
            if (res > rotateArray[i]) {
                res = rotateArray[i];
            }
        }

        return res;
    }
    
    int minInRotateArrayTwo(vector<int> rotateArray) {
        if (rotateArray.size() == 0) {
            return 0;
        }

        int mid;
        int left = 0, right = rotateArray.size() - 1;

        while (left < right) {
            if (right - left == 1) {
                mid = right;
                cout << "find the number" << endl;
                break;
            }

            int temp = (left + right) / 2;

            if (rotateArray[left] <= rotateArray[temp]) {
                left = temp;
            } 
            else if (rotateArray[right] >= rotateArray[temp]) {
                right = temp;
            }
        }

        return rotateArray[mid];
    }
};

int main() {
    int a[] = { 4, 5, 1, 2, 3};
    vector<int> rotateArray(a, a + 5);

    Solution sol;
    int result = sol.minInRotateArray(rotateArray);
    cout << result << endl;

    result = sol.minInRotateArrayTwo(rotateArray);
    cout << result << endl;

}

