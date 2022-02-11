#include<iostream>
#include<vector>
#include<queue>

using namespace std;

void dijkstra(vector<int>& dis, int src, vector<vector<pair<int,int>>>& graph){
    dis[src]=0;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;

    pq.push({0,src});

    while(pq.size()){
        pair<int,int> p=pq.top(); pq.pop();

        int cDis=p.first;
        int u=p.second;

        for(auto& nbr:graph[u]){
            int w=nbr.second;
            int v=nbr.first;

            if(dis[v] > cDis + w){
                dis[v]=cDis+w;
                pq.push({dis[v],v});
            }
        }
    }
}

int main(){
      ios::sync_with_stdio(0); cin.tie(0);
    int n,m,k,x;
    
    cin>>n>>m>>k>>x;

    vector<int> choc(n+1,false);

    for(int i=0; i<k; i++){
        int num;
        cin>>num;
        choc[num]=true;
    }

    vector<vector<pair<int,int>>> graph(n+1);

    for(int i=0; i<m; i++){
        int u,v,w;
        cin>>u>>v>>w;

        graph[u].push_back({v,w});
        graph[v].push_back({u,w});
    }

    int src,des;
    cin>>src>>des;

    vector<int> srcDis(n+1,(int)(1e8));
    vector<int> desDis(n+1,(int)(1e8));

    dijkstra(srcDis,src,graph);
    dijkstra(desDis,des,graph);
    int ans=(int)(1e8);

    for(int i=0; i<=n; i++){
        if(choc[i]){
            if(desDis[i]<x && srcDis[i]!=(int)(1e8)){
                ans=min(ans,desDis[i]+srcDis[i]);
            }
        }
    }

    if(ans==(int)(1e8)){
        cout<<-1<<endl;
    } else {
        cout<<ans<<endl;
    }
}