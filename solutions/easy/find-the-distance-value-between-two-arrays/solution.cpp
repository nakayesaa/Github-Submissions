class Solution {
public:
    int findTheDistanceValue(vector<int>& arr1, vector<int>& arr2, int d) {
        sort(arr2.begin(), arr2.end());
        int result = 0;

        for(int x : arr1){
            auto it = lower_bound(arr2.begin(), arr2.end(), x);
            int minDiff = 10e8;

            if(it != arr2.end())
                minDiff = min(minDiff, abs(x - *it));

            if(it != arr2.begin())
                minDiff = min(minDiff, abs(x - *prev(it)));

            if(minDiff > d)
                result++;
        }
        return result;
    }
};
