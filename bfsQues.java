class bfsQues {
    

// is bipartite 

// leet 785 =========================================================== 
// -1 -> not visited
// 0-> blue
// 1-> green

public boolean bfs_bipartite(int[][] graph, int src,int[] colors){
    int c=0; // starting with blue color

    LinkedList<Integer> q=new LinkedList<>();
    q.addLast(src);

    while(q.size()>0){
        int s=q.size();
        while (s-->0){
            int u=q.removeFirst();

            if(colors[u]!=-1){
                if(colors[u]!=c) return false;

                continue;
            }

            colors[u]=c;

            for(int v:graph[u]){
                if(colors[v]==-1){
                    q.addLast(v);
                }
            }
        }
        c=(c+1)%2;
    }
    return true;
}

public boolean isBipartite(int[][] graph) {
    int V=graph.length;

    int[] colors=new int[V];
    Arrays.fill(colors,-1);

    for(int i=0; i<V; i++){
        if(colors[i]==-1){
            boolean isBipartite=bfs_bipartite(graph,i,colors);

            if(!isBipartite) return false;
        }
    }        

    return true;
}

// leet 542 =================================================================

public int[][] updateMatrix(int[][] mat) {
    LinkedList<Integer> q=new LinkedList<>();

    int n=mat.length;
    int m=mat[0].length;

    boolean[][] vis=new boolean[n][m];

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(mat[i][j]==0){
                q.addLast(i*m+j);
                vis[i][j]=true;
            }
        }
    }        

    int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};
    int level=0;
    while(q.size()>0){
        int s=q.size();
        while(s-->0){
            int idx=q.removeFirst();

            int i=idx/m;
            int j=idx%m;

            for(int[] dir:dirs){
                int x=i+dir[0];
                int y=j+dir[1];

                if(x>=0 && y>=0 && x<n && y<m && !vis[x][y]){
                    vis[x][y]=true;
                    grid[x][y]=level+1;
                    q.addLast(x*m+y);
                }
            }        
        }
        level++;
    }

    return grid;
}


// leet 329 =========================================================== 

public int longestIncreasingPath(int[][] matrix) {
    int n=matrix.length;
    int m=matrix[0].length;

    int[][] indegree=new int[n][m];

    int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            for(int [] dir:dirs){
                int x=i+dir[0];
                int y=j+dir[1];

                if(x>=0 && y>=0 && x<n && y<m && matrix[x][y]>matrix[i][j]){
                    indegree[x][y]++;
                }
            }
        }
    }

    LinkedList<Integer> que=new LinkedList<>();
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(indegree[i][j]==0){
                que.add(i*m+j);
            }
        }
    }       

    int level=0;
    while(que.size()>0){
        int size=que.size();

        while(size-->0){
            int idx=que.removeFirst();

            int i=idx/m;
            int j=idx%m;

            for(int[] dir:dirs){
                int x=i+dir[0];
                int y=j+dir[1];

                if(x>=0 && y>=0 && x<n && y<m && matrix[x][y]>matrix[i][j]){
                    indegree[x][y]--;
                    if(indegree[x][y]==0){
                        que.addLast(x*m+y);
                    }
                }
            }
        }

        level++;
    }

    return level;
}

}