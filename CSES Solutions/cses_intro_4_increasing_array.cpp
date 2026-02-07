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
        vector<ll> a(n,0);
        fo(i,n)
        {
            int x;
            cin>>a[i];
        }
        ll curr = a[0],ans=0; 
        rep(i,1,n)
        {
            if(a[i]<curr)
               ans += curr - a[i];
            else 
                curr = max(curr,a[i]); 
        }
       cout<<ans; 
    }
    return 0;
}