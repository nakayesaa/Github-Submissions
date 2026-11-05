class Solution {
public:
    bool uniformArray(vector<int>& nums1){
        sort(nums1.begin(), nums1.end());

        int odd = 0;
        int smallestOdd = INT_MAX;
        int smallestEven = INT_MAX;
        for(int x : nums1){
            if(x % 2){
                odd++;
                smallestOdd = std::min(smallestOdd, x);
            }else smallestEven = std::min(smallestEven, x);
        }

        if(odd && odd != nums1.size()){
            vector<int> nums2;

            for(int i = 0; i < nums1.size(); i++){
                if(nums1[i] % 2) nums2.push_back(nums1[i]);
                else{
                    int x = nums1[i] - smallestOdd;
                    if(x >= 1) nums2.push_back(x);
                }
            }
            if(nums2.size() == nums1.size()) return true;
            else return false;
        }
        return true;
    }
};
