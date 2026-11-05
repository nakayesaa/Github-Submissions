class Solution {
public:
    int minimumOperations(string num){ 
        int total = INT_MAX;

        for(int i = 0; i < num.size(); i++){

            if(num[i] == '2'){
                for(int j = i + 1; j < num.size(); j++){
                    if(num[j] == '5'){
                        int current = j - (i + 1) + num.size() - j - 1;
                        total = min(total, current);
                    }
                }
            }

            else if(num[i] == '5'){
                for(int j = i + 1; j < num.size(); j++){
                    if(num[j] == '0'){
                        int current = j - (i + 1) + num.size() - j - 1;
                        total = min(total, current);
                    }
                }
            }

            else if(num[i] == '7'){
                for(int j = i + 1; j < num.size(); j++){
                    if(num[j] == '5'){
                        int current = j - (i + 1) + num.size() - j - 1;
                        total = min(total, current);
                    }
                }
            }

            else if(num[i] == '0'){
                for(int j = i + 1; j < num.size(); j++){
                    if(num[j] == '0'){
                        int current = j - (i + 1) + num.size() - j - 1;
                        total = min(total, current);
                    }
                }
            }
        }
        if(total == INT_MAX){
            int res = num.size();
            for(int i = 0; i<num.size();i++){
                if(num[i] == '0'){
                    res = num.size() -1;
                    break;
                }
            }
            return res;
        }
        return total;
    }
};
