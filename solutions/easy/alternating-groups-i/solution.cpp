class Solution {
public:
    int numberOfAlternatingGroups(vector<int>& colors){
        colors.push_back(colors[0]);
        colors.push_back(colors[1]);
        int sum = 0;
        for(int i = 0; i<colors.size()-2;i++){
            if(colors[i] != colors[i+1] && colors[i+1] != colors[i+2]) sum++;
        }
        return sum;
    }
};
