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
            if(freq[store[i].first] == 3){
                int a = store[i].second;
                int b = store[i+1].second;
                int c = store[i+2].second;
                if(b-a == c-b) result++;
                i+=2;
            }else i += freq[store[i].first] - 1;
        }
        return result;
    }
};
