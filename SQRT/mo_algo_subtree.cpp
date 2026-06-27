#include <bits/stdc++.h>
using namespace std;

#define int long long
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define endl '\n'
#define mod 1000000007
#define F first
#define S second

/* 
https://codeforces.com/contest/375/problem/D
*/
typedef pair<pair<int,int>,int> pp;

vector<int> adj[100005];
int arr[100005];
int f[1000005],in[100005],out[100005],euler[100005];
int cnt[100005];
int BL_SZ;
int ans=0;
int timer=0;


struct query{
    int l,r,k,id;
    bool operator < (const query &a) const {
        int x=l/BL_SZ;
        int y=a.l/BL_SZ;

       if(x!=y)return x<y;
       if(x&1)return r<a.r;
       return r>a.r;
    }
}q[100005];

void dfs(int nn, int pp){
    in[nn]=++timer;
    euler[timer]=arr[nn];

    for(int x:adj[nn]){
        if(x!=pp){
            dfs(x,nn);
        }
    }
    out[nn]=timer;
}


void insert(int x){
   f[x]++;
   cnt[f[x]]++;
}

void remove(int x){
   cnt[f[x]]--;
   f[x]--;
}

void solve(){
    int n,m;
    cin>>n>>m;

    BL_SZ=sqrt(n)+1;

    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        arr[i]=x;
    }

    for(int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;

        adj[u].pb(v);
        adj[v].pb(u);
    }

    dfs(1,0);

    for(int i=0;i<m;i++){
       int v,k;
       cin>>v>>k;
       q[i].l=in[v];
       q[i].r=out[v];
       q[i].k=k;
       q[i].id=i;
    }

    sort(q,q+m);
    memset(f,0,sizeof(f));
    memset(cnt,0,sizeof(cnt));

    vector<int> fans(m);
    int s=1,e=0;
    for(int i=0;i<m;i++){
        while(e<q[i].r){
            e++;
            insert(euler[e]);
        }
        while(s>q[i].l){
            s--;
            insert(euler[s]);
        }
        while(e>q[i].r){
            remove(euler[e]);
            e--;
        }
        while(s<q[i].l){
            remove(euler[s]);
            s++;
        }
        fans[q[i].id]=cnt[q[i].k];
    }

    for(int i=0;i<m;i++){
        cout<<fans[i]<<endl;
    }
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    // pre();
    int t = 1;
    // cin>>t;
    while (t--) {
        solve();
    }

    return 0;
}