class Solution {
public:
    int largestInteger(int n, int s){
        if(s == 0) return 0;
        int limit = std::pow(10,n);
        int res = 1;
        int answer = 0;
        int uper = 9 * n;
        if(s > uper) return -1;
        else{
            while(res < limit){
                int x = limit - res;
                int sum = 0;

                while(x > 0){
                    sum += x % 10;
                    x /= 10;
                }

                if(sum == s){
                    answer = limit - res;
                    break;
                }
                res++;
            }
        }
        if(answer) return answer;
        else return -1;
    }
};
