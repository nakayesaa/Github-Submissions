class Solution {
public:
    int reverseDegree(string s){
        int product = 0;
        for(int i = 0; i<s.size();i++){
            int val = static_cast<int>(s[i]) - 96;
            int reverseVal = std::abs((val-26)-1);
            product += reverseVal * (i+1);
        }
        return product;
    }
};
