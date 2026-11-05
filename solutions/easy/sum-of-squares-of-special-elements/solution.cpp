class Solution {
public:
    int sumOfSquares(vector<int>& nums){
        std::vector<int> factor;
        int size = nums.size();
        for(int i = 0;i<=size;i++){
            if(size % (i+1) == 0) factor.push_back(nums[i]);
        }

        int res = 0;
        for(int i = 0; i<factor.size();i++) res += factor[i] * factor[i];
        return res;
    }
};
