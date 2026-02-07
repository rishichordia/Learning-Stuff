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
    ll x,y,t;
    t =1;
    cin>>t;
    while(t--)
    {
      cin>>x>>y;
      ll ans = 0;
      if(x>=y)
      {
        ans = (x-1)*(x-1);
        if(x&1)
        {
            ans += y;
        }
        else ans+= (2*x -y);
      }
      else
      {
        ans=(y-1)*(y-1);
        if(y&1)
            ans+= (2*y-x);
        else
            ans+=x;
      }
      cout<<ans<<endl;
        
    }
    return 0;
}
