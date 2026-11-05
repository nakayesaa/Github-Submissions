class Solution {
public:
    int distinctAverages(vector<int>& nums){
        sort(nums.begin(), nums.end());
        int right = nums.size()-1;
        int left = 0;
        std::map<float,int> store;
        int limit = nums.size()/2;

        while(limit--){
            int a = nums[left++];
            int b = nums[right--];
            float c = static_cast<float>(a+b)/2;
            store[c]++;
        }
        return store.size();
    }
};
