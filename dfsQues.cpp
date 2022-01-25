#include<vector>
#include<queue>
using namespace std;

void dfs(int i, int j,vector<vector<char>>& grid){
    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    grid[i][j]='0';
    for(auto &dir:dirs){
        int r=i+dir[0];
        int c=j+dir[1];

        if(r>=0 && c>=0 && r<grid.size() && c<grid[0].size() && grid[r][c]=='1'){
            dfs(r,c,grid);
        }
    }
}

int numIslands(vector<vector<char>>& grid) {
    int num=0;

    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            if(grid[i][j]=='1'){
                num++;
                dfs(i,j,grid);
            }
        }
    }
    return num;    
}

// leet 695 ================================================= 

void dfs2(int i, int j,vector<vector<int>>& grid, int &size){
    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};
    size++;
    grid[i][j]=0;
    for(auto &dir:dirs){
        int r=i+dir[0];
        int c=j+dir[1];

        if(r>=0 && c>=0 && r<grid.size() && c<grid[0].size() && grid[r][c]==1){
            dfs2(r,c,grid,size);
        }
    }
}

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int max_area=0;

    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[i].size(); j++){
            if(grid[i][j]==1){
                int size=0;
                dfs2(i,j,grid,size);
                max_area=max(max_area,size);
            }
        }
    }        
    return max_area;
}


// leet 463 ==============================================

int islandPerimeter(vector<vector<int>>& grid) {
    int noOfOne=0;
    int nbrCount=0;
    int n=grid.size();
    int m=grid[0].size();

    vector<vector<int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                noOfOne++;
                for(auto &dir:dirs){
                    int r=i+dir[0];
                    int c=j+dir[1];

                    if(r>=0 && c>=0 && r<n && c<m && grid[r][c]==1){
                        nbrCount++;
                    }
                }
            }
        }
    }        
    return 4*noOfOne - nbrCount;
}

// leet 130 ===================================================== 

void dfs3(int i, int j, vector<vector<char>>& board){
    board[i][j]='B';

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};
    for(auto &dir:dirs){
        int r=i+dir[0];
        int c=j+dir[1];

        if(r>=0 && c>=0 && r<board.size() && c<board[0].size() && board[r][c]=='O'){
            dfs3(r,c,board);
        }
    }
}

void solve(vector<vector<char>>& board) {
    int n=board.size();
    int m=board[0].size();

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            // calling dfs from boundaries 
            if(i==0 || j==0 || i==n-1 || j==m-1){
                if(board[i][j]=='O')
                    dfs3(i,j,board);
            }
        }
    }        

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(board[i][j]=='O'){
                board[i][j]='X';
            } else if(board[i][j]=='B'){
                board[i][j]='O';
            }
        }
    }
}

// leet 1905 ==================================================== 

bool dfs4(vector<vector<int>>& grid1, vector<vector<int>>& grid2, int i, int j, int n, int m){
    bool ans= (grid1[i][j]==grid2[i][j]);

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};
    grid2[i][j]=0;
    for(auto &dir:dirs){
        int r=i+dir[0];
        int c=j+dir[1];

        if(r>=0 && c>=0 && r<n && c<m && grid2[r][c]==1){
            ans = dfs4(grid1,grid2,r,c,n,m) && ans;
        }
    }

    return ans;
}

int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
    int ans=0;
    int n=grid1.size();
    int m=grid1[0].size();

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid2[i][j]==1){
                bool isSub=dfs4(grid1,grid2,i,j,n,m);
                if(isSub) ans++;
            }
        }
    }        

    return ans;
}

int main(){
    return 0;
}