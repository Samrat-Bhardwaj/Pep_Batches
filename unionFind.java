class unionFind{

    int[] par;
    public int findPar(int u){
        if(par[u]==u) return u;

        return par[u]=findPar(par[u]);
    }

    public List<Integer> numIslands2(int n, int m, int[][] positions) {
        int[][] grid=new int[n][m];

        par=new int[n*m];
        for(int i=0; i<n*m; i++){
            par[i]=i;
        }

        int[][] dirs={{0,1},{1,0},{0,-1},{-1,0}};

        List<Integer> ans=new ArrayList<>();
        int count=0;
        for(int[] pos:positions){
            int x=pos[0];
            int y=pos[1];

            if(grid[x][y]==1){
                ans.add(count);
                continue;
            }

            grid[x][y]=1;
            count++;
            int p1=findPar(x*m+y);
            for(int[] dir:dirs){
                int i=x+dir[0];
                int j=y+dir[1];

                if(i>=0 && j>=0 && i<n && j<m && grid[i][j]==1){
                    int p2=findPar(i*m+j);

                    if(p1!=p2){
                        par[p2]=p1;
                        count--;
                    }
                }
            }
            ans.add(count);
        }

        return ans;
    }

    // leet 924 =======================================================================
    int[] par;
    int[] size;

    public int findPar(int u){
        if(par[u]==u) return u;

        return par[u]=findPar(par[u]);
    }

    public void merge(int p1, int p2){
        if(size[p1]<=size[p2]){
            par[p1]=p2;
            size[p2]+=size[p1];
        } else {
            par[p2]=p1;
            size[p1]+=size[p2];
        }
    }

    public int minMalwareSpread(int[][] graph, int[] initial) {
        int n=graph.length;

        par=new int[n];
        size=new int[n];

        for(int i=0; i<n; i++){
            par[i]=i;
            size[i]=1;
        }

        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(graph[i][j]==0) continue;
                if(i==j) continue;

                int p1=findPar(i);
                int p2=findPar(j);

                if(p1!=p2){
                    merge(p1,p2);
                }
            }
        }
        
        // it will store number of components visit
        int[] fre=new int[n];

        Arrays.sort(initial);

        for(int i=0; i<initial.length; i++){
            int p=findPar(initial[i]);

            fre[p]++;
        }

        int max=0;
        int ans=-1;

        for(int i=0; i<initial.length; i++){
            int p=findPar(initial[i]);

            if(fre[p]>1) continue;

            if(size[p]>max){
                max=size[p];
                ans=initial[i];
            }
        }

        // if no answer, return minimum node 
        if(ans==-1) return initial[0];

        return ans;

    }
}