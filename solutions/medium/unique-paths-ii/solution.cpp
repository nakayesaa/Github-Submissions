class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid){
        int m = obstacleGrid.size();
        int n = obstacleGrid[0].size();
        std::vector<std::vector<int>> path(m, std::vector<int>(n,0));
        for(int i = 0; i<m;i++){
            for(int j = 0; j<n;j++){
                if(obstacleGrid[i][j] == 1) path[i][j] = 0;
                else if(i == 0 && j == 0) path[i][j] = 1;
                else{
                    if(i > 0) path[i][j] += path[i-1][j];
                    if(j > 0) path[i][j] += path[i][j-1];
                }
            }
        }
        return path[m-1][n-1];
    }
};
