class Solution {
public:
    int digitrange(int a){
        int lowest = 10000000;
        int highest = -1;
        while(a > 0){
            int x = a % 10;
            a /= 10;
            if(x < lowest) lowest = x;
            if(x > highest) highest = x;
        }

        return highest - lowest;
    }
    int maxDigitRange(vector<int>& nums){
        std::map<int,int> store;
        for(int i = 0; i<nums.size();i++){
            int x = nums[i];
            int rng = digitrange(x);
            store[rng] += x;
        }

        int res = 0;
        int maxRange = -1;

        for(auto x : store){
            if(x.first > maxRange){
                maxRange = x.first;
                res = x.second;
            }
        }
        
        return res;
    }
};
