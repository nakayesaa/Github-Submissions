class Solution {
public:
    int manhattan(int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }
    int nearestDrone(vector<vector<int>>& drones, vector<int>& target){
        int smallest = 10000000;
        int track = 1000000;
        int found = 0;
        for(int i = 0; i<drones.size();i++){
            std::vector<int> curr = drones[i];
            int x = curr[0];
            int y = curr[1];
            int total = manhattan(x,y,target[0], target[1]);
            if(total <= curr[2]){
                found = 1;
                if(total < smallest || (total == smallest && i < track)){
                    smallest = total;
                    track = i;
                }
            }
        }
        if(found) return track;
        else return -1;
    }
};
