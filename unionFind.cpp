#include<iostream>
#include<vector>

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
int main(){
    return 0;
}