class algoQues {

    public int dijkstra(ArrayList<int[]>[] graph, int n, int src){
        int[] dis=new int[n];
        Arrays.fill(dis,(int)(1e8));

        // wsf,src
        PriorityQueue<int[]> pq=new PriorityQueue<>((a,b)->{
            return a[0] - b[0];
        });

        pq.add(new int[]{0,src});
        dis[src]=0;

        while(pq.size()>0){
            int[] t=pq.remove();

            int u=t[1];
            int wsf=t[0];

            for(int[] nbr:graph[u]){
                int v=nbr[0];
                int w=nbr[1];

                if(w+wsf < dis[v]){
                    dis[v]=w+wsf;
                    pq.add(new int[]{dis[v],v});
                }
            }
        }

        int ans=0;
        for(int i=0; i<n; i++){
            // we can not get to i
            if(dis[i]==(int)(1e8)) return -1;

            ans=Math.max(ans,dis[i]);
        }

        return ans;
    }

    public int networkDelayTime(int[][] times, int n, int k) {
        ArrayList<int[]>[] graph=new ArrayList[n];

        for(int i=0; i<n; i++){
            graph[i]=new ArrayList<>();
        }

        for(int[] time:times){
            int u=time[0]-1;
            int v=time[1]-1;
            int w=time[2];

            graph[u].add(new int[]{v,w});
        }

        return dijkstra(graph,n,k-1);
    }


// bellman ford =========================================================== 
    public int bellmanFord(int n, int[][] edges, int src, int des){
        int[] dis=new int[n];

        Arrays.fill(dis,(int)(1e8));
        dis[src]=0;

        boolean negativeCycle=false;

        for(int i=1; i<=n; i++){
            int[] ndis=new int[n];
            // copy 
            for(int j=0; j<n; j++){
                ndis[j]=dis[j];
            }

            boolean isUpdate=false;

            for(int[] edge:edges){
                int u=edge[0];
                int v=edge[1];
                int w=edge[2];

                if(dis[u] + w < ndis[v]){
                    ndis[v]=dis[u]+w;
                    isUpdate=true;
                }
            }

            if(isUpdate==false) break;

            if(i==n && isUpdate){
                negativeCycle=true;
            }

            dis=ndis;
        }

        return dis[des];
    }
}