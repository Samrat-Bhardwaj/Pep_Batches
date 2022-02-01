#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

vector<int> par; // leader 
vector<int> size; 

int findPar(int u){
    if(par[u]==u){
        return u;
    }

    return par[u]=findPar(par[u]);
}

void merge(int p1, int p2){
    if(size[p1]<=size[p2]){
        par[p1]=p2;
        size[p2]+=size[p1];
    } else {
        par[p2]=p1;
        size[p1]+=size[p2];
    }
}

int union_find(int n,vector<vector<int>>& edges){
    par.resize(n);
    size.resize(n);

    for(int i=0; i<n; i++){
        par[i]=i;
        size[i]=1;
    }

    for(auto& edge:edges){
        int u=edge[0];
        int v=edge[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            merge(p1,p2);
        }
    }

    int number_of_components=0;

    for(int i=0; i<n; i++){
        int p=findPar(i);
        if(i==p){
            number_of_components++;
        }
    }

    return number_of_components;
}

// leet 684 ==================================================== 

vector<int> findRedundantConnection(vector<vector<int>>& edges) {
    int n=edges.size();
     par.resize(n+1);
    size.resize(n+1);
    
    for(int i=0; i<n; i++){
        par[i]=i;
        size[i]=1;
    }

    for(auto& e:edges){
        int u=e[0];
        int v=e[1];

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1==p2) return e;
        
        merge(p1,p2);
    }
    return {};

}   

// leet 1319 ======================================== 


int makeConnected(int n, vector<vector<int>>& connections) {
    if(connections.size()<n-1) return -1;

    par.resize(n);
    size.resize(n);

    for(int i=0; i<n; i++){
        par[i]=i;
        size[i]=1;
    }        

    for(auto &e:connections){
        int p1=findPar(e[0]);
        int p2=findPar(e[1]);

        if(p1!=p2){
            merge(p1,p2);
        }
    }

    int comp=0;
    for(int i=0; i<n; i++){
        int p=findPar(i);
        if(p==i){
            comp++;
        }
    }

    return comp-1;
}

// leet 1601 ========================

string smallestEquivalentString(string s1, string s2, string baseStr) {
    par.resize(26);

    for(int i=0; i<26; i++){
        par[i]=i;
    }        

    for(int i=0; i<s1.size(); i++){
        int u=s1[i]-'a';
        int v=s2[i]-'a';

        int p1=findPar(u);
        int p2=findPar(v);

        if(p1!=p2){
            par[p2]=min(p1,p2);
            par[p1]=min(p1,p2);
        }
    }

    string ans="";
    for(int i=0; i<baseStr.size(); i++){
        int u=baseStr[i]-'a';

        int p=findPar(u);
        ans=ans+(char)('a'+p);
    }

    return ans;
}

// leet 695 ==============================

int maxAreaOfIsland(vector<vector<int>>& grid) {
    int n=grid.size();
    if(n==0) return 0;

    int m=grid[0].size();

    par.resize(n*m);
    size.resize(n*m);

    for(int i=0; i<n*m; i++){
        par[i]=i;
        size[i]=1;
    }

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                int p1=findPar(i*m+j);

                for(auto const& dir:dirs){
                    int x=i+dir[0];
                    int y=j+dir[1];

                    if(x>=0 && y>=0 && x<n && y<m && grid[x][y]==1){
                       
                        int p2=findPar(x*m+y);
                        
                        if(p1!=p2){
                            // merge(p1,p2);
                            par[p2]=p1;
                            size[p1]+=size[p2];
                        }
                    }
                }
            }
        }
    }

    int maxArea=0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(grid[i][j]==1){
                int p=findPar(i*m+j);
                if(p==i*m+j){
                    maxArea=max(maxArea,size[i*m+j]);
                }
            }
        }
    }

    return maxArea;    
}

// leet 990 ============================================= 
int fp(int u){
    if(par[u]==u) return u;
    return par[u] = fp(par[u]);
}

bool equationsPossible(vector<string>& equations) {
    par.resize(26);

    for(int i=0; i<26; i++){
        par[i]=i;
    }

    for(string &eq:equations){
        if(eq[1]=='='){
            int p1=fp(eq[0]-'a');
            int p2=fp(eq[3]-'a');

            if(p1!=p2){
                par[p1]=p2;
            }
        }
    }

    for(string &eq:equations){
        if(eq[1]=='!'){
            int p1=fp(eq[0]-'a');
            int p2=fp(eq[3]-'a');

            if(p1==p2){
                return false;
            }
        }
    }

    return true;
}

// leet 1202

