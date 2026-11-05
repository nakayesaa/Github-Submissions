class Solution {
public:
    int maxDifference(string s){
        std::map<char,int> store;
        for(int i = 0; i<s.size();i++){
            char x = s[i];
            store[x]++;
        }
        int maxodd = 0;
        int maxeven = 10000000;
        for(auto x : store){
            if(x.second % 2 != 0 && x.second > maxodd) maxodd = x.second;
            else{
                if(x.second % 2 == 0 && x.second < maxeven) maxeven = x.second;
            }
        }
        return maxodd - maxeven;
    }
};
