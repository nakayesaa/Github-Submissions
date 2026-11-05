class Solution {
public:
    int maximumLengthSubstring(string s){
        std::map<char,int> store;
        int tail = 0;
        int max = 0;
        int curr = 0;

        for(int i = 0; i<s.size(); i++){
            store[s[i]]++;
            curr++;

            if(store[s[i]] > 2){
                char x = s[i];

                for(int j = tail; j<i; j++){
                    store[s[j]]--;
                    curr--;

                    if(s[j] == x){
                        tail = j+1;
                        break;
                    }
                }
            }

            if(curr > max) max = curr;
        }

        return max;
    }
};
