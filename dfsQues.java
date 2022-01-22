public class dfsQues {
    // leet 200

public void dfs(int i, int j,char[][] grid){
    int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};

    grid[i][j]='0';
    for(var dir:dirs){
        int r=i+dir[0];
        int c=j+dir[1];

        if(r>=0 && c>=0 && r<grid.length && c<grid[0].length && grid[r][c]=='1'){
            dfs(r,c,grid);
        }
    }
}

public int numIslands(char[][] grid) {
    int num=0;

    for(int i=0; i<grid.length; i++){
        for(int j=0; j<grid[i].length; j++){
            if(grid[i][j]=='1'){
                num++;
                dfs(i,j,grid);
            }
        }
    }
    return num;    
}


// leet 695 ================================
public int dfs2(int i, int j,int[][] grid){
    int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};
    int size=0;
    grid[i][j]=0;

    for(int[] dir:dirs){
        int r=i+dir[0];
        int c=j+dir[1];

        if(r>=0 && c>=0 && r<grid.length && c<grid[0].length && grid[r][c]==1){
            size+=dfs2(r,c,grid);
        }
    }

    return size+1;
}

public int maxAreaOfIsland(int[][] grid) {
    int max_area=0;

    for(int i=0; i<grid.length; i++){
        for(int j=0; j<grid[i].length; j++){
            if(grid[i][j]==1){
                int size=dfs2(i,j,grid,size);
                max_area=Math.max(max_area,size);
            }
        }
    }        
    return max_area;
}

// leet 463 ==========================

public int islandPerimeter(int[][] grid) {
    int noOfOne=0;
    int nbrCount=0;
    int n=grid.length;
    int m=grid[0].length;

    int[][] dirs={{0,1},{1,0},{-1,0},{0,-1}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                noOfOne++;
                for(int[] dir:dirs){
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

public void dfs3(int i, int j, char[][] board){
    board[i][j]='B';

    int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};
    for(int[] dir:dirs){
        int r=i+dir[0];
        int c=j+dir[1];

        if(r>=0 && c>=0 && r<board.length && c<board[0].length && board[r][c]=='O'){
            dfs3(r,c,board);
        }
    }
}

public void solve(char[][] board) {
    int n=board.length;
    int m=board[0].length;

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

} 