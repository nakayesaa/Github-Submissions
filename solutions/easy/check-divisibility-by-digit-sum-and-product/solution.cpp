class Solution {
public:
    int digitproduct(int n){
        int sum = 1;
        int x;
        while(n > 0){
            x = n%10;
            n/=10;
            sum*=x;
        }
        return sum;
    }
    int digitsum(int n){
        int sum = 0;
        int x;
        while(n > 0){
            x = n%10;
            n/=10;
            sum+=x;
        }
        return sum;
    }
    bool checkDivisibility(int n){
        if(n % (digitproduct(n) + digitsum(n)) == 0) return true;
        else return false;
    }
};
