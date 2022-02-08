#include<vector>
#include<queue>

using namespace std;

int dijkstra(vector<vector<pair<int,int>>>& graph, int src, int n){
    vector<int> dis(n,(int)(1e8));

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    // {wsf,src}
    pq.push({0,src});
    dis[src]=0;

    while(pq.size()){
        pair<int,int> t=pq.top(); pq.pop();

        int u=t.second;
        int wsf=t.first;

        for(auto &nbr:graph[u]){
            int v=nbr.first;
            int w=nbr.second;
            
            if(w + wsf < dis[v]){
                dis[v] = w + wsf;
                pq.push({dis[v],v});
            }
        }
    }

    int ans=0;
    for(int i=0; i<n; i++){
        if(dis[i]==(int)(1e8)) return -1;
        ans=max(ans,dis[i]);
    }

    return ans;
}

int networkDelayTime(vector<vector<int>>& times, int n, int k) {
    vector<vector<pair<int,int>>> graph(n);

    for(auto& time:times){
        // u -> v,w
        graph[time[0]-1].push_back({time[1]-1,time[2]});
    }

    return dijkstra(graph,k-1,n);
}


// leet 787 

int findCheapestPrice(int n, vector<vector<int>>&flights, int src, int dst, int k) {
        vector<int> dis(n,(int)(1e8));

        dis[src]=0;

        bool negativeCycle=false;

        for(int i=1; i<=k+1; i++){
            vector<int> ndis=dis;

            bool isUpdate=false;

            for(auto& edge:flights){
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

        return dis[dst] == (int)(1e8) ? -1 : dis[dst];
    }