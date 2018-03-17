class Solution {
public:
    vector<string> letterCombinations(string digits) {
        static const vector<string> flag = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> res;
        
        if (digits.size() < 1) return res;
        else res.push_back("");
        
        for (auto d : digits) {
            vector<string> temp;
            for (int i = 0; i < res.size(); i++) {
                for (auto c : flag[d - '0']) {
                    temp.push_back(res[i] + c);
                }
            }
            res.swap(temp);
        }
        return res;

    }
};
