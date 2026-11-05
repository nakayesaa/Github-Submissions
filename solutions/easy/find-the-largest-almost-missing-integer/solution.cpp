class Solution {
public:
    int largestInteger(vector<int>& nums, int k){
        if(k == 1){
            int max = -1;
            std::map<int,int> store;
            for(int i = 0; i<nums.size();i++) store[nums[i]]++;

            for(auto x : store){
                if(x.second == 1 && x.first > max) max = x.first;
            }

            return max;
        }else if(k == nums.size()) return *max_element(nums.begin(), nums.end());
        else{
            int start = nums[0];
            int end = nums[nums.size()-1];
            if(start == end) return -1;
            for(int i = 1; i<nums.size()-1;i++){
                if(nums[i] == start) start = -1;
                else if(nums[i] == end) end = -1;
            }
            if(start == 0 && end == 0) return -1;
            else return std::max(start,end);
        }
    }
};
