class Solution {
public:
    uint32_t reverseBits(uint32_t n) {
        int res = 0;
        for (int i = 0; i < 32; i++, n >>= 1) {
            res = res << 1 | (n & 0x1);
        }
        
        return res;
    }
};
