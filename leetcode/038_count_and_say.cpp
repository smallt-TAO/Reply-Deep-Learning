class Solution {
public:
    string countAndSay(int n) {
        string res("1");
        while (--n) {
            res = help(res);
        }
        
        return res;
    }
    
    string help(string s) {
        string res = "";
        
        for (int i = 0; i < s.size(); i++) {
            int temp = 1;
            while (i + 1 < s.size() && s[i] == s[i + 1]) {
                i++;
                temp++;
            }
            res += to_string(temp) + s[i];
        }
        
        return res;
    }
};
