class Solution {
public:
    long long maxSum(vector<vector<int>>& grid, vector<int>& limits, int k){
        std::vector<std::pair<int,int>> store;
        for(int i = 0; i < grid.size(); i++){
            std::vector<int> current = grid[i];
            sort(current.begin(), current.end(), std::greater<int>());
            for(int j = 0; j < limits[i] && j < current.size(); j++){
                store.push_back({current[j], i});
            }
        }
        sort(store.begin(), store.end(), std::greater<std::pair<int,int>>());
        long long result = 0;
        int index = 0;
        while(k > 0 && index < store.size()){
            result += store[index].first;
            index++;
            k--;
        }
        return result;
    }
};
