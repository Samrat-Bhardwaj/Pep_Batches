class dijkstraPrims {
    public static class Edge{
        int v;
        int w;

        Edge(int v, int w){
            this.v=v;
            this.w=w;
        }

        public toString(){
            return this.v + ", " + this.w;
        }
    }

    public static void addEdge(int u, int v, int w, ArrayList<Edge>[] graph){
        graph[u].add(new Edge(v,w));
    }

    public static class pair {
        int src=0;
        int par=0;
        int w=0;
        int wsf=0;

        pair(int src, int wsf){
            this.src=src;
            this.wsf=wsf;
        }

        pair(int src, int par, int w, int wsf){
            this.src=src;
            this.par=par;
            this.w=w;
            this.wsf=wsf;
        }
    }

    public static void dijkstra(ArrayList<Edge>[] graph, int src){
        int V=graph.length;

        ArrayList<Edge>[] myGraph=new ArrayList[V];

        for(int i=0; i<V; i++){
            myGraph[i]=new ArrayList<>();
        }

        PriorityQueue<pair> pq=new PriorityQueue<>((a,b)->{
            return a.wsf - b.wsf;
        });

        boolean[] vis=new boolean[V];

        pq.add(new pair(src,-1,0,0));

        while(pq.size()>0){
            pair t=pq.remove();

            if(vis[t.src]) continue;

            if(t.par!=-1){
                addEdge(t.par,t.src,t.w,myGraph);
            }

            vis[t.src]=true;

            for(Edge nbr:graph[t.src]){
                if(!vis[nbr.v]){
                    pq.add(new pair(nbr.v,t.src,nbr.w,t.wsf+nbr.w));
                }
            }
        }
    }

    public static void dijkstra(ArrayList<Edge>[] graph, int src){
        int V=graph.length;

        int[] dis=new int[V];

        Arrays.fill(dis,(int)(1e8));

        PriorityQueue<pair> pq=new PriorityQueue<>((a,b)->{
            return a.wsf - b.wsf;
        });


        dis[src]=0;
        pq.add(new pair(src,0));

        while(pq.size()>0){
            pair t=pq.remove();

            if(dis[t.src] < t.wsf) continue;

            for(Edge nbr:graph[t.src]){
                if(t.wsf + nbr.w < dis[nbr.v]){
                    dis[nbr.v] = t.wsf + nbr.w;
                    pq.add(new pair(nbr.v,dis[nbr.v]));
                }
            }
        }
    }

// prims =======================================================================================

    public static void prims(ArrayList<Edge>[] graph, int src){
        int V=graph.length;

        ArrayList<Edge>[] myGraph=new ArrayList[V];

        for(int i=0; i<V; i++){
            myGraph[i]=new ArrayList<>();
        }

        PriorityQueue<pair> pq=new PriorityQueue<>((a,b)->{
            return a.w - b.w;
        });

        boolean[] vis=new boolean[V];

        pq.add(new pair(src,-1,0,0));

        while(pq.size()>0){
            pair t=pq.remove();

            if(vis[t.src]) continue;

            if(t.par!=-1){
                addEdge(t.par,t.src,t.w,myGraph);
            }

            vis[t.src]=true;

            for(Edge nbr:graph[t.src]){
                if(!vis[nbr.v]){
                    pq.add(new pair(nbr.v,t.src,nbr.w,t.wsf+nbr.w));
                }
            }
        }
    }
}