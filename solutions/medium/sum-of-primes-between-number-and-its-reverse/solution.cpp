class Solution {
public:
    bool isPrime(int n){
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        for (int i = 3; i * i <= n; i += 2) {
            if(n % i == 0) return false;
        }
    
        return true;
    }
    int revers(int x){
        std::string revs = "";
        while(x > 0){
            int xx = x%10;
            x /= 10;
            revs += std::to_string(xx);
        }
        return std::stoi(revs);
    }
    int sumOfPrimesInRange(int n){
        int upper = revers(n);
        int sum = 0;
        int higher = (upper > n)? upper : n;
        int lower = (upper > n)? n : upper;
        for(int i = lower; i <=higher;i++){
            if(isPrime(i)) sum+= i;
        }

        return sum;
    }
};
