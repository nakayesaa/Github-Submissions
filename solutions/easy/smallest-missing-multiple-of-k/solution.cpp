class Solution {
public:
    int missingMultiple(vector<int>& nums, int k){
        std::map<int,int> store;
        for(int i = 0; i<nums.size();i++) store[nums[i]]++;
        int start = k;
        while(1){
            if(store[start] == 0) return start;
            start += k;
        }
    }
};
