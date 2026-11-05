class Solution {
public:
    string maxSumOfSquares(int num, int sum){
        if(sum > 9 * num) return "";
        long long numb = 0;
        int counter = 0;
        std::string result= "";
        while(1){
            if(result.size() == num) break;
            else{
                int a = std::min(9,sum);
                sum -= a;
                result += char('0' + a);
            }
        }
        return result;
    }
};
