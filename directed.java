class directed{
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

    public static void display(ArrayList<Edge>[] graph){
        int V=graph.length;
        
        for(int i=0; i<V; i++){
            System.out.print(i+" ->");
            
            for(int j=0; j<graph[i].size(); j++){
                Edge e=graph[i].get(j);
                // System.out.println(e)
                System.out.print("{ " + e.v + ", " + e.w + " }")
            }

            System.out.println();
        }
    }

    public static void addEdge(int u, int v, int w, ArrayList<Edge>[] graph){
        graph[u].add(new Edge(v,w));
    }

    public static int findEdge(int u, int v, ArrayList<Edge>[] graph){
        for(int i=0; i<graph[u].size(); i++){
            Edge e=graph[u].get(i);

            if(e.v==v){
                return i;
            }
        }

        return -1;
    }

    public static void removeEdge(int u, int v, ArrayList<Edge>[] graph){
        int idx=findEdge(u,v,graph);
        graph[u].remove(idx);
    }

    // topological ordering =======================

    public void dfs_topo(int src,ArrayList<Edge>[] graph,boolean[] vis,ArrayList<Integer> topo){
        vis[src]=true;

        for(Edge nbr:graph[src]){
            if(!vis[nbr.v]){
                dfs_topo(nbr.v,graph,vis,topo);
            }
        }

        topo.add(src);
    }

    public void topological_order(ArrayList<Edge>[] graph){
        int V=graph.length;

        boolean[] vis=new boolean[V];
        ArrayList<Integer> topo=new ArrayList<>();
        for(int i=0; i<V; i++){
            if(!vis[i]){
                dfs_topo(i,graph,vis,topo);
            }
        }

        for(int i=topo.size()-1; i>=0; i--){
            System.out.println(topo.get(i));
        }
    }

    // kahn's algo ===============================================================

    ArrayList<Integer> topological_order_bfs(ArrayList<Edge>[] graph){
        int V=graph.length;

        int[] indegree=new int[V];

        for(int i=0; i<V; i++){
            for(Edge e:graph[i]){
                indegree[e.v]++;
            }
        }

        LinkedList<Integer> que=new LinkedList<>();
        ArrayList<Integer> topo_order=new ArrayList<>();

        for(int i=0; i<V; i++){
            if(indegree[i]==0){
                que.addLast(i);
            }
        }

        while(que.size()>0){
            int ele=que.removeFirst();
            topo_order.add(ele);

            for(Edge e:graph[ele]){
                indegree[e.v]--;
                if(indegree[e.v]==0){
                    que.addLast(e.v);
                }
            }
        }

        if(topo_order.size()!=V){
            System.out.println("NO SOLUTION!!!!!!!");
            return new ArrayList<>();
        }

        return topo_order;
    }

    // level wise topo ordering 
    ArrayList<ArrayList<Integer>> topological_order_bfs(ArrayList<Edge>[] graph){
        int V=graph.length;

        int[] indegree=new int[V];

        for(int i=0; i<V; i++){
            for(Edge e:graph[i]){
                indegree[e.v]++;
            }
        }

        LinkedList<Integer> que=new LinkedList<>();
        ArrayList<ArrayList<Integer>> topo_order=new ArrayList<>();

        for(int i=0; i<V; i++){
            if(indegree[i]==0){
                que.addLast(i);
            }
        }

        while(que.size()>0){
           int size=que.size();
           ArrayList<Integer> smallAns=new ArrayList<>();
           while(size-->0){
               int ele=que.removeFirst();
                smallAns.add(ele);

                for(Edge e:graph[ele]){
                    indegree[e.v]--;
                    if(indegree[e.v]==0){
                        que.addLast(e.v);
                    }
                }
           }
           topo_order.add(smallAns);
        }

        return topo_order;
    }


// kruskal Algorithm ======================================================================= 
    int[] par;
    public int findPar(int u){
        if(par[u]==u) return u;

        return par[u]=findPar(par[u]);
    }

    public ArrayList<Edge>[] kruskal(int[][] edges, int N){
        Arrays.sort(edges,(int[] a, int [] b)->{
            return a[2] - b[2]; // sorting on the bases of weight
        });

        ArrayList<Edge>[] mst=new ArrayList[N];
        for(int i=0; i<N; i++){
            mst[i]=new ArrayList<>();
        }

        par=new int[N];
        for(int i=0; i<N; i++){
            par[i]=i;
        }

        for(int i=0; i<edges.length; i++){
            int[] edge=edges[i];

            int u=edge[0];
            int v=edge[1];
            int w=edge[2];

            int p1=findPar(u);
            int p2=findPar(v);

            if(p1!=p2){
                addEdge(u,v,w,mst);
                par[p2]=p1;
            }
        }

        return mst;
    }

    public static void construct(){
        int V=11;

        ArrayList<Edge>[] graph=new ArrayList[V];

        for(int i=0; i<V; i++){
            graph[i]=new ArrayList<>();
        }

        addEdge(0,1,2,graph);
        addEdge(1,3,4,graph);
        addEdge(1,2,3,graph);
        addEdge(3,4,5,graph);
        addEdge(2,4,7,graph);
        addEdge(4,9,8,graph);
        addEdge(4,10,10,graph);
        addEdge(9,10,8,graph);
        addEdge(4,6,11,graph);
        addEdge(5,6,2,graph);
        addEdge(6,7,3,graph);
        addEdge(5,7,3,graph);

        // gcc
        // removeEdge(4,9,graph);
        // removeEdge(4,10,graph);
        // removeEdge(4,5,graph);
        // removeEdge(4,2,graph);

        // bfs 
        removeEdge(4,6,graph);
    }

    public static void main(String[] args){
        construct();
    }
}