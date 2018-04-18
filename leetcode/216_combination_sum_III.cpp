class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int> > res;
        vector<int> temp;
        help(k, n, 1, res, temp);
        
        return res;
    }
    
    void help(int k, int n, int start, vector<vector<int> >& res, vector<int>& temp) {
        if (n < 0 || temp.size() > k || start > 10) return;
        if (n == 0 && temp.size() == k) res.push_back(temp);
        
        for (int i = start; i < 10; i++) {
            temp.push_back(i);
            help(k, n - i, i + 1, res, temp);
            temp.pop_back();
        }
    }
        
};
