#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void printNNumber(int N) {
        vector<string> res(1, "0");

        while (N) {
            vector<string> temp;

            for (auto s : res) {
                for (int i = 0; i < 10; ++i) {
                    temp.push_back(s + to_string(i));
                }
            }

            res = temp;
            N--;
        }

        for (auto ss : res) {
            int i = 0;
            while (ss[i] == '0') {
                i++;
            }

            while (i < ss.size()) {
                cout << ss[i++];
            }

            cout << " ";
        }
        cout << endl;
    }
};

int main() {
    Solution sol;
    sol.printNNumber(3);

    return 0;
}

