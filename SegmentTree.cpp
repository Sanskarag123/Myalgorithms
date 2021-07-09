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
int getrangesum(vector<int> tree,int start, int end,int left, int right,int i){
    if(left<=start && right>=end){
        return tree[i];
    }
    if(end<left || start>right){
        return 0;
    }
    int mid = start+((end-start)/2);
    return getrangesum(tree,start,mid,left,right,2*i+1)+getrangesum(tree,mid+1,end,left,right,2*i+2);
}
int constructSegmenttree(vector<int> arr,vector<int> &v1,int start,int end,int i){
    if(start==end){
        v1[i] = arr[start]; 
        return arr[start];
    }
    int mid = start+((end-start)/2);
    v1[i] = constructSegmenttree(arr,v1,start,mid,2*i+1)+constructSegmenttree(arr,v1,mid+1,end,i*2+2);
    
    return v1[i];
}
void solve(){
    int n;
    cin>>n;
    vector<int> v1;
    rep(i,0,n-1){
        int a;
        cin>>a;
        v1.push_back(a);
    }
    int x = (int)(ceil(log2(n)));
 
    //Maximum size of segment tree
    int max_size = 2*(int)pow(2, x) - 1;
 
    vector<int> tree(max_size);
    constructSegmenttree(v1,tree,0,n-1,0);
    cout<<getrangesum(tree,0,n-1,1,n-1,0);

}
