class Solution {
public:
    int matrixSum(vector<vector<int>>& nums){
        int max = 0;
        int counter = 0;
        int size = nums[0].size();
        int res = 0;

        for(auto& row : nums){
            sort(row.begin(), row.end());
        }
        while(size--){
            for(int i = 0; i<nums.size();i++){
                max = std::max(max, nums[i][counter]);
            }
            counter++;
            res += max;
            max = 0;
        }
        return res;
    }
};
