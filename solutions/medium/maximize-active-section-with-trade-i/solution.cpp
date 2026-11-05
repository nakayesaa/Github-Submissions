class Solution {
public:
    int maxActiveSectionsAfterTrade(string s){
        std::vector<int> store;
        for(int i = 0; i < s.size(); i++)
            if(s[i] == '1') store.push_back(i);

        int result = store.size();
        int maxx = 0;
        for(int i = 0; i < store.size(); i++){
            int j = i;
            while(j+1 < store.size() && store[j+1] == store[j]+1) j++;

            int left = (i == 0) ? -1 : store[i-1];
            int right = (j == store.size()-1) ? s.size() : store[j+1];

            int leftZeros = store[i] - left - 1;
            int rightZeros = right - store[j] - 1;

            if(leftZeros > 0 && rightZeros > 0) maxx = std::max(maxx, leftZeros + rightZeros);
            i = j;
        }

        result += maxx;
        return result;
    }
};
