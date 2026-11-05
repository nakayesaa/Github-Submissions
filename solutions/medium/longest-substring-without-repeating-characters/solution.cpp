class Solution {
public:
    int lengthOfLongestSubstring(string s){
        int maxx = 0;
        std::map<char,int> store;
        int left = 0;
        std::string result = "";

        for(int i = 0; i<s.size();i++){
            store[s[i]]++;
            while(store[s[i]] > 1){
                int start = 0;
                for(int j = left; j < i && s[j] != s[i];j++){
                    store[s[j]] -= 1;
                    start++;
                }
                left += start + 1;
                store[s[left-1]]--;
                result.erase(0, start + 1);
            }
            result += s[i];
            maxx = std::max(maxx, (int)result.size());
        }
        return maxx;
    }
};
