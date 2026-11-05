class Solution {
public:
    int minMergedInteger(vector<int>& nums){
        std::vector<int> merged;
        for(int i = 0; i<nums.size();i+=2){
            std::string a = std::to_string(nums[i]);
            a += std::to_string(nums[i+1]);
            merged.push_back(std::stoi(a));
        }
        int minimum = 10e8;
        for(int i = 0; i<merged.size();i++){
            minimum = std::min(minimum, merged[i]);
        }
        return minimum;
    }
};
