class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned){
        string ans = "";
        string curr = "";
        map<string,int> store;
        int maxx = 0;

        for(int i = 0;i<paragraph.size();i++){
            if(isalpha(paragraph[i])){
                curr += tolower(paragraph[i]);
            }else{
                if(curr != ""){
                    store[curr]++;
                    curr = "";
                }
            }
        }

        if(curr != ""){
            store[curr]++;
        }

        for(auto val : store){
            if(find(banned.begin(),banned.end(),val.first) == banned.end()){
                if(val.second > maxx){
                    maxx = val.second;
                    ans = val.first;
                }
            }
        }

        return ans;
    }
};
