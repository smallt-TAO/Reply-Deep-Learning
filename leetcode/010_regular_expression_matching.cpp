#include <iostream>
#include <string>

using namespace std;

class Solution {
    public:
    bool checkMatch(string s, string p) {
        if (p.empty())  return s.empty();

        if (p[1] == '*') {
            return checkMatch(s, p.substr(2)) ||
                   (!s.empty() && (s[0] == p[0] || '.' == p[0]) && checkMatch(s.substr(1), p));
        }
        else {
            return !s.empty() && (s[0] == p[0] || '.' == p[0]) && checkMatch(s.substr(1), p.substr(1));
        }

    }

};

int main() {
    string s("aa");
    string p("a*");
    Solution sol;
    cout << sol.checkMatch(s, p) << endl;

    return 0;
}

