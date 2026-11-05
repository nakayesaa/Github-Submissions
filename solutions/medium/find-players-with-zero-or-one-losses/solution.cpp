class Solution {
public:
    vector<vector<int>> findWinners(vector<vector<int>>& matches){
        std::vector<int> winners;
        std::map<int,int> store;
        for(int i = 0; i<matches.size();i++){
            winners.push_back(matches[i][0]);
        }
        for(int i = 0; i<matches.size();i++){
            store[matches[i][1]]++;
        }


        std::vector<int> type1;
        std::vector<int> type2;
        for(int i = 0; i<winners.size();i++){
            if(store[winners[i]] == 0) type1.push_back(winners[i]);
            else if(store[winners[i]] == 1) type2.push_back(winners[i]);
        }

        for(auto x : store){
            if(x.second == 1) type2.push_back(x.first);
        }

        std::sort(type1.begin(), type1.end());
        type1.erase(std::unique(type1.begin(), type1.end()), type1.end());
        std::sort(type2.begin(), type2.end());
        type2.erase(std::unique(type2.begin(), type2.end()), type2.end());


        
        std::vector<std::vector<int>> result;
        result.push_back(type1);
        result.push_back(type2);
        return result;
    }
};
