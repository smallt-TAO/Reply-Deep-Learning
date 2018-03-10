class Solution {
    int numMatchingSubseq(string S, vector<string>& words) {
        int count = 0;
        unordered_map<char, list<string>>maps;
        for (auto& s : words)
            maps[s[0]].push_back(s);
        for (auto& c : S){
            if (maps.count(c)) {
                int n = maps[c].size();
                while (n--) {
                    string word = maps[c].front();
                    maps[c].pop_front();
                    if (word.length() == 1) count++;
                    else maps[word[1]].push_back(word.substr(1));
                }
            }
        }
        return count;
};
