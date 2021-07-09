#include<bits/stdc++.h>
using namespace std;
#define INT_MAX 2147483647
bool BFS(vector<vector<int>> adj, vector<int> &leveltree, int startnode,int sinknode,int n){
    queue<int> q;
    leveltree[startnode] = 0;
    q.push(startnode);
    vector<bool> visited(n, false);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        visited[node] = true;
        for(int i=0;i<adj[node].size();i++){
            if(!visited[i] && adj[node][i]!=0){
                leveltree[i] = leveltree[node]+1;
                q.push(i);
            }
        }
    }
    return leveltree[sinknode]!=-1;
}
int dfs(vector<vector<int>> &adj,vector<int> leveltree,int node,vector<bool> visited,int minimum ,int sink){
    if(node == sink) return minimum;
    for(int i=0;i<adj[node].size();i++){
        if((!visited[i] && leveltree[i]>leveltree[node]) && adj[node][i]!=0){
            minimum = min(minimum, adj[node][i]);
            int boottleneck = dfs(adj, leveltree, i, visited, minimum, sink);
            adj[node][i] -= boottleneck;
            if(boottleneck>0){
                cout<<adj[node][i]<<" "<<i<<endl;
                return boottleneck;
            }
        }
    }
    return 0;
}
int main(){
int n;
n = 8;
vector<vector<int>> adj = {
    { 0, 5, 0, 4, 0, 0, 3, 0},
    { 0, 0, 2, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 4, 0, 0},
    { 0, 0, 0, 0, 4, 0, 0, 0},
    { 0, 0, 0, 0, 0, 2, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 2, 0, 0, 3},
    { 0, 0, 0, 0, 0, 6, 0, 0},
};
vector<bool> visited(n,false);
vector<int> leveltree(n,-1);
vector<int> bootlenecks;
while(BFS(adj,leveltree, 0, 5, n)){
    cout<<"yes";
    bootlenecks.push_back(dfs(adj,leveltree, 0, visited, INT_MAX, 5));
    for(int &x:leveltree){
        x = -1;
    }
}
int min_bootleneck = accumulate(bootlenecks.begin(), bootlenecks.end(), 0);
cout<<min_bootleneck;

return 0;
}
