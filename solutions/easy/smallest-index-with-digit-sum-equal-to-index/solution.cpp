class Solution {
public:
    int sumdigit(int n){
        int sum = 0;
        while(n > 0){
            sum += n%10;
            n /= 10;
        }
        return sum;
    }
    int smallestIndex(vector<int>& nums){ 
        int result = -1;
        for(int i = 0; i<nums.size();i++){
            if(i == sumdigit(nums[i])){
                result = i;
                break;
            }
        }
        if(result < 0) return -1;
        else return result;
    }
};
