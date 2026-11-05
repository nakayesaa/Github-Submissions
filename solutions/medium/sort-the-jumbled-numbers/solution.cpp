
class Solution {
public:
    vector<int> sortJumbled(vector<int>& mapping, vector<int>& nums){
        std::map<int, int> system;
        std::map<int, int> real;
        std::vector<int> numsTransformation;
        for (int i = 0; i < mapping.size(); i++) system[i] = mapping[i];

        for (int i = 0; i < nums.size(); i++){
            int x = nums[i];
            vector<int> digits;
            if(x == 0) digits.push_back(system[0]);
            while(x > 0){
                int val = x % 10;
                int realVal = system[val];
                digits.push_back(realVal);
                x /= 10;
            }
            int mapped = 0;
            for (int j = digits.size() - 1; j >= 0; j--) mapped = mapped * 10 + digits[j];
            numsTransformation.push_back(mapped);
        }

        std::vector<int> index;
        for(int i = 0; i<nums.size();i++) index.push_back(i);
        stable_sort(index.begin(), index.end(),
            [&](int a, int b){
                return numsTransformation[a] < numsTransformation[b];
            }
        );

        std::vector<int> result;
        for(int i = 0; i<index.size();i++) result.push_back(nums[index[i]]);
        return result;
    }
};
