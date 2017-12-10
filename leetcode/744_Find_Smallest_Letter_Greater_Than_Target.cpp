# 744 
class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int dist = 26;
        for (auto c : letters) {
            dist = min(dist, (c + 25 - target) % 26 + 1);
        }
        return 'a' + (target + dist - 'a') % 26;
    }
};