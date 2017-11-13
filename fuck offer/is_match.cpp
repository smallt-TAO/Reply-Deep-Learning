#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

// if  p[j+1] == '*' -> (i + 1, j + 1)
// else if p[i] == p[j] -> (i + 1, j + 2) or (i, j+2)
// else -> (i, j+2)

class Solution {
public:
    bool isMatch(const char* s, const char* p) {
        if (*p == '\0') {
            return !(*s);
        }

        int slen = strlen(s);
        int plen = strlen(p);

        if (plen == 1 || *(p + 1) != '*') {
            return slen && (p[0] == '.' || *s == *p) && isMatch(s + 1, p + 1);
        }
        else {
            while (*s != '\0' && (*p == '.' || *s == *p)) {
                if (isMatch(s++, p + 2)) {
                    return true;
                }

            }
        }

        return isMatch(s, p + 2);
    }
};

int main() {
    char s[] = {'a', 'b'};
    char p[] = {'a', '*'};

    Solution sol;
    cout << sol.isMatch(s, p) << endl;

    return 0;
}

