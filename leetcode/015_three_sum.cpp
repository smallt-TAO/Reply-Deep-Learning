class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int> > res;
        
        if (nums.size() < 3) {
            return res;
        }
        
        // Main processing
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            int target = -nums[i];
            int left = i + 1;
            int right = nums.size() - 1;
            
            while (left < right) {
                if (nums[left] + nums[right] == target) {
                    vector<int> temp;
                    temp.push_back(nums[i]);
                    temp.push_back(nums[left]);
                    temp.push_back(nums[right]);
                    res.push_back(temp);
                    
                    // more thing to do
                    while (left < right && nums[left] == temp[1]) left++;
                    while (left < right && nums[right] == temp[2]) right--;
                }
                else if (nums[left] + nums[right] > target) right--;
                else left++;
            }
            while (i + 1 < nums.size() && nums[i + 1] == nums[i]) i++;
        }
        
        return res;
        
    }
};
