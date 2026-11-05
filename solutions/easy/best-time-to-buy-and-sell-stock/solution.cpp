class Solution {
public:
    int maxProfit(vector<int>& prices){
        int start = prices[0];
        int res = 0;
        for(int i = 1; i<prices.size();i++){
            int x = prices[i];
            if(x - start > res) res = x - start;
            if(x < start) start = x;
        }

        return res;
    }
};
