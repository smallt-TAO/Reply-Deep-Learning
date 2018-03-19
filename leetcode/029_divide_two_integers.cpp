class Solution {
public:
    int divide(int dividend, int divisor) {
        if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) {
            return INT_MAX;
        }
        
        int sign = ((dividend > 0) ^ (divisor > 0)) ? -1 : 1;
        int res = 0;
        long long div = labs(dividend);
        long long dor = labs(divisor);
        while (div >= dor) {
            long long cur = 1;
            long long temp = dor;
            while (div >= (temp << 1)) {
                cur <<= 1;
                temp <<= 1;
            }
            res += cur;
            div -= temp;
        }
        
        return sign * res; 
    }
};
