class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        
        int n1 = num1.size();
        int n2 = num2.size();
        vector<int> v(n1 + n2, 0);
        
        for (int i = n1 - 1; i > -1; i--) {
            for (int j = n2 - 1; j > -1; j--) {
                v[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
            }
        }
        
        for (int i = n1 + n2 - 1; i > 0; i--) {
            if (v[i] >= 10) {
                v[i - 1] += v[i] / 10;
                v[i] = v[i] % 10;
            }
        }
        
        string res;
        for (int i = (v[0] == 0); i < v.size(); i++) {
            res += to_string(v[i]);
        }
        
        return res;
    }
};