string smallestStringWithSwaps(string s, vector<vector<int>>& pairs) {
    int n=s.size();

    par.resize(n);

    for(int i=0; i<n; i++){
        par[i]=i;
    }        

    for(auto &p:pairs){
        int p1=findPar(p[0]);
        int p2=findPar(p[1]);

        if(p1!=p2){
            par[p1]=p2;
        }
    }

    unordered_map<int,string> m; // parent vs group characaters

    for(int i=0; i<n; i++){
        int p=findPar(i);
        m[p]=m[p]+s[i];
    }

    for(auto &kv:m){
        sort(kv.second.begin(),kv.second.end());
        reverse(kv.second.begin(),kv.second.end());
    }

    string ans="";
    for(int i=0; i<n; i++){
        int p=findPar(i);

        string &s=m[p];
        ans+=s[s.size()-1];

        s.pop_back();
    }

    return ans;
}

// leet 721 ====================================
vector<int> par;
int findPar(int u){
    if(par[u]==u){
        return u;
    }

    return par[u]=findPar(par[u]);
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
    unordered_map<string,int> etuid; // email to unique id
    unordered_map<string,string> etn; // email to name
    int uid=0;

    par.resize(1001);
    for(int i=0; i<=1000; i++){
        par[i]=i;
    }

    for(auto &account:accounts){
        string name=account[0];
        for(int i=1; i<account.size(); i++){
            string email=account[i];

            if(etuid.find(email)==etuid.end()){
                etuid[email]=uid;
                uid++;
            }

            etn[email]=name;

            // parent of first email id in this account
            int p1=findPar(etuid[account[1]]);
            // parent of current email
            int p2=findPar(etuid[email]);

            if(p1!=p2){
                par[p2]=p1;
            }
        }
    }

    vector<vector<string>> ans;
    unordered_map<int,vector<string>> res; // par vs emails

    for(auto &kv:etuid){
        int id=kv.second;

        int p=findPar(id);
        if(res.find(p)==res.end()){
            res[p]={kv.first};
        } else {
            res[p].push_back(kv.first);
        }
    }

    for(auto &kv:res){
        vector<string> &emails=kv.second;

        sort(emails.begin(),emails.end());
        // inserting name in the front
        emails.insert(emails.begin(),etn[emails[0]]);

        ans.push_back(emails);
    }

    return;
}


// leet 839 ======================================================== 
unordered_map<string,string> par;

string findPar(string& u){
    if(par[u]==u) return u;

    return par[u]=findPar(par[u]);
}

bool isSimilar(string& a, string& b){
    int diff=0;
    for(int i=0; i<a.size(); i++){
        if(a[i]!=b[i]) diff++;
        if(diff>2) return false;
    }

    if(diff==0) return true;

    return diff==2;
}

int numSimilarGroups(vector<string>& strs) {
    for(string s:strs){
        par[s]=s;
    }

    int comps=strs.size();


    for(int i=0; i<strs.size(); i++){
        string p1=findPar(strs[i]);
        for(int j=i+1; j<strs.size(); j++){
            if(isSimilar(strs[i],strs[j])){
                string p2=findPar(strs[j]);

                if(p1!=p2){
                    par[p2]=p1;
                    comps--;
                }
            }
        }
    }

    

    return comps;
}


// leet 1168 ====================================================
vector<int> par;
int fp(int u){
    return par[u] == u ? u : par[u]=fp(par[u]);
}

int minCostToSupplyWater(int n, vector<int>& wells, vector<vector<int>>& pipes) {
    par.resize(n+1);

    for(int i=0; i<=n; i++) par[i]=i;

    for(int i=0; i<wells.size(); i++){
        vector<int> pipe={0,i+1,wells[i]};
        pipes.push_back(pipe);
    }

    sort(pipes.begin(),pipes.end(),[](vector<int>& a, vector<int>& b){
        return a[2] < b[2];
    });


    int final_cost=0;
    for(int i=0; i<pipes.size(); i++){
        int u=pipes[i][0];
        int v=pipes[i][1];
        int c=pipes[i][2];

        int p1=fp(u);
        int p2=fp(v);

        if(p1!=p2){
            par[p2]=p1;
            final_cost+=c;
        }
    }

    return final_cost;
}


// leet 1584 ============================================================ 
vector<int> par;
vector<int> size;
int fp(int u){
    return par[u] == u ? u : par[u]=fp(par[u]);
}

void merge(int p1, int p2){
    if(size[p2]<=size[p1]){
        par[p2]=p1;
        size[p1]+=size[p2];
    } else {
        par[p1]=p2;
        size[p2]+=size[p1];
    }
}

