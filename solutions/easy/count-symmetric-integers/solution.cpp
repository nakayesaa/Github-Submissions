class Solution {
public:
    int sumdigit(int x){
        int sum = 0;
        while(x > 0){
            sum += x%10;
            x /= 10;
        }
        return sum;
    }
    int countSymmetricIntegers(int low, int high){
        int res = 0;
        int a = 0;
        int b = 0;
        for(int i = low; i<=high;i++){
            if(i >=10 && i <=99){
                a = sumdigit(i/10);
                b = sumdigit(i%10);
            }
            else if(i >=1000 && i <=9999){
                a = sumdigit(i/100);
                b = sumdigit(i%100);
            }else continue;
            if(a == b) res++;
        }

        return res;
    }
};
