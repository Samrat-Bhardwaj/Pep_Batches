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

int main(){
    return 0;
}