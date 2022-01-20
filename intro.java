class intro{
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
        graph[v].add(new Edge(u,w));
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

        idx=findEdge(v,u,graph);
        graph[v].remove(idx);
    }

    public static class pair{
        String psf;
        int wsf;

        public pair(String psf, int wsf){
            this.psf=psf;
            this.wsf=wsf;
        }
    }

    // maximum weight path (which and with what weight)
    public static pair maxWeightPath(int src, int des, ArrayList<Edge>[] graph,boolean[] vis){
        if(src==des){
            return new pair(""+des,0);
        }

        vis[src]=true;

        pair myAns=new pair("",-1);
        for(Edge nbr:graph[src]){
            if(vis[nbr.v]) continue;

            pair recAns=maxWeightPath(nbr.v,des,graph,vis);

            if(recAns.wsf!=-1 && recAns.wsf + nbr.w > myAns.w){
                myAns.w=recAns.wsf + nbr.w;
                myAns.psf= src + recAns.psf;
            }
        }
        vis[nbr]=false;
        return myAns;
    } 

    // minimum weight path (which and with what weight)
    public static pair minWeightPath(int src, int des, ArrayList<Edge>[] graph,boolean[] vis){
        if(src==des){
            return new pair(""+des,0);
        }

        vis[src]=true;

        pair myAns=new pair("",(int)(1e9));
        for(Edge nbr:graph[src]){
            if(vis[nbr.v]) continue;

            pair recAns=maxWeightPath(nbr.v,des,graph,vis);

            if(recAns.wsf!=(int)(1e9) && recAns.wsf + nbr.w < myAns.w){
                myAns.w=recAns.wsf + nbr.w;
                myAns.psf= src + recAns.psf;
            }
        }
        vis[nbr]=false;
        return myAns;
    }

    // count number of paths between src and des
    public static int countAllPaths_helper(int src, int des,ArrayList<Edge>[] graph, boolean[] vis){
        if(src==des){
            return 1;
        }
        vis[src]=true;
        int count=0;
        for(Edge nbr:graph[src]){
            if(vis[e.nbr]) continue;
                
            count+=countAllPaths_helper(e.v,des,graph,vis);
        }

        vis[src]=false;
        return count;
    }

    public static int countAllPaths(int src, int des,ArrayList<Edge>[] graph){
        int V=graph.length;

        boolean[] vis=new boolean[V];

        return countAllPaths_helper(src,des,graph,vis);
    }

    public static hasPath_helper(int src, int des,ArrayList<Edge>[] graph,boolean[] vis){
        if(src==des){
            return true;
        }

        vis[src]=true;

        for(Edge nbr:graph[u]){
            if(vis[nbr.e]) continue;

            if(hasPath_helper(nbr.e,des,graph,vis)) return true;
        }
        
        return false;
    }

    public static boolean hasPath(int src, int des, ArrayList<Edge>[] graph){
        int V=graph.length;

        boolean[] vis=new boolean[V];

        return hasPath_helper(src,des,graph,vis);
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
    }

    public static void main(String[] args){
        construct();
    }
}