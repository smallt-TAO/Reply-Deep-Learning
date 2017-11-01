#include <iostream>

using namespace std;

class Solution {
    public:
    void replace(string &str, int length) {
        int counter = 0;
        for (auto &s : str) {
            if (s == ' ') s = 'A';
        }
    }

};

int main() {
    string str = "a b c d";

    Solution solu;
    solu.replace(str, 10);

    cout <<str <<endl;
    return 0;
}
