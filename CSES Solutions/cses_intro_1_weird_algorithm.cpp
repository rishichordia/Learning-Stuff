#include <iostream>
#include <bits/stdc++.h>
#include <string>
typedef long long int ll;
 
#define deb(x) cout << #x << " is " << x << "\n"
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << "\n"
#define fo(i,n) for(ll i=0;i<n;i++)
#define rep(i,j,n) for(ll i=j;i<n;i++)
#define pb push_back
#define ff first
#define ss second
#define mk make_pair
#define pll pair<ll,ll>
 
const ll mod = 1e9+7;
const ll nmax = 2e5 + 5;
using namespace std;
vector<vector<pll>> adj;
vector<bool>vis;
vector<ll>topsort;
vector<pll> ways;
vector<ll> mxf;
vector<ll> minf;


vector<ll> apply(vector<ll> seq,vector<ll> per)
{
    vector<ll> newSeq(seq.size(),0);
    for(int i= 0;i<seq.size();i++)
    {
        newSeq[i] = seq[per[i]];
    }
    return newSeq;
}

int main()
{
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    ll n,k,t;
    t =1;
    //cin>>t;
    while(t--)
    {
        cin>>n;
        while(n>1)
        {
            cout<<n<<" ";
            if(n&1)
                n=3*n+1;
            else
                n>>=1;
        }
        cout<<1;
    }
    return 0;
}