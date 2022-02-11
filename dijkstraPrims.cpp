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


// leet 505 (The Maze 2)=================================================================== 

int shortestDistance(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
    vector<vector<int>> dirs={{0,1},{1,0},{-1,0},{0,-1}};

    int n=maze.size();
    int m=maze[0].size();

    vector<vector<int>> vis(n,vector<int>(m,(int)(1e8)));

    //{dis,vtx}
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;

    q.push({0,start[0]*m+start[1]});
    vis[start[0]][start[1]]=0;

    while(q.size()){
        auto idx=q.top(); q.pop();

        int dis=idx.first;

        int i=idx.second/m;
        int j=idx.second%m;

        if(i==destination[0] && j==destination[1]) return dis;

        for(auto &dir:dirs){
            int x=i+dir[0];
            int y=j+dir[1];

            int curr=1;
            while(x>=0 && y>=0 && x<n && y<m && maze[x][y]!=1){
                x+=dir[0];
                y+=dir[1];
                curr++;
            } 
            
            // moving back one step
            x-=dir[0];
            y-=dir[1];
            curr--;

            if(vis[x][y]<=dis+curr) continue;

            vis[x][y]=dis+curr;

            q.push({dis+curr,x*m+y});
        }        
    }
    return -1;
}


int main(){
    return 0;
}