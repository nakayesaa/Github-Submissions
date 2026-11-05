class Solution {
public:
    int longestSubsequence(vector<int>& nums){
        if(all_of(nums.begin(), nums.end(), [](int x){
            return x == 0;
        })) return 0;
        if(nums.size() == 1){
            if(nums[0] == 0) return 0;
            else return 1;
        }
        int max = 0;
        int curr = nums[0];
        int track = 0;
        for(int i = 1; i<nums.size();i++){
            int oper = nums[i] ^ curr;
            if(oper == 0 && i == nums.size()-1) break;
            else{
                curr = oper;
                track++;
            } 

            if(track > max) max = track;
        }

        return max + 1;
    }
};
