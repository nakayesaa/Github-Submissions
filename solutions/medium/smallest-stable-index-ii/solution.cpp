class Solution {
public:
    int firstStableIndex(vector<int>& nums, int k){   
                std::vector<int> premax(nums.size());
        std::vector<int> premin(nums.size());

        int max = -1;
        for(int i = 0; i<nums.size();i++){
            if(nums[i] > max) max = nums[i];
            premax[i] = max;
        }
        int min = 1000000000;
        for(int i = nums.size()-1; i>=0;i--){
            if(nums[i] < min) min = nums[i];
            premin[i] = min;
        }

        int result = -1;
        for(int i = 0; i<nums.size();i++){
            int res = premax[i] - premin[i];
            if(res <= k){
                result = i;
                break;
            }
        }

        return result;
    }
};
