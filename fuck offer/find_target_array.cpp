#include <iostream>
#include <vector>

using namespace std;

#define __main main
#define __tmain test

class Solution{
public:
    bool find(vector<vector<int> > array, int target) {
        bool res = false;
        int row = array.size();
        int col = array[0].size();
        
        // find the target begin from right-up position.
        for (int i = 0, j = row - 1; (i >= 0 && i < row) && (j >= 0 && j < col); ) {
            if (array[i][j] == target) {
                res = true;
                break;
            }

            if (array[i][j] > target) {
#ifdef __tmain
                cout << target << " < " << array[i][j] << " turn left" << endl;
#endif // __tmain
                j--;
            }

            if (array[i][j] < target) {
                i++;
            }
        }
        return res;
    }
};


int __main() {
    int a1[] = { 1, 2, 8, 9, };
    int a2[] = { 2, 4, 9, 12, };
    int a3[] = { 4, 7, 10, 13, };
    int a4[] = { 6, 8, 11, 15, };
    vector<vector<int>> array;
    array.push_back(vector<int>(a1, a1 + 4));
    array.push_back(vector<int>(a2, a2 + 4));
    array.push_back(vector<int>(a3, a3 + 4));
    array.push_back(vector<int>(a4, a4 + 4));
    
    Solution sol;
    string res = sol.find(array, 7) ? "Yes" : "No";
    cout << res << endl;
    
    return 0;
}
