class Solution {
public:
    int minimumCost(vector<int>& nums, int k) {
        long long total = 0;
        for(int x : nums) total += x;
        
        long long refill = 0;
        if(total > k){
            refill = (total - k + k - 1) / k;
        }

        long long cost;
        if(refill % 2 == 0){
            cost = ((refill / 2) % 1000000007) * ((refill + 1) % 1000000007);
        }else{
            cost = (refill % 1000000007) * (((refill + 1) / 2) % 1000000007);
        }

        return cost % 1000000007;
    }
};
