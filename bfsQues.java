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

}