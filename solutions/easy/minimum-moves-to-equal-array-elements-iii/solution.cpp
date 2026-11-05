class Solution {
public:
    int minMoves(vector<int>& nums){
        int max = -1;
        for(auto x : nums) max = std::max(max,x);
        int result = 0;
        for(int i = 0; i<nums.size();i++){
            result += std::abs(max - nums[i]);
        }
        return result;
    }
};
