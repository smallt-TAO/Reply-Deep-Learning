class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int res = 0;
        if (nums.size() < 3) return res;
        
        res = nums[0] + nums[1] + nums[2];
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            int front = i + 1;
            int rear = nums.size() - 1;
            
            while (rear > front) {
                int temp = nums[front] + nums[rear] + nums[i];
                if (temp == target ) {
                    return temp;
                }
                
                if (abs(temp - target) < abs(res - target)) {
                    res = temp;
                }
                
                if (temp - target > 0) rear--;
                else if (temp - target < 0) front++;
            }
            
            while (i + 1 < nums.size() - 1 && nums[i] == nums[i + 1]) i++;
        }
        return res;
    }
};
