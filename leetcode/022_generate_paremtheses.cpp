class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        help(0, 0, res, "", n);
        
        return res;
    }
    
    void help(int left, int right, vector<string>& res, string temp, int n) {
        if (left < right) return;
        
        if (left == n && right == n) {
            res.push_back(temp);
            return;
        }
        
        if (left <= n) help(left + 1, right, res, temp + "(", n);
        if (right <= n) help(left, right + 1, res, temp + ")", n);
    }
        
};
