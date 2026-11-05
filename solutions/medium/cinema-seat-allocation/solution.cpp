class Solution {
public:
    bool finda(int n){
        if(n >= 2 && n <= 5) return true;
        else return false;
    }

    bool findb(int n){
        if(n >= 6 && n <= 9) return true;
        else return false;
    }

    bool findc(int n){
        if(n >= 4 && n <= 7) return true;
        else return false;
    }

    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats){
        std::map<int,std::vector<int>> store;
        for(int i = 0; i < reservedSeats.size(); i++){
            store[reservedSeats[i][0]].push_back(reservedSeats[i][1]);
        }

        std::map<int,int> reserved;
        for(auto x : store){
            reserved[x.first] = 0;
            int counta = 1;
            int countb = 1;
            int countc = 1;

            for(int i = 0; i < x.second.size(); i++){
                if(finda(x.second[i])) counta = 0;
                if(findb(x.second[i])) countb = 0;
                if(findc(x.second[i])) countc = 0;
            }

            if(counta && countb) reserved[x.first] = 2;
            else if(counta || countb || countc) reserved[x.first] = 1;
        }
        int sum = (n - store.size()) * 2;

        for(auto x : reserved) sum += x.second;
        return sum;
    }
};
