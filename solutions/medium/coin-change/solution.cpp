class Solution {
public:
    const int INF = 1e8;
    int solve(vector<int>& coins, int amount, vector<int>& dp){
        if(amount == 0) return 0;
        if(amount < 0) return INF;

        if(dp[amount] != -1) return dp[amount];

        int best = INF;
        for(int i = 0; i < coins.size(); i++){
            best = min(best, 1 + solve(coins, amount - coins[i], dp));
        }
        dp[amount] = best;
        return best;
    }
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, -1);
        int result = solve(coins, amount, dp);
        return result >= INF ? -1 : result;
    }
};
