class Solution {
public:
    int minimumOperationsToMakeKPeriodic(string word, int k){
        std::map<std::string,int> store;
        for(int i = 0; i < word.size(); i += k){
            if(i + k <= word.size()){
                std::string curr = word.substr(i, k);
                store[curr]++;
            }else{
                std::string curr = word.substr(i);
                store[curr]++;
            }
        }
        int max = -1;
        for(auto x : store) if(x.second > max) max = x.second;
        int result = word.size()/k - max;
        return result;
    }
};
