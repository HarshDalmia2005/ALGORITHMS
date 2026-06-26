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
https://codeforces.com/contest/86/problem/D 
*/
typedef pair<pair<int,int>,int> pp;

int f[1000005];
int BL_SZ;

int ans=0;

bool cmp(pp a, pp b) {
   int x=a.F.F/BL_SZ;
   int y=b.F.F/BL_SZ;

   if(x!=y)return x<y;
   if(x&1)return a.F.S<b.F.S;
   return a.F.S>b.F.S;
}

// void compress(vector<int>& arr){
//     vector<int> b=arr;
//     sort(all(b));
//     b.erase(unique(all(b)),b.end());

//     for(int i=0;i<arr.size();i++){
//         carr[i]=lower_bound(all(b),arr[i])-b.begin();
//     }
// }

void insert(int x){
    ans-=f[x]*f[x]*x;
    f[x]++;
    ans+=f[x]*f[x]*x;
}

void remove(int x){
   ans-=f[x]*f[x]*x;
    f[x]--;
    ans+=f[x]*f[x]*x;
}

void solve(){
    int n,m;
    cin>>n>>m;

    vector<int> arr(n);

    for(int i=0;i<n;i++){
        cin>>arr[i];
    }


    BL_SZ=sqrt(n)+1;
    vector<pp> q(m);

    for(int i=0;i<m;i++){
        cin>>q[i].F.F>>q[i].F.S;
        q[i].F.F--;
        q[i].F.S--;
        q[i].S=i;
    }

    sort(all(q),cmp);
    vector<int> fans(m);
    int s=0,e=-1;
    for(int i=0;i<m;i++){
        while(e<q[i].F.S){
            e++;
            insert(arr[e]);
        }
        while(s>q[i].F.F){
            s--;
            insert(arr[s]);
        }
        while(e>q[i].F.S){
            remove(arr[e]);
            e--;
        }
        while(s<q[i].F.F){
            remove(arr[s]);
            s++;
        }
        fans[q[i].S]=ans;
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