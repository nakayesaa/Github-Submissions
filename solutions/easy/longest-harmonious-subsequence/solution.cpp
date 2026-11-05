class Solution {
public:
    int findLHS(vector<int>& nums){
        std::map<int,int> store;
        for(auto x : nums) store[x]++;
        int max = 0;
        for(int i = 0; i<nums.size();i++){
            int x = nums[i];
            if(store[x-1]){
                if(store[x-1] + store[x] > max) max = store[x-1] + store[x];
            }else if(store[x+1]){
                if(store[x+1] + store[x] > max) max = store[x+1] + store[x];
            }
        }
        return max;
    }
};
