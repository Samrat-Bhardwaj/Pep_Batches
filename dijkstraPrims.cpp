#include<vector>
#include<queue>

using namespace std;

class Edge {
    public:
    int v;
    int w;

    Edge(int v, int w){
        this->v=v;
        this->w=w;
    }
};

void addEdge(int u, int v, int w, vector<vector<Edge>>& graph){
        graph[u].push_back(Edge{v,w});
}

class Pair {
    public:
    int src;
    int par;
    int w;
    int wsf;

    Pair(int src, int par, int w, int wsf){
        this->src=src;
        this->par=par;
        this->w=w;
        this->wsf=wsf;
    }

    Pair(int src, int wsf){
        this->src=src;
        this->wsf=wsf;
    }
};

class comp {
    public:
    bool operator()(Pair& a, Pair& b){
        return a.wsf > b.wsf;
    }
};

void dijkstra(vector<vector<Edge>> graph, int src){
    int V=graph.size();

    vector<vector<Edge>> myGraph(V,vector<Edge>());

    priority_queue<Pair,vector<Pair>, comp> pq;

    vector<bool> vis(V,false);

    pq.push(Pair(src,-1,0,0));

    while(pq.size()){
        Pair t=pq.top();
        pq.pop();

        if(vis[t.src]) continue;

        vis[t.src]=true;

        if(t.par!=-1){
            addEdge(t.par,t.src,t.w,myGraph);
        }

        for(Edge nbr:graph[t.src]){
            if(!vis[nbr.v]){
                pq.push(Pair(nbr.v,t.src,nbr.w,nbr.w+t.wsf));
            }
        }
    }
}

void dijkstra2(vector<vector<Edge>> graph, int src){
    int V=graph.size();

    vector<int> dis(V,(int)(1e8));

    priority_queue<Pair,vector<Pair>, comp> pq;

    pq.push(Pair(src,0));
    dis[src]=0;

    while(pq.size()){
        Pair t=pq.top();
        pq.pop();

        for(Edge nbr:graph[t.src]){
            if(nbr.w + t.wsf < dis[nbr.v]){
                dis[nbr.v]=nbr.w+t.wsf;
                pq.push(Pair(nbr.v,nbr.w+t.wsf));
            }
        }
    }
}


int main(){
    return 0;
}