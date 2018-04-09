class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() == 0) return 0;
        
        int p = 0;
        int h = 0;
        for (int i = 0; i < height.size(); i++) {
            if (height[i] > h) {
                h = height[i];
                p = i;
            }
        }
        
        int res = 0;
        int l = height[0];
        for (int i = 0; i < p; i++) {
            if (height[i] < l) {
                res += l - height[i];
            } else {
                l = height[i];
            }
        }
        
         l = height[height.size() - 1];
        for (int i = height.size() - 1; i > p; i--) {
            if (height[i] < l) {
                res += l - height[i];
            }
            else {
                l = height[i];
            }
        }
        
        return res;
        
    }
};
