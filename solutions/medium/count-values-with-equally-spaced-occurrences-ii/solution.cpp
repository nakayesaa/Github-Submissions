class Solution {
public:
    int countSpecialIntegers(vector<int>& nums){
        std::vector<std::pair<int,int>> store;
        std::map<int,int> freq;
        for(int i = 0; i<nums.size();i++){
            store.push_back({nums[i], i});
            freq[nums[i]]++;
        }
        if(store.size() < 3) return 0;
        sort(store.begin(), store.end());
        int result = 0;
        for(int i = 0; i<store.size()-2;i++){
            if(freq[store[i].first] >= 3){
                int real = 1;
                int diff = store[i+1].second - store[i].second;
                for(int j = i+1; j<i+freq[store[i].first];j++){
                    if(store[j].second - store[j-1].second != diff){
                        real = 0;
                        break;
                    }
                }
                if(real) result++;
                i += freq[store[i].first] - 1;
            }else i += freq[store[i].first] - 1;
        }
        return result;
    }
};
