#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int> > findContinuousSequence(int target) {
        int start = 1;
        int end = 2;
        int mid = (target + 1) / 2;

        int curSum = start + end;
        vector<vector<int> > res;
        vector<int> temp;

        while (start < mid && end < target) {
            if (curSum == target) {
                res.clear( );
                for (int i = start; i < end + 1; ++i) {
                    temp.push_back(i);
                }

                res.push_back(temp);

                end++;
                curSum += end;
            }
            else if (curSum < target) {
                end++;
                curSum += end;
            }
            else {
                curSum -= start;
                start++;
            }
        }

        return res;
    }
};

int main() {
    Solution sol;
    vector<vector<int> > res = sol.findContinuousSequence(100);

    for (auto re : res) {
        for (auto r : re) {
            cout << r << " ";
        }
    }
    cout << endl;

    return 0;
}

