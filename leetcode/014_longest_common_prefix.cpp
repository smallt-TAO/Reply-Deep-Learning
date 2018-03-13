class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.size() == 0) return "";
        
        string res = strs[0];
        for (auto str : strs) {
            res = pre(str, res);
        }
        return res;
        
    }
    
    string pre(string a, string b) {
        int n = min(a.size(), b.size());
        int i;
        for (i = 0; i < n; i++) {
            if (a[i] != b[i]) {
                break;
            }
        }
        
        return a.substr(0, i);
    }
};
