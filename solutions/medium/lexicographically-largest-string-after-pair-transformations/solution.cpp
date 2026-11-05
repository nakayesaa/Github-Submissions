class Solution {
public:
    vector<string> largestString(vector<int>& nums){
        std::vector<std::string> result(nums.size());
        for(int i = 0; i<nums.size();i++){
            std::vector<int> a;
            std::string res = "";
            int x = nums[i];
            int z = (1 << 25);
            while(x >= z){
                res += 'z';
                x -= z;
            }
            while(x != 0){
                a.push_back(x % 2);
                x /= 2;
            }
            std::vector<int> b;
            for(int j = a.size() - 1; j >= 0; j--){
                if(a[j] == 1) b.push_back(std::pow(2, j));
            }
            for(int k = 0; k < b.size();k++){
                int xx = std::log2(b[k]);
                res += 'a' + xx;
            }
            result[i] = res;
        }
        return result;
    }
};
