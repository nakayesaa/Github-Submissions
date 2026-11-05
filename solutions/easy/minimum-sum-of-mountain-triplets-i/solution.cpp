class Solution {
public:
    int minimumSum(vector<int>& nums){
        vector<pair<int, int>> store;
        for(int i = 0; i < nums.size(); i++) store.push_back({nums[i], i});
        sort(store.begin(), store.end());

        int minn = INT_MAX;
        for(int i = 0; i < store.size(); i++){
            for(int k = i + 1; k < store.size(); k++){
                int left = min(store[i].second, store[k].second);
                int right = max(store[i].second, store[k].second);
                int x = store[i].first;
                int y = store[k].first;
                for(int j = k + 1; j < store.size(); j++){
                    int midIndex = store[j].second;
                    int midValue = store[j].first;
                    if(midIndex > left && midIndex < right && midValue > x && midValue > y){
                        if(x + y + midValue < minn) minn =  x + y + midValue;
                        break;
                    }
                }
            }
        }

        return minn == INT_MAX ? -1 : minn;
    }
};
