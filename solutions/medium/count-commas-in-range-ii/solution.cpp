class Solution {
public:
    long long res(long long n){
        if (n < 1000) return 0;
        long long start = 1000;
        long long sum = 0;
        int order = 1;
        while(1){
            if(start * 1000 <= n){
                sum += (start * 999) * order;
                order++;
                start *= 1000;
            }
            else {
                sum += (n - start + 1) * order;
                break;
            }
        }

        return sum;
    }

    long long countCommas(long long n){
        return res(n);
    }
};
