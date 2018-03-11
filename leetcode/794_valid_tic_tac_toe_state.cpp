#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool validTicTacToe(vector<string>& board) {
        int xNum = 0;
        int oNum = 0;
        for (auto bo : board) {
            for (auto b : bo) {
                if (b == 'X') xNum++;
                else if (b == '0') oNum++;
            }
        }
        
        // handle the situation of property
        if (xNum - oNum != 1) return false;
        
        // handle the situation of end
        int xWin = help(board, 'X');
        int oWin = help(board, '0');
        if (xWin + oWin > 1) return false;

        return true;

    }

    int help(vector<string>& map, char c) {
        for (int i = 0; i < 3; ++i) {
            if (map[i][0] == map[i][1] && map[i][1] == map[i][2]
                    && map[i][2] == c) {
                return 1;
            }
        }

        for (int j = 0; j < 3; ++j) {
            if (map[0][j] == map[1][j] && map[1][j] == map[2][j]
                    && map[2][j] == c) {
                return 1;
            }
        }


        if ((map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[2][2] == c) ||
            (map[0][2] == map[1][1] && map[1][1] == map[2][0] && map[2][0] == c))
            return 1;
    }
};

int main() {
    string a[] = {"XXX", "   ", "0 0"};
    vector<string> board(a, a + 3);

    Solution sol;
    cout << sol.validTicTacToe(board) << endl;

    return 0;
}

