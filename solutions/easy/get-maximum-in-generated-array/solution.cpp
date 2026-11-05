class Solution {
public:
    int getMaximumGenerated(int n){
        if(n <= 2) return n == 0 ? 0 : 1;
        else{
            std::vector<int> nums(n+1);
            nums[0] = 0;
            nums[1] = 1;
            int result = 1;
            for(int i = 2; i<=n;i++){
                if(i % 2 == 0) nums[i] = nums[i/2];
                else nums[i] = nums[i/2] + nums[(i/2) + 1];
                result = std::max(result,nums[i]);
            }
            return result;
        }
    }
};
