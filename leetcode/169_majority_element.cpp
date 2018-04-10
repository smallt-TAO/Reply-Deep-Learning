class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int res = nums[0];
        int k = 1;
        
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] != res) {
                k--;
            } 
            else {
                k++;
            }
            
            if (k == -1) {
                res = nums[i];
                k = 1;
            }
        }
        
        return res;
        
    }
};
