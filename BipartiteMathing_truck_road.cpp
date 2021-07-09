// Created by Sanskar Agrawal
#include <bits/stdc++.h>

#define db1(x) cout<<#x<<"="<<x<<'\n'
#define db2(x,y) cout<<#x<<"="<<x<<","<<#y<<"="<<y<<'\n'
#define db3(x,y,z) cout<<#x<<"="<<x<<","<<#y<<"="<<y<<","<<#z<<"="<<z<<'\n'
#define rep(i,a,n) for(int i=a;i<=(n);++i)
#define brep(i,a,n) for(int i=a;i>=(n);--i)
#define vi vector<int>
#define pii pair<int,int>
#define sz(x) (x).size()
#define fullvect(x) (x).begin(),(x).end()


using namespace std;
using ll = long long;
bool BFS(vector<vector<int>> adj,vector<int> &leveltree, int startnode,int sink){
    queue<int> q;
    q.push(startnode);
    leveltree[startnode] = 0;
    vector<bool> visited(adj.size(),false);
    while(!q.empty()){
        int node = q.front();
        q.pop();
        visited[node] = true;
        rep(i,0,adj[node].size()-1){
            if(!visited[i] && adj[node][i]>0){
                leveltree[i] = leveltree[node]+1;
                q.push(i);
            }
        }
    }
    return leveltree[sink] !=-1;
}
int dfs(vector<vector<int>> &adj, vector<int> leveltree, int startnode, int sink,vector<bool> visited,int min_flow){
    if(sink ==  startnode) return min_flow;
    rep(i,0,adj.size()-1){
        if((!visited[i] && adj[startnode][i]>0) && leveltree[startnode]<leveltree[i]){
            min_flow = min(min_flow,adj[startnode][i]);
            int bottleneck = dfs( adj, leveltree, i, sink, visited, min_flow);
            adj[startnode][i]-=bottleneck;

            if(bottleneck>0){
                return bottleneck;
            }
        }
    }
    return 0;
}
void solve(){
    int n,m,k;
    cin>>n>>m>>k;
    int n1 = n+m+2;
    vector<vector<int>> adj(n1,vector<int>(n1,0));
    //cout<<"No";
    rep(i, 0,k-1){
        int x,y;
        cin>>x>>y;
        adj[x][n+y] = 1;
    }
    rep(i,0,m-1){
        int a;
        cin>>a;
        adj[(n+1)+i][n1-1] = a;
    }
    rep(i,0,n-1){
        adj[0][i+1] = 1;
    }
    int z;
    cin>>z;
    vector<vector<int>> reduced(z);
    rep(i, 0, z-1){
    int a,b;
    cin>>a>>b;
    reduced[i].push_back(a);
    reduced[i].push_back(b);
    }

    vector<int> leveltree(n1,-1);
    vector<bool> visited(n1,false);
    int max_flow = 0;
    int source = 0;
    int sink = n1-1;
    vector<vector<int>> adj1(adj.begin(),adj.end());
    rep( i, 0, z-1){
    adj1[n+reduced[i][0]][n1-1] -= reduced[i][1];
    }
    //cout<<z;
    vector<int> results;
    for(int i=z-1;i>=0;i--){
        adj1[n+reduced[i][0]][n1-1] += reduced[i][1];
          while(BFS(adj1,leveltree,0,n1-1)){
        //cout<<"YES";
        max_flow+=dfs(adj1, leveltree, source, sink, visited, INT_MAX);
        for(int &x:leveltree){
            x = -1;
        }
    
    }
    results.push_back(max_flow);
    
    }
    reverse(results.begin(),results.end());
    for(auto x:results){
        cout<<x<<endl;
    }
    

}

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t=1;
    //cin>>t;
    while(t--){
        //cout<<"yes";
        solve();
    }
    return 0;
}
