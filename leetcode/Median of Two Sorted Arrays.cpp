class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size();
        int n = nums2.size();
        int total = m + n;
        if (total % 2 == 1) 
            return helper(nums1, m, nums2, n, total / 2 + 1, 0, 0);
        else
            return (helper(nums1, m, nums2, n, total / 2, 0, 0) + helper(nums1, m, nums2, n, total / 2 + 1, 0, 0)) / 2;
    }
    
    double helper(vector<int>& nums1, int m, vector<int>& nums2, int n, int k, int start1, int start2){
        // reverse the nums
        if (m > n)
            return helper(nums2, n, nums1, m, k, start2, start1);
        if (m == 0)
            return nums2[k - 1];
        // find the min in index zero.
        if (k == 1)
            return min(nums1[start1], nums2[start2]);
        
        // divide the sums1 with a.
        int a = min(k / 2, m);
        int b = k - a;
        if(nums1[a + start1 - 1] <= nums2[b + start2 - 1]){
            return helper(nums1, m - a, nums2, n, k - a, start1 + a, start2);
        } else {
            return helper(nums1, m, nums2, n - b, k - b, start1, start2 + b);
        }
    }
};