#include <iostream>
#include <vector>

using namespace std;

class Solution {
    public:
    int numberMatchingSubseq(string s, vector<string>& words) {
        int res = 0;
        int n = s.size();
        vector<vector<int> > temp(n, vector<int>(27, -1));

        // init the temp vector for first row
        for (int i = n - 1; i >= 0; --i) {
            temp[0][s[i] - 'a'] = i + 1;
        }

        for (int j = n - 2; j >= 0; --j) {
            for (int i = 0; i < 27; ++i) {
                temp[j + 1][i] = temp[j + 2][i];
            }

            // handle situation for change 
            temp[j + 1][s[j + 1] - 'a'] = j + 2;
        }

        for (auto word : words) {
            cout << word << endl;
            int start = 0;
            bool ok = true;
            for (int i = 0; i < word.size(); i++) {
                int next = temp[start][word[i] - 'a'];
                if (next != -1) start = next;
                else ok = false;
            }
            cout << ok << endl;
            if (ok) res++;
        }

        return res;
    }
};

int main() {
    string s("abcd");
    string a[3] = {"a", "ac", "dd"};
    vector<string> words(a, a + 3);

    Solution sol;
    cout << sol.numberMatchingSubseq(s, words) << endl;

    return 0;
}

