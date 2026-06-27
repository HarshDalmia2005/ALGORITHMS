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
    https://codeforces.com/contest/455/problem/D
*/

int f[320][100005];
int BL_SZ;
deque<int> dq[320];

void solve(){
    int n;
    cin>>n;

    BL_SZ=sqrt(n)+1;

    auto get_block = [&](int idx) {
        return (idx-1) / BL_SZ;
    };

    memset(f,0,sizeof(f));

    for(int i=1;i<=n;i++){
        int x;
        cin>>x;

        int bl=get_block(i);
        dq[bl].push_back(x);
        f[bl][x]++;
    }

    

    int q;
    cin>>q;

    int lastans=0;
    while(q--){
        int t;
        cin>>t;

        if(t==1){
            int l,r;
            cin>>l>>r;

            int p=((l+lastans-1)%n)+1;
            int q=((r+lastans-1)%n)+1;

            if(p>q)swap(p,q);

            int bl_p=get_block(p);
            int bl_q=get_block(q);

            int idx_q=(q-1)%BL_SZ;
            int idx_p=(p-1)%BL_SZ;

            int x=dq[bl_q][idx_q];
            f[bl_q][x]--;
            dq[bl_q].erase(dq[bl_q].begin()+idx_q);

            dq[bl_p].insert(dq[bl_p].begin()+idx_p,x);
            f[bl_p][x]++;

            for(int i=bl_p+1;i<=bl_q;i++){
                int y=dq[i-1].back();
                dq[i-1].pop_back();
                f[i-1][y]--;
                dq[i].push_front(y);
                f[i][y]++;
            }

        }else{
            int l,r,k;
            cin>>l>>r>>k;

            int p=((l+lastans-1)%n)+1;
            int q=((r+lastans-1)%n)+1;
            int s=((k+lastans-1)%n)+1;

            if(p>q)swap(p,q);

            int bl_p=get_block(p);
            int bl_q=get_block(q);
            int ans=0;
            if(bl_p==bl_q){
                for(int i=(p-1)%BL_SZ;i<=(q-1)%BL_SZ;i++){
                    if(dq[bl_p][i]==s)ans++;
                }
            }else{
                
                for(int i=bl_p+1;i<bl_q;i++){
                    ans+=f[i][s];
                }

                for(int i=(p-1)%BL_SZ;i<dq[bl_p].size();i++){
                    if(dq[bl_p][i]==s)ans++;
                }

                for(int i=0;i<=(q-1)%BL_SZ;i++){
                    if(dq[bl_q][i]==s)ans++;
                }
            }

            lastans=ans;
            cout<<ans<<"\n";
        }
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