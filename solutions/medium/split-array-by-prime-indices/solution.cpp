class Solution {
public:
    bool isPrime(int n){
        if(n <= 1) return false;
        if(n == 2) return true;
        if(n % 2 == 0) return false;

        for(int i = 3; i * i <= n; i += 2){
            if(n % i == 0) return false;
        }
        return true;
    }

    long long splitArray(vector<int>& nums){
        long long a = 0;
        long long b = 0;

        for(int i = 0; i < nums.size(); i++){
            if(isPrime(i)) a += nums[i];
            else b += nums[i];
        }

        return std::abs(a - b);
    }
};
