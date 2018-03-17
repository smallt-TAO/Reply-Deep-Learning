class Solution {
public:
    bool isValid(string s) {
        if (s == "") return true;
        stack<int> temp;
        
        for (auto c : s) {
            if (temp.empty()) temp.push(c);
            else if (temp.top() - c == -1 || temp.top() - c == -2){
                temp.pop();
            }
            else {
                temp.push(c);
            }
        }
        
        return temp.empty();
            
    }
};

