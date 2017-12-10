class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int result = 0;
        int current = 0;
        unordered_map<char, int> hash;
        for (int i = 0; i < s.size(); i++) {
            if (hash.find(s[i]) != hash.end()) {
                result = max(result, current);
                current = min(i - hash[s[i]], current + 1);
            }
            else {
                current ++;
            }
            hash[s[i]] = i;
        }
        
        return max(result, current);
    }
};