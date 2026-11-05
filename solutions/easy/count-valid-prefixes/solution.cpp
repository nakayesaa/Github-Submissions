class Solution {
public:
    int countValidPrefixes(string s){
        int counter = 0;
        int zero = 0;
        int one = 0;
        for(int i = 0; i<s.size();i++){
            if(s[i] == '1') one++;
            else zero++;
            int curind = i+1;
            if(curind % 2 == 0 && zero == one) counter++;
            else{
                int low = (zero < one)? zero : one;
                int max = (zero > one)? zero : one;
                if(low >= max-1) counter++;
            }
        }

        return counter;
    }
};
