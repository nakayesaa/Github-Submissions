class Solution{
public:
    string rotate(string inp){
        char x = inp[0];

        for(int i = 1; i < inp.size(); i++) inp[i - 1] = inp[i];
        inp[inp.size() - 1] = x;

        return inp;
    }

    int minOperations(string s){

        string ddd = s;

        int minCost = 1000000000;
        
        int head = s.size() - 1;
        int currCost = 0;

        for(int i = 0; i < s.size() / 2; i++){

            int x = s[i] - 'a';
            int y = s[head--] - 'a';

            int a = abs(x - y);
            int b = 26 - a;

            int cost = min(a, b);

            currCost += cost;
        }

        minCost = min(minCost, currCost);
        currCost = 0;

        for(int r = 1; r < s.size(); r++){

            s = rotate(s);
            currCost++;

            head = s.size() - 1;

            for(int i = 0; i < s.size() / 2; i++){
                int x = s[i] - 'a';
                int y = s[head--] - 'a';
                int a = abs(x - y);
                int b = 26 - a;
                int cost = min(a, b);

                currCost += cost;
            }

            minCost = min(minCost, currCost);
            currCost = r;
        }

        return minCost;
    }
};
