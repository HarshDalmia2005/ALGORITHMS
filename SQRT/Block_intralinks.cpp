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
    https://codeforces.com/contest/13/problem/E
*/

int nxt[100005],jmp[100005],last[100005];
int BL_SZ;


void solve(){
    int n,m;
    cin>>n>>m;

    vector<int> arr(n+1);

    for(int i=1;i<=n;i++){
        cin>>arr[i];
    }


    BL_SZ=sqrt(n)+1;

    auto get_block = [&](int idx) {
        return (idx - 1) / BL_SZ;
    };

    for(int i=n;i>=1;i--){
        int pos=i+arr[i];
        if(pos<=n && get_block(pos)==get_block(i)){
            nxt[i]=nxt[pos];
            jmp[i]=jmp[pos]+1;
            last[i]=last[pos];
        }else{
            nxt[i]=pos;
            jmp[i]=1;
            last[i]=i;
        }
    }


    for(int i=0;i<m;i++){
        int t;
        cin>>t;

        if(t){
            int a;
            cin>>a;

            int ans=0;
            int prev=a;
            while(a<=n){
                ans+=jmp[a];
                prev=last[a];
                a=nxt[a];
            }

            cout<<prev<<" "<<ans<<"\n";
        }else{
            int a,b;
            cin>>a>>b;

            int start=get_block(a)*BL_SZ+1;
            arr[a]=b;
            for(int i=a;i>=start;i--){
                int pos=i+arr[i];
                if(pos<=n && get_block(pos)==get_block(i)){
                    nxt[i]=nxt[pos];
                    jmp[i]=jmp[pos]+1;
                    last[i]=last[pos];
                }else{
                    nxt[i]=pos;
                    jmp[i]=1;
                    last[i]=i;
                }
            }
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