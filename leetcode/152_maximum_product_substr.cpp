class Solution {
public:
    int maxProduct(vector<int>& nums) {
        if (nums.size() == 0) return -1;
        
        int ma = nums[0];
        int mi = nums[0];
        int res = nums[0];
        for (int i = 1; i < nums.size(); i++) {
            int ma_temp = max(max(ma * nums[i], mi * nums[i]), nums[i]);
            int mi_temp = min(min(ma * nums[i], mi * nums[i]), nums[i]);
            ma = ma_temp;
            mi = mi_temp;
            res = max(res, ma);
        }
        
        return res;
    }
};
