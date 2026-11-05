class Solution {
public:
    int getMinDistance(vector<int>& nums, int target, int start){ 
        int max = INT_MAX;
        for(int i = 0; i<nums.size();i++){
            if(nums[i] == target){
                if(std::abs(i - start) < max) max = std::abs(i-start);
            }
        }
        return max;
    }
};
