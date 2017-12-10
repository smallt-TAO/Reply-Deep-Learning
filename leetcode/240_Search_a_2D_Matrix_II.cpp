#
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.size() == 0) return false;
        int m = 0;
        int n = matrix[0].size() - 1;
        
        while (n >= 0 && m < matrix.size()) {
            if (matrix[m][n] == target) {
                return true;
            }   
            else if (matrix[m][n] > target) {
                n--;
            }
            else {
                m++;
            }
        }
        
        return false;
    } 
    
};