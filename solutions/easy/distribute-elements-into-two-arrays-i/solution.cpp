class Solution {
public:
    vector<int> resultArray(vector<int>& nums){
        std::vector<int> a;
        std::vector<int> b;
        a.push_back(nums[0]);
        b.push_back(nums[1]);
        for(int i = 2; i<nums.size();i++){
            if(a[a.size()-1] > b[b.size()-1]) a.push_back(nums[i]);
            else b.push_back(nums[i]);
        }

        a.insert(a.end(), b.begin(), b.end());
        return a;
    }
};
