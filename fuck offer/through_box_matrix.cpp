#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> throughPrintMatrix(vector<vector<int> > matrix) {
        vector<int> res;
        m = matrix.size();
        n = matrix[0].size();

        if (m == 0 || n == 0) {
            return res;
        }

        value = vector<vector<bool> >(m, vector<bool>(n, false));
        const int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        int counter = m * n;

        int i = 0, j = 0, dCounter = 0;
        while (counter--) {
            res.push_back(matrix[i][j]);
            value[i][j] = true;

            if (!judge(i + d[dCounter][0], j + d[dCounter][1])) {
                dCounter++;
                dCounter %= 4;
            }

            i += d[dCounter][0];
            j += d[dCounter][1];
        }

        return res;
    }

private:
    int m;
    int n;
    vector<vector<bool> > value;
    bool judge(int i, int j) {
        return (i >= 0 && i < m && j >= 0 && j < n && !value[i][j]);
    }

};


int main() {
    int a1[] = {  1,  2,  3,  4 };
    int a2[] = {  5,  6,  7,  8 };
    int a3[] = {  9, 10, 11, 12 };
    int a4[] = { 13, 14, 15, 16 };
    vector<int> vec1(a1, a1 + 4);
    vector<int> vec2(a2, a2 + 4);
    vector<int> vec3(a3, a3 + 4);
    vector<int> vec4(a4, a4 + 4);

    vector< vector<int> > vec;
    vec.push_back(vec1);
    vec.push_back(vec2);
    vec.push_back(vec3);
    vec.push_back(vec4);
    
    Solution sol;
    vector<int> vv = sol.throughPrintMatrix(vec);
    for (auto v : vv) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}

