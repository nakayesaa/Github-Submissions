class Solution {
public:
    int elevatorRequests(int n, vector<int>& requests){
        int sum = 0;
        for(int i = 1; i<requests.size();i++)sum += std::abs(requests[i] - requests[i-1]);
        sum += requests[0];
        return sum;
    }
};
