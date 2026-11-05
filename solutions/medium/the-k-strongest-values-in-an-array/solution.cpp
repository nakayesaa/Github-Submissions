class Solution {
public:
    vector<int> getStrongest(vector<int>& arr, int k){
        sort(arr.begin(), arr.end());
        int n = arr.size();
        int middle = arr[(n - 1) / 2];

        int left = 0;
        int right = n - 1;

        vector<int> result;
        while(result.size() < k){
            int leftIndex = abs(arr[left] - middle);
            int rightIndex = abs(arr[right] - middle);

            if(rightIndex > leftIndex){
                result.push_back(arr[right]);
                right--;
            }
            else if(leftIndex > rightIndex){
                result.push_back(arr[left]);
                left++;
            }
            else{
                if(arr[right] > arr[left]){
                    result.push_back(arr[right]);
                    right--;
                }else{
                    result.push_back(arr[left]);
                    left++;
                }
            }
        }
        return result;
    }
};
