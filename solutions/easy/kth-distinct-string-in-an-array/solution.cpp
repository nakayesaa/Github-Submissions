class Solution {
public:
    string kthDistinct(vector<string>& arr, int k) {
        std::map<std::string,int> store;
        int track = 1;
        for(int i = 0; i<arr.size();i++){
            std::string curr = arr[i];
            store[curr]++;
        }
        for(int i = 0; i<arr.size();i++){
            if(store[arr[i]] == 1){
                if(track == k) return arr[i];
                else track++;
            }
        }

        return "";
    }
};
