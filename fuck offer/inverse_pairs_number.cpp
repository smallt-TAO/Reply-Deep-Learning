#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int inversePairs(vector<int> numbers) {
        if (numbers.empty()) {
            return -1;
        }

        vector<int> temp(numbers.size());
        int res = inversePairsCore(numbers, 0, numbers.size() - 1, temp);

        return res;
    }

    int mergeElem(vector<int> &numbers, int start, int mid, int end, vector<int> &temp) {
        int i = mid;
        int j = end;
        int k = 0;  // temp vector
        int count = 0;

        while (start <= i && mid < j) {
            if (numbers[i] > numbers[j]) {
                temp[k++] = numbers[i--];
                count += j - mid;
            }
            else if (numbers[i] <= numbers[j]) {
                temp[k++] = numbers[j--];
            }
        }

        while (start <= i) {
            temp[k++] = numbers[i--];
        }

        while (mid < j) {
            temp[k++] = numbers[j--];
        }

        for (i = 0; i < end - start + 1; ++i) {
            numbers[end - i] = temp[i];
        }
        
        // cout << count << endl;

        return count;
    }


    int inversePairsCore(vector<int> &numbers, int start, int end, vector<int> &temp) {
        int counter = 0;
        if (start < end) {
            int mid = (start + end) / 2;

            counter += inversePairsCore(numbers, start, mid, temp);
            counter += inversePairsCore(numbers, mid + 1, end, temp);
            counter += mergeElem(numbers, start, mid, end, temp);
        }

        return counter;
    }
};

int main() {
    int a[] = {3, 4, 5, 1, 8, 24, 56};
    vector<int> vec(a, a + 7);

    Solution sol;
    cout << sol.inversePairs(vec) << endl;

    return 0;
}

