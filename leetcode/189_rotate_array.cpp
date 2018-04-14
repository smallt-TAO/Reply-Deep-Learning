class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        
        int cnt = 0;
        for (auto n : nums) cnt++;
        k %= cnt;
        
        reverse(nums.begin(), nums.begin() + cnt - k);
        reverse(nums.begin() + cnt - k, nums.begin() + cnt);
        reverse(nums.begin(), nums.end());
        
    }
};
