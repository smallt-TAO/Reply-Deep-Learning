class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;
        int res = 0;
        while (left < right) {
            int m = min(height[right], height[left]);
            res = max(res, (right - left) * m);
            
            if (height[left] > height[right]) {
                right--;
            }
            else {
                left++;
            }
        }
        
        return res;
    }
};
