class Solution {
public:
    string generateTheString(int n){
        int start = 97;
        std::string inp;
        if(n % 2 == 0){
            int limit = n;
            while(limit > 1){
                inp.push_back('a');
                limit--;
            }
            inp.push_back('b');
            return inp;
        }else{
            for(int i = 0; i<n;i++) inp.push_back('a');
            return inp;
        }
    }
};
