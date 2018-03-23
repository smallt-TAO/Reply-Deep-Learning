class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> te;
        sort(candidates.begin(), candidates.end());
        if (candidates.size() == 0) return res;
        
        help(res, te, candidates, 0, target, 0);
        
        return res;
    }
    
    void help(vector<vector<int> >& res, vector<int> temp, vector<int> candidates, int sum, int target, int start) {
        if (sum > target) return;
        if (sum == target) {
            res.push_back(temp);
            return;
        }
        
        for (int i = start; i < candidates.size(); i++) {
            temp.push_back(candidates[i]);
            help(res, temp, candidates, sum + candidates[i], target, i);
            temp.pop_back();
        }
    }
};
