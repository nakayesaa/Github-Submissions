class Solution {
public:
    int minFallingPathSum(vector<vector<int>>& matrix){
        int m = matrix.size();
        int n = matrix[0].size();
        std::vector<std::vector<int>> path(m, std::vector<int>(n,0));
        for(int j = 0; j<n;j++){
            path[0][j] = matrix[0][j];
        }

        for(int i = 1; i<m;i++){
            for(int j = 0; j<n;j++){
                int a = 10000000, b = 1000000, c = 100000000;
                a = path[i-1][j];
                if(j > 0) b = path[i-1][j-1];
                if(j + 1 < n) c = path[i-1][j+1];
                path[i][j] = matrix[i][j] + std::min({a,b,c});
            }
        }
        int result = 100000000;
        for(int j = 0; j<n;j++){
            result = std::min(result, path[m-1][j]);
        }
        return result;
    }
};