int getDis(vector<int>& c1, vector<int>& c2){
    return abs(c1[0]-c2[0]) + abs(c1[1]-c2[1]);
}
int minCostConnectPoints(vector<vector<int>>& points) {
    vector<vector<int>> edges;

    int n=points.size();

    par.resize(n);
    size.resize(n,1);

    for(int i=0; i<n; i++) par[i]=i;

    for(int i=0; i<n; i++){
        for(int j=i+1; j<n; j++){
            int dis=getDis(points[i],points[j]);

            edges.push_back({i,j,dis});
        }
    }        

    sort(edges.begin(),edges.end(),[](vector<int>& a, vector<int>& b){
        return a[2] < b[2];
    });

    int cost=0;
    for(int i=0; i<edges.size(); i++){
        int u=edges[i][0];
        int v=edges[i][1];
        int w=edges[i][2];

        int p1=fp(u);
        int p2=fp(v);

        if(p1!=p2){
            par[p2]=p1;
            cost+=w;
        }
    }

    return cost;
}

// num of islands 2======================================

vector<int> par;
int findPar(int u){
    if(par[u]==u) return u;

    return par[u]=findPar(par[u]);
}

vector<int> numIslands2(int n, int m, vector<vector<int>>& positions) {
    vector<vector<int>> grid(n,vector<int>(m,0));

    par.resize(n*m);
    for(int i=0; i<n*m; i++){
        par[i]=i;
    }

    int count=0;
    vector<int> ans;

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(int i=0; i<positions.size(); i++){
        int px=positions[i][0];
        int py=positions[i][1];

        if(grid[px][py]==1){
            ans.push_back(count);
            continue;
        }

        grid[px][py]=1;
        count++;
        int p1=findPar(px*m+py);
        for(auto &dir:dirs){
            int i=px+dir[0];
            int j=py+dir[1];

            if(i>=0 && j>=0 && i<n && j<m && grid[i][j]==1){
                int p2=findPar(i*m+j);

                if(p1!=p2){
                    par[p2]=p1;
                    count--;
                }
            }
        }
        ans.push_back(count);
    }

    return ans;
}

// num of islands 2 ===========================================================
vector<int> par;
int findPar(int u){
    return par[u]==u ? u : par[u]=findPar(par[u]);
}

vector<int> numIslands2(int n, int m, vector<vector<int>>& positions) {
    par.resize(n*m,-1); // -1 -> water

    int count=0;
    vector<int> ans;

    vector<vector<int>> dirs={{0,1},{1,0},{0,-1},{-1,0}};

    for(vector<int>& pos:positions){
        int px=pos[0];
        int py=pos[1];

        if(par[px*m+py]!=-1){
            ans.push_back(count);
            continue;
        }

        par[px*m+py]=px*m+py;
        count++;
        int p1=findPar(px*m+py);

        for(auto &dir:dirs){
            int i=px+dir[0];
            int j=py+dir[1];

            if(i>=0 && j>=0 && i<n && j<m && par[i*m+j]!=-1){
                int p2=findPar(i*m+j);

                if(p1!=p2){
                    par[p2]=p1;
                    count--;
                }
            }
        }
        ans.push_back(count);
    }
    return ans;    
}

// leet 924 =====================================================================
vector<int> par;
vector<int> size;

int findPar(int u){
    if(par[u]==u) return u;

    return par[u]=findPar(par[u]);
}

void merge(int p1, int p2){
    if(size[p2]<=size[p1]){
        par[p2]=p1;
        size[p1]+=size[p2];
    } else {
        par[p1]=p2;
        size[p2]+=size[p1];
    }
}

int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
    int n=graph.size();

    par.resize(n);
    size.resize(n);

    for(int i=0; i<n; i++){
        par[i]=i;
        size[i]=1;
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(graph[i][j]==0) continue;
            if(i==j) continue;

            int p1=findPar(i);
            int p2=findPar(j);

            if(p1!=p2){
                merge(p1,p2);
            }
        }
    }

    sort(initial.begin(),initial.end());

    vector<int> fre(n,0);
    for(int i=0; i<initial.size(); i++){
        int e=initial[i];

        int p=findPar(e);
        fre[p]++;
    }

    int m=0;
    int ans=-1;

    for(int i=0; i<initial.size(); i++){
        int e=initial[i];

        int p=findPar(e);

        if(fre[p]==1){
            if(size[p]>m){
                m=size[p];
                ans=e;
            }
        }
    }

    if(ans==-1) return initial[0];

    return ans;
}

int main(){
    return 0;
}