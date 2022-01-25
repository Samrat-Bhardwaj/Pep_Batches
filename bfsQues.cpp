#include<vector>
#include<queue>

using namespace std;

// leet 994 ==========================================

int orangesRotting(vector<vector<int>>& grid) {
    int n=grid.size();
    int m=grid[0].size();

    queue<int> q;
    int freshOranges=0;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                freshOranges++;
            } else if(grid[i][j]==2){
                q.push(i*m+j);
            }
        }
    }

    if(freshOranges==0) return 0;

    vector<vector<int>> dirs={{0,1},{-1,0},{0,-1},{1,0}};
    int level=0;
    while(q.size()){
        int s=q.size();

        while (s--){
            int idx=q.front(); q.pop();
            int i=idx/m;
            int j=idx%m;

            for(auto &dir:dirs){
                int r=i+dir[0];
                int c=j+dir[1];

                if(r>=0 && c>=0 && r<n && c<m && grid[r][c]==1){
                    grid[r][c]=2;
                    q.push(r*m+c);
                    freshOranges--;

                    if(freshOranges==0) return level+1;
                }
            }

        }
        level++;
    }

    return -1;
}



// is bipartite 

// leet 785 =========================================================== 
// -1 -> not visited
// 0-> blue
// 1-> green

bool bfs_bipartite(vector<vector<int>>& graph, int src,vector<int>& colors){
    int c=0; // starting with blue color

    queue<int> q;
    q.push(src);

    while(q.size()){
        int s=q.size();
        while (s--){
            int u=q.front(); q.pop();

            if(colors[u]!=-1){
                if(colors[u]!=c) return false;

                continue;
            }

            colors[u]=c;

            for(int v:graph[u]){
                if(colors[v]==-1){
                    q.push(v);
                }
            }
        }
        c=(c+1)%2;
    }
    return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    int V=graph.size();

    vector<int> colors(V,-1);

    for(int i=0; i<V; i++){
        if(colors[i]==-1){
            bool isBipartite=bfs_bipartite(graph,i,colors);

            if(!isBipartite) return false;
        }
    }        

    return true;
}


// leet 1020 =============================================

// boundary to interior


// converting whole island to water
void bfs_convert(int i, int j, vector<vector<int>>& grid){
    int n=grid.size();
    int m=grid[0].size();

    vector<vector<int>> dirs={{0,1},{-1,0},{0,-1},{1,0}};
    queue<int> q;

    q.push(i*m+j);
    grid[i][j]=0;

    while(q.size()>0){
        int s=q.size();
        while(s-->0){
            int idx=q.front(); q.pop();

            i=idx/m;
            j=idx%m;

            for(auto &dir:dirs){
                int r=i+dir[0];
                int c=j+dir[1];

                if(r>=0 && c>=0 && r<n && c<m && grid[r][c]==1){
                    grid[r][c]=0;
                    q.push(r*m+c);
                }
            }
        }
    }
}

int numEnclaves(vector<vector<int>>& grid) {
    int n=grid.size();
    int m=grid[0].size();

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(i==0 || j==0 || i==n-1 || j==m-1){
                if(grid[i][j]==1){
                    bfs_convert(i,j,grid);
                }
            }
        }
    }
    int area=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            area+=(grid[i][j]==1);
        }
    }

    return area;
}


// interior to boundary ========

int bfs_count(vector<vector<int>>& grid, int i, int j){
    int n=grid.size();
    int m=grid[0].size();

    vector<vector<int>> dirs={{0,1},{-1,0},{0,-1},{1,0}};
    queue<int> q;

    q.push(i*m+j);
    grid[i][j]=0;
        
    int count=1;
    bool boundary=false;

    while(q.size()>0){
        int s=q.size();
        while(s-->0){
            int idx=q.front(); q.pop();

            int x=idx/m;
            int y=idx%m;
            
            for(auto &dir:dirs){
                int r=x+dir[0];
                int c=y+dir[1];
                
                if(r>=0 && c>=0 && r<n && c<m && grid[r][c]==1){
                    if(r==0 || c==0 || r==n-1|| c==m-1) boundary=true;
                    q.push(r*m+c);
                    count++;
                    grid[r][c]=0;
                }
            }
        }
    }

    if(boundary || i==0 || j==0 || i==n-1 || j==m-1) return 0;
    return count;
}

int numEnclaves(vector<vector<int>>& grid) {
    int n=grid.size();
    int m=grid[0].size();

    int area=0;

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                 int count=bfs_count(grid,i,j);
                area+=count;
            }
           
        }
    }

    return area;
}




int main(){
    return 0;
}