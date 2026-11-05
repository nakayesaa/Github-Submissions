class Solution {
public:
    bool isAdjacentDiffAtMostTwo(string s){
        for (size_t i = 0; i + 1 < s.size(); i++) {
            int x = abs((s[i] - '0') - (s[i + 1] - '0'));
            if (x > 2) return false;
        }

        return true;
    }
};
