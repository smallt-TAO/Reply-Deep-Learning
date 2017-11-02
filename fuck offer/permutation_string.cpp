#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// #define __tmain main();
#ifdef __tmain
    #define debug cout
#else
    #define debug 0 && cout
#endif

class Solution {
public:
    void permutation(string prefix, string str) {
        if (str.size() == 0) {
            res.push_back(prefix);
            return;
        }

        for (int i = 0; i < str.size(); ++i) {
            permutation(prefix + str[i], 
                    str.substr(0, i) + str.substr(i + 1, str.length()));
        }
    }

    vector<string> permutation(string s) {
        res.clear();
        if (s.empty()) return res;

        permutation("", s);
        sort(res.begin(), res.end());
        res.erase(unique(res.begin(), res.end()), res.end());
        return res;
    }

    void permutationV1(string str, int begin) {
        if (str[begin] == '\0') {
            res.push_back(str);
            return;
        }

        for (int i = begin; i < str.size(); ++i) {
            if (!hasDuplicate(str, begin, i)) {
                swap(str[begin], str[i]);
                permutationV1(str, begin + 1);
                swap(str[begin], str[i]);
            }
        }
    }

    vector<string> permutationV1(string s) {
        res.clear();
        if (s.empty()) return res;
        
        debug << s << endl;
        permutationV1(s, 0);
        for (auto r : res) {
            debug << r << " ";
        }
        debug << endl;
        sort(res.begin(), res.end());
        return res;
    }

private:
    vector<string> res;
    
    bool hasDuplicate(string str, int left, int right) {
        for (int i = left; i < right; ++i) {
            if (str[i] == str[right]) return true;
        }

        return false;
    }
};


int main() {
    string s = "aab";
    Solution sol;
    debug << "haha" << endl;
    debug << s << endl;
    // vector<string> res = sol.permutation(s);
    vector<string> res = sol.permutationV1(s);

    for (auto re : res) {
        cout << re << " ";
    }
    cout << endl;
}

